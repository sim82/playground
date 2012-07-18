#ifndef __id_map_h
#define __id_map_h

#include <cstddef>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <array>
#include <algorithm>


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
class id_map_dynamic {
public:
    typedef uint64_t bitfield_t;
    
    id_map_dynamic() 
     : bits_(0)
    {
        
    }
    
    typedef typename std::vector<Value>::iterator iterator;
    typedef typename std::vector<Value>::const_iterator const_iterator;
    
    inline const_iterator end() const {
        return values_.end();
    }
    
    inline iterator end() {
        return values_.end();
    }
    
    inline bool set( size_t id, Value &&v ) {
        
        assert( id <= max_id());
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
//             std::cout << "replace\n";
            values_[idx] = std::move(v);
        } else {
            bits_ |= mask;
            auto it = values_.begin() + idx;
            
            values_.emplace(it, std::move(v));
        }
        
        return true;
//          std::cout << "bits: " << id << " " << mask << "\n";
    }
    
    inline bool set( size_t id, const Value &v ) {
        assert( id <= max_id());
#if 1
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
#endif
    }
    
    inline void remove( size_t id ) {
        assert( id <= max_id());
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
            bits_ &= ~mask;
            auto it = values_.begin() + idx;
            values_.erase( it );
        }
    }
    
    inline const_iterator find( size_t id ) const {
        assert( id <= max_id());
        bitfield_t mask = id_mask(id);
        
        if( (bits_ & mask) == 0 ) {
            //throw std::runtime_error( "bad id" );
            
            return values_.end();
        } 
        
        size_t idx = index(id);
        
//         std::cout << "find: " << id << " " << idx << "\n";
        
        return values_.begin() + idx;
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
    
    inline uint64_t id_mask( size_t id ) const {
        return bitfield_t(1) << (id + 1);
    }
    
    inline size_t index( size_t id ) const {
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
