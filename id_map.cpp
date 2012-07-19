#include <cstddef>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include <memory>
// #include <type_traits>
#include "id_map.h"

template<typename K, typename V>
class flat_map {
public:
    flat_map() : sorted_(true) {}
    
    void sort() {
        if( !sorted_ ) {
            std::sort( pairs_.begin(), pairs_.end() );
            sorted_ = true;
        }
    }
    
    void put_fast( const K &key, const V &value ) {
        pairs_.emplace_back( key, value );
        
        sorted_ = false;
    }
    
    void put_fast( const K &key, V &&value ) {
        pairs_.emplace_back( key, value );
        
        sorted_ = false;
    }
    template<typename... Args>
    void emplace_fast( const K &key, Args&&... args) {
        pairs_.emplace_back( key, args... );
        
        sorted_ = false;
    
    }
    
    
    void put( const K &key, const V &value ) {
        if( !sorted_ ) {
            throw std::runtime_error( "flat_map::put on unsorted map" );
        }
        
        ipair p{key, value};
        auto lb = std::lower_bound( pairs_.begin(), pairs_.end(), p );
        
        pairs_.insert(lb, std::move(p));
    }
    
    const V * get( const K &key ) const {
        if( !sorted_ ) {
            throw std::runtime_error( "flat_map::get on unsorted map" );
        }
        auto lb = std::lower_bound( pairs_.begin(), pairs_.end(), ipair{key, V()} );
        
        if( lb == pairs_.end() || lb->key_ != key ) {
            return nullptr;
        } else {
            return &lb->value_;
        }
    }
    
    void reserve( size_t s ) {
        pairs_.reserve(s);
    }
        
    
private:
    struct ipair {
        K key_;
        V value_;
        
        ipair( const K &key, const V &value ) : key_(key), value_(value) {}
        
        
        inline bool operator<( const ipair &other ) const {
            return key_ < other.key_;
        }
        
        
    };
    
    
    std::vector<ipair> pairs_;
    bool sorted_;
};   
    

template<typename Value>
class id_map_sorted : private flat_map<size_t,Value> {
public:
    typedef const Value *iterator;
    
    bool set( size_t id, Value v ) {
        flat_map<size_t,Value>::put(id,v);
        
        return true;
    }
    
    iterator find( size_t id ) {
        return flat_map<size_t,Value>::get(id);
    }
    
    
    iterator end() {
        return nullptr;
    }
    
    static size_t max_id() {
        return 63;
    }
private:
  
    
};

#if 0

template<typename Value, size_t max_num, typename Bitfield = uint64_t >
class id_map_fixed {
public:
    
    typedef Bitfield bitfield_t;
    
    id_map_fixed() 
     : bits_(0)
    {
        
    }
    
    typedef typename std::array<Value, max_num>::iterator iterator;
    
    
    inline iterator end() {
        return values_.end();
    }
    
    inline bool set( size_t id, Value v ) {
        
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
//             std::cout << "replace\n";
            values_[idx] = v;
        } else {
            size_t count = popcount( bits_ );
            
            if( count >= max_num ) {
                return false;
            }
            
            bits_ |= mask;
            auto it = values_.begin() + idx;
            auto end = values_.begin() + count;
           // values_.insert(it, v);
//             std::cout << "set: " << count << "\n";
            std::copy_backward( it, end, end+1 );
            values_[idx] = v;
        }
        
        return true;
//          std::cout << "bits: " << id << " " << mask << "\n";
    }
    
    inline void remove( size_t id ) {
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
            bits_ &= ~mask;
            size_t count = popcount( bits_ );
            auto it = values_.begin() + idx;
            auto end = values_.begin() + count;
            
            std::copy_backward( it+1, end + 1, end );
            //values_.erase( it );
        }
    }
    
    inline iterator find( size_t id ) {
        bitfield_t mask = id_mask(id);
        
        if( (bits_ & mask) == 0 ) {
            //throw std::runtime_error( "bad id" );
            
            return values_.end();
        } 
        
        size_t idx = index(id);
        
//         std::cout << "find: " << id << " " << idx << "\n";
        
        return values_.begin() + idx;
    }
    inline static size_t max_id() {
        return sizeof(bitfield_t) * 8 - 1;
    }
private:
    inline size_t popcount( uint32_t f ) {
        return __builtin_popcount(f);
    }
    inline size_t popcount( uint64_t f ) {
        return __builtin_popcountll(f);
    }
    inline uint64_t id_mask( size_t id ) {
        return bitfield_t(1) << (id + 1);
    }
    
    inline size_t index( size_t id ) {
        uint64_t mask = bitfield_t(-1) >> (num_bits_ - id - 1);
        
//         std::cout << "mask: " << mask << " " << id << "\n";
        
//         mask >>= (num_bits_ - id);
        
        //return __builtin_popcountll(mask & bits_);
        return popcount(mask & bits_);
        
    }
    
    
    const static size_t num_bits_ = sizeof(bitfield_t) * 8;
    bitfield_t bits_;
    std::array<Value,max_num> values_;
};


template<typename Value>
class id_map {
public:
    typedef uint64_t bitfield_t;
    
    id_map() 
     : bits_(0)
    {
        
    }
    
    typedef typename std::vector<Value>::iterator iterator;
    
    
    inline iterator end() {
        return values_.end();
    }
    
    inline bool set( size_t id, Value v ) {
        
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
//             std::cout << "replace\n";
            values_[idx] = v;
        } else {
            bits_ |= mask;
            auto it = values_.begin() + idx;
            
            values_.insert(it, v);
        }
        
        return true;
//          std::cout << "bits: " << id << " " << mask << "\n";
    }
    
    inline void remove( size_t id ) {
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
            bits_ &= ~mask;
            auto it = values_.begin() + idx;
            values_.erase( it );
        }
    }
    
    inline iterator find( size_t id ) {
        bitfield_t mask = id_mask(id);
        
        if( (bits_ & mask) == 0 ) {
            //throw std::runtime_error( "bad id" );
            
            return values_.end();
        } 
        
        size_t idx = index(id);
        
//         std::cout << "find: " << id << " " << idx << "\n";
        
        return values_.begin() + idx;
    }
    inline static size_t max_id() {
        return sizeof(bitfield_t) * 8 - 1;
    }
private:
    
    inline uint64_t id_mask( size_t id ) {
        return bitfield_t(1) << (id + 1);
    }
    
    inline size_t index( size_t id ) {
        uint64_t mask = bitfield_t(-1) >> (num_bits_ - id - 1);
        
//         std::cout << "mask: " << mask << " " << id << "\n";
        
//         mask >>= (num_bits_ - id);
        
        //return __builtin_popcountll(mask & bits_);
        return __builtin_popcountll(mask & bits_);
    }
    
    
    const static size_t num_bits_ = sizeof(bitfield_t) * 8;
    bitfield_t bits_;
    std::vector<Value> values_;
};


template<typename Value,size_t num_slots> 
class id_map_vanilla {
public:
    typedef typename std::array<Value,num_slots>::iterator iterator;
    
    id_map_vanilla() {
        std::fill( used_.begin(), used_.end(), false );
        
    } 
    
    inline bool set( size_t id, Value v ) {
        used_[id] = true;
        slots_[id] = v;
        
        return true;
    }
    
    
    inline iterator find( size_t id ) {
        if( !used_[id] ) {
            return slots_.end();
        } else {
            return slots_.begin() + id;
        }
    }
    inline size_t max_id() const {
        return used_.size() - 1;
    }
    
    inline iterator end() {
        return slots_.end();
    }
private:
    std::array<uint8_t,num_slots> used_;
    std::array<Value,num_slots> slots_;
    
};

#endif

template<typename Map>
void read_bench( Map & im ) {
    
    size_t num_set = 0;
    size_t count = 0;
    size_t max_id = im.max_id();
    while( true ) {
     //   size_t id = rand() % max_id;
        size_t id = count % max_id;
        auto it = im.find(id);
        
        if( it != im.end() ) {
            ++num_set;
        } 
        ++count;
        
        if( count % 100000000 == 0 ) {
            for( size_t i = 0; i < max_id; ++i ) {
                auto it = im.find(i);
                if( it != im.end() ) {
//                     std::cout << i << ": " << *(im.find(i)) << "\n";
                   ++num_set;
                   if( *it != int(i) ) {
                       std::cout << "meeeep: " << i << " " << *it << "\n";
                       getchar();
                   }
                }
            }
            
            std::cout << "num: " << num_set << "\n";
        }
        
//         getchar();
    }
    
}

#if 1
int main() {
//     return 0;

    {
        id_map_dynamic<std::unique_ptr<int>> im;
        
//         std::shared_ptr<int> p1;
       // im.set(1,std::make_shared<int>(0));
        im.set(1,std::unique_ptr<int>(nullptr));
//         im.set(1,p1);
    }
    
    typedef id_map_fixed<int, 5> id_map_t;
//     typedef id_map<int> id_map_t;
//     typedef id_map_sorted<int> id_map_t;
//     typedef id_map_vanilla<int,64> id_map_t;
    id_map_t im;
    
//     std::cout << sizeof( im2 ) << " " << sizeof( im ) << "\n";
    
//     id_map_vanilla<int,64> im;
    size_t max_id = im.max_id();
//     size_t count = 0;
    
    for( size_t i = 0; i < 5; ++i ) {
        size_t id = rand() % max_id;
        bool b = im.set(id,id);
        
        std::cout << b << "\n";
        
    }
    
    
    std::vector<id_map_t> tv;
    
    while( tv.size() < 10000000 ) {
        tv.push_back( im );
    }
  
    
    read_bench(im);
    
    
    
    
    return 0;
#if 0
    while( true ) {
        size_t id = rand() % max_id;
//         size_t id = count % 31;
        auto it = im.find(id);
        
        if( it == im.end() ) {
            im.set( id, id );
//             std::cout << "set: " << id << "\n";
        } else {
            im.remove( id );
        }
        
        ++count;
        size_t num_set = 0;
        if( count % 100000000 == 0 ) {
            for( size_t i = 0; i < max_id; ++i ) {
                auto it = im.find(i);
                if( it != im.end() ) {
//                     std::cout << i << ": " << *(im.find(i)) << "\n";
                   ++num_set;
                   if( *it != i ) {
                       std::cout << "meeeep: " << i << " " << *it << "\n";
                       getchar();
                   }
                }
            }
            
            std::cout << "num: " << num_set << "\n";
        }
        
//         getchar();
    }
    im.set(32, 32);
    im.set(2, 2);
    std::cout << "get: " << *(im.find(2)) << "\n";
    
    im.remove(2);
    std::cout << "get: " << *(im.find(32)) << "\n";
#endif
}
#endif
