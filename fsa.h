#ifndef FSA_H
#define FSA_H

#include <array>
#include <memory>
#include <bitset>
#include <mutex>
#include <cstddef>
#include <cassert>
#include <unordered_map>
#include <atomic>
#include "ml_bitmap.h"


namespace fsa {
class spinlock {
public:
    spinlock() : state_(false) {}
    void lock()
    {
        while (state_.exchange(true, std::memory_order_acquire)) {
          /* busy-wait */
        }
    }
    void unlock()
    {
        state_.store(false, std::memory_order_release);
    }
private:
    std::atomic<bool> state_;
};

#if 0
template<size_t num_blocks = 1024>
class allocator {
    typedef spinlock lock_type;
    //typedef std::mutex lock_type;
public:
    allocator(size_t block_size)
        : block_size_(align<16>(block_size))
        , num_allocated_(0)
        , buf_size_(num_blocks * block_size_)
        , buf_(std::make_unique<char[]>(num_blocks * block_size_))
    {
        std::cout << "allocator: " << block_size_ << " (" << block_size << ")\n";
    }

    template<typename T>
    T *allocate() {
        if( block_size_ < sizeof(T) ) {
            throw std::runtime_error( "bad object size for allocator" );
        }

        std::unique_lock<lock_type> lock(mtx_);
        if( num_allocated_ >= num_blocks ) {
            return nullptr;
        }
        size_t b = bitmap_.allocate();
        ++num_allocated_;

        lock.unlock();

        char *ptr = block_ptr(b);
//        std::cout << "alloc: " << this << " " << ptr << "\n";
        return new(ptr)T();
    }

    char *allocate_raw() {
        std::lock_guard<lock_type> lock(mtx_);
        if( num_allocated_ >= num_blocks ) {
            return nullptr;
        }
        size_t b = bitmap_.allocate();
        ++num_allocated_;
        return block_ptr(b);
    }

    void deallocate_raw( char *ptr ) {
        size_t b = ptr_to_block(ptr);

        std::lock_guard<lock_type> lock(mtx_);
        bitmap_.deallocate(b);
        assert(num_allocated_>0);
        --num_allocated_;
    }

    template<typename T>
    void deallocate( T *ptr ) {
        size_t b = ptr_to_block((char*)ptr);

        ptr->~T();
//        std::cout << "dealloc: " << this << " " << ptr << "\n";
        std::lock_guard<lock_type> lock(mtx_);
        bitmap_.deallocate(b);
        assert(num_allocated_>0);
        --num_allocated_;
    }

private:
    template<size_t a>
    static size_t align(size_t in) {
        if( in % a != 0 ) {
            return (in / a + 1) * a;
        }
        return in;
    }

    inline char *block_ptr( size_t block ) {
        return buf_.get() + block * block_size_;
    }

    inline size_t ptr_to_block( char *ptr ) const {
        auto offs = std::distance(buf_.get(), ptr );
        if( offs < 0 || offs >= static_cast<decltype(offs)>(buf_size_) ) {
            throw std::runtime_error( "ptr out of range for allocator");
        }

        if( offs % block_size_ != 0 ) {
            throw std::runtime_error( "bad ptr alignment for allocator");
        }

        return offs / block_size_;
    }

    ml_bitmap<num_blocks> bitmap_;
    size_t block_size_;
    size_t num_allocated_;
    size_t buf_size_;
    std::unique_ptr<char[]> buf_;

    lock_type mtx_;
};

class allocator_team : public allocator<> {
public:

    allocator_team(size_t size) : allocator(size) {}
};

template<typename T>
class unique_ptr {
public:
    unique_ptr() : ptr_(nullptr) {}

    ~unique_ptr() {
        if( ptr_ != nullptr ) {
            at_->deallocate(ptr_);
        }
    }

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr& operator=(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other ) {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        at_ = other.at_;
    }

    template<typename U>
    unique_ptr(unique_ptr<U> &&other ) {
        ptr_ = other.release();
        at_ = other.get_at();
    }




    unique_ptr &operator=(unique_ptr &&other ) {
        if( ptr_ != nullptr ) {
            at_->deallocate(ptr_);
        }

        ptr_ = other.ptr_;
        at_ = other.at_;
        other.ptr_ = nullptr;

        return *this;
    }
    template<typename U>
    unique_ptr &operator=(unique_ptr<U> &&other ) {
        if( ptr_ != nullptr ) {
            at_->deallocate(ptr_);
        }

        ptr_ = other.release();
        at_ = other.get_at();

        return *this;
    }


    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    const T& operator*() const {
        return *ptr_;
    }

    const T* operator->() const {
        return ptr_;
    }

    T* release() {
        auto tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    allocator_team *get_at() {
        return at_;
    }

    template<typename TDest>
    unique_ptr<TDest>static_cast_move() {
        return unique_ptr<TDest>(static_cast<TDest*>(release()), at_);
    }

    unique_ptr( T* ptr, allocator_team *at ) : ptr_(ptr), at_(at) {}

private:

    friend class allocator_chain;
    T *ptr_;
    allocator_team *at_;
};


class allocator_chain {
    const static size_t alignment = 16;
public:
    template<typename T>
    std::pair<T *, allocator_team *> allocate_old() {
        size_t size = align<alignment>(sizeof(T));

        auto it = allocators_.find(size);

        if( it == allocators_.end()) {
            it = allocators_.emplace(size, std::make_unique<allocator_team>(size)).first;
        }

        allocator_team *a = it->second.get();
        T* ptr = a->allocate<T>();

        return std::make_pair(ptr, a);
    }

    template<typename T>
    unique_ptr<T> allocate() {
        size_t size = align<alignment>(sizeof(T));

        auto it = allocators_.find(size);

        if( it == allocators_.end()) {
            it = allocators_.emplace(size, std::make_unique<allocator_team>(size)).first;
        }

        allocator_team *a = it->second.get();
        T* ptr = a->allocate<T>();

        return unique_ptr<T>(ptr, a);
    }
private:
    template<size_t a>
    static size_t align(size_t in) {
        if( in % a != 0 ) {
            return (in / a + 1) * a;
        }
        return in;
    }
    std::unordered_map<size_t, std::unique_ptr<allocator_team>> allocators_;
};
template<typename Tout, typename Tin>
unique_ptr<Tout> static_cast_move(unique_ptr<Tin> && ptr ) {
    auto * at = ptr.get_at();
    return unique_ptr<Tout>(static_cast<Tout*>(ptr.release()), at);
}

#else
#include <memory>
template<typename T>
using unique_ptr = std::unique_ptr<T>;
class allocator_chain {
public:
    template<typename T>
    unique_ptr<T> allocate() {
        return std::make_unique<T>();
    }
};
template<typename Tout, typename Tin>
unique_ptr<Tout> static_cast_move(unique_ptr<Tin> && ptr ) {
    return unique_ptr<Tout>(static_cast<Tout*>(ptr.release()));
}
#endif

}

#endif // FSA_H

