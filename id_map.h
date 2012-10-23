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
    typedef typename std::array<Value, max_num>::const_iterator const_iterator;
    
    
    inline iterator end() {
        return values_.end();
    }
    inline const_iterator end() const {
        return values_.end();
    }
  
    template<typename... Args>
    inline bool emplace( size_t id, Args&&... args) {
        
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
//             std::cout << "replace\n";
            values_[idx] = Value(std::forward<Args>(args)...);
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
            std::move_backward( it, end, end+1 );
            
            values_[idx] = Value(std::forward<Args>(args)...);
        }
        
        return true;
//          std::cout << "bits: " << id << " " << mask << "\n";
    }
    
    // CHECK: did I understand this correctly: implementing const & and && setter in terms of emplace is 'the right thing' in c++11?
//     inline bool set( size_t id, Value &&v ) {
//         return emplace( id, std::move(v));
//     }
    
    
    
//     inline bool set( size_t id, const Value &v ) {
//         std::cout << "copy set\n";
//         return emplace( id, v );
//     }

// CHECK2: can this thing really replace all setters?
    template<typename T1>
    inline bool set( size_t id, T1 &&v ) {
//         std::cout << "forward\n";
        return emplace( id, std::forward<T1>(v));
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
    inline const_iterator find( size_t id ) const {
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
    inline size_t popcount( uint32_t f ) const {
        return __builtin_popcount(f);
    }
    inline size_t popcount( uint64_t f ) const {
        return __builtin_popcountll(f);
    }
    inline uint64_t id_mask( size_t id ) const {
        return bitfield_t(1) << (id + 1);
    }
    
    inline size_t index( size_t id ) const {
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
    
    
    
    template<typename... Args>
    inline bool emplace( size_t id, Args&&... args) {
        assert( id <= max_id());
        bitfield_t mask = id_mask(id);
        
        size_t idx = index(id);
        
        if( (bits_ & mask) != 0 ) {
//             std::cout << "replace\n";
            
            values_[idx] = Value(std::forward<Args>(args)...);
        } else {
            bits_ |= mask;
            auto it = values_.begin() + idx;
            
           // values_.emplace(it, std::move(v));
            values_.emplace(it, std::forward<Args>(args)...);
        }
        
        return true;
    }
    
    // CHECK: did I understand this correctly: implementing const & and && setter in terms of emplace is 'the right thing' in c++11?
//     inline bool set( size_t id, Value &&v ) {
//         return emplace( id, std::move(v));
//     }
    
    
    
//     inline bool set( size_t id, const Value &v ) {
//         std::cout << "copy set\n";
//         return emplace( id, v );
//     }

// CHECK2: can this thing really replace all setters?
    template<typename T1>
    inline bool set( size_t id, T1 &&v ) {
//         std::cout << "forward\n";
        return emplace( id, std::forward<T1>(v));
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
    typedef typename std::array<Value,num_slots>::const_iterator const_iterator;
    
    id_map_vanilla() {
        std::fill( used_.begin(), used_.end(), false );
        
    } 
    template<typename... Args>
    inline bool emplace( size_t id, Args&&... args) {
        used_[id] = true;
        slots_[id] = Value(std::forward<Args>(args)...);
        
        return true;
//          std::cout << "bits: " << id << " " << mask << "\n";
    }
    

// CHECK2: can this thing really replace all setters?
    template<typename T1>
    inline bool set( size_t id, T1 &&v ) {
//         std::cout << "forward\n";
        return emplace( id, std::forward<T1>(v));
    }
    
    
    
    inline iterator find( size_t id ) {
        if( !used_[id] ) {
            return slots_.end();
        } else {
            return slots_.begin() + id;
        }
    }
    inline const_iterator find( size_t id ) const {
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
    inline const_iterator end() const {
        return slots_.end();
    }
    
private:
    std::array<uint8_t,num_slots> used_;
    std::array<Value,num_slots> slots_;
    
};

#endif
