/*
 * reverse_bits.cpp
 *
 *  Created on: 15/11/2011
 *      Author: sim
 */


#include <array>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>

#include <cstdint>
#include <cstdlib>
#include <cassert>

typedef unsigned long long ticks;

static __inline__ ticks getticks(void)
{
     unsigned a, d;
     asm volatile("rdtsc" : "=a" (a), "=d" (d));
     return ((ticks)a) | (((ticks)d) << 32);
}



std::array<uint8_t,256> rev_table() {
    std::array<uint8_t,256> rev;

    for( size_t i = 0; i < rev.size(); ++i ) {
        uint8_t t = i;
        rev[i] = 0;
        for( size_t j = 0; j < 8; ++j ) {
            rev[i] |= (t&1) << (7-j);
            t >>= 1;
        }

    //    std::cout << i << " " << int(rev[i]) << "\n";

    }

    return rev;
}

const static size_t p16 = 256 * 256;
std::array<uint16_t,p16> rev_table( std::array<uint8_t,256> rev8 ) {
    std::array<uint16_t,p16> rev;

    for( size_t i = 0; i < rev8.size(); ++i ) {
        for( size_t j = 0; j < rev8.size(); ++j ) {
            rev[i*256 + j] = uint16_t(rev8[i]) << 8 | rev8[j];

  //          std::cout << i * 256 + j << " " << int(rev[i * 256 + j]) << "\n";
        }



    }

    return rev;
}

template<typename T, size_t len>
class arr_trans {
public:
    arr_trans( const std::array<T,len> &a ) : a_(a) {}

    T operator()( T v ) {
        return a_[v];
    }

private:
    const std::array<T,len> &a_;
};



int funcx( int v ) {
    int v0 = v;

    v = 1 | (v0&16) >> 3 | (v0&16) >> 2 | (v0 & 2) << 3;

    return v;
}

int main() {

    std::cout << funcx(17) << " " << funcx(7) << "\n";


    std::array<uint8_t,256> rev = rev_table();
    std::array<uint16_t,p16> rev16 = rev_table(rev);

    std::vector<uint8_t> arr( 1000 * 1000 );
    std::generate(arr.begin(), arr.end(), rand );


    std::vector<uint8_t> arrt1_8( 1000 * 1000 );
    std::vector<uint8_t> arrt1_16( 1000 * 1000 );


    ticks t0 = getticks();

    if(true)
    {
        for( size_t i = 0; i < 5000; i++ ) {
            std::transform( arr.begin(), arr.end(), arrt1_8.begin(), arr_trans<uint8_t,256>(rev) );
            //std::transform( arrt1_8.begin(), arrt1_8.end(), arrt2.begin(), arr_trans<uint8_t,256>(rev) );
            //std::cout << "equal: " << std::equal( arr.begin(), arr.end(), arrt2.begin() ) << "\n";
        }
    }
    ticks t1 = getticks();
    if(true)
    {

        assert( arr.size() % 2 == 0);

        for( size_t i = 0; i < 5000; i++ ) {



            uint16_t *s_start = (uint16_t*)arr.data();
            uint16_t *s_end = s_start + (arr.size() / 2);
            uint16_t *d16 = (uint16_t*)arrt1_16.data();

            std::transform( s_start, s_end, d16, arr_trans<uint16_t,p16>(rev16) );

            //std::transform( arrt1.begin(), arrt1.end(), arrt2.begin(), arr_trans<uint16_t,p16>(rev16) );

//            std::cout << "equal2: " << std::equal( arr.begin(), arr.end(), arrt2.begin() ) << "\n";
        }
    }
    ticks t2 = getticks();
    std::cout << "equal 8/16: " << std::equal( arrt1_8.begin(), arrt1_8.end(), arrt1_16.begin() ) << "\n";

    double dt1 = t1 - t0;

    double dt2 = t2 - t1;

    std::cout << "ticks: " << t1 - t0 << " " << t2 - t1 << " " << dt2 / dt1 << "\n";


}
