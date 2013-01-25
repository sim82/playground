// #include <boost/thread.hpp>
#include <thread>
#include <future>
#include <vector>
#include <deque>
#include <iostream>


int main( int argc, char *argv[] ) {
    
    std::deque<std::future<int>> res;
    
    for( size_t i = 0; i < 10; ++i ) {
        auto result = std::async(std::launch::async, [=]() {
            size_t res = 3 + i;
            
            for( size_t j = 0; j < argc * 10000000000; ++j ) {
                res *= size_t(argv[0]);
                
            }
            
            return int(res);
        });
        
        res.push_back( std::move(result));
        
    }
    
    
    while( !res.empty() ) {
        int r = res.front().get();
        res.pop_front();
        std::cout << "get " << r << "\n";
    }
    
   
}