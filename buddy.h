#ifndef BUDDY_H
#define BUDDY_H
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <array>

#include <vector>
#include <memory>
#include <cassert>

namespace buddy {
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
class static_buddy {

public:
    const static size_t num_levels_ = static_log2<Size>::value + 1;
    const static bool dump_split_join = false;

    static_buddy() {
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
        size_t b = make_free_on_level( ml, 0 );

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
    size_t find_free_on_level( size_t level, size_t start ) {

        size_t ls = level_size(level);
        for( size_t i = start; i < ls; ++i ) {
            if( get( level, i ) ) {
                return i;
            }
        }

        return size_t(-1);

    }


    size_t make_free_on_level( size_t level, size_t start ) {

        if( level >= num_levels_ ) {
            return size_t(-1);
        }

        size_t b = find_free_on_level( level, start );

        if( b != size_t(-1) ) {
            set( level, b, false );
            return b;
        }

        size_t nlb = make_free_on_level( level + 1, b * 2 );

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

template<size_t Size>
class dynamic_buddy {
    typedef static_buddy<Size> bb_type;
    typedef std::unique_ptr<bb_type> bb_ptr;

public:

    size_t allocate() {
        size_t bb_num = -1;
        size_t b_num = -1;


        for( size_t i = 0; i < bbs_.size(); ++i ) {
            if( bb_num_alloc_[i] < Size ) {
                bb_num = i;
                b_num = bbs_[i]->allocate( 1 );
                ++bb_num_alloc_[i];
            }
        }

        if( bb_num == size_t(-1)) {
            bbs_.emplace_back( new bb_type() );
            bb_num_alloc_.emplace_back(1);

            bb_num = bbs_.size() - 1;
            b_num = bbs_.back()->allocate( 1 );
        }

        return bb_num * Size + b_num;

    }

    void deallocate( size_t b ) {
        size_t bb_num = b % Size;
        size_t b_num = b / Size;

        assert( bb_num < bbs_.size() );
        assert( b_num < Size );

        bbs_[bb_num]->deallocate( b_num, 1 );
        --bb_num_alloc_[bb_num];
    }

private:
    std::vector<bb_ptr> bbs_;
    std::vector<size_t> bb_num_alloc_;

};

//template<size_t Size>
//class bitmap_tree {
//    const static size_t num_levels_ = static_log2<Size>::value + 1;
//public:
//    bitmap_tree() {
//        for( size_t i = 0; i < num_levels_; ++i ) {
//            level_offset_[i] = level_offset_calc(i);
//            level_size_[i] = level_size_calc(i);
//            block_size_[i] = block_size_calc(i);
//        }

//    }

//    size_t allocate() {
//        size_t level_size = 2;
//        size_t offset = 0;

//        while(true) {
//            for( size_t i = 0; i < 2; ++i ) {
//                if( !bs_[offset + i] ) {
//                    offset += level_size + ;
//                }
//            }
//        }
//        if( bs_[0] ) {
//            return size_t(-1);
//        }
//        ++level;
//        size_t offset = 0;
//        for( ; level < num_levels_; ++level ) {
//            size_t lo = level_offset(level);
//            offset *= 2;

//            if( !bs_[lo + offset] ) {
//                continue;
//            } else if( !)

//        }
//    }

//private:
//    bool get( size_t level, size_t off ) {
//        if( off >= level_size( level ) ) {
//            throw std::runtime_error( "offset out of range" );
//        }
//        return bs_[level_offset( level ) + off];
//    }

//    void set( size_t level, size_t off, bool v ) {
//        if( off >= level_size( level ) ) {
//            throw std::runtime_error( "offset out of range" );
//        }
//        bs_[level_offset( level ) + off] = v;
//    }

//    size_t level_size_calc( size_t level ) {
//        size_t s = 1;
//        for( size_t i = 0; i < level; ++i ) {
//            s *= 2;
//        }

//        return s;
//    }

//    size_t level_offset_calc( size_t level ) {
//        size_t all_s = 0;
//        for( size_t i = 0; i < level; ++i ) {
//            all_s += level_size_calc( i );
//        }

//        return all_s;
//    }

//    inline size_t level_size( size_t level ) {
//        return level_size_[level];
//    }

//    inline size_t level_offset( size_t level ) {
//        return level_offset_[level];
//    }


//    std::bitset<Size * 2> bs_;
//    std::array<size_t,num_levels_> level_size_;
//    std::array<size_t,num_levels_> level_offset_;
//};

}
#endif // BUDDY_H
