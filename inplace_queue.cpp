#include <array>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>

#include <cstdlib>

#include <cassert>
#include <bits/algorithmfwd.h>





class base_queue {
public:
    virtual ~base_queue() {}
};


template<size_t Size, size_t BlockSize, size_t ExtraSize>
class inplace_queue {
    
public:
    inplace_queue() 
      : push_ptr_(0), pop_ptr_(0) 
    {
        assert( ((Size + ExtraSize) % BlockSize) == 0 );    
    }
    
    inline size_t wrap( size_t v ) {
        return v % num_blocks;
    }
    
    template<typename T, typename... Args>
    void emplace_back( Args...  args ) {
        
        assert( pop_ptr_ <= push_ptr_ );
        
        const size_t obj_size = sizeof(T);
        
        if( obj_size > ExtraSize ) {
            throw std::runtime_error( "object too big" );
        }
        
        const size_t obj_blocks = (obj_size / BlockSize) + 1;
        
        
        size_t push_first = push_ptr_;
        size_t push_last = push_ptr_ + obj_blocks;
        
        size_t push_first_wrap = wrap( push_first );
        size_t push_last_wrap = wrap( push_last );
        
        
        
        if( push_last_wrap < push_first_wrap ) {
            std::cout << "wrap: " << push_first << " " << push_last << " " << push_first_wrap << " " << num_blocks << "\n";   
            
            
        }
        
        
        if( push_last > pop_ptr_ + num_blocks ) {
            throw std::runtime_error( "overflow" );
        }
        
        char *base = &(queue_[push_first_wrap][0]);
        obj_ptrs_[push_first_wrap] = new (base) T(args...);
        obj_size_[push_first_wrap] = obj_blocks;
        
        push_ptr_ = push_last;
        
        
        
//         if( wrap_last >
        
    }
    
    base_queue *front() {
     
        assert( pop_ptr_ <= push_ptr_ );
        
        
        if( pop_ptr_ == push_ptr_ ) {
            return 0;   
        }
        size_t pop_first_wrap = wrap( pop_ptr_ );
        
        return obj_ptrs_[pop_first_wrap];
        
    }
    
    void pop_front() {
        assert( pop_ptr_ <= push_ptr_ );
        
        if( pop_ptr_ == push_ptr_ ) {
            throw std::runtime_error( "cannot pop" );
        }
        
        size_t pop_first = pop_ptr_;
        
        size_t pop_first_wrap = wrap( pop_first );

        const size_t obj_blocks = obj_size_[pop_first_wrap];
        size_t pop_last = pop_ptr_ + obj_blocks;        
        
        assert( pop_last <= push_ptr_ );
        
        obj_ptrs_[pop_first_wrap]->~base_queue();
        
        
        pop_ptr_ = pop_last;
    }
    
    
private:
    typedef std::array<char,BlockSize> block_type;
    
    const static size_t num_blocks = Size / BlockSize;
    const static size_t num_blocks_extra = (Size + ExtraSize) / BlockSize;
    
    
    typedef std::array<block_type, num_blocks_extra> queue_type;
    queue_type queue_;
    
    std::array<base_queue *, num_blocks> obj_ptrs_;
    std::array<size_t, num_blocks> obj_size_;
    
    
    size_t push_ptr_;
    size_t pop_ptr_;
    
};


class type1 : public base_queue {
public:
    type1() {
        std::fill( data_.begin(), data_.end(), 1 );
//         std::cout << "type1\n";   
    }
    
    virtual ~type1() {
        
        std::for_each( data_.begin(), data_.end(), [] (char x) { 
            if( x != 1 ) { 
                std::cout << "bad data\n";
                abort();
            }
        } );
//         std::cout << "~type1\n";   
    }
    
    
    std::array<char, 4> data_;
};


class type2 : public base_queue {
public:
    type2() {
        std::fill( data_.begin(), data_.end(), 2 );
//         std::cout << "type2\n";   
    }
    
    virtual ~type2() {
        std::for_each( data_.begin(), data_.end(), [] (char x) { 
            if( x != 2 ) { 
                std::cout << "bad data\n";
                abort();
            }
        } );
//         std::cout << "~type2\n";   
    }
    
    
    std::array<char, 512> data_;
};

double frand() {
    return rand() / double(RAND_MAX);
    
}

int main() {
 
    inplace_queue<1024 * 128, 16, 1024> queue;
    
    
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