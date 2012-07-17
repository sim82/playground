#include <functional>
#include <iostream>
#include <fstream>
#include <map>
#include <cassert>

typedef std::pair<size_t,size_t>game_id;

typedef std::pair<int,int> result;

template<typename T>
int sign( const T &a ) {
    if( a > 0 ) {
        return 1;
    } else if( a < 0 ) {
        return -1;
    } else {
        return 0;
    }
}

size_t score( const result &tip, const result &truth ) {
    int dtip = tip.first - tip.second;
    int dtruth = truth.first - truth.second;
    
    if( tip == truth ) {
        return 3;
    } else if( dtip == dtruth ) {
        return 2;
    } else if( sign( dtip ) == sign( dtruth ) ) {
        return 1;
    } else {
        return 0;
    }
    
}


std::map<game_id,result> read_list( std::istream &is ) {
    std::map<game_id,result> res_list;
    
    
    while( is.good() ) {
        game_id g(-1,-1);
        
        is >> g.first;
        is >> g.second;
        
        result res(-1,-1);
        
            
        
        is >> res.first;
        is >> res.second;
        
        if( res.first < 0 || res.second < 0 ) {
            continue;
        }
        
        res_list.insert( std::make_pair( g, res ));
    }
    
    return res_list;
    
}


size_t calc_sum( const std::map<game_id,result> &tip_list, const std::map<game_id,result> &res_list ) {
    
    size_t sum = 0;
    
    for( auto &res : res_list ) {
        auto tit = tip_list.find( res.first );
        
//         assert( tip != tip_list.end() );
        
        size_t s = score( (*tit).second, res.second );
//         std::cout << "score: " << s << "\n";
        sum += s;
    }
    
    
    return sum;
}

int main( int argc, char *argv[] ) {
//     const size_t n_teams = 16;
    
    std::map<game_id,result> tip;
    
    
    {
        std::ifstream is( "tip.txt" );
     
        assert( is.good() );
        
        tip = read_list(is);
        
    }
    
    std::map<game_id,result> res;
    {
        std::ifstream is( "res.txt" );
        
        assert( is.good() );
        res = read_list(is);
        
    }
    
    
    size_t score_sum = calc_sum( tip, res );
        
    std::cout << "sum: " << score_sum << "\n";
    
    
}