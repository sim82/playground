#include <vector>
#include <iostream>
#include "replication.h"

class replicator {
public:
    //virtual rep( int & ) = 0;
};


template<typename Thost, typename Trep>
class implant_base {
public:
    implant_base( Thost &host ) : host_(host) {}

//    void rep( int & x ) {

//    }

    Trep &rep() {
        return rep_;
    }

    virtual void replicate() = 0;
public:
    Thost &host_;
    Trep rep_;
};



#if 0
#define IMPLANT_BOILERPLATE(Thost,Trep) \
    typedef implant_base<Thost,Trep> ib; \
    c_implant( Thost &host ) \
        : implant_base<Thost,Trep>(host) {}
#endif
#if 0
#define DECL_IMPLANT(name) \
template<typename Thost, typename Trep> \
class c_implant \
   : public implant_base<Thost, Trep>


#define IMPLANT_BOILERPLATE(name) \
public: \
typedef implant_base<Thost,Trep> ib; \
    name( Thost &host ) \
        : implant_base<Thost,Trep>(host) {}
#endif
#if 0
//template<typename Thost, typename Trep>
//class c_implant
//   : public implant_base<Thost, Trep>
//{
//public:
//    typedef implant_base<Thost, Trep> ib;

//    c_implant( Thost &host )
//        : implant_base<Thost,Trep>(host) {}

//    IMPLANT_BOILERPLATE(Thost,Trep)
#endif



//DECL_IMPLANT( c_implant )
//{
//    IMPLANT_BOILERPLATE( c_implant )
//    void replicate() {
//        ib::rep_( ib::host_.a_ );
//        ib::rep_( ib::host_.b_ );
//        ib::rep_( ib::host_.c_ );

//    }
//};



template<typename Thost, typename Trep>
class c_implant {

    IMPLANT_BOILERPLATE

    void replicate() {
        rep_ & host().a_ & host().b_ & host().c_;

//        rep_( host().a_ );
//        rep_( host().b_ );
//        rep_( host().c_ );

   }
};

class c_proxy : public c_implant<c_proxy,recv_replicator> {
public:
    friend class c_implant<c_proxy, recv_replicator>;


    c_proxy() : a_(5), b_(6), c_(7) {}


    void test() {
        std::cout << "proxy: " << a_ << " " << b_ << " " << c_ << "\n";
    }

private:
    int a_;
    int b_;
    int c_;

};

class c_stub : public c_implant<c_stub,send_replicator> {
public:
    friend class c_implant<c_stub, send_replicator>;

    c_stub() : a_(0), b_(1), c_(2) {}



private:
    int a_;
    int b_;
    int c_;
};


int main() {

    c_stub stub;

    c_proxy proxy;



    stub.rep().start();
    stub.replicate();


    const auto &read_rep = stub.rep();
    auto &write_rep = proxy.rep();

    write_rep.start( read_rep.buf_int_ );
    proxy.replicate();

    proxy.test();
}
