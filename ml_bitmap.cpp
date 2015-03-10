#include <cstdint>
#include <cstddef>
#include <cassert>
#include <limits>
#include <set>
#include <unordered_set>

#include <iostream>
#include <array>
#include <stdexcept>
#include <memory>
#include "ml_bitmap.h"


void test1() {
    typedef ml_bitmap<1024*1024> bitmap_type;
    std::unique_ptr<bitmap_type> mlb{std::make_unique<bitmap_type>()};

    std::set<size_t> check_set;

    size_t n = 0;
    while( true) {
        auto a = mlb->allocate();

        if( a == size_t(-1)) {
            break;
        }

        if( !check_set.insert(a).second ) {
            throw std::runtime_error( "xxx1" );
        }
        ++n;
    }

    std::cout << "n: " << n << "\n";


    for( size_t i = 0; i < mlb->size(); i += 2 ) {

        auto ele = rand() % mlb->size();
        bool b = mlb->deallocate( ele );

        if( b ) {
            check_set.erase(ele);
        }
    }

    n = 0;
    while( true) {
        auto a = mlb->allocate();

        if( a == size_t(-1)) {
            break;
        }

        if( !check_set.insert(a).second ) {
            throw std::runtime_error( "xxx2" );
        }
        ++n;
    }

    std::cout << "n: " << n << "\n";

}

int main() {
    test1();
#if 0

    const size_t num_bits = 1024 * 1024;
    const size_t ptsize = size_in_bits<uint64_t>();
    auto nl = num_levels(num_bits, size_in_bits<uint64_t>() );
    auto ull = used_on_last_level(num_bits, size_in_bits<uint64_t>() );
    std::cout << "nl: " << nl << " " << ull << "\n";

    size_t nbalx = 0;
    for( size_t i = 0; i < nl; ++i ) {
        size_t nbl = num_bits_on_level(i, num_bits, size_in_bits<uint64_t>());
        nbalx += std::max(nbl, ptsize);
        std::cout << "level: " << i << " " << num_bits_on_level(i, num_bits, size_in_bits<uint64_t>()) << "\n";
    }

    std::cout << "all levels: " << nbalx << " " << num_bits_on_all_levels(num_bits, ptsize) << "\n";
#endif
    typedef ml_bitmap<1024 * 1024 * 128> bitmap_type;
    std::unique_ptr<bitmap_type> mlb{std::make_unique<bitmap_type>()};

//    for( size_t i = 0; i < mlb.size(); ++i ) {
//        auto a = mlb.alloc();
//        std::cout << "alloc: " << a << "\n";
//    }
    size_t n = 0;
    while( mlb->allocate() != size_t(-1)) {
        ++n;
    }

    std::cout << "n: " << n << "\n";
}
