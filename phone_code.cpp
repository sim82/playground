#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <stdexcept>
#include <cctype>

char letter_to_num( char c ) {
    c = tolower(c);
    
    if( c >= 'a' && c <= 'c' ) {
        return '2';
    } else if( c >= 'd' && c <= 'f' ) {
        return '3';
    } else if( c >= 'g' && c <= 'i' ) {
        return '4';
    } else if( c >= 'j' && c <= 'l' ) {
        return '5';
    } else if( c >= 'm' && c <= 'o' ) {
        return '6';
    } else if( c >= 'p' && c <= 's' ) {
        return '7';
    } else if( c >= 't' && c <= 'v' ) {
        return '8';
    } else if( c >= 'w' && c <= 'z' ) {
        return '9';
    } else {
        throw std::runtime_error( "bad character" );
    }
    
}


int main() {
    std::ifstream is( "/usr/share/dict/words" );
    typedef std::map<std::string,std::vector<std::string> > dict_map_type;
    
    dict_map_type dict_map;
    
    while( is.good() ) {
        std::string s;
        std::getline( is, s );
        
        size_t num_letters = std::count_if( s.begin(), s.end(), isalpha );
    
        
        
        if( num_letters == s.size() ) {
            std::string encoded_s = s;
            
            std::transform( s.begin(), s.end(), encoded_s.begin(), letter_to_num );
            
            dict_map_type::iterator it = dict_map.find( encoded_s );
            
            if( it == dict_map.end() ) {
                std::pair<dict_map_type::iterator,bool> ret;
                
                ret = dict_map.insert( std::make_pair( encoded_s, std::vector<std::string>() ));
                
                if( !ret.second )  {
                    throw std::runtime_error( "internal error" );
                }
                
                it = ret.first;
            }
            
            it->second.push_back( s );
        }
        
    }
    
    if( false ) {
        for( auto it = dict_map.begin(), e = dict_map.end(); it != e; ++it ) {
            std::cout << it->first << " -> ";
            std::copy( it->second.begin(), it->second.end(), std::ostream_iterator<std::string>(std::cout, " " ) );
            std::cout << "\n";
        }
    }
    
    std::cout << "size: " << dict_map.size() << "\n";
    
    while( std::cin.good() ) {
        std::string code;
        std::getline( std::cin, code );
        
        size_t num_digits = std::count_if( code.begin(), code.end(), isdigit );
        
        if( num_digits == 0 || num_digits != code.size() ) {
            std::cout << "non digit character\n";
            continue;
        }
        
        
        dict_map_type::iterator it_lower = dict_map.lower_bound( code );
        dict_map_type::iterator it_upper = dict_map.upper_bound( code );
        
        while( it_lower != dict_map.end() ) {
            
            if( it_lower->first.find( code ) != 0 ) {
                break;
            }
            
            //std::cout << it_lower->first << " ->\n";
            std::copy( it_lower->second.begin(), it_lower->second.end(), std::ostream_iterator<std::string>(std::cout, " " ) );
            std::cout << " ";
            ++it_lower;
        }
        
        std::cout << "\n";
        
    }
    
}