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


template<size_t N>
struct static_log2 {
    const static size_t value = 1 + static_log2<N/2>::value;
    static_assert( static_log2<N/2>::value != 0, "non power of 2" );
};

template<>
struct static_log2<2> {
    const static size_t value = 1;
};

template<>
struct static_log2<1> {
    const static size_t value = 0;
};




template<size_t Size>
class buddy {
public:
    const static size_t num_levels_ = static_log2<Size>::value + 1;
    const static bool dump_split_join = false;
    
    buddy() {
        for( size_t i = 0; i < num_levels_; ++i ) {
            level_offset_[i] = level_offset_calc(i);
            level_size_[i] = level_size_calc(i);
            block_size_[i] = block_size_calc(i);
        }
        
        
        std::cout << "size: " << bs_.size() << "\n";
        for( size_t i = 0; i < num_levels_; ++i ) {
            
            std::cout << "level: " << i << " " << level_size(i) << " " << level_offset( i ) << " " << block_size( i ) << "\n";
        }
        
//         for( size_t i = 1; i <= Size; ++i ) {
//             std::cout << i << " level: " << min_level(i) << "\n";
//         }
        
        bs_[level_offset(num_levels_ - 1)] = true;
    }
    
    
    void print() {
        for( size_t i = 0; i < num_levels_; ++i ) {
            
            std::cout << i << ": " << "\n";
            
            size_t ls = level_size(i);
            for( size_t j = 0; j < ls; ++j ) {
                std::cout << get( i, j ) << " ";
            }
            std::cout << "\n";
        }
        
    }
    
    
     size_t allocate( size_t bs_user ) {
        size_t ml = min_level( bs_user );
        size_t bs = block_size( ml );
        size_t b = make_free_on_level( ml );
        
        assert( b != size_t(-1) );
        return bs * b;
    }
    
    void deallocate( size_t b_user, size_t bs_user ) {
        size_t ml = min_level( bs_user );
        size_t bs = block_size( ml );
        
        size_t b = b_user / bs;
        free_on_level( ml, b );
    }
private:
    
    size_t level_size_calc( size_t level ) {
        size_t s = Size;
        for( size_t i = 0; i < level; ++i ) {
            s /= 2;
        }
        
        return s;
    }
    
    size_t level_offset_calc( size_t level ) {
        size_t all_s = 0;
        for( size_t i = 0; i < level; ++i ) {
            all_s += level_size_calc( i );
        }
        
        return all_s;
    }
    
    size_t block_size_calc( size_t level ) {
        return Size / level_size_calc(level);
    }
    
    
    
    size_t min_level( size_t bs ) {
        size_t level = 0;
        
        if( bs > Size ) {
            throw std::runtime_error( "bad block size" );
        }
        
        while( block_size( level ) < bs ) {
            ++level;
        }
//         while( 
        
        return level;
    }
    size_t find_free_on_level( size_t level ) {
        
        size_t ls = level_size(level);
        for( size_t i = 0; i < ls; ++i ) {
            if( get( level, i ) ) {
                return i;
            }
        }
        
        return size_t(-1);

    }
    
    
    size_t make_free_on_level( size_t level ) {
        
        if( level >= num_levels_ ) {
            return size_t(-1);
        }
        
        size_t b = find_free_on_level( level );
        
        if( b != size_t(-1) ) {
            set( level, b, false );
            return b;
        }
        
        size_t nlb = make_free_on_level( level + 1 );
        
        if( nlb == size_t(-1) ) {
            throw std::runtime_error( "out of memory" );
        }
        
        set( level + 1, nlb, false );
        
        if( dump_split_join ) {
            std::cout << "split " << level + 1 << " " << nlb << "\n";
        }
        assert( get( level, nlb * 2 ) == false );
        //set( level, nlb * 2, false ); must still be false
        set( level, nlb * 2 + 1, true );
        
        return nlb * 2;

    }
    
    
    void free_on_level( size_t level, size_t b ) {
        assert( b < level_size(level) );
        
        
        
        bool have_buddy = level != (num_levels_ - 1);
        size_t buddy = (b % 2) == 0 ? b + 1 : b - 1;
        
        if( have_buddy ) {
            assert( !get( level + 1, b / 2) );
        }
        
        if( have_buddy && get( level, buddy ) ) {
            free_on_level( level + 1, b / 2 );
            set( level, buddy, false );
            if( dump_split_join ) {
                std::cout << "join: " << (level + 1) << " " << (b / 2) << "\n";
            }
        } else {
            
            set( level, b, true );            
        }
        
    }
    
    bool get( size_t level, size_t off ) {
        if( off >= level_size( level ) ) {
            throw std::runtime_error( "offset out of range" );
        }
        return bs_[level_offset( level ) + off];
    }
    
    void set( size_t level, size_t off, bool v ) {
        if( off >= level_size( level ) ) {
            throw std::runtime_error( "offset out of range" );
        }
        bs_[level_offset( level ) + off] = v;
    }
    
   
    
    inline size_t level_size( size_t level ) {
        return level_size_[level];
    }
    
    inline size_t level_offset( size_t level ) {
        return level_offset_[level];
    }
    
    inline size_t block_size( size_t level ) {
        return block_size_[level];
    }
private:    
    std::bitset<Size * 2> bs_;
    std::array<size_t,num_levels_> level_size_;
    std::array<size_t,num_levels_> level_offset_;
    std::array<size_t,num_levels_> block_size_;
    
};


double frand() {
    return rand() / double(RAND_MAX);
}

void test() {
    std::vector< std::pair<size_t,size_t> > abs;
    
    buddy<1024 * 1024> b;

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
    
    test();
    
    
    buddy<32> b;
    
    for( size_t i = 0; i < 32; ++i ) {
        std::cout << "alloc: " << b.allocate(1) << "\n";
        b.print();
    }
    
    
    for( size_t i = 0; i < 16; ++i ) {
        b.deallocate( i, 2 );
        std::cout << "free: " << i << "\n";
        b.print();
    }
    
    
    
}