#include <cstdlib>
#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>


#include "cycle.h"

int main() {
    
    std::vector<double> fracs = { 0.1, 0.5, 0.9, 0.95, 0.99, 0.995, 0.999, 0.9995, 0.9999, 0.99995 };
    
    
    for( double frac : fracs ) {
//         std::cout << "frac: " << frac << "\n";
        
        const size_t n = 1024 * 1024 * 10;
        const size_t m = 10;
        
        boost::dynamic_bitset<> bs(n);
        std::vector<bool> bv(n); 
        for( size_t i = 0; i < n; ++i ) {
            bool b = (rand() / double(RAND_MAX)) > frac;
            
            bs[i] = b;
            bv[i] = b;
            
        }
        
        
        ticks t1 = getticks();
        size_t count1 = 0;
        
        //std::cout << "start:\n";
        for( size_t o = 0; o < m; ++o ) {
            size_t i = bs.find_first();
            
            while( i < bs.npos ) {
                ++count1;
                i = bs.find_next(i);
            }
        }
        ticks t2 = getticks();
        //std::cout << "count: " << count << "\n";
        
        size_t count2 = 0;
        for( size_t o = 0; o < m; ++o ) {
//             for( size_t i = 0; i < n; ++i ) {
//                 if( bs[i] ) {
//                     ++count2;
//                 }
//             }
            for( bool b : bv ) {
                if( b ) {
                    ++count2;
                }
            }


        }
        ticks t3 = getticks();
//         std::cout << "count: " << count << "\n";
        
        std::cout << 1-frac << " " << elapsed(t2, t1) << " " << elapsed( t3, t2 ) << " " << count1 << " " << count2 << "\n";
    }
}