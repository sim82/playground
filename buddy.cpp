/*
 * Copyright (C) 2013 Simon A. Berger
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

#include <sys/time.h>

#include <bitset>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
#include "time.h"
#include "cycle.h"
#include "buddy.h"

double ivy_mike::perf_timer::my_getticks() {
#if defined(WIN32) && !defined(_M_X64)
        return double(getticks().QuadPart);
#else
        return double(getticks());
#endif
}

double ivy_mike::gettime(void )
{
#ifdef WIN32
    static bool g_pc_valid = false;
    static LARGE_INTEGER g_pc_freq;

        if( !g_pc_valid ) {
                QueryPerformanceFrequency( &g_pc_freq );
                g_pc_valid = true;
        } 
        LARGE_INTEGER pcv;
        QueryPerformanceCounter( &pcv );
        return pcv.QuadPart / double(g_pc_freq.QuadPart);
        
#else
        struct timeval ttime;
        gettimeofday(&ttime , 0);
        return ttime.tv_sec + ttime.tv_usec * 0.000001;
#endif
}


using namespace buddy;

double frand() {
    return rand() / double(RAND_MAX);
}

void test() {
    std::vector< std::pair<size_t,size_t> > abs;
    
    static_buddy<1024 * 1024> b;

    ivy_mike::timer t;
    
    size_t num_alloc = 0;
    size_t num_free = 0;
    size_t num_oom = 0;
    size_t size_alloc = 0;
    while( true ) {
        
        if( t.elapsed() >= 1.0 ) {
            std::cout << "num: " << num_alloc << " " << num_free << " " << num_oom << " " << abs.size() << " === " << size_alloc << "\n";
            num_alloc = num_free = num_oom = 0;
            t = ivy_mike::timer();
            
        }
        if( frand() < 0.5 ) {
            const size_t bs_max = 345;
            size_t bs = 2 + (rand() % bs_max);
            
            try {
                size_t block = b.allocate( bs );
            
                size_alloc += bs;
//                 b.print();
                abs.push_back( std::make_pair( block, bs ) );
                ++num_alloc;
            } catch( std::runtime_error x ) {
                ++num_oom;
           //     std::cout << "out of memory: " << bs << "\n";
//                 getchar();
            }
            
        } else {
            if( abs.empty() ) {
                continue;
            }
               
               
            auto it = abs.begin() + (rand() % abs.size());
            
            
            b.deallocate( it->first, it->second );
            size_alloc -= it->second;
            ++num_free;
            
            abs.erase(it); 
            /*
            if( abs.size() > 1 ) {
                *it = abs.back();
            }
            abs.erase(abs.end() - 1);
            */
        }
        
    }
    
}

int main() {
    std::cout << "log2: " << static_log2<32>::value << "\n";
    
   // test();
    
    
    static_buddy<32> b;
    
    for( size_t i = 0; i < 33; ++i ) {
        std::cout << "alloc: " << b.allocate(1) << "\n";
        b.print();
    }
    
    
    for( size_t i = 0; i < 32; ++i ) {
        b.deallocate( i, 1 );
        std::cout << "free: " << i << "\n";
        b.print();
    }
    
    
    
}
