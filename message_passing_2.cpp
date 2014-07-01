#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <deque>
#include <memory>
#include <cassert>

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





//template<typename... Args>
//struct pack { };

void test1( int a, float b, int c ) {
    std::cout << "test1 " << a << " " << b << "\n";
}

void test2( int a, float b, int c ) {
    std::cout << "test2 " << a << " " << b << "\n";
}


struct msgx_base {};

template<class... Args>
struct A : public msgx_base
{
//    using args = pack<Args...>;
    using func = std::function<void(Args...)>;
    using tup = std::tuple<Args...>;

    tup payload;
};

struct msgx1 : public A<int,float,int> {};
struct msgx2 : public A<int,float,int> {};

class abstract_dispatcher {
public:
    virtual void dispatch( msgx_base *msg ) = 0;
    virtual ~abstract_dispatcher() {}
};

template <typename MsgT, typename ...Args>
class dispatch_helper : public abstract_dispatcher
{
public:
    dispatch_helper(std::function<void(Args...)> f) : func(f) {}

    //    std::tuple<Args...> params;
    std::function<void(Args...)> func;

    template<std::size_t ...I>
    void call_func(std::tuple<Args...> &params, std::index_sequence<I...>)
    {
        func(std::get<I>(params)...);
    }
    //    void delayed_dispatch() override
    //    { call_func(std::index_sequence_for<Args...>{}); }


    void dispatch( msgx_base *msg ) override {
        MsgT *mx = static_cast<MsgT*>(msg);
        call_func(mx->payload, std::index_sequence_for<Args...>{});
    }
};

class queue {

    template <typename MsgT, typename... Args>
    struct rcr
    {
        /* Your original function, now inside a struct.
         I'm using direct tuple construction and an
         initializer list to circumvent the order-of-
         construction problem mentioned in the comment
         to your question. */
        static void call(queue &d, Args... args)
        {
            //return rcr<MsgT,Args...>::call(args);

            //        std::unique_ptr<typename MsgT::TupleType> msg( new typename MsgT::TupleType(args...));
            MsgT *msg = new MsgT;
            msg->payload = std::tuple<Args...>(args...);

            d.q.emplace_back(std::type_index(typeid(MsgT)), msg);
            //            auto it =
            //            abstract_save_it_for_later *sfl = new save_it_for_later<Args...> = {std::tuple<Args...>(args...),
        }

        static void register_callback(queue &d, std::function<void(Args...)> f)
        {
            std::cout << "rc: " << typeid(MsgT).name() << "\n";
            //          d.handler_map.emplace(std::type_index(typeid(MsgT)), [=]( msgx_base &m ) {
            //              MsgT &mx = static_cast<MsgT&>(m);
            //              save_it_for_later<Args...> s = {mx.payload, f};
            //              s.delayed_dispatch();
            //          });
            d.handler_map2.emplace(std::type_index(typeid(MsgT)), new dispatch_helper<MsgT,Args...>(f));
        }
    };
    template <typename MsgT, typename ...Args>
    struct rcr<MsgT,std::tuple<Args...>>
    {
        /* Specialized for tuple. */
        static void call(queue &d, Args... args)
        {
            return rcr<MsgT,Args...>::call(d, args...);
        }

        /* Specialized for tuple. */
        static void register_callback(queue &d, std::function<void(Args...)> f)
        { return rcr<MsgT,Args...>::register_callback(d, f); }
    };

public:
    template<typename A>
    void register_callback(typename A::func x) {
        rcr<A, typename A::tup>::register_callback(*this, x);

    }

    template<typename A, typename ...Args>
    void call(Args... args) {
        rcr<A,std::tuple<Args...>>::call(*this, args...);
    }

    void dispatch() {
        while( !q.empty() ) {
            const auto &ti = q.front().first;
            msgx_base *msg = q.front().second;

            auto it = handler_map2.find(ti);
            assert( it != handler_map2.end() );

            //it->second(*msg);
            it->second->dispatch(msg);
            q.pop_front();
        }
    }

private:
    //    std::unordered_map<std::type_index, std::function<void(msgx_base &m)>> handler_map;
    std::unordered_map<std::type_index, abstract_dispatcher*> handler_map2;
    std::deque<std::pair<std::type_index, msgx_base *>> q;
    //    std::deque<save_it_for_later *> q2;
};
int main() {

    queue q;
    q.register_callback<msgx1>(test1);
    q.register_callback<msgx2>(test2);
    q.call<msgx1>(1, 2.2, 2.2);
    q.call<msgx2>(21, 22.2, 23);

    q.dispatch();

    return 0;
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
