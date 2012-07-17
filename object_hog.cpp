#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include "ivymike/time.h"

int main() {
    std::vector<std::vector<char> > bufs;
    
    
    bool alloc = true;
    size_t size = 0;
    size_t num_allocs = 0;
    size_t last_allocs = 0;
    const size_t low_size =  128 * 1024 * 1024;
    const size_t high_size = size_t(low_size * 1.1);
    
    ivy_mike::timer t1;
    
    while( true ) {
        
        
        if( t1.elapsed() > 5.0 ) {
            
            std::cout << "alloc: " << size * 1.0e-6 << " MB " << num_allocs - last_allocs << "\n";
            t1 = ivy_mike::timer();
            last_allocs = num_allocs;
        }
        
        ++num_allocs;
        
        if( alloc ) {
            const size_t as = (rand() % 1024) * 16;
            
            bufs.emplace_back( as );
            std::fill( bufs.back().begin(), bufs.back().end(), char(size) );
            
            size += as;
            
            if( size > high_size ) {
                alloc = false;
            }
        } else {
            const size_t re = rand() % bufs.size();
            
            std::vector<std::vector<char> >::iterator it = bufs.begin() + re;
            assert( it < bufs.end() );
            
            size -= it->size();
            
            bufs.erase( it );
            
            
            
            if( size < low_size ) {
                alloc = true;
            }
        }
        
        
    }
    
    
}