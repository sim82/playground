#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <deque>
#include <memory>
#include <mutex>
#include <cassert>
#include <thread>
#include <condition_variable>
#include <map>
//class abstract_save_it_for_later {
//public:
//    virtual void delayed_dispatch() = 0;
//    virtual ~abstract_save_it_for_later() {}
//};

//template <typename ...Args>
//class save_it_for_later : public abstract_save_it_for_later
//{
//public:
//    save_it_for_later(std::tuple<Args...> p, std::function<void(Args...)> f) : params(p), func(f) {}

//    std::tuple<Args...> params;
//    std::function<void(Args...)> func;

//    template<std::size_t ...I>
//    void call_func(std::index_sequence<I...>)
//    { func(std::get<I>(params)...); }
//    void delayed_dispatch() override
//    { call_func(std::index_sequence_for<Args...>{}); }
//};

//class msg_basex {
//public:
//    //virtual void call() = 0;
//};

//template<typename ...Args>
//class msg_base : public msg_basex {
//public:
//    typedef std::tuple<Args...> TupleType;
//    TupleType params;
//};

//class msg1 : public msg_base<int, float, int> {};
//class msg2 : public msg_base<int, float, int> {};

////typedef std::tuple<int, float, int> msg1;
////typedef std::tuple<int, float, int> msg2;

////template<typename MsgType, typename ...Args>
////void register_callbackx( std::function<Args...> f ) {
////    auto caller = [=](MsgType::TupleType t) {
////        save_it_for_later<Args...> s = {t, f};
////        s(t);
////    }
////}



////template<typename ...Args>
////void call_func( std::tuple<Args...> t, std::function<void(Args...)> f ) {
////    save_it_for_later<Args...> s = {t, f};
////    s.delayed_dispatch();
////}



//class dispatcher {
//public:
//    template <typename MsgT, typename... Args>
//    struct rcr
//    {
//        /* Your original function, now inside a struct.
//         I'm using direct tuple construction and an
//         initializer list to circumvent the order-of-
//         construction problem mentioned in the comment
//         to your question. */
//        static void call(dispatcher &d, Args... args)
//        {
//            //return rcr<MsgT,Args...>::call(args);

//            //        std::unique_ptr<typename MsgT::TupleType> msg( new typename MsgT::TupleType(args...));
//            MsgT *msg = new MsgT;
//            msg->params = std::tuple<Args...>(args...);

//            d.q.emplace_back(std::type_index(typeid(MsgT)), msg);
//        }

//        static void rc(dispatcher &d, std::function<void(Args...)> f)
//        {
//            std::cout << "rc: " << typeid(MsgT).name() << "\n";
//            d.caller_map.emplace( typeid(MsgT), [=](msg_basex &m) {
//                MsgT &m2 = static_cast<MsgT &>(m);
//                save_it_for_later<Args...> s = {m2.params, f};
//                s.delayed_dispatch();
//            });
//        }
//    };
//    template <typename MsgT, typename ...Args>
//    struct rcr<MsgT,std::tuple<Args...>>
//    {
//        /* Specialized for tuple. */
//        static void call(dispatcher &d, Args... args)
//        {
//            return rcr<MsgT,Args...>::call(d, args...);
//        }

//        /* Specialized for tuple. */
//        static void rc(dispatcher &d, std::function<void(Args...)> f)
//        { return rcr<MsgT,Args...>::rc(d, f); }
//    };



//    template<typename MsgT, typename ...Args>
//    void register_callback(std::function<void(Args...)> f) {
//        rcr<MsgT,typename MsgT::TupleType>::rc(*this, f);
//    }

//    void dispatch() {
//        while( !q.empty() ) {
//            std::type_index ti = q.front().first;
//            msg_basex *m = std::move(q.front().second);

//            auto c_it = caller_map.find(ti);

//            assert( c_it != caller_map.end() );
//            auto h = c_it->second;
//            h(*m);

//            q.pop_front();
//        }
//    }

//    typedef std::pair<std::type_index, msg_basex*> QueueEntryType;
//    std::deque<QueueEntryType> q;
//    std::unordered_map<std::type_index,std::function<void(msg_basex &)>> caller_map;
//};



class testxxx {
public:
    testxxx(int x) : i(x) {}
    ~testxxx() {
        i = 555;
    }
    int i;
};

//template<typename... Args>
//struct pack { };
std::tuple<int, float, int /*std::unique_ptr<testxxx>*/> testr1(int a, float b, int c) {
    std::cout << "testr1: " << a << " " << b << " " << c << std::endl;
    return std::make_tuple(a + 1, b * 2, c + 2);
    //return std::make_tuple(1, 6.6, std::make_unique<testxxx>(666));
}


void test1( int a, float b, int c ) {
//    std::cout << "test1 " << a << " " << b << "\n";
}

void test2( int a, float b, int c ) {
//    std::cout << "test2 " << a << " " << b << "\n";
}

void test3() {
//    std::cout << "test3\n";
}


void test4( std::unique_ptr<testxxx> p ) {
    std::cout << "ptr: " << p->i << "\n";
}

void test5( int a, float b, int c ) {
    std::cout << "test5 " << a << " " << b << std::endl;
}

struct abstract_msg {
public:
    // virtual destructor omitted by design: messages are static_cast to  (and destroyed as) their concrete
    // type by the dispatcher
    //virtual ~abstract_msg() {}
};

template<class... Args>
struct msg_impl : public abstract_msg
{
//    using args = pack<Args...>;
    using func = std::function<void(Args...)>;
    using tuple = std::tuple<Args...>;
    using return_type = void;
//    msg_impl(tuple &&t ) : payload(std::move(t)) {}
//    msg_impl() {}
    tuple payload;
};

struct msgx1 : public msg_impl<int,float,int> {};
struct msgx2 : public msg_impl<int,float,int> {};
struct msgx3 : public msg_impl<> {};
struct msgx4 : public msg_impl<std::unique_ptr<testxxx>> {};
struct msgx5 : public msg_impl<int,float,int> {};
struct msg_stop : public msg_impl<> {};
struct msg_stop_trick : public msg_impl<> {};



//struct abstract_msg_ret {
//public:
//    // virtual destructor omitted by design: messages are static_cast to  (and destroyed as) their concrete
//    // type by the dispatcher
//    //virtual ~abstract_msg() {}
//};

template<class TRet, class... Args>
struct msg_ret_impl : public abstract_msg
{
//    using args = pack<Args...>;
    using tuple = std::tuple<Args...>;
    using return_message = TRet;
    using ret_tuple = typename TRet::tuple;
    using return_type = ret_tuple;
    using func = std::function<ret_tuple(Args...)>;
    using return_func = typename TRet::func;
//    msg_impl(tuple &&t ) : payload(std::move(t)) {}
//    msg_impl() {}
    tuple payload;
};

struct msgr1 : public msg_ret_impl<msgx5,int,float,int> {};
struct msgr_stop_trick : public msg_ret_impl<msg_stop_trick> {};

class queue {
    class abstract_dispatcher;
    class abstract_dispatcher_ret;

    struct token_map_hash {
        size_t operator()(const std::pair<std::type_index, int> &v) const {
            return std::hash<std::type_index>()(v.first) ^ std::hash<int>()(v.second);
        }
    };

public:
    typedef std::unordered_map<std::type_index, std::unique_ptr<abstract_dispatcher>> handler_map_type;
    typedef std::unordered_map<std::pair<std::type_index, int>, std::unique_ptr<abstract_dispatcher>, token_map_hash> token_handler_map_type;
//    typedef std::unordered_map<std::type_index, abstract_dispatcher_ret*> handler_ret_map_type;
    class callback_guard {
    public:
        callback_guard() : q_(nullptr) {

        }

        callback_guard( queue *q, queue::handler_map_type::iterator iter ) : q_(q), iter_(iter) {}

        callback_guard( callback_guard &) = delete;
        callback_guard &operator=(callback_guard &) = delete;

        callback_guard( callback_guard &&other )  {
            unregister();

            q_ = other.q_;
            iter_ = other.iter_;
            other.q_ = nullptr;
        }

        callback_guard &operator=(callback_guard &&other ) {
            unregister();

            q_ = other.q_;
            iter_ = other.iter_;
            other.q_ = nullptr;

            return *this;
        }

//        void release() {
//            q_ = nullptr;
//        }

        ~callback_guard() {
            unregister();
        }

    private:
        void unregister() {
            if(q_ != nullptr) {
                q_->unregister_callback(iter_);
                q_ = nullptr;
            }
        }

        queue *q_;
        queue::handler_map_type::iterator iter_;

    };

private:
    class abstract_dispatcher {
    public:
        virtual void dispatch( std::unique_ptr<abstract_msg> msg, queue *target_q, int token ) = 0;
        virtual ~abstract_dispatcher() {}
    };

    template <typename MsgT, typename ...Args>
    class dispatcher_impl : public abstract_dispatcher
    {
    public:
        dispatcher_impl(std::function<void(Args...)> f) : func(f) {}

        //    std::tuple<Args...> params;
        std::function<void(Args...)> func;

        template<std::size_t ...I>
        inline void call_func(std::tuple<Args...> &&params, std::index_sequence<I...>) {
            func(std::get<I>(std::move(params))...);
        }

        inline void dispatch( std::unique_ptr<abstract_msg> msg, queue *, int ) override {
            std::unique_ptr<MsgT> mx(static_cast<MsgT*>(msg.release()));
            call_func(std::move(mx->payload), std::index_sequence_for<Args...>{});
        }
    };

//    class abstract_dispatcher_ret {
//    public:
//        virtual void dispatch( std::unique_ptr<abstract_msg> msg, queue *target_q ) = 0;
//        virtual ~abstract_dispatcher_ret() {}
//    };

    template <typename MsgT, typename ...Args>
    class dispatcher_ret_impl : public abstract_dispatcher
    {
    public:
        using return_message = typename MsgT::return_message;
        using return_type = typename MsgT::return_type;
        typedef std::function<typename MsgT::return_type(Args...)> func_type;

        dispatcher_ret_impl(func_type f) : func(f) {}

        //    std::tuple<Args...> params;
        func_type func;

        template<std::size_t ...I>
        inline return_type call_func(std::tuple<Args...> &&params, std::index_sequence<I...>) {
            return func(std::get<I>(std::move(params))...);
        }

//        template<typename RetMsgT, std::size_t ...I>
//        inline void call_return(queue *q, std::tuple<Args...> &&params, std::index_sequence<I...>) {
//            q->call<RetMsgT>(std::get<I>(std::move(params))...);
//        }

        inline void dispatch( std::unique_ptr<abstract_msg> msg, queue *target_q, int token ) override {
            std::unique_ptr<MsgT> mx(static_cast<MsgT*>(msg.release()));
            auto ret = call_func(std::move(mx->payload), std::index_sequence_for<Args...>{});

            target_q->call_ret<return_message>(ret, token);
            //call_return<typename MsgT::return_message>(target_q, ret, std::index_sequence_for<Args...>{});
        }
    };

    // register_callback_helper:
    // use class template specialization to resolve Args... from arbitrary MsgT::tuple
    // review: is there an easier way to do this?
    template <typename X, typename Y>
    struct register_callback_helper {};

    template <typename MsgT, typename ...Args>
    struct register_callback_helper<MsgT,std::tuple<Args...>> {
        /* Specialized for tuple. */
        //typedef queue::handler_map_type handler_map_type;
        static queue::handler_map_type::iterator register_callback(queue &d, std::function<void(Args...)> f)
        {
            std::cout << "rc: " << typeid(MsgT).name() << "\n";
            auto res = d.handler_map_.emplace(std::type_index(typeid(MsgT)), std::make_unique<dispatcher_impl<MsgT,Args...>>(f));
            assert(res.second);
            return res.first;
            //return rcr<MsgT,Args...>::register_callback(d, f);
        }

        static void register_token_callback(queue &d, int token, std::function<void(Args...)> f)
        {
//            std::cout << "rc: " << typeid(MsgT).name() << "\n";
            d.token_handler_map_.emplace(std::make_pair(std::type_index(typeid(MsgT)), token), std::make_unique<dispatcher_impl<MsgT,Args...>>(f));
            assert(res.second);
            //return rcr<MsgT,Args...>::register_callback(d, f);
        }
    };

    template <typename X, typename Y, typename Z>
    struct register_callback_ret_helper {};

    template <typename MsgT, typename ...Args, typename ...Args2>
    struct register_callback_ret_helper<MsgT,std::tuple<Args...>, std::tuple<Args2...>> {
        /* Specialized for tuple. */
        //typedef queue::handler_map_type handler_map_type;
        static queue::handler_map_type::iterator register_callback(queue &d, std::function<std::tuple<Args2...>(Args...)> f)
        {
            std::cout << "rc: " << typeid(MsgT).name() << "\n";
            auto res = d.handler_map_.emplace(std::type_index(typeid(MsgT)), std::make_unique<dispatcher_ret_impl<MsgT,Args...>>(f));
            assert(res.second);
            return res.first;
            //return rcr<MsgT,Args...>::register_callback(d, f);
        }
    };

public:


    queue() : b_stop_(false), next_return_token_(1) {
    }

    ~queue() {
        stop_handler_guard_ = callback_guard();
        if( !handler_map_.empty() ) {
            std::cout << "WARNING: queue destroyed with callbacks still registered: " << handler_map_.size() << "\n";
        }
    }

    template<typename T = msg_stop>
    void add_default_stop_handler() {
        stop_handler_guard_ = register_callback<T>(std::bind(&queue::stop, this));
    }

    template<typename MsgT>
    callback_guard register_callback(typename MsgT::func x) {
        // trick: use class template specialization to resolve Args... from MsgT::tuple
        std::lock_guard<std::mutex> lock(mtx_);
        return callback_guard( this
                               , register_callback_helper<MsgT, typename MsgT::tuple>::register_callback(*this, x));
    }

    template<typename MsgT>
    callback_guard register_callback_ret(typename MsgT::func x) {
        // trick: use class template specialization to resolve Args... from MsgT::tuple
        std::lock_guard<std::mutex> lock(mtx_);
        return callback_guard( this
                               , register_callback_ret_helper<MsgT, typename MsgT::tuple, typename MsgT::return_type>::register_callback(*this, x));
    }

    template<typename MsgT, typename... Args>
    inline void call(Args&&... args) {
        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>();

        // TODO: check if we can create the pyload tuple in place rather than moving to the default initialized thing
        msg->payload = std::tuple<Args...>(std::forward<Args>(args)...);

//        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>({std::tuple<Args...>(std::forward<Args>(args)...)});


        std::lock_guard<std::mutex> lock(mtx_);
        q_.emplace_back(std::type_index(typeid(MsgT)), std::move(msg), nullptr, 0);
        //        rcr<A,std::tuple<Args...>>::call(*this, args...);
        cond_var_.notify_one();
    }

    template<typename MsgT, typename... Args>
    inline void call2(queue *target_q, typename MsgT::return_func ret_func, Args&&... args) {
        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>();

        // TODO: check if we can create the pyload tuple in place rather than moving to the default initialized thing
        msg->payload = std::tuple<Args...>(std::forward<Args>(args)...);

//        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>({std::tuple<Args...>(std::forward<Args>(args)...)});

        int token = target_q->add_token_callback<typename MsgT::return_message>(ret_func);

        std::lock_guard<std::mutex> lock(mtx_);
        q_.emplace_back(std::type_index(typeid(MsgT)), std::move(msg), target_q, token);
        //        rcr<A,std::tuple<Args...>>::call(*this, args...);
        cond_var_.notify_one();
    }

    template<typename MsgT>
    int add_token_callback( typename MsgT::func f ) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto token = next_return_token_++;
        register_callback_helper<MsgT, typename MsgT::tuple>::register_token_callback(*this, token, f);

        return token;
    }

    template<typename MsgT>
    inline void call_ret(typename MsgT::tuple ret_tuple, int token) {
        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>();

        // TODO: check if we can create the pyload tuple in place rather than moving to the default initialized thing
        msg->payload = ret_tuple;

//        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>({std::tuple<Args...>(std::forward<Args>(args)...)});


        std::lock_guard<std::mutex> lock(mtx_);
        q_.emplace_back(std::type_index(typeid(MsgT)), std::move(msg), nullptr, token);
        //        rcr<A,std::tuple<Args...>>::call(*this, args...);
        cond_var_.notify_one();
    }

    void stop() {
        std::unique_lock<std::mutex> lock(mtx_);
        b_stop_ = true;
        cond_var_.notify_all();
    }

    bool is_stopped() {
        std::unique_lock<std::mutex> lock(mtx_);
        return b_stop_;
    }

    bool dispatch_pop() {
        std::unique_lock<std::mutex> lock(mtx_);

        while( q_.empty() && !b_stop_ ) {
            cond_var_.wait(lock);
        }

        if( b_stop_ ) {
            return false;
        }
        const auto &ti = std::get<0>(q_.front());
//            abstract_msg &msg = *q.front().second;


        std::unique_ptr<abstract_msg> msg = std::move(std::get<1>(q_.front()));
        auto *target_q = std::get<2>(q_.front());
        auto token = std::get<3>(q_.front());
        std::unique_ptr<abstract_dispatcher> delete_dispatcher;
        abstract_dispatcher *dispatcher = nullptr;

        if( token != 0 && target_q == 0 ) {
            auto it = token_handler_map_.find(std::make_pair(ti, token));
            assert( it != token_handler_map_.end() );
            dispatcher = it->second.get();

            // erase dispatcher from token handler map
            // and delete the dispatcher after the call has returned (via the unique ptr)
            delete_dispatcher = std::move(it->second);
            token_handler_map_.erase(it);

        } else {
            auto it = handler_map_.find(ti);
            assert( it != handler_map_.end() );
            dispatcher = it->second.get();
        }

        //it->second(*msg);
        q_.pop_front();
        lock.unlock();

        dispatcher->dispatch(std::move(msg), target_q, token);

        return true;
    }

private:
    void unregister_callback( handler_map_type::iterator iter ) {
        handler_map_.erase(iter);
    }

    // lock for handler_map and q
    std::mutex mtx_;
    std::condition_variable cond_var_;
    bool b_stop_;
    //    std::unordered_map<std::type_index, std::function<void(msgx_base &m)>> handler_map;

    handler_map_type handler_map_;
    token_handler_map_type token_handler_map_;
//    handler_ret_map_type handler_ret_map_;

    std::deque<std::tuple<std::type_index, std::unique_ptr<abstract_msg>, queue *, int>> q_;
    //    std::deque<save_it_for_later *> q2;
    callback_guard stop_handler_guard_;
    int next_return_token_;

    friend class callback_guard;
};


void prod_thread(queue &q) {
    for( size_t i = 0; i < 1000000; ++i ) {
        q.call<msgx1>(1, 2.2, 2.2);
        q.call<msgx2>(21, 22.2, 23);
        q.call<msgx3>();
    }
    auto u = std::make_unique<testxxx>(666);
    q.call<msgx4>(std::move(u));

}

void cons_thread(queue &q) {
    size_t i = 0;

    while(q.dispatch_pop()) {
        ++i;
    }
    std::cout << "cons: " << i << "\n";
}

void ret_thread2(queue &q) {
    std::cout << "thread 2: " << (void*)pthread_self() << std::endl;

    auto gr1 = q.register_callback_ret<msgr1>([](int a, float b, int c) {
//        std::cout << "testr1: " << (void*)pthread_self() << std::dec << " " << a << " " << b << " " << c << std::endl;
        return std::make_tuple(a * 2, b * 3, c * 4);
    });


    auto gr2 = q.register_callback_ret<msgr_stop_trick>([]() {
//        std::cout << "testr1: " << (void*)pthread_self() << std::dec << " " << a << " " << b << " " << c << std::endl;
        return std::make_tuple();
    });
    size_t i = 0;
    while(q.dispatch_pop()) {
        ++i;
    }
    std::cout << "test_thread2 ret: " << i << "\n";
}


void test_return() {
    std::cout << "main thread: " << (void*)pthread_self() << std::endl;
    queue q;

    queue q2;//&other_q = start_ret_consumer();
    q.add_default_stop_handler();
    q2.add_default_stop_handler();

    std::thread t2([&](){ret_thread2(q2);});


    for( size_t i = 0; i < 10000; ++i ) {
        q2.call2<msgr1>(&q, [](int a, float b, int c){
//            std::cout << "return testr1: " << (void*)pthread_self() << std::dec << " " << a << " " << b << " " << c << std::endl;
        }
        , 3, 4.0, 5);
    }


    q2.call2<msgr_stop_trick>(&q, [&]() {
        q.call<msg_stop>();
    });
    q2.call<msg_stop>();


    size_t i = 0;
    while(q.dispatch_pop()) {
        ++i;
    }

    t2.join();
    std::cout << "t2 joined\n";


    std::cout << "main thread ret: " << i << std::endl;

//    getchar();
}

int main() {
#if 0
    queue q;
    auto g1 = q.register_callback<msgx1>(test1);
    auto g2 = q.register_callback<msgx2>(test2);
    auto g3 = q.register_callback<msgx3>(test3);
    auto g4 = q.register_callback<msgx4>(test4);
    auto g5 = q.register_callback<msgx5>(test5);
    auto gr1 = q.register_callback_ret<msgr1>(testr1);

    q.add_default_stop_handler();
    std::thread c([&](){cons_thread(q);});
    std::thread c2([&](){cons_thread(q);});
    std::thread p([&](){prod_thread(q);});

    p.join();


    std::cout << "p joined" << std::endl;


//    std::thread::

    q.call<msg_stop>();
    c.join();
    c2.join();

    std::cout << "joined\n";

    return 0;
#else
    test_return();
    return 0;
#endif
    //    save_it_for_later<int,float> x = {std::make_tuple(1, 66.6f), test1 };
    //    x.delayed_dispatch();

//    std::cout << typeid(msg1).name() << " " << typeid(msg2).name() << "\n";

//    dispatcher d;
//    //   d.register_callback<msg1>(test1);
//    dispatcher::rcr<msg1,msg1::TupleType>::rc(d, test1);
//    dispatcher::rcr<msg2,msg2::TupleType>::rc(d, test2);


//    dispatcher::rcr<msg1,msg1::TupleType>::call(d, 1,66.6,2);
//    dispatcher::rcr<msg2,msg2::TupleType>::call(d, 2,266.6,22);
//    d.dispatch();
}
