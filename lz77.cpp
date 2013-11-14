#include <deque>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>

std::pair<size_t,size_t> longest_match( const std::deque<char> &dict, const std::deque<char> &preview ) {


    auto ds = dict.size();
    auto ps = preview.size();

    if( ds == 0 ) {
        return std::make_pair(0,0);
    }

    auto diter = dict.begin();
    auto dlast = dict.end();
    auto plast = preview.end();
    size_t len_max = 0;
    size_t i_max = -1;

    size_t num_iter;
    if( ds >= ps ) {
        num_iter = ds - ps + 1;
    } else {
        num_iter = 1;
    }

    for( size_t i = 0; i < num_iter; ++i, ++diter ) {
        auto diter_inner = diter;
        auto pfirst = preview.begin();
        for( ;pfirst != plast && diter_inner != dlast && *pfirst == *diter_inner; ++pfirst, ++diter_inner ) {

        }
        size_t len = std::distance( preview.begin(), pfirst );
        if( len > len_max ) {
            len_max = len;
            i_max = i;
        }

    }

    return std::make_pair(len_max, i_max);
}

//void buffer_shift( const std::deque<char> &dict, const std::deque<char> &preview, )

int main() {

//    std::ifstream is( "lz77.cpp" );

//    std::string input;
//    input.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());

    std::string input = "abcabcabcqwertyabcabcabc";
    //std::string input = "ANANAS";
    auto first = input.begin();
    auto last = input.end();



    std::deque<char> dict;
    std::deque<char> preview;

    const size_t size_dict = 8;
    const size_t size_preview = 4;

    assert( input.size() >= size_preview );

    for( size_t i = 0; i < size_preview; ++i ) {
        preview.push_back(*first++);
    }

    while( !preview.empty() ) {
        std::string pd( dict.begin(), dict.end() );
        std::cout << std::setw(size_dict) << pd << " | ";

        assert( !preview.empty() );
        std::string ps( preview.begin(), preview.end() );
        std::cout << std::setw(size_preview) << ps << " ";

        auto m = longest_match( dict, preview );




        size_t len = m.first;
        size_t pos = m.second;
        size_t consume = std::min( preview.size(), len + 1 );

        size_t pad = size_dict - dict.size();
        size_t dpos = len > 0 ? pos + pad : 0;

        char output;
        for(size_t i = 0; i < consume; ++i ) {
            dict.push_back(preview.front());
            if( dict.size() > size_dict ) {
                dict.pop_front();
            }

            if( i == len ) {
                output = preview.front();
            }
            preview.pop_front();


            if( first != last ) {
                preview.push_back(*first);
                ++first;
            }
        }

        std::cout << dpos << " " << len << " " << output << "\n";


    }


}
