#ifndef MP2_H
#define MP2_H

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
#include "fsa.h"


namespace d3d { namespace ortho {
namespace mp2 {

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


struct msg_stop : public msg_impl<> {};



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


class queue {
    class abstract_dispatcher;
    class abstract_dispatcher_ret;

    struct token_map_hash {
        inline size_t operator()(const std::pair<std::type_index, int> &v) const {
            return std::hash<std::type_index>()(v.first) ^ std::hash<int>()(v.second);
        }
    };

public:
    typedef std::unordered_map<std::type_index, std::unique_ptr<abstract_dispatcher>> handler_map_type;
    typedef std::unordered_map<std::pair<std::type_index, int>, std::unique_ptr<abstract_dispatcher>, token_map_hash> token_handler_map_type;
//    typedef std::unordered_map<std::type_index, abstract_dispatcher_ret*> handler_ret_map_type;
    class callback_guard {
    public:
        callback_guard() : q_(nullptr) {}
        callback_guard( queue *q, queue::handler_map_type::iterator iter ) : q_(q), iter_(iter) {}

        callback_guard( callback_guard &&other );
        callback_guard &operator=(callback_guard &&other );

        ~callback_guard();

        callback_guard( callback_guard &) = delete;
        callback_guard &operator=(callback_guard &) = delete;
    private:
        void unregister();

        queue *q_;
        queue::handler_map_type::iterator iter_;
    };

private:
    class abstract_dispatcher {
    public:
        virtual void dispatch( fsa::unique_ptr<abstract_msg> msg, queue *target_q, int token ) = 0;
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

        inline void dispatch( fsa::unique_ptr<abstract_msg> msg, queue *, int ) override {
            //fsa::unique_ptr<MsgT> mx(msg.static_cast_move<MsgT>());
            fsa::unique_ptr<MsgT> mx(fsa::static_cast_move<MsgT>(std::move(msg)));
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

        inline void dispatch( fsa::unique_ptr<abstract_msg> msg, queue *target_q, int token ) override {
            //fsa::unique_ptr<MsgT> mx(msg.static_cast_move<MsgT>());
            fsa::unique_ptr<MsgT> mx(fsa::static_cast_move<MsgT>(std::move(msg)));
            auto ret = call_func(std::move(mx->payload), std::index_sequence_for<Args...>{});

            target_q->call_with_token<return_message>(std::move(ret), token);
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
            //assert(res.second);
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
    queue();
    ~queue();

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
        fsa::unique_ptr<MsgT> msg(alloc_.allocate<MsgT>());

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
        fsa::unique_ptr<MsgT> msg(alloc_.allocate<MsgT>());

        // TODO: check if we can create the pyload tuple in place rather than moving to the default initialized thing
        msg->payload = std::tuple<Args...>(std::forward<Args>(args)...);

//        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>({std::tuple<Args...>(std::forward<Args>(args)...)});

        int token = target_q->add_token_callback<typename MsgT::return_message>(ret_func);

        std::lock_guard<std::mutex> lock(mtx_);
        q_.emplace_back(std::type_index(typeid(MsgT)), std::move(msg), target_q, token);
        //        rcr<A,std::tuple<Args...>>::call(*this, args...);
        cond_var_.notify_one();
    }


    void stop();

    bool is_stopped();

    bool dispatch_pop();

private:
    void unregister_callback( handler_map_type::iterator iter );

    template<typename MsgT>
    int add_token_callback( typename MsgT::func f ) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto token = next_return_token_++;
        register_callback_helper<MsgT, typename MsgT::tuple>::register_token_callback(*this, token, f);

        return token;
    }

    template<typename MsgT>
    inline void call_with_token( typename MsgT::tuple &&ret_tuple, int token) {
        fsa::unique_ptr<MsgT> msg(alloc_.allocate<MsgT>());

        // TODO: check if we can create the pyload tuple in place rather than moving to the default initialized thing
        msg->payload = std::move(ret_tuple);

//        std::unique_ptr<MsgT> msg = std::make_unique<MsgT>({std::tuple<Args...>(std::forward<Args>(args)...)});


        std::lock_guard<std::mutex> lock(mtx_);
        q_.emplace_back(std::type_index(typeid(MsgT)), std::move(msg), nullptr, token);
        //        rcr<A,std::tuple<Args...>>::call(*this, args...);
        cond_var_.notify_one();
    }


    // lock for handler_map and q
    std::mutex mtx_;
    std::condition_variable cond_var_;
    bool b_stop_;
    //    std::unordered_map<std::type_index, std::function<void(msgx_base &m)>> handler_map;

    handler_map_type handler_map_;
    token_handler_map_type token_handler_map_;
//    handler_ret_map_type handler_ret_map_;

    fsa::allocator_chain alloc_;
    std::deque<std::tuple<std::type_index, fsa::unique_ptr<abstract_msg>, queue *, int>> q_;
    //    std::deque<save_it_for_later *> q2;
    callback_guard stop_handler_guard_;
    int next_return_token_;

    friend class callback_guard;
};
}}} // namespace d3d::ortho::mp2
#endif // MP2_H
