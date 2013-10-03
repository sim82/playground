#include <unistd.h>

#include "message_passing.h"

using mp::queue;
using mp::make_unique;
namespace msg {
 
    class t1_ret : public base {
    public:
        t1_ret( size_t m ) : m1_(m) 
        {}
        
        size_t m1_;
    };
    
    class t1 : public base {
        
    public:
        typedef t1_ret return_type;
        
        t1( const t1 & ) = delete;
        t1 & operator==( const t1 & ) = delete;
        
        t1( size_t m) : m1_(m) {
//             std::cout << "t1()\n";
        }
        
        virtual ~t1() {
//             std::cerr << "~t1()" << std::endl;   
        }
        
        size_t m1_;
    };
    
    
    
    
    class t2 : public base {
        
    public:
        typedef stop return_type;
        t2( size_t m = 0 ) : m1_(m) {}
        size_t m1_;
        size_t m2_;
    };
}



class worker {
public:
    
    
    void operator()() {
        
    
    
        
        
        
        
//         q_.add_handler_ret<msg::t1_ret, msg::t1>( []( std::unique_ptr<msg::t1> m ) {
//             std::cout << "handler: msg::t1 " << m->m1_ << "\n";
//             
//             return make_unique<msg::t1_ret>(  );
//         } );
        
        q_.add_handler_ret<msg::t1>( []( std::unique_ptr<msg::t1> m ) {
            
            //usleep( 10000 );
            
            return make_unique<msg::t1_ret>( m->m1_ );
//             std::cout << "handler: msg::t1 " << m->m1_ << "\n";
            std::vector<int> v(1000, m->m1_ );
            
            
            size_t count = std::count_if( v.begin(), v.end(), [&m](int a) { return m->m1_ == a; } );
            
            if( count == v.size() ) {
                return make_unique<msg::t1_ret>( m->m1_ );
            } else {
                return make_unique<msg::t1_ret>( 0 );
            }
        } );
        
        q_.add_handlerx<msg::t2>( []( std::unique_ptr<msg::t2> m ) {
            std::cout << "handler: msg::t2 " << m->m1_ << " "<< m->m2_ << "\n";
        } );   
        
        
        q_.add_handlerx<msg::stop>( [this]( std::unique_ptr<msg::stop> m ) {
            std::cout << "handler: msg::stop\n";
            //do_stop = true;
            q_.stop();
        } );   
        
        
        auto m = [&]() {
            while( !q_.is_stopped() ) {
                
                q_.dispatch_pop();
                //             std::cout << "dispatch: " << q_not_empty << "\n";
                
                
            }
            std::cerr << "worker returned\n";
        };
        
        std::thread t1(m);
        std::thread t2(m);
        
        t1.join();
        t2.join();
        
//         while( !q_.is_stopped() ) {
//             
//             q_.dispatch_pop();
// //             std::cout << "dispatch: " << q_not_empty << "\n";
//             
//          
//         }
        
        
    }
    
    queue &get_q() {
        return q_;
    }
    
    
    
private:
    queue q_;
    
};


// class test1 {
//     
// public:
//     test1( int v ) : v_(v) {
//         
//     }
//     
//     
//     test1( test1 && other ) {
//         std::cout << "const: " << v_ << " " << other.v_ << "\n";
//         
//     }
//     
//     test1 &operator=(test1 && other) {
//         std::cout << "assign: " << v_ << " " << other.v_ << "\n";
//         
//         return *this;
//     }
//     
//     
//     
//     int v_;
// };

int main() {
    
//     test1 t(1);
    
//     t = test1(2);
//     return 0;
    
    
    queue q;
    q.add_default_stop_handler();
    
    
    
    bool do_stop = false;
//     q.add_handlerx<msg::t1_ret>([&do_stop]( std::unique_ptr<msg::t1_ret> m ) {
//         std::cout << "handler: msg::t1_ret " << "\n";
//         do_stop = true;
//     } );   
    
    worker w1;
    worker w2;
    
    std::thread t1( [&w1]() {w1();} );
    std::thread t2( [&w2]() {w2();} );
    std::cout << "wait\n";
  
    
    std::cout << "start\n";
    queue &t1q = w1.get_q();
    queue &t2q = w2.get_q();
    
    const size_t num = 1000000;
    for( size_t i = 0; i < num; ++i ) {
        
        
        
//         q.add_token_handler<msg::t1>( t1q.emplace_return<msg::t1 >( &q, i ), [&do_stop] ( std::unique_ptr<msg::t1_ret> m ) {
// //             std::cout << "token handler: msg::t1_ret " << m->m1_ << "\n";
//             
//             if( m->m1_ == num - 1 ) {
//                 do_stop = true;   
//             }
//             
//         } );
        
        auto h = [&q] ( std::unique_ptr<msg::t1_ret> m ) {
//             std::cout << "token handler: msg::t1_ret " << m->m1_ << "\n";
            
            if( m->m1_ == num - 1 ) {
                //do_stop = true;   
                std::cout << "send stop\n";
                q.emplace<msg::stop>();
            }
            
        };
        
        t1q.emplace_return_deluxe<msg::t1>( q, h, i );
        
        //while( q.dispatch_pop() ) {}
    }
//     t1q.emplace<msg::t1>();
    t1q.emplace<msg::t2>();
    
    t1q.emplace<msg::stop>();
    
    
    t2q.emplace<msg::stop>();
    
    
    while( !q.is_stopped() ) { q.dispatch_pop(); }
    
    t1.join();
    t2.join();
    
}