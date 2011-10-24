#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cassert>
#include <memory>
#include <unordered_set>

using std::shared_ptr;

template<typename iiter>
class lexer {
    
    
public:
    
    class token {
    public:
        virtual ~token() {};
    };
    
    class name : public token, private std::string {
    public:
        
        name( const std::string &name ) : std::string( name ) 
        {}
        
        const std::string &get() {
            return this;
        }
        
    };
    
    class keyword : public token, private std::string {
      
    public:
        keyword( const std::string &keyword ) : std::string( keyword ) 
        {}
    };
    
    lexer( iiter start, iiter end ) : start_(start), end_(end)
    {
        keywords_ = {"auto","break","case","char","continue","default","do","double","else","entry","enum","extern","float","for","goto","if","int","long","legister","return","short","sizeof","static","struct","switch","typdef","union","unsigned","void","while"};
        std::sort( keywords_.begin(), keywords_.end() ); // just to make sure...
        
    }
    
    inline bool is_keyword( const std::string &s ) {
     
        return std::binary_search( keywords_.begin(), keywords_.end(), s );
    }
    
    inline bool is_letter( char c ) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }
    
    
    shared_ptr<token> next() {
     
        if( start_ == end_ ) {
         
            return shared_ptr<token>(nullptr);
        }
        
        while( isspace(*start_) ) {
         
            start_++;
            
            if( start_ == end_ ) {
             
                return shared_ptr<token>();
            }
        }
        
        char c = *start_;
        
        if( is_letter(c) ) {
            std::string s;
             
            s.push_back(c);
            ++start_;
            while( start_ != end_ ) {
                c = *start_;
                if( is_letter(c) || std::isdigit(c)) {
                    s.push_back(c);
                } else {
                    break;
                }
                ++start_;
            }
            
            if( is_keyword(s) ) {
             
                return std::make_shared<keyword>(s);
            } else {
                return std::make_shared<name>(s);
            }
        }
        return shared_ptr<token>(nullptr);
    }
    
    void test() {
        while( start_ != end_ ) {
            std::cout << *start_;
            start_++;
        }   
    }
private:
    
    iiter start_;
    iiter end_;
    std::vector<std::string> keywords_;
};


int main() {
  
    std::ifstream is( "test.c" );
    
    
    
    assert( is.good() );
    
    is >> std::noskipws;
    
    typedef lexer<std::istream_iterator<char>> my_lexer;
   
    
    my_lexer l( (std::istream_iterator<char>(is)), std::istream_iterator<char>() );
    
    
    shared_ptr<my_lexer::token> token;
    
    while( (token = l.next()).get() != nullptr ) {
        
        std::cout << "token: " << typeid(*token).name() << "\n";
        
    }
    
//     std::cout << "blub\n";
};