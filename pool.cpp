#include <thread>
#include <iostream>
#include <deque>

#include <condition_variable>
#include <mutex>

#include <cassert>

class test {
    int m_v;
public:
    test( int v ) : m_v(v) {}
    
    void operator()() {
          
        std::cout << "run" << m_v << "\n";
        
        usleep(20000);
    }
};

template<typename runnable>
class pool {
  
    std::deque<runnable> queue_;
    
    std::mutex mtx_;
    std::condition_variable cond_;
    
public:
    void put( runnable && r ) {
     
        std::lock_guard<std::mutex> lock(mtx_);
        
        queue_.push_back(r);
        
       
        cond_.notify_all();
    }
    
    runnable get() {
     
        std::unique_lock<std::mutex> lock( mtx_ );
        
        while( queue_.empty() ) {
            cond_.wait(lock);
        }
        
        assert( !queue_.empty() );
        
    
        runnable r = std::move(queue_.back());
        queue_.pop_back();
        return r;
    }
    
    
    
};


template<typename runnable>
class worker {
    
    const size_t m_rank;
public:
    
    worker( size_t rank ) : m_rank(rank) {}
    
    void operator()( pool<runnable> * m_queue ) {
        
        while( true ) {
         
            runnable r = m_queue->get();
            
            std::cout << "worker: " << m_rank << "\n";
            
            r();
        }
        
    }
    
};

int main() {
 
   pool<test> p;
   
   std::thread t1( std::move(worker<test>(0)), &p);
   std::thread t2( std::move(worker<test>(1)), &p);
   
   for( int i = 0; i < 10; ++i ) {
      
        p.put( test(i) );
   }
   
   t1.join();
   t2.join();
   
}