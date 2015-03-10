#ifndef MP3_H
#define MP3_H
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <deque>
#include <mutex>
#include <vector>
#include <condition_variable>

namespace d3d { namespace mp3 {

template<typename Msg>
struct message_traits
{
    typedef Msg message_type;
    typedef std::function<void(const message_type &)> func_type;
};

template<typename Msg>
struct return_message_traits
{
    typedef Msg message_type;
    typedef typename Msg::msg_ret return_message_type;
    typedef std::function<return_message_type(const message_type &)> func_type;
    typedef std::function<void(size_t, const return_message_type &)> return_func_type;
};

class dispatcher
{
public:
    dispatcher();

    void invoke(std::type_index ti, void *msg_ptr, std::unique_lock<std::mutex> &&lock);

    std::pair<std::type_index, void *> invoke_ret(std::type_index ti, void *msg_ptr, std::unique_lock<std::mutex> &&lock);

    void invoke_token(size_t token, void *msg_ptr, std::unique_lock<std::mutex> &&lock);

    template<typename Msg>
    void register_handler(typename message_traits<Msg>::func_type f)
    {
#ifndef NO_MULTI_HANDLER
        auto it = handler_map.find(typeid(Msg));

        if( it == handler_map.end() )
        {
            handler_map.emplace(typeid(Msg), std::unique_ptr<abstract_handler>(new msg_handler<Msg>(f)));
        }
        else
        {
            //it->second->append(f);
            auto *ch = static_cast<msg_handler<Msg> *>(it->second.get());
            ch->append(f);
        }
#else
        handler_map.emplace(typeid(Msg), std::unique_ptr<abstract_handler>(new msg_handler<Msg>(f)));
#endif
    }

//    template<typename Msg, typename HClass>
//    void register_handler(HClass *hinst, void (HClass::*method_ptr)(const Msg &))
//    {
//        handler_map.emplace(typeid(Msg), std::unique_ptr<abstract_handler>(new msg_handler<Msg>(std::bind(method_ptr, hinst, std::placeholders::_1))));
//    }

    template<typename Msg>
    void register_handler_ret(typename return_message_traits<Msg>::func_type f)
    {
        handler_map_ret.emplace(typeid(Msg), std::unique_ptr<abstract_handler_ret>(new msg_handler_ret<Msg>(f)));
    }


    template<typename Msg>
    size_t register_return_handler(typename return_message_traits<Msg>::return_func_type f)
    {
        size_t token = next_token_++;
        handler_map_ret_token.emplace(token, std::unique_ptr<abstract_handler_token>(new msg_handler_token<Msg>(f)));

        return token;
    }

private:
    struct abstract_handler
    {
        virtual ~abstract_handler() {}
        virtual void handle(void *) = 0;
    };
#ifdef NO_MULTI_HANDLER
    template<typename Msg>
    struct msg_handler : public abstract_handler
    {
        typedef std::function<void(const Msg &)> func_type;

        msg_handler(func_type f)
            : func_(f)
        {}
        inline void handle(void *vp) override
        {
            std::unique_ptr<Msg> mp(reinterpret_cast<Msg*>(vp));
            func_(*mp);
        }

        func_type func_;
    };
#else

    template<typename Msg>
    struct msg_handler : public abstract_handler
    {
        typedef std::function<void(const Msg &)> func_type;

        msg_handler(func_type f)
        {
            func_.emplace_back(std::move(f));
        }
        inline void handle(void *vp) override
        {
            std::unique_ptr<Msg> mp(reinterpret_cast<Msg*>(vp));
            for( auto it = func_.begin(), eit = func_.end(); it != eit; ++it )
            {
                (*it)(*mp);
            }
        }
        inline void append(func_type f)
        {
            func_.emplace_back(std::move(f));
        }
        std::vector<func_type> func_;
    };
#endif



    struct abstract_handler_ret
    {
        virtual ~abstract_handler_ret() {}
        virtual std::pair<std::type_index, void *>handle(void *) = 0;
    };

    template<typename Msg>
    struct msg_handler_ret : public abstract_handler_ret
    {
        typedef typename Msg::msg_ret msg_ret_type;

        typedef std::function<msg_ret_type(const Msg &)> func_type;

        msg_handler_ret(func_type f) : func_(f)
        {}
        inline std::pair<std::type_index, void *>handle(void *vp) override
        {
            std::unique_ptr<Msg> mp(reinterpret_cast<Msg*>(vp));

            msg_ret_type *msg_ret = new msg_ret_type(func_(*mp));

            return {typeid(typename Msg::msg_ret), msg_ret};
        }


        func_type func_;
    };

    struct abstract_handler_token
    {
        virtual ~abstract_handler_token() {}
        virtual void handle(size_t token, void *) = 0;
    };
    template<typename Msg>
    struct msg_handler_token : public abstract_handler_token
    {
        typedef typename return_message_traits<Msg>::return_func_type func_type;
        typedef typename return_message_traits<Msg>::return_message_type message_type;

        msg_handler_token(func_type f)
            : func_(f)
        {}
        inline void handle(size_t token, void *vp) override
        {
            std::unique_ptr<message_type> mp(reinterpret_cast<message_type*>(vp));
            func_(token, *mp);
        }

        func_type func_;
    };


    std::unordered_map<std::type_index, std::unique_ptr<abstract_handler>> handler_map;
    std::unordered_map<std::type_index, std::unique_ptr<abstract_handler_ret>> handler_map_ret;
    std::unordered_map<size_t, std::unique_ptr<abstract_handler_token>> handler_map_ret_token;
    size_t next_token_;
};

class queue : private dispatcher {
public:
    dispatcher &get_dispatcher()
    {
        return *this;
    }

    template<typename Msg>
    inline void register_handler(std::function<void(const Msg&)> f)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler<Msg>(std::move(f));
    }

    template<typename Msg>
    inline void register_function(void(*func_ptr)(const Msg &))
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler<Msg>(func_ptr);
    }

    template<typename Msg, typename HClass>
    inline void register_method(HClass *hinst, void (HClass::*method_ptr)(const Msg &))
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler<Msg>(std::bind(method_ptr, hinst, std::placeholders::_1));
    }

    template<typename Msg>
    void register_handler_ret(typename return_message_traits<Msg>::func_type f)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler<Msg>(std::move(f));
    }

    template<typename Msg>
    inline void register_function(typename Msg::msg_ret (*func_ptr)(const Msg &))
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler_ret<Msg>(func_ptr);
    }

    template<typename Msg, typename HClass>
    inline void register_method(HClass *hinst, typename Msg::msg_ret (HClass::*method_ptr)(const Msg &))
    {
        std::lock_guard<std::mutex> lock(mtx_);
        dispatcher::register_handler<Msg>(std::bind(method_ptr, hinst, std::placeholders::_1));
    }

    template<typename Msg>
    void call(Msg && m)
    {
        auto msg_ptr = new Msg(std::move(m));

        std::lock_guard<std::mutex> lock(mtx_);
        queue_.emplace_back(typeid(Msg), msg_ptr, 0, nullptr);

        cond_var_.notify_one();
    }

    template<typename Msg>
    size_t call(Msg && m, queue &target_queue, typename return_message_traits<Msg>::return_func_type f_ret)
    {
        auto msg_ptr = new Msg(std::move(m));
        std::lock_guard<std::mutex> lock(mtx_);

        auto token = target_queue.register_return_handler<Msg>(f_ret);

        queue_.emplace_back(typeid(Msg), msg_ptr, token, &target_queue);
        cond_var_.notify_one();

        return token;
    }

    void call_token(std::type_index ti, void *msg_ptr, size_t token )
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.emplace_back(ti, msg_ptr, token, nullptr);

        cond_var_.notify_one();
    }

    bool dispatch_pop();

private:
    typedef std::tuple<std::type_index, void *, size_t, queue *> queue_entry;

    std::deque<queue_entry> queue_;

    std::mutex mtx_;
    std::condition_variable cond_var_;
    bool b_stop_;

};


} }

#endif // MP3_H

