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
#include "mp2.h"

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

using d3d::ortho::mp2::msg_impl;
using d3d::ortho::mp2::msg_ret_impl;

struct msgx1 : public msg_impl<int,float,int> {};
struct msgx2 : public msg_impl<int,float,int> {};
struct msgx3 : public msg_impl<> {};
struct msgx4 : public msg_impl<std::unique_ptr<testxxx>> {};
struct msgx5 : public msg_impl<std::unique_ptr<testxxx>,int,float,int> {};
struct msg_stop_trick : public msg_impl<> {};

struct msgr1 : public msg_ret_impl<msgx5,int,float,int, std::unique_ptr<testxxx>> {};
struct msgr_stop_trick : public msg_ret_impl<msg_stop_trick> {};


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




void prod_thread(d3d::ortho::mp2::queue &q) {
    for( size_t i = 0; i < 1000000; ++i ) {
        q.call<msgx1>(1, 2.2, 2.2);
        q.call<msgx2>(21, 22.2, 23);
        q.call<msgx3>();
    }
    auto u = std::make_unique<testxxx>(666);
    q.call<msgx4>(std::move(u));

}

void cons_thread(d3d::ortho::mp2::queue &q) {
    size_t i = 0;

    while(q.dispatch_pop()) {
        ++i;
    }
    std::cout << "cons: " << i << "\n";
}

void ret_thread2(d3d::ortho::mp2::queue &q) {
    std::cout << "thread 2: " << (void*)pthread_self() << std::endl;

    auto gr1 = q.register_callback_ret<msgr1>([](int a, float b, int c, std::unique_ptr<testxxx> p) {
//        std::cout << "testr1: " << (void*)pthread_self() << std::dec << " " << a << " " << b << " " << c << std::endl;
        return std::make_tuple(std::move(p), a * 2, b * 3, c * 4);
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
    d3d::ortho::mp2::queue q;

    d3d::ortho::mp2::queue q2;//&other_q = start_ret_consumer();
    q.add_default_stop_handler();
    q2.add_default_stop_handler();

    std::thread t2([&](){ret_thread2(q2);});


    for( size_t i = 0; i < 1000000; ++i ) {
        q2.call2<msgr1>(&q, [](std::unique_ptr<testxxx>, int a, float b, int c){
//            std::cout << "return testr1: " << (void*)pthread_self() << std::dec << " " << a << " " << b << " " << c << std::endl;
        }
        , 3, 4.0, 5, std::unique_ptr<testxxx>());
    }


    q2.call2<msgr_stop_trick>(&q, [&]() {
        q.call<d3d::ortho::mp2::msg_stop>();
    });
    q2.call<d3d::ortho::mp2::msg_stop>();


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
