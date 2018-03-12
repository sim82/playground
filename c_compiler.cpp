/*
 * Copyright (C) 2011 Simon A. Berger
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


#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cassert>
#include <memory>
#include <unordered_set>
#include <stdexcept>
#include <functional>

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

	const_type get_type() const {
		return type_;
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
        
        // if i'm not wrong, then every non empty prefix of a separator is also a separator (=i.e., something like a trie),
        // so the longest separators can be easily transformed into a prefix array for fast lookup.
        // pure genius, Mr. Ritchie!
        auto sep_raw = {
        	"<<=", ">>=",
        	"++", "--", "+=", "-=", "*=", "/=", "%=", "!=", "==", ">=", "<=", "^=",
        	"||", "&&",
        	".", ",", "->", "(", ")", "[", "]", "{", "}", "?", ":", ";"
        };

        // ok, this looks kind of dorky compared to an unordered_set, but I think, when you write a k&r c compiler, you should prefer sorted arrays+binary search to the modern stuff.
        for( const std::string &s : sep_raw ) {
			auto it = s.end();
			while( it != s.begin() ) {
				sep_.push_back( std::string(s.begin(), it) );
				--it;
			}

        }
        std::sort( sep_.begin(), sep_.end() );
        sep_.erase(std::unique( sep_.begin(), sep_.end() ), sep_.end() );

        std::copy( sep_.begin(), sep_.end(), std::ostream_iterator<std::string>(std::cout, "\n" ));


    }
    
    bool is_separator( const std::string & s ) {
    	return std::binary_search(sep_.begin(), sep_.end(), s );
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
    
    static char translate_escape( char cc ) {
    	switch( cc ) {
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case '0':
			return '\0';
		case '\\':
		case '\'':
		case '\"':
			return cc;
		default:
			std::cerr << "bad: " << int(cc) << "\n";
			throw std::runtime_error( "unknown escape char");
		}
    }

    shared_ptr<lex::token> next() {
     
    	using namespace lex;

        if( start_ == end_ ) {
         
            return shared_ptr<token>(nullptr);
        }

        while( true ) {
			while( isspace(*start_) ) {

				++start_;

				if( start_ == end_ ) {

					return shared_ptr<token>();
				}
			}

			if( *start_ == '#' ) {
				++start_;
				while( start_ != end_ ) {
//					std::cout << "skip: " << *start_ << "\n";
					if( *start_ == '\n' ) {

						++start_;
						break;
					}
					++start_;
				}
			} else {
				break;
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

        	bool is_escape = false;
        	//assert( cc != '\\' ); // fix escapes later...
        	if( cc == '\\' ) {
        		is_escape = true;
        		++start_;
        		check_not_end();

        		cc = *start_;
        	}
        	++start_;

        	check_not_end();
        	if( *start_ != '\'' ) {
        		throw std::runtime_error( "missing closing ' in char constant");
        	}

        	++start_;

        	if( is_escape ) {
        		cc = translate_escape(cc);
        	}

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
        		bool is_escape = false;
				//assert( cc != '\\' ); // fix escapes later...
				if( *start_ == '\\' ) {
					is_escape = true;
					++start_;
					check_not_end();


				}

				if( is_escape ) {
					s.push_back(translate_escape(*start_));
				} else {
					s.push_back(*start_);
				}

        		++start_;
        		check_not_end();
        	}

        	++start_;

        	return std::make_shared<constant>( s, constant::const_type::string );
        } else {

        	std::string s;


			while( start_ != end_ ) {
				s.push_back(*start_);

				if( !is_separator( s )) {
					assert( !s.empty() );

					s.erase( s.end() - 1 );
					break;
				}

				++start_;
			}

			if( s.empty()) {
				throw std::runtime_error( "unparsable char" );
			} else {
				return std::make_shared<other>(s);
			}

		//	return std::make_shared<other>( s );

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
    std::vector<std::string> sep_;
};

class token_stream : private std::vector<std::shared_ptr<lex::token> > {

public:
	friend class ts_trans;


	template<typename iiter>
	token_stream( lexer<iiter> * l ) {
		reserve(100000);
		while( true ) {
			auto tok = l->next();

			if( tok.get() == 0 ) {
				break;
			}

			//std::cout << "add: " << *tok << "\n";

			push_back( tok );
		}

		current_ = begin();
	}

	typedef std::vector<std::shared_ptr<lex::token> > base_type;
	typedef base_type::iterator iterator;

	using base_type::begin;
	using base_type::end;

	std::shared_ptr<lex::token> get_and_next() {
		assert( current_ != end() );
		return *(current_++);
	}

	std::shared_ptr<lex::token> get() {
		assert( current_ != end() );
		return *current_;
	}

	void next() {
		++current_;
	}


	bool end_of_input() {
		return current_ >= end();
	}


private:

	iterator current_;
};

class ts_trans {

public:
	ts_trans( token_stream * ts ) : ts_(ts), iter_(ts->current_), commit_(false)
	{

	}

	~ts_trans() {
		if( !commit_ ) {
			ts_->current_ = iter_;
		}
	}

	inline void commit() {
		commit_ = true;
	}

private:
	token_stream *ts_;
	token_stream::iterator iter_;
	bool commit_;
};

std::ostream &operator<<( std::ostream &os, lex::token &t ) {
	t.print(os);

	return os;
}

template<typename T1, typename T2>
inline bool isa( T2 * ptr ) {
    return typeid(*ptr) == typeid(T1);
}


// TODO: is this a good idea? the pointer version above should win if appropriate
template<typename T1, typename T2>
inline bool isa( T2 & ref ) {
    return typeid(ref) == typeid(T1);
}


namespace parse {

typedef std::shared_ptr<lex::token> lex_token;

class node : private std::deque<node> {
public:
	node( lex_token tok ) : null_(false), is_term_(true), term_(tok), prod_("term") {}

	node( const std::initializer_list<node> &l, const std::string &prod ) : std::deque<node>(l), null_(false), is_term_(false), term_(0), prod_(prod) {}

	template<typename iiter>
	node( iiter first, iiter last, const std::string &prod ) : std::deque<node>(first, last), null_(false), is_term_(false), term_(0), prod_(prod) {}
//		node( const std::vector<node> &l, const char *prod ) : std::vector<node>(l), null_(false), is_term_(false), term_(0), prod_(prod) {}
	//node( const std::initializer_list<node> &l, const char *prod ) : std::vector<node>(l), null_(false), is_term_(false), term_(0), prod_(prod) {}

	node() : null_(true), is_term_(false), term_(0), prod_("null") {}

	bool is_terminal() const {


		return is_term_;
	}

	lex_token get_terminal() const {
		assert( !is_null() );
		assert( is_terminal() );
		return term_;
	}

	const std::deque<node> &get_list() const {

		assert( !is_terminal() );
		assert( !is_null() );
		return *this;
	}

	bool is_null() const {
		return null_;
	}

	const std::string &get_prod() const {
		return prod_;
	}

	void flatten( std::vector<lex_token> *fl ) const {
		assert( fl != 0 );


		assert( !is_null() );

		if( is_terminal() ) {
			fl->push_back(term_);
		} else {
			for( auto it = begin(); it != end(); ++it  ) {
				it->flatten(fl);
			}
		}

	}

	void annotate( const char *annot ) {
		annot_ = annot;
	}


	const std::string &get_annot() const {
		return annot_;
	}

	using std::deque<node>::at;
	using std::deque<node>::push_front;
	using std::deque<node>::push_back;
	using std::deque<node>::size;
private:
	bool null_;
	bool is_term_;
	lex_token term_;

	std::string prod_;
	std::string annot_;
};

void print_node( const node &n, int indent = 0 ) {

	for( int i = 0; i < indent; ++i ) {
		std::cout << " ";
	}

	const std::string &a = n.get_annot();

	if( !a.empty() ) {
		std::cout << "[" << a << "]";
	}
	if( n.is_null() ) {
		std::cout << "null!!!\n";

	} else if( n.is_terminal() ) {
		std::cout << "term: " << *(n.get_terminal()) << "\n";
	} else {
		std::cout << n.get_prod() << "(\n";

		for( const node &cn : n.get_list() ) {
			print_node( cn, indent+1 );
		}

	}
}

struct value {

	value( int v ) : v_(v), is_lvalue_(false)
	{

	}

	value( int v, const std::string &lvalue )
	  : v_(v), is_lvalue_(true), lvalue_name_(lvalue)
	{

	}

	operator const int () {
		return v_;
	}

	int v_;

	void mod_lvalue( std::map<std::string,int> &env, int v, bool add  ) {
		assert( is_lvalue_);

		auto it = env.find(lvalue_name_);
		assert( it != env.end() );

		// assert( v_ == it->second ); this is not true: e.g. for a = a++ if 'a' is evaluated before 'a++'

		auto pair = *it;
		if( add ) {
			v_ += v;
		} else {
			v_ = v;
		}

		env[lvalue_name_] = v_;
//			std::cout << "mod_lvalue: " << v_ << " " << lvalue_name_ << " " << pair.second << "\n";
	}
	bool is_lvalue_;
	std::string lvalue_name_;
};

value eval_node( const node &n, std::map<std::string,int> &env ) {
	if( n.is_terminal() ) {

		lex_token tok = n.get_terminal();

		if( isa<lex::name>(*tok)) {
			std::string name = (static_cast<lex::name *>(tok.get()))->get();

			auto it = env.find(name);
			if( it == env.end() ) {
				std::cout << "eval lex::name: not found: " << name << "\n";
				throw std::runtime_error( "bailing out" );
			}

			std::cout << "get name: " << name << " " << it->second << "\n";

			return value( it->second, name );
		} else if( isa<lex::constant>(*tok)) {
			lex::constant *c = static_cast<lex::constant *>(tok.get());

			if( c->get_type() != lex::constant::const_type::integer ) {
				throw std::runtime_error( "non integer const" );
			}

			return value( atoi(c->get().c_str() ) );
		}

		throw std::runtime_error( "don't know what to do with terminal");
//			if( tok->)//
	} else {

		if( n.get_prod() == "infix_add" ) {
			assert( n.size() == 2 );
			int v1 = eval_node(n.at(0), env);
			int v2 = eval_node(n.at(1), env);

			return v1 + v2;
		} else if( n.get_prod() == "infix_sub" ) {
			assert( n.size() == 2 );
			int v1 = eval_node(n.at(0), env);
			int v2 = eval_node(n.at(1), env);

			return v1 - v2;
		} else if( n.get_prod() == "infix_mult" ) {
			assert( n.size() == 2 );
			int v1 = eval_node(n.at(0), env);
			int v2 = eval_node(n.at(1), env);

			return v1 * v2;
		} else if( n.get_prod() == "infix_add" ) {
			assert( n.size() == 2 );
			int v1 = eval_node(n.at(0), env);
			int v2 = eval_node(n.at(1), env);

			return v1 / v2;
		} else if( n.get_prod() == "postfix_inc" ) {
			assert( n.size() == 1 );
			value v1 = eval_node(n.at(0), env);
			int vret = v1;


			v1.mod_lvalue(env, 1, true );
			return vret;
		} else if( n.get_prod() == "postfix_dec" ) {
			assert( n.size() == 1 );
			value v1 = eval_node(n.at(0), env);
			int vret = v1;


			v1.mod_lvalue(env, -1, true );
			return vret;
		} else if( n.get_prod() == "prefix_inc" ) {
			assert( n.size() == 1 );
			value v1 = eval_node(n.at(0), env);

			v1.mod_lvalue(env, 1, true );
			return int(v1); // TODO: can v1 keep it's lvalue status?
		} else if( n.get_prod() == "prefix_dec" ) {
			assert( n.size() == 1 );
			value v1 = eval_node(n.at(0), env);

			v1.mod_lvalue(env, -1, true );
			return int(v1);
		} else if( n.get_prod() == "paren" ) {
			assert( n.size() == 1 );
			return eval_node(n.at(0), env);
		} else if( n.get_prod() == "expr_list") {
			assert( n.size() == 2 );

			eval_node(n.at(0), env);
			return eval_node(n.at(1), env);
		} else if( n.get_prod() == "assign" ) {
			assert( n.size() == 2 );
			value v1 = eval_node(n.at(0), env);
			value v2 = eval_node(n.at(1), env);

			v1.mod_lvalue(env, v2, false );
			return int(v1);
		}

		std::cerr << "non-term: " << n.get_prod() << "\n";
		throw std::runtime_error( "unhandled non-terminal");
	}
}



class parser {
public:

	//typedef std::vector<node> node_list;

	typedef std::function<node (token_stream *)> rule_t;

	class match_keyword : private std::string {
	public:
		match_keyword( const std::string &s ) : std::string(s) {}

		node operator()( token_stream *ts ) {
			if( ts->end_of_input() ) {
				return node();
			}
			if( isa<lex::keyword>(*ts->get())) {
				if( static_cast<lex::keyword&>(*ts->get()).get() == *this ) {
					return node( ts->get_and_next() );
				} else {
					return node();
				}
			}

		}

	};

	class match_other : private std::string {
	public:
		match_other( const std::string &s ) : std::string(s) {}

		node operator()( token_stream *ts ) {
			if( ts->end_of_input() ) {
				return node();
			}
			if( isa<lex::other>(*ts->get())) {
				if( static_cast<lex::other&>(*ts->get()).get() == *this ) {
					return node( ts->get_and_next() );
				}
			}
			return node();

		}

	};


	class match_name {
	public:
		match_name() {}

		node operator()( token_stream *ts ) {
			if( ts->end_of_input() ) {
				return node();
			}
			if( isa<lex::name>(*ts->get())) {
				return node( ts->get_and_next() );
			} else {
				return node();
			}

		}

	};

	template<const lex::constant::const_type type>
	class match_constant {
	public:
		match_constant() {}

		node operator()( token_stream *ts ) {
//			std::cout << "try constant:\n";
			if( ts->end_of_input() ) {
				return node();
			}


			if( isa<lex::constant>(*ts->get())) {
//				std::cout << "is constatant\n";
				if( static_cast<lex::constant&>(*ts->get()).get_type() == type ) {
//					std::cout << "is type\n";
					return node( ts->get_and_next() );
				}
			}
			return node();

		}

	};

	class match_list {

	public:
		match_list( std::initializer_list<rule_t> list, const char *annot = "", int passthrough = -1 ) : ml_(list), annot_(annot), passthrough_(passthrough) {}

		node operator()(token_stream *ts) {
			if( ts->end_of_input() ) {
				return node();
			}

			ts_trans tr( ts );

			std::vector<node> nodes;

			for( size_t i = 0; i < ml_.size(); ++i ) {
				rule_t rule = ml_[i];
				node n = rule(ts);

				if( n.is_null() ) {
					return node();
				}

				if( passthrough_ < 0 || int(i) == passthrough_ ) {
					nodes.push_back( n );
				}
			}

			tr.commit();

			if( !annot_.empty() ) {
				return node(nodes.begin(), nodes.end(), annot_);
			} else {
				return node(nodes.begin(), nodes.end(), "list");
			}


		}

	private:
		std::vector<rule_t> ml_;
		std::string annot_;
		const int passthrough_;
	};


//	class match_multi {
//	public:
//		match_multi( rule_t r ) : r_(r) {}
//
//		node operator()( token_stream *ts ) {
//
//			if( ts->end_of_input() ) {
//				return node();
//			}
//
//			std::vector<node> nodes;
//
//			while( true ) {
//				node n = r_(ts);
//
//				if( n.is_null() ) {
//					break;
//				}
//
//				nodes.push_back( n );
//
//			}
//
//			return node(nodes, "multi");
//		}
//
//	private:
//		rule_t r_;
//	};


	class match_any {
	public:
		match_any( std::initializer_list<rule_t> list ) : ml_(list) {}

		node operator()(token_stream *ts) {
			if( ts->end_of_input() ) {
				return node();
			}



			for( rule_t rule : ml_ ) {
				node n = rule(ts);

				if( !n.is_null() ) {
					return n;
				}
			}
			return node();
		}

	private:
		std::vector<rule_t> ml_;

	};


	node match_term_primary( token_stream *ts ) {
		rule_t expression = [&]( token_stream *ts ) {return match_expression(ts);};
		return (match_any( {
			match_constant<lex::constant::const_type::character>(),
			match_constant<lex::constant::const_type::integer>(),
			match_constant<lex::constant::const_type::string>(),
			match_name(),
			match_list( {match_other( "(" ), expression, match_other(")") }, "paren", 1 )
		}))(ts);
	}

	node match_primary( token_stream *ts ) {

		node tn = match_term_primary(ts);
		if( tn.is_null()) {
			return tn;
		}

		rule_t primary = [&]( token_stream *ts ) {return match_primary(ts);};

		rule_t expression = [&]( token_stream *ts ) {return match_expression(ts);};
		rule_t dot = match_list( {match_other( "." ), primary }, "dot" );
		rule_t arrow = match_list( {match_other( "->" ), primary }, "arrow" );
		rule_t bracket = match_list( {match_other( "[" ), expression, match_other( "]") }, "index" );

		rule_t any = match_any({dot,arrow, bracket});

		node an = any(ts);
		if( an.is_null() ) {
			return tn;
		} else {

			return node( {tn, an}, "postfix" );
		}

	}

	node match_unary( token_stream *ts ) {
		rule_t primary = [&]( token_stream *ts ) {return match_primary(ts);};

		rule_t unary = [&]( token_stream *ts ) {return match_unary(ts);};

		rule_t unary_sel = match_any( {
			match_list( {match_other( "sizeof"), primary }, "sizeof_primary", 1 ),
			match_list( {primary, match_other( "++") }, "postfix_inc", 0),
			match_list( {primary, match_other( "--") }, "postfix_dec", 0),
			primary,
			match_list( {match_other( "*"), unary }, "unary_star", 1),
			match_list( {match_other( "&"), unary }, "unary_amp", 1),
			match_list( {match_other( "-"), unary }, "unary_minus", 1),
			match_list( {match_other( "!"), unary }, "unary_not", 1),
			match_list( {match_other( "~"), unary }, "unary_tilde", 1),
			match_list( {match_other( "++"), unary }, "prefix_inc", 1),
			match_list( {match_other( "--"), unary }, "prefix_dec", 1),

		} );

		return unary_sel(ts);
	}

	node match_binary_mult( token_stream *ts ) {
		rule_t unary = [&]( token_stream *ts ) {return match_unary(ts);};

		node n = unary(ts);

		if( n.is_null() ) {
			return n;
		}
#if 0
		rule_t mult = [&]( token_stream *ts ) {return match_binary_mult(ts);};


		rule_t binary_mult = match_any( {
			match_list( { match_other("*"), unary }, "infix_mult" ),
			match_list( { match_other("/"), unary }, "infix_div" )
		});

		{

			node nx;
			while( !(nx = binary_mult(ts)).is_null() ) {

				n = node( { n, nx }, "mult" );
			}
		}
		return n;
#endif
		return match_all_from_left (ts, n, match_any( {
			match_list( { match_other("*"), unary }, "infix_mult", 1 ),
			match_list( { match_other("/"), unary }, "infix_div", 1 ),
			match_list( { match_other("%"), unary }, "infix_mod", 1 )

		}));
	}

	node match_binary_add( token_stream *ts ) {
		rule_t binary_mult = [&]( token_stream *ts ) {return match_binary_mult(ts);};
		node n = binary_mult(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n, match_any( {
			match_list( { match_other("+"), binary_mult }, "infix_add", 1 ),
			match_list( { match_other("-"), binary_mult }, "infix_sub", 1 )
		}));
	}

	node match_binary_shift( token_stream *ts ) {
		rule_t binary_add = [&]( token_stream *ts ) {return match_binary_add(ts);};
		node n = binary_add(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n, match_any( {
			match_list( { match_other("<<"), binary_add }, "infix_lshift", 1 ),
			match_list( { match_other(">>"), binary_add }, "infix_rshift", 1 )
		}));
	}

	node match_binary_compare( token_stream *ts ) {
		rule_t binary_shift = [&]( token_stream *ts ) {return match_binary_shift(ts);};
		node n = binary_shift(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n, match_any( {
			match_list( { match_other("<"), binary_shift }, "infix_lt", 1 ),
			match_list( { match_other("<="), binary_shift }, "infix_lteq", 1 ),
			match_list( { match_other(">"), binary_shift }, "infix_gt", 1 ),
			match_list( { match_other(">="), binary_shift }, "infix_gteq", 1 )
		}));
	}
	node match_binary_equal( token_stream *ts ) {
		rule_t binary_compare = [&]( token_stream *ts ) {return match_binary_compare(ts);};
		node n = binary_compare(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n, match_any( {
			match_list( { match_other("=="), binary_compare }, "infix_eq", 1 ),
			match_list( { match_other("!="), binary_compare }, "infix_neq", 1 ),

		}));
	}

	node match_binary_bit_and( token_stream *ts ) {
		rule_t prec = [&]( token_stream *ts ) {return match_binary_equal(ts);};
		node n = prec(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n,
				match_list( { match_other("&"), prec }, "infix_bit_and", 1 )
		);
	}

	node match_binary_bit_xor( token_stream *ts ) {
		rule_t prec = [&]( token_stream *ts ) {return match_binary_bit_and(ts);};
		node n = prec(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n,
			match_list( { match_other("^"), prec }, "infix_bit_xor", 1 )
		);
	}
	node match_binary_bit_or( token_stream *ts ) {
		rule_t prec = [&]( token_stream *ts ) {return match_binary_bit_xor(ts);};
		node n = prec(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n,
			match_list( { match_other("|"), prec }, "infix_bit_or", 1 )
		);
	}
	node match_binary_log_and( token_stream *ts ) {
		rule_t prec = [&]( token_stream *ts ) {return match_binary_bit_or(ts);};
		node n = prec(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n,
			match_list( { match_other("&&"), prec }, "infix_log_and", 1 )
		);
	}

	// top level of binary terms: log_or
	node match_binary( token_stream *ts ) {
		rule_t prec = [&]( token_stream *ts ) {return match_binary_log_and(ts);};
		node n = prec(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left (ts, n,
			match_list( { match_other("||"), prec }, "infix_log_or", 1 )
		);
	}

	node match_all_from_left( token_stream *ts, node n, rule_t rule ) {

		node nx;
		while(!(nx = rule(ts)).is_null() ) {

			//n = node( { n, nx.at(1) }, nx.get_prod() );
			if( !n.is_null() ) {
				nx.push_front( n );
			}
			n = nx;
		}
		return n;
	}



	// TODO: add inline conditional. it seems kind of whacky...


	node match_assignment( token_stream *ts ) {
		rule_t binary = [&]( token_stream *ts ) {return match_binary(ts);};

		// K&R says that conditional either match plain binary _or_ unaries followed by assignment.
		// Supposingly this is because only unaries can potentially yield lvalues. i assume that it is ok to
		// match binries followed by assignment and worry about the lvalue stuff during semantic analysis.

		node n = binary(ts);

		if( n.is_null()) {
			return n;
		}

		rule_t assignment = [&]( token_stream *ts ) {return match_assignment(ts);};

		rule_t r = match_any( {
			match_list( { match_other("="), assignment }, "assign", 1 ),
			match_list( { match_other("*="), assignment }, "assign_mult", 1 ),
			match_list( { match_other("/="), assignment }, "assign_div", 1 ),
			match_list( { match_other("%="), assignment }, "assign_mod", 1 ),
			match_list( { match_other("+="), assignment }, "assign_add", 1 ),
			match_list( { match_other("-="), assignment }, "assign_sub", 1 ),
			match_list( { match_other(">>="), assignment }, "assign_rshift", 1 ),
			match_list( { match_other("<<="), assignment }, "assign_lshift", 1 ),
			match_list( { match_other("&="), assignment }, "assign_and", 1 ),
			match_list( { match_other("^="), assignment }, "assign_xor", 1 ),
			match_list( { match_other("|="), assignment }, "assign_or", 1 ),

		} );
		node nx;
		while( !(nx = r(ts)).is_null()) {
			nx.push_front(n);
			n = nx;
		}
		return n;
	}


	node match_expression( token_stream *ts ) {
		rule_t assignment = [&]( token_stream *ts ) {return match_assignment(ts);};
		node n = assignment(ts);

		if( n.is_null() ) {
			return n;
		}

		return match_all_from_left( ts, n, match_list( {match_other(","), assignment }, "expr_list", 1));
	}


};
} // namespace parse
//class parser2 {
//
//
//	parser2( token_stream &ts ) : ts_(ts)
//	{}
//
//
//	bool match_name() {
//		if( isa<lex::name>(*(ts_.get())) ) {
//			ts_.next();
//			return true;
//		} else {
//			return false;
//		}
//
//	}
//
//	bool match_keyword( const char *w ) {
//		if( isa<lex::keyword>(*(ts_.get())) ) {
//			if( static_cast<lex::keyword*>(ts_.get().get())->get() == w ) {
//				ts_.next();
//				return true;
//			}
//		}
//		return false;
//
//	}
//
//	bool match_other( const char *w ) {
//		if( isa<lex::other>(*(ts_.get())) ) {
//			if( static_cast<lex::other*>(ts_.get().get())->get() == w ) {
//				ts_.next();
//				return true;
//			}
//		}
//		return false;
//
//	}
//private:
//	token_stream &ts_;
//};

int main() {
  
    std::ifstream is( "test5.c" );
    
    
    
    assert( is.good() );
    
    is >> std::noskipws;
    
    typedef lexer<std::istream_iterator<char>> my_lexer;
   
    
    my_lexer l( (std::istream_iterator<char>(is)), std::istream_iterator<char>() );
    
    token_stream tb( &l );
    
    for( auto it = tb.begin(); it != tb.end(); ++it ) {

    	std::cout << "tb " << (it - tb.begin()) << ": " << *(*it) << "\n";
    }

    std::cout << "num token: " << (tb.end() - tb.begin()) << "\n";

    parse::parser p;
    parse::node n = p.match_expression( &tb );
    parse::print_node(n);

    std::map<std::string,int> env;
    env["a"] = 1;
    env["b"] = 2;
    env["c"] = 3;
    env["d"] = 4;
    env["e"] = 5;
    env["f"] = 6;

    int res = parse::eval_node(n, env);

    std::cout << "res: " << res << "\n";
}
