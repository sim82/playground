#include <array>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>
#include <atomic>
#include <thread>
#include <cstdlib>

#include <cassert>
#include <bits/algorithmfwd.h>

#include <unistd.h>



class base_queue {
public:
    virtual ~base_queue() {}
};


template<size_t Size, size_t BlockSize, size_t ExtraSize>
class inplace_queue {
    
public:
    inplace_queue() 
      : queue_(num_blocks_extra), obj_ptrs_(num_blocks), obj_size_(num_blocks), push_ptr_(0), pop_ptr_(0) 
    {
        std::fill( obj_ptrs_.begin(), obj_ptrs_.end(), (base_queue*)0 );
        std::fill( obj_size_.begin(), obj_size_.end(), 0 );
        
        assert( ((Size + ExtraSize) % BlockSize) == 0 );    
    }
    
    inline size_t wrap( size_t v ) {
        return v % num_blocks;
    }
    
    template<typename T, typename... Args>
    bool emplace_back( Args...  args ) {
        
     //   assert( pop_ptr_ <= push_ptr_ );
        
        const size_t obj_size = sizeof(T);
        
        if( obj_size > ExtraSize ) {
            throw std::runtime_error( "object too big" );
        }
        
        const size_t obj_blocks = (obj_size / BlockSize) + 1;
        
        //restart:
        
        size_t push_first_wrap = size_t(-1);
        while(true) {
            size_t push_first = push_ptr_.load(std::memory_order_acquire);
            size_t push_last = push_first + obj_blocks;
            
            push_first_wrap = wrap( push_first );
            

#if 0            
            size_t push_last_wrap = wrap( push_last );
            if( push_last_wrap < push_first_wrap ) {
                std::cout << "wrap: " << push_first << " " << push_last << " " << push_first_wrap << " " << num_blocks << "\n";   
                
                
            }
#endif

            
            if( push_last > pop_ptr_.load(std::memory_order_acquire) + num_blocks ) {
                //    throw std::runtime_error( "overflow" );
                return false;
            }
            
            if( push_ptr_.compare_exchange_weak( push_first, push_last, std::memory_order_acq_rel ) ) {
                break;
            }
        }

        char *base = &(queue_[push_first_wrap][0]);
        
        base_queue *x = new (base) T(args...);
        
        
        obj_size_[push_first_wrap].store( obj_blocks, std::memory_order_relaxed );
        obj_ptrs_[push_first_wrap].store( x, std::memory_order_release );

        return true;
    }
    
    base_queue *front() {
     
        assert( pop_ptr_ <= push_ptr_ );
        
        
        size_t pop_first = pop_ptr_.load(std::memory_order_acquire);
        
        
        if( pop_first == push_ptr_.load(std::memory_order_acquire)) {
            return 0;   
        }
        
        
        size_t pop_first_wrap = wrap( pop_first );


        base_queue *x = 0;        

        while( (x = obj_ptrs_[pop_first_wrap].load(std::memory_order_consume)) == 0 ) {}

        return x;
    }
    
    void pop_front() {
        assert( pop_ptr_ <= push_ptr_ );
        
        if( pop_ptr_ == push_ptr_ ) {
            throw std::runtime_error( "cannot pop" );
        }

        
        
        size_t pop_first = pop_ptr_.load( std::memory_order_acquire );
        
        
        size_t pop_first_wrap = wrap( pop_first );

        
        
        base_queue *x = 0;

                
        while( (x = obj_ptrs_[pop_first_wrap].load(std::memory_order_consume)) == 0 ) {}
        const size_t obj_blocks = obj_size_[pop_first_wrap].load(std::memory_order_relaxed);

        size_t pop_last = pop_first + obj_blocks;        
        
        
        x->~base_queue();
        obj_size_[pop_first_wrap].store(0, std::memory_order_relaxed);
        obj_ptrs_[pop_first_wrap].store(0, std::memory_order_release);
        
        
        pop_ptr_.store(pop_last, std::memory_order_release);
    }
    
    
private:
    typedef std::array<char,BlockSize> block_type;
    
    const static size_t num_blocks = Size / BlockSize;
    const static size_t num_blocks_extra = (Size + ExtraSize) / BlockSize;
    
    
    //typedef std::array<block_type, num_blocks_extra> queue_type;
    typedef std::vector<block_type> queue_type;
    queue_type queue_;
    
//     std::array<base_queue *, num_blocks> obj_ptrs_;
//     std::array<std::atomic<size_t>, num_blocks> obj_size_;
    
    std::vector<std::atomic<base_queue *>> obj_ptrs_;
    std::vector<std::atomic<size_t>> obj_size_;
    
    
    std::atomic<size_t> push_ptr_;
    std::atomic<size_t> pop_ptr_;
    
};


class type1 : public base_queue {
public:
    type1() {
        
        std::fill( data_.begin(), data_.end(), 1 );
//         std::cout << "type1\n";   
    }
    
    virtual ~type1() {
//         return;
        std::for_each( data_.begin(), data_.end(), [] (char x) { 
            if( x != 1 ) { 
                std::cout << "bad data\n";
                abort();
            }
        } );
//         std::fill( data_.begin(), data_.end(), 0 );
  //      std::cout << "~type1\n";   
    }
    
    
    std::array<char, 128> data_;
};


class type2 : public base_queue {
public:
    type2() {
        
        std::fill( data_.begin(), data_.end(), 2 );
//         std::cout << "type2\n";   
    }
    
    virtual ~type2() {
//         return;
        std::for_each( data_.begin(), data_.end(), [] (char x) { 
            if( x != 2 ) { 
                std::cout << "bad data\n";
                abort();
            }
        } );
//         std::fill( data_.begin(), data_.end(), 0 );
//        std::cout << "~type2\n";   
    }
    
    
    std::array<char, 512> data_;
};

double frand() {
    return rand() / double(RAND_MAX);
    
}


typedef inplace_queue<1024L * 128 * 8, 16, 1024> queue_type;

template<typename T>
void produce( queue_type & queue, bool do_print = false ) {
    
    size_t num_success = 0;
    size_t num_fail = 0; 
    while( true ) {
        bool success = queue.emplace_back<T>();
        if( success ) {
            ++num_success;
        } else {
            ++num_fail;
        }
        
        
        if( num_success % (1024 * 1024) == 0 ) {
            if( do_print ) {
                std::cout << "ratio: " << num_success << " " << num_fail << " " << typeid(T).name() << "\n";
            }
            num_success = 0;
            num_fail = 0;
        }
        //         usleep(0);
//         pthread_yield();
        //             usleep(0);
    }
}



int main() {
 
    queue_type queue;
    

    std::thread c0( [&queue]() {
        while( true ) {
            while( queue.front() == 0 ) {
                
            }
            
            queue.pop_front();
        }
    } );
    
    
    std::thread p0( [&queue]() {
        produce<type1>(queue, true);
        
        
    } );
    
    std::thread p1( [&queue]() {
        produce<type2>(queue, true);
    } );
    

    p0.join();
    p1.join();
    c0.join();
    return 0;
    
    queue.emplace_back<type1>();
    queue.emplace_back<type2>();
    queue.emplace_back<type1>();
    
    while( true ) {
        queue.pop_front();
        if( frand() < 0.5 ) {
            queue.emplace_back<type1>();
        } else {
            queue.emplace_back<type2>();
        }
    }
    queue.pop_front();
    queue.pop_front();
    queue.pop_front();
    
}