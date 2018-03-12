#include <string>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <typeindex>
#include <iostream>

#include "mp3.h"

struct msg_base
{

};


struct msg_type1 /*: public msg_base*/
{
    int a;
    std::string blub;
    //const char *blub;
};

struct msg_type2_ret 
{
    int a;
};

struct msg_type2 /*: public msg_base*/
{
    typedef msg_type2_ret msg_ret;
    int a;
    std::string blub;
    //const char *blub;
};




using namespace d3d::mp3;




class handler_class
{
public:
    handler_class( queue &q )
    {
        q.register_method(this, &handler_class::on_msg_type1);
        q.register_method(this, &handler_class::on_msg_type2);
    }
    void on_msg_type1(const msg_type1 &m)
    {
        std::cout << "class handler " << m.a << " " << m.blub << "\n";
    }

    msg_type2::msg_ret on_msg_type2(const msg_type2 &m)
    {
        std::cout << "class handler " << m.a << " " << m.blub << "\n";

        return {7};
    }
};

void on_msg_type1(const msg_type1 &m)
{
    auto &x = m.a;

    //const std::string x = "bla";
    std::cout << m.a << " " << m.blub << "\n";
}

msg_type2::msg_ret on_msg_type2(const msg_type2 &m)
{
    auto &x = m.a;

    //const std::string x = "bla";
    std::cout << "msg_type2" << m.a << " " << m.blub << std::endl;

    return{ 7 };
}

void on_msg_type2_ret(const msg_type2::msg_ret &m)
{
    auto &x = m.a;

    //const std::string x = "bla";
    std::cout << "msg_type2 ret" << m.a << "\n";

}



//template<typename Msg>
//void call(Msg && m)
//{
//    auto msg_ptr = new Msg(std::move(m));

//    d.invoke(typeid(Msg), msg_ptr);
//}
static dispatcher d;

template<typename Msg>
size_t call_ret(Msg && m, std::function<void(const typename Msg::msg_ret &)> ret_func )
{
    auto msg_ptr = new Msg(std::move(m));


    auto token = d.register_return_handler<Msg>(ret_func);

    void *msg_ret_ptr = d.invoke_ret(typeid(Msg), msg_ptr);

    d.invoke_token(token, msg_ret_ptr);
    return token;
}


int main()
{
    queue q;

    handler_class hc(q);
    q.register_function(on_msg_type1);

    q.register_handler<msg_type1>([](const auto &m) {
        std::cout << "lambda handler " << m.a << " " << m.blub << "\n";
    });

    q.call(msg_type1{1, "blub"});
    q.dispatch_pop();

    q.register_function(on_msg_type2);

    q.call(msg_type2{2, "blub2"}, q, [](size_t token, const msg_type2_ret &m) {
        std::cout << "lambda return handler " << m.a << std::endl;
    });

    while(q.dispatch_pop()) {}

//    d.register_handler_ret<msg_type2>(on_msg_type2);
//    call_ret<msg_type2>({2, "blub2"}, [](msg_type2_ret m){
//        std::cout << "return " << m.a << "\n";
//    });

}
