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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <cassert>
#include <cstring>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include <set>
#include <map>

class mapped_file {
public:
    mapped_file( const char *filename )
      : base_(0)
    {
        int mode = O_RDONLY;



        fd_ = open( filename, mode );
        //assert( fd_ != -1 );
        if( fd_ == -1 ) {
            throw std::runtime_error("cannot open file");
        }


        size_ = lseek( fd_, 0, SEEK_END );
        lseek( fd_, 0, SEEK_SET );

        map();

    }
    size_t size() const {
        return size_;
    }

    void unmap() {
        assert( base_ != 0 );
        munmap( base_, size_ );
        base_ = 0;
    }
    void map() {
        assert( base_ == 0 );
        int prot = PROT_READ;


        base_ = mmap( 0, size_, prot, MAP_SHARED, fd_, 0 );
        assert( base_ != 0 );
        madvise( base_, size_, MADV_RANDOM );

    }

    ~mapped_file() {
        if( base_ != 0 ) {
            unmap();
        }
        close( fd_ );
    }

    void *base() {
        return base_;
    }


private:
    void *base_;
//     bool read_write_;
    int fd_;
    off_t size_;
    bool read_write_;
};


struct id3_struct {
    char id[3];
    char title[30];
    char interpret[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre[1];
};


typedef std::set<std::string> string_set_type;

string_set_type title_set;
string_set_type interpret_set;
string_set_type album_set;

static std::string extract_cstr( const char *str, const size_t max_len = 30 ) {
    std::string ret;
    ret.reserve(32);

    for( size_t i = 0; i < max_len && str[i] != 0; ++i ) {
        ret.push_back(str[i]);
    }

    while( isspace(ret.back() ) ) {
        ret.pop_back();
    }
    return ret;
}


struct song {
    string_set_type::iterator title;
    string_set_type::iterator interpret;
    string_set_type::iterator album;
};


bool operator<( const song &a, const song &b ) {
    if( *(a.interpret) < *(b.interpret) ) {
        return true;
    } else if( *(a.interpret) > *(b.interpret) ) {
        return false;
    } else if( *(a.album) < *(b.album) ) {
        return true;
    } else if( *(a.album) > *(b.album) ) {
        return false;
    } else if( *(a.title) < *(b.title) ) {
        return true;
    } else {
        return false;
    }

}

bool operator==(const song &a, const song &b) {
    return *(a.interpret) == *(b.interpret) && *(a.album) == *(b.album) && *(a.title) == *(b.title);
}

bool operator!=(const song &a, const song &b) {
    return !(a == b);
}

template<typename iter>
std::vector<std::pair<iter,iter> > equal_runs( iter first, iter last ) {
    std::vector<std::pair<iter,iter> > ret;

    iter s = first;
    //iter e = first;

    ++first;
    while( first != last ) {
        if( *first != *s ) {
            ret.emplace_back( s, first );
            s = first;
        }

        ++first;
    }

    ret.emplace_back( s, first );

    return ret;
}

std::ostream &operator<<( std::ostream &os, const song& s ) {
    os << *(s.interpret) << " --- " << *(s.album) << " --- " << *(s.title);
    return os;
}

int main() {
    std::string name;




    std::vector<song> song_list;

    size_t num_bad_file = 0;
    size_t num_no_tags = 0;
    size_t num_incomplete_tags = 0;
    while( std::cin.good() ) {
        std::getline( std::cin, name );

        //std::cout << "file: '" << name << "'\n";

        if( name.empty() ) {
            continue;
        }

        try {

            mapped_file mf( name.c_str() );

            const char * data = (const char *) mf.base();
            auto size = mf.size();

            if( size < sizeof( id3_struct )) {
//                std::cout << "file too small.";
                ++num_bad_file;
                continue;
            }

            const id3_struct *id3 = (const id3_struct*)( data + size - sizeof( id3_struct ) );

//            std::cout << id3->id[0] << " " << id3->id[1] << " " << id3->id[2] << "\n";

            if( id3->id[0] != 'T' || id3->id[1] != 'A' || id3->id[2] != 'G' ) {
//                std::cout << "no id3v1\n";
                ++num_no_tags;
                continue;
            }

            const size_t name_len = 30;
            std::string title = extract_cstr( id3->title, name_len );
            std::string interpret = extract_cstr( id3->interpret, name_len );
            std::string album = extract_cstr( id3->album, name_len );

            if( interpret.empty() || album.empty() || title.empty() ) {
                ++num_incomplete_tags;
                continue;
            }

            //std::cout << title << " --- " << interpret << " --- " << album << "\n";

            auto title_res = title_set.insert( title );
            auto interpret_res = interpret_set.insert( interpret );
            auto album_res = album_set.insert( album );

            song s = {title_res.first, interpret_res.first, album_res.first };

            song_list.push_back(s);

        } catch( std::runtime_error x ) {
            std::cout << "file not found: '" << name << "'.\n";
        }
    }
    std::cout << "end: " << num_bad_file << " " << num_no_tags << " " << num_incomplete_tags << " => " << song_list.size() << "\n";

    std::vector<song> song_list_sorted = song_list;

    std::sort( song_list_sorted.begin(), song_list_sorted.end() );

    std::vector<song> song_list_unique;
    std::unique_copy(song_list_sorted.begin(), song_list_sorted.end(), std::back_inserter(song_list_unique));

    std::cout << "unique: " << song_list_sorted.size() << " -> " << song_list_unique.size() << "\n";

//    for( const song &s : song_list_sorted ) {
//        std::cout << *(s.interpret) << " --- " << *(s.album) << " --- " << *(s.title) << "\n";
//    }

    auto ers = equal_runs( song_list_sorted.begin(), song_list_sorted.end() );
    std::multimap<size_t, std::pair<std::vector<song>::iterator,std::vector<song>::iterator> > ers_sizes;

    for( const auto & er : ers ) {
        ers_sizes.emplace( std::distance( er.first, er.second), er );
    }

    std::cout << "ers: " << ers.size() << "\n";

    {
        std::multimap<size_t, std::pair<std::vector<song>::iterator,std::vector<song>::iterator> >::reverse_iterator rit = ers_sizes.rbegin();
        for( size_t i = 0; rit != ers_sizes.rend() && rit->first > 1; ++i, ++rit ) {
//            size_t size = rit->first;
//            song s = *(rit->second.first);
//            std::cout << rit->first << " " << *(rit->second.first) << "\n";
        }
   }

//    sleep(5);

}
