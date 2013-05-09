#include <iostream>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <memory>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <algorithm>

namespace msg {
 
    
    class base {
    public:
        ~base() {}  
        
        
        template<typename T> 
        T &as_type() {
            return static_cast<T &>(*this) ;
        }
    };
    
    class stop : public base {};
    
}


namespace mp {

class typeinfo_wrapper {
public:
    typeinfo_wrapper( const std::type_info &t ) : t_(t) {}

    inline bool operator==( const typeinfo_wrapper &other ) const {
        return t_ == other.t_;   
    }
    
    inline size_t hash_value() const {
        return t_.hash_code();
    }

    inline const char *name() const {
        return t_.name();
    }

    struct hash
    {
        size_t operator()(const typeinfo_wrapper & x) const
        {
            return x.t_.hash_code();
        }
    };

    
private:  
    
    const std::type_info &t_;
    
  
};



    
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template<typename T>
class msg_fwd {
public:
    typedef std::function<void(std::unique_ptr<T>)> fwd_func_type;
    
    fwd_func_type func_;
    
    msg_fwd( fwd_func_type func ) : func_(func) {}
    
    inline void operator()( std::unique_ptr<msg::base> msg ) {
    
        func_( std::unique_ptr<T>( static_cast<T*>(msg.release())) );
    }
    
};

template<typename TRet, typename T>
class msg_ret_fwd {
public:
    typedef std::function<std::unique_ptr<TRet>(std::unique_ptr<T>)> fwd_func_type;
    
    fwd_func_type func_;
    
    msg_ret_fwd( fwd_func_type func ) : func_(func) {}
    
    inline std::unique_ptr<msg::base> operator()( std::unique_ptr<msg::base> msg ) {
    
        return func_( std::unique_ptr<T>( static_cast<T*>(msg.release())) );
    }
    
};


class queue {
    
    const size_t TOKEN_NONE = size_t(-1);
    struct q_entry_type {
        q_entry_type( typeinfo_wrapper && wrap, std::unique_ptr<msg::base> && msg, size_t token, bool return_msg ) : wrap_(wrap), msg_(std::move(msg)), return_token_(token), return_msg_(return_msg) {}
        
        typeinfo_wrapper wrap_;
        std::unique_ptr<msg::base> msg_;
        size_t return_token_;
        bool return_msg_;
        
    };
    
    typedef std::function<void(std::unique_ptr<msg::base>)> handler_type;
    typedef std::function<std::unique_ptr<msg::base>(std::unique_ptr<msg::base>)> handler_ret_type;
    
    
    struct return_entry_type {

        return_entry_type( queue *q, typeinfo_wrapper &&typeinfo ) : q_(q), typeinfo_(typeinfo) {}
        queue * q_;
        typeinfo_wrapper typeinfo_;
    };
    
public:
    
    queue();
    
    
    template<typename T, typename... Args>
    void emplace( Args...  args ) {
        std::unique_lock<std::mutex> lock( central_mtx_ );
        q_.emplace_back( typeinfo_wrapper(typeid(T)), make_unique<T>(std::forward<Args>(args)...), TOKEN_NONE, false );
        
        lock.unlock();
        q_cond_.notify_one();
    }

   
   
   void emplace_msg( typeinfo_wrapper && typeinfo, std::unique_ptr<msg::base> msg, size_t token, bool return_msg );
   
    template<typename T, typename... Args>
    size_t emplace_return( queue *ret_queue, Args...  args ) {
        std::unique_lock<std::mutex> lock( central_mtx_ );
        
        size_t token = return_token_count_++;
        
        return_map_.emplace( token, return_entry_type(ret_queue, typeinfo_wrapper(typeid(typename T::return_type))) );
        q_.emplace_back( typeinfo_wrapper(typeid(T)), make_unique<T>(std::forward<Args>(args)...), token, false );
        
        
        lock.unlock();
        q_cond_.notify_one();
        
        return token;
    }
    
    
    template<typename T, typename... Args>
    void emplace_return_deluxe( queue &ret_queue, std::function<void(std::unique_ptr<typename T::return_type>)> h, Args...  args ) {
        std::unique_lock<std::mutex> lock( central_mtx_ );
        
        size_t token = return_token_count_++;
        
        return_map_.emplace( token, return_entry_type(&ret_queue, typeinfo_wrapper(typeid(typename T::return_type))) );
        q_.emplace_back( typeinfo_wrapper(typeid(T)), make_unique<T>(std::forward<Args>(args)...), token, false );
        
        
        lock.unlock();
        q_cond_.notify_one();
        
        
        ret_queue.add_token_handler<T>(token, h);
        
    }
   
   
    void dispatch( q_entry_type &&ent );
    
    
    void dispatch_ret( q_entry_type &&ent, return_entry_type ret_ent, size_t token );
   
    bool dispatch_pop();
    
    template<typename T>
    void add_handler( handler_type h ) {
        std::lock_guard<std::mutex> lock( central_mtx_ );

        handler_map_.emplace( typeinfo_wrapper(typeid(T)), h );    
        
    }
    
    
    template<typename T>
    void add_handlerx( std::function<void(std::unique_ptr<T>)> h ) {
        std::lock_guard<std::mutex> lock( central_mtx_ );
        handler_map_.emplace( typeinfo_wrapper(typeid(T)), msg_fwd<T>(h) );    
    }
    
    
    template<typename T>
    void add_handler_ret( std::function<std::unique_ptr<typename T::return_type>(std::unique_ptr<T>)> h ) {
        std::lock_guard<std::mutex> lock( central_mtx_ );
        handler_ret_map_.emplace( typeinfo_wrapper(typeid(T)), msg_ret_fwd<typename T::return_type, T>(h) );    
    }
    
    
    template<typename T>
    void add_token_handler( size_t token, std::function<void(std::unique_ptr<typename T::return_type>)> h ) {
        std::lock_guard<std::mutex> lock( central_mtx_ );
//         std::cout << "add token handler: " << token << "\n";
        token_handler_map_.emplace( token, msg_fwd<typename T::return_type>(h) );  
    }
    
    void stop();
    
    bool is_stopped() const;
    
    void add_default_stop_handler();
    
private:
    mutable std::mutex central_mtx_;
    std::condition_variable q_cond_;
    
    size_t return_token_count_;
    bool do_stop_;
    
    std::deque<q_entry_type> q_;
    
    
    
    std::unordered_map<typeinfo_wrapper,handler_type,typeinfo_wrapper::hash> handler_map_;
    std::unordered_map<typeinfo_wrapper,handler_ret_type,typeinfo_wrapper::hash> handler_ret_map_;
    
    std::unordered_map<size_t,handler_type> token_handler_map_;
    
    std::unordered_map<size_t, return_entry_type> return_map_;
    
};

}

/*
namespace std {
    
    
    using mp::hash<typeinfo_wrapper>;
    
}*/