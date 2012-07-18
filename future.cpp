#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <algorithm>

std::vector<char> xxx( int x ) {
    return std::vector<char>( 1024, char(x) );
}

void exec( std::packaged_task<std::vector<char>(int)>  & t ) {
    t(666);
}

int main2() {
    
    typedef std::packaged_task<std::vector<char>(int)> my_task;
    typedef std::future<std::vector<char>> my_future;
    
//     my_task t(xxx);
    
    const size_t num = 1024 * 1024;
    std::vector<my_task> tasks;
    while( tasks.size() < num ) {
        tasks.emplace_back(xxx);
    }
    
    
    std::vector<my_future> futs;
    
    std::for_each( tasks.begin(), tasks.end(), [&](my_task &t) { return futs.emplace_back(t.get_future()); } );
    
    
    
    
    std::for_each( tasks.begin(), tasks.end(), []( my_task &t ) { t(666); });
//     exec(tasks.front());
    
    
   
    
    std::cout << futs.front().get().size() << "\n";
    getchar();
    
    return 0;
}


int main() {
    
 //   typedef std::packaged_task<std::vector<char>(int)> my_task;
    typedef std::future<std::vector<char>> my_future;
    
//     my_task t(xxx);
    
    const size_t num = 10;//1024 * 1024;
    
    
    
    std::vector<my_future> futs;
    
    for( size_t i = 0; i < num; ++i ) {
        futs.push_back( std::async( std::launch::async, xxx, 666) );
    }
    
     
   
    
    std::cout << futs.front().get().size() << "\n";
    getchar();
    
    return 0;
}
