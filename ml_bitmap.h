#ifndef ML_BITMAP_H
#define ML_BITMAP_H

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

template<typename T>
constexpr size_t size_in_bits() {
    return sizeof(T) * 8;
}

//constexpr size_t num_levels( size_t num_bits, size_t psize ) noexcept {
//    size_t num_levels = 1;
//    while( num_bits > psize ) {
//        num_bits /= psize;
//        ++num_levels;
//    }
//    return num_levels;
//}

constexpr size_t num_bits_on_all_levels( size_t num_bits, size_t psize ) {
    return num_bits <= psize ? psize : num_bits + num_bits_on_all_levels(num_bits/psize, psize);
}

constexpr size_t num_levels( size_t num_bits, size_t psize ) {
    return num_bits <= psize ? 1 : 1 + num_levels(num_bits/psize,psize);
}

constexpr size_t used_on_last_level( size_t num_bits, size_t psize ) {
    return num_bits <= psize ? num_bits : used_on_last_level(num_bits/psize,psize);
}

constexpr size_t num_bits_on_level( size_t level, size_t num_bits, size_t psize ) {
    return level == 0 ? num_bits : num_bits_on_level(level-1, num_bits/psize,psize);
}

template<typename T>
class first_false_bit_fast {
public:
    inline size_t operator()( const T& p ) {
        T mask = 1;
        for( size_t i = 0; i < sizeof(T) * 8; ++i ) {
            if( (p & mask) == 0 ) {
                return i;
            }
            mask <<= 1;
        }

        throw std::runtime_error( "bad call of first_false_bit" );
    }
};

template<>
class first_false_bit_fast<uint8_t> {
public:

    first_false_bit_fast() {
        for( size_t i = 0; i < 255; ++i ) {
            ltable_[i] = first_false_bit(uint8_t(i));
        }
        ltable_[255] = size_t(-1);
    }
    inline size_t operator()( const uint8_t &p ) {
        return ltable_[p];
    }


    static inline size_t first_false_bit( const uint8_t &p ) {

        uint8_t mask = 1;
        for( size_t i = 0; i < sizeof(uint8_t) * 8; ++i ) {
            if( (p & mask) == 0 ) {
                return i;
            }
            mask <<= 1;
        }

        throw std::runtime_error( "bad call of first_false_bit" );
    }
public:
    std::array<size_t, 256> ltable_;
};

template<>
class first_false_bit_fast<uint16_t> {
public:
    const static size_t table_size = (256 * 256);
    first_false_bit_fast() {
        for( size_t i = 0; i < table_size - 1; ++i ) {
            ltable_[i] = first_false_bit(uint16_t(i));
        }
        ltable_[table_size - 1] = uint8_t(-1);
    }
    inline size_t operator()( const uint16_t &p ) {
        return size_t(ltable_[p]);
    }


    static inline uint8_t first_false_bit( const uint16_t &p ) {

        uint16_t mask = 1;
        for( size_t i = 0; i < sizeof(uint16_t) * 8; ++i ) {
            if( (p & mask) == 0 ) {
                assert( i < std::numeric_limits<uint8_t>::max());
                return uint8_t(i);
            }
            mask <<= 1;
        }

        throw std::runtime_error( "bad call of first_false_bit" );
    }
public:
    std::array<uint8_t, table_size> ltable_;
};


template<>
class first_false_bit_fast<uint32_t> {
public:
    first_false_bit_fast<uint16_t> ffb16;
    inline size_t operator()( const uint32_t &p ) {
#if 0
        const uint32_t v = ~p;
        // find the number of trailing zeros in v
        static const int Mod37BitPosition[] = // map a bit value mod 37 to its position
        {
          32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4,
          7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5,
          20, 8, 19, 18
        };
        return Mod37BitPosition[(-v & v) % 37];
#elif 0
        unsigned int v = ~p;      // 32-bit word input to count zero bits on right
        unsigned int c = 32; // c will be the number of zero bits on the right
        v &= -signed(v);
        if (v) c--;
        if (v & 0x0000FFFF) c -= 16;
        if (v & 0x00FF00FF) c -= 8;
        if (v & 0x0F0F0F0F) c -= 4;
        if (v & 0x33333333) c -= 2;
        if (v & 0x55555555) c -= 1;

        return c;
#else
        auto low = p & 0xFFFF;
        auto high = (p & 0xFFFF0000) >> 16;

        if( low != 0xFFFF ) {
            return ffb16(low);
        } else if( high != 0xFFFF ){
            return 16 + ffb16(high);
        } else {
            throw std::runtime_error( "bad call of first_false_bit" );
        }
#endif
    }
};

template<size_t num_bits>
class ml_bitmap {
    //typedef uint8_t ptype;
    typedef uint16_t ptype;
    //typedef uint32_t ptype;
    static constexpr size_t nbp = size_in_bits<ptype>();
    static constexpr size_t nlevels = num_levels(num_bits, nbp);
    static constexpr size_t num_bits_all = num_bits_on_all_levels(num_bits, nbp);
    static constexpr size_t num_p_all = num_bits_all / nbp;
    first_false_bit_fast<ptype> first_false_bit_;
public:
    ml_bitmap() {
        raw_.fill(0); // necessary? there does not seem to be value initialization for array elements.

        auto offs = size_t();
        //size_t offs = 0;
        //for( int i = nlevels - 1; i >= 0; --i ) {
        for( size_t i = 0; i < nlevels; ++i ) {
            assert( offs % nbp == 0 );
            level_offset_[i] = offs / nbp;
            assert( (offs + num_bits_on_level(i, num_bits, nbp)) / nbp <= num_p_all );

            // on the last level not all off the bits in the pblock are used
            // we still have to increment offset by the full size of the pblock.
            offs += std::max(num_bits_on_level(i, num_bits, nbp), size_t(nbp));

            std::cout << "level offset: " << level_offset_[i] << " " << num_bits_on_level(i, num_bits, nbp) << "\n";

            if( i == nlevels - 1 ) {
                size_t bits_last_level = num_bits_on_level(i, num_bits, nbp);
                std::cout << "last level: " << bits_last_level << "\n";

                ptype &ll = raw_[level_offset_[i]];

                for( size_t j = bits_last_level; j < nbp; ++j ) {
                    set_bit(ll, j);
                }
                print_bits(ll);
            }
        }
    }

    size_t allocate() {

        size_t false_bit = -1;

#define STORE_LEVEL_P

#ifdef STORE_LEVEL_P
        std::array<size_t, nlevels> level_p;
#endif
        std::array<size_t, nlevels> level_false_bit;

        //size_t in_level_offset = 0;
        size_t offset_all = 0;
        for( size_t i = 0; i < nlevels; ++i ) {
            const size_t level = nlevels - i - 1;

            // the overall offset of the bit on the last level equals the
            // offset of the 'primitive block' on the current level.
            const size_t pblock_offset = level_offset_[level] + offset_all;
#ifdef STORE_LEVEL_P
            level_p[level] = pblock_offset;
#endif
       //     assert( level_p[level] < raw_.size());

            ptype &p = raw_[pblock_offset];
#if 0
            if( i == 0 ) {
                print_bits(p);
            }
#endif
            if( !has_false_bit(p) ) {
                std::cout << "break on level " << level << "\n";
                print_bits(p);
                return size_t(-1);
            }

            false_bit = first_false_bit_(p);
//            std::cout << "false on level " << level << " " << false_bit << "\n";
            level_false_bit[level] = false_bit;

            // overall offset of the current bit
            offset_all *= nbp;
            offset_all += false_bit;
        }

        const auto offset_return = offset_all;
        for( size_t level = 0; level < nlevels; ++level ) {
#ifdef STORE_LEVEL_P
            const size_t pblock_offset = level_p[level];
#else
            offset_all /= nbp;
            const size_t pblock_offset = level_offset_[level] + offset_all;
#endif
            ptype &p = raw_[pblock_offset];
            //   ptype &p = raw_[level_p[level]];

            set_bit(p, level_false_bit[level]);

  //          std::cout << "set on level " << level << " " << level_false_bit[level] << "\n";
   //         print_bits(p);
            if( has_false_bit(p) ) {
                break;
            }
        }
        return offset_return;
    }

    bool deallocate( size_t bit ) {
        for( size_t level = 0; level < nlevels; ++level ) {
            size_t level_bit = bit % nbp;
            bit /= nbp;
            const size_t pblock_offset = level_offset_[level] + bit;

            ptype &p = raw_[pblock_offset];
            //   ptype &p = raw_[level_p[level]];

            if( level == 0 && !get_bit(p, level_bit)) {
                return false;
            }

            clear_bit(p, level_bit);
        }
        return true;
    }

    size_t size() const {
        return num_bits;
    }
private:
    static inline void clear_bit( ptype &p, size_t bit ) {
        p = p & ~(ptype(1) << bit);
    }

    static inline void set_bit( ptype &p, size_t bit ) {
        p = p | (ptype(1) << bit);
    }

    static inline bool get_bit( const ptype &p, size_t bit ) {
        return (p & (ptype(1) << bit)) != 0;
    }

    static inline bool has_false_bit( const ptype &p ) {
        return p != ptype(-1);
    }


    static inline size_t first_false_bit( const ptype &p ) {

        ptype mask = 1;
        for( size_t i = 0; i < nbp; ++i ) {
            if( (p & mask) == 0 ) {
                return i;
            }
            mask <<= 1;
        }

        throw std::runtime_error( "bad call of first_false_bit" );
    }

    void print_bits( ptype &p ) {
        for( size_t i = 0; i < nbp; ++i ) {
            std::cout << get_bit(p, i);
        }
        std::cout << "\n";
    }

    std::array<ptype, num_p_all> raw_;
    std::array<size_t, nlevels> level_offset_;
};

#endif // ML_BITMAP_H

