/*
 * Copyright (C) 2011 Simon A. Berger
 *
 *  This program is free software; you may redistribute it and/or modify its
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 */

#include <thread>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <cassert>




class runnable {
public:
    virtual void operator()() = 0;
};



class pool {

public:
    pool() : wait_empty_(0) {}
    
    void put( std::unique_ptr<runnable> r ) {
     
        std::unique_lock<std::mutex> lock(mtx_);
        
        
        queue_.push_back(std::move(r));
        
        if( queue_.size() == 1 ) {
         
            lock.unlock();
            cond_.notify_one();
        }
        
    }
    
    std::unique_ptr<runnable> get() {
        std::unique_lock<std::mutex> lock(mtx_);
        
        while(queue_.empty() && wait_empty_ > 0 ) {
            cond_.wait(lock);
            
        }

        if( queue_.empty() ) {
            return std::unique_ptr<runnable>(nullptr);
        }
       
       
        auto front = std::move(queue_.front());
        queue_.pop_front();
        return front;
    }
    
    void inc_wait_empty() {
     
        std::lock_guard<std::mutex> lock(mtx_);
        wait_empty_++;
        
    }
    
    void dec_wait_empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        
        assert( wait_empty_ > 0 );
        wait_empty_--;
        
        if( wait_empty_ == 0 ) {
            cond_.notify_all();
        }
    }
private:
    
    std::deque<std::unique_ptr<runnable> > queue_;
    std::mutex mtx_;
    std::condition_variable cond_;
    
    int wait_empty_;
    
};


class pool_keeper {
  
public:
    pool_keeper( pool * p ) : pool_(p) {
        pool_->inc_wait_empty();
    }

    ~pool_keeper() {
        pool_->dec_wait_empty();
    }
private:
    pool *pool_;
};

// template<typename t>
// std::unique_ptr<t> make_unique( t * ptr ) {
//     return std::unique_ptr<t>(ptr);
// }

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args... args) {
 
    return std::unique_ptr<T>( new T(args...));
}

class worker {
    
public:
    worker( pool *p, int rank ) : pool_(p), rank_(rank) {}
    
    void operator()() {
     
        std::cout << "start worker: " << rank_ << "\n";
        while( true ) {
         
            std::unique_ptr<runnable> rp( pool_->get() );
            
            if( rp.get() == nullptr ) {                    
                std::cout << "worker exit: " << rank_ << "\n";
                return;
            }
            std::cout << "worker: " << rank_ << "\n";
            (*rp)();
        }
    }
private:
    pool *pool_;
    int rank_;
};

class work : public runnable {
    
public:
    work( int v ) : v_(v) {};
    void operator()() {
     
        
        std::vector<int> v(1024 * 1024 * 1, 666);
        
        size_t acc = std::accumulate( v.begin(), v.end(), 0 );
    
        
        std::cout << "work: " << v_ << " " << acc << "\n";
    }
private:
    int v_;
};

class thread_group {
public:
    template<typename Callable,typename... Args>
    void create_thread(Callable func,Args... args) {
        threads_.push_back( std::thread( func, args... ));
    }
    
    void join_all() {
     
        for( std::thread & thread : threads_ ) {
            thread.join();
        }
    }
    
private:
    std::vector<std::thread> threads_;
};

int main() {
    
    
    thread_group tg;
    pool p;
    {
        
        pool_keeper pk(&p);
        
        for( int i = 0; i < 2; ++i ) {
            tg.create_thread( worker( &p, i ) );
            
        }
        for( int i = 0; i < 10; ++i ) {
            p.put( make_unique<work>(i) );
        }
    }
    tg.join_all();
}
