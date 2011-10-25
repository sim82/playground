#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cassert>
#include <memory>
#include <unordered_set>
#include <stdexcept>

using std::shared_ptr;

namespace lex {
class token {
public:
    virtual ~token() {};

    virtual void print( std::ostream & ) = 0;
};

class name : public token, private std::string {
public:
    
    name( const std::string &name ) : std::string( name )
    {}
    
    const std::string &get() {
        return *this;
    }
    
    void print( std::ostream &os ) {
    	os << "name: " << get();
    }

};

class keyword : public token, private std::string {

public:
    keyword( const std::string &keyword ) : std::string( keyword )
    {}

    const std::string &get() {
		return *this;
	}


    void print( std::ostream &os ) {
		os << "keyword: " << get();
	}
};

class constant : public token, private std::string {
public:
	enum class const_type {
		integer,
		long_int,
		character,
		floating,
		string
	};
	constant( char cc ) {
		std::string::push_back(cc);
		type_ = const_type::character;
	}

	constant( const std::string &s, const_type type ) : std::string(s), type_(type) {}
	const std::string &get() {
		return *this;
	}

	const char *type_name( const_type t ) {
		switch( t ) {
		case const_type::integer:
			return "integer";
		case const_type::long_int:
			return "long_int";
		case const_type::character:
			return "character";
		case const_type::floating:
			return "floating";
		case const_type::string:
			return "string";
		}

		return 0;
	}

	void print( std::ostream &os ) {
		os << "constant (" << type_name(type_) << ") " << get();
	}

private:
	const_type type_;
};

class other : public token, private std::string {
public:
	other( const std::string &s ) : std::string(s) {}

	const std::string &get() {
		return *this;
	}


	void print( std::ostream &os ) {
		os << "other: " << get();
	}
};


}

template<typename iiter>
class lexer {


public:


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
    
    void check_not_end() {
    	if( start_ == end_ ) {
    		throw std::runtime_error( "preliminary end of input" );
    	}
    }
    
    shared_ptr<lex::token> next() {
     
    	using namespace lex;

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
        
        assert( !isspace(c) );

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
        } else if( c == '\'') {
        	++start_;

        	check_not_end();

        	char cc = *start_;

        	assert( cc != '\\' ); // fix escapes later...
        	++start_;

        	check_not_end();
        	if( *start_ != '\'' ) {
        		throw std::runtime_error( "missing closing ' in char constant");
        	}

        	++start_;

        	return std::make_shared<constant>(cc);
        } else if( isdigit(c)) {
        	std::string s;

        	s.push_back(c);

        	++start_;
        	// TODO: handle float and long

        	while( start_ != end_ ) {
        		c = *start_;

        		if( !isdigit(c) ) {
        			return std::make_shared<constant>(s, constant::const_type::integer );
        		}
        		s.push_back( c );
        		++start_;
        	}
        } else if( c == '"' ) {
        	std::string s;

        	++start_;
        	check_not_end();


        	while( *start_ != '"' ) {
        		s.push_back(*start_);

        		++start_;
        		check_not_end();
        	}

        	++start_;

        	return std::make_shared<constant>( s, constant::const_type::string );
        } else {
        	std::string s;
        	s.push_back(c);

        	++start_;
//
//			while( start_ != end_ ) {
//				char c = *start_;
//
//				// TODO: what about '.'?!
//
//				if( is_letter(c) || isdigit(c) || c == '"' || c == '\'' || isspace(c) ) {
//					break;
//				}
//				s.push_back(c);
//
//				++start_;
//
//
//
//			}
			return std::make_shared<other>( s );

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

class token_buffer : private std::vector<std::shared_ptr<lex::token> > {

public:
	template<typename iiter>
	token_buffer( lexer<iiter> * l ) {
		while( true ) {
			auto tok = l->next();

			if( tok.get() == 0 ) {
				break;
			}

			std::cout << "add: " << *tok << "\n";

			push_back( tok );
		}
	}

	typedef std::vector<std::shared_ptr<lex::token> > base_type;
	typedef base_type::iterator iterator;

	using base_type::begin;
	using base_type::end;


private:

};

std::ostream &operator<<( std::ostream &os, lex::token &t ) {
	t.print(os);

	return os;
}

int main() {
  
    std::ifstream is( "test.c" );
    
    
    
    assert( is.good() );
    
    is >> std::noskipws;
    
    typedef lexer<std::istream_iterator<char>> my_lexer;
   
    
    my_lexer l( (std::istream_iterator<char>(is)), std::istream_iterator<char>() );
    
    token_buffer tb( &l );
    
    for( auto it = tb.begin(); it != tb.end(); ++it ) {

    	std::cout << "tb " << (it - tb.begin()) << ": " << *(*it) << "\n";
    }
    
//     std::cout << "blub\n";
};
