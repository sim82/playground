#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <bitset>
#include <stdint.h>


#include "cycle.h"
#include "time.h"



double ivy_mike::perf_timer::my_getticks() {
#if defined(WIN32) && !defined(_M_X64)
        return double(getticks().QuadPart);
#else
        return double(getticks());
#endif
}

template<typename T>
class rel_ptr {
public:
    rel_ptr() : off_(0) {
        
    }
    
    rel_ptr( const rel_ptr &other ) {
        reset( other.get() );
    }
    
    rel_ptr operator=( const rel_ptr &other ) {
        reset( other.get() );
    }
    
    rel_ptr( T *ptr ) {
        reset( ptr );
	}
	
	
	void reset( T *ptr ) {
        size_t dest = size_t(ptr);
        size_t src = size_t(this);
        
        off_ = off_t(dest - src);    
    }
	
	inline T* get() const {
        if( off_ == 0 ) {
            throw std::runtime_error( "bad relative ptr" );
        }
        
        size_t src = size_t(this);
        size_t dest = src + off_;
        
        return (T*)(dest);
	}
	
	inline bool valid() const {
        return off_ != 0;
    }
	
	void test() const {
        std::cout << "rel ptr: " << this << " + " << off_ << " = " << get() << "\n";
    }
	
private:
	ssize_t off_;
	
};

class test1 {
public:
    
    test1( rel_ptr<test1> prev ) : prev_(prev) {
        
    }
    
    test1() {}
    
    rel_ptr<test1> prev_;
};


class test1_abs {
public:
    
    test1_abs( test1_abs *prev ) : prev_(prev) {
        
    }
    
    test1_abs() : prev_(0) {}
    
    test1_abs *prev_;
};


template<typename T>
class inc_alloc {
public:
    
    inc_alloc( size_t num ) : num_(num), buf_(num_ * sizeof(T) ), iter_(buf_.begin()) {
        
        
    }
    
//     void *alloc( size_t s ) {
//         char *ptr = &(*iter_);
//         iter_ += s;
//         
//         if( iter_ > buf_.end() ) {
//             throw std::runtime_error( "out of memory" );
//             
//         }
//         
//         return ptr;
//     }
    
    
    T* alloc() {
        size_t s = sizeof(T);
        
        char *ptr = &(*iter_);
        iter_ += s;
        
        if( iter_ > buf_.end() ) {
            throw std::runtime_error( "out of memory" );
            
        }
        
        return (T*)ptr;
    }
    
    const std::vector<char> &buf() const {
        return buf_;
    }
    
private:
    size_t num_;
    std::vector<char> buf_;
    std::vector<char>::iterator iter_;
    
};


template<typename T, size_t Num>
class rnd_alloc {
public:
    
    rnd_alloc() : num_(Num), in_use_ptr_(new std::bitset<Num>), in_use_(*in_use_ptr_), buf_( Num * sizeof(T) ) {
        
        
    }
    
//     void *alloc( size_t s ) {
//         char *ptr = &(*iter_);
//         iter_ += s;
//         
//         if( iter_ > buf_.end() ) {
//             throw std::runtime_error( "out of memory" );
//             
//         }
//         
//         return ptr;
//     }
    
    
    T* alloc() {
        
        T* bufx = (T*) buf_.data();
        
        T* ptr = 0;
        do {
            size_t r = std::rand() % Num;
            if( !in_use_[r] ) {
                ptr = bufx + r;
                in_use_[r] = true;
            }
        } while( ptr == 0 );
        
        return ptr;
    }
    
    const std::vector<char> &buf() const {
        return buf_;
    }
    
private:
    size_t num_;
    std::auto_ptr<std::bitset<Num> > in_use_ptr_;
    std::bitset<Num> &in_use_;
    std::vector<char> buf_;
    
    
};



template<typename T, typename TStor>
T* relocate( const TStor *base_src, const TStor *base_dest, T *ptr ) {
    ssize_t off = size_t(base_dest) - size_t(base_src);    

    
    
    size_t src = size_t(ptr);
    size_t dest = src + off;
    
    std::cout << "reloc: " << off << " " << src << " " << dest << "\n";
    return (T*)dest;
}

void bench( test1 * const ptr, test1_abs * const ptr_abs ) {
    size_t sum = 0;
    size_t count = 0;
    std::cout << "init done\n";
    ivy_mike::perf_timer t1;
    test1 *xptr = ptr;
    while( xptr != 0 ) {
     //   sum += size_t(xptr);
     //   ++count;
        if( xptr->prev_.valid() ) {
            xptr = xptr->prev_.get();
        } else {
            xptr = 0;
        }
        
    }

    
    
    t1.add_int();
    
    sum += size_t(xptr);
    
    test1_abs * xptr_abs = ptr_abs;
    while( xptr_abs != 0 ) {
      //  sum += size_t(xptr_abs);
      //  ++count;
        if( xptr_abs->prev_ != 0 ) {
            xptr_abs = xptr_abs->prev_;
        } else {
            xptr_abs = 0;
        }
        
    }
    t1.add_int();
    
    sum += size_t(xptr_abs);
    
    t1.print();   
    std::cout << sum << " " << count << "\n";
}

int main() {
    
    std::unique_ptr<test1> ptr_a( new test1 );
    std::cout << "a: " << ptr_a.get() << "\n";
    
    rel_ptr<test1> rptr_a(ptr_a.get());
    rptr_a.test();
    
    
    rel_ptr<test1> rptr_b(rptr_a);
    rptr_b.test();
    
    std::cout << "size: " << sizeof( rel_ptr<test1> ) << "\n";
    
    
    size_t a = 1;
    size_t b = UINT64_MAX / 2;
    
    ssize_t off = a - b;
    
    std::cout << off << " " << ((b + off) == a) << "\n";
	
    
#if 1
    const size_t num = 1024 * 1024 * 512;
    inc_alloc<test1> xalloc(num + 1);
    inc_alloc<test1> xalloc2(num + 1);
#else
    const size_t num = 1024 * 1024 * 16;
    rnd_alloc<test1,num * 2> xalloc;
    rnd_alloc<test1,num * 2> xalloc2;
#endif
    test1 * const ptr = new(xalloc.alloc()) test1;
    test1 *xptr = ptr;
    
    test1_abs * const ptr_abs = new(xalloc2.alloc()) test1_abs;
    test1_abs *xptr_abs = ptr_abs;
    
    for( size_t i = 0; i < num; ++i ) {
        
        
        xptr->prev_.reset(new(xalloc.alloc()) test1);
        xptr = xptr->prev_.get();
        
        xptr_abs->prev_ = new(xalloc2.alloc()) test1_abs;
        xptr_abs = xptr_abs->prev_;
        
//         std::cout << "alloc ptr: " << xptr << "\n";
        
    }
    
#if 0
    xptr = ptr;

    while( xptr != 0 ) {
    
        std::cout << "ptr: " << xptr << "\n";
        if( xptr->prev_.valid() ) {
            xptr = xptr->prev_.get();
        } else {
            xptr = 0;
        }
    }
    
    std::vector<char> buf2 = xalloc.buf();
    
    
    xptr = relocate( xalloc.buf().data(), buf2.data(), ptr );
    while( xptr != 0 ) {
    
        std::cout << "ptr2: " << xptr << "\n";
        if( xptr->prev_.valid() ) {
            xptr = xptr->prev_.get();
        } else {
            xptr = 0;
        }
    }
#endif
    bench( ptr, ptr_abs );

    
}