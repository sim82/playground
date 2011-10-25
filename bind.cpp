#include <functional>
#include <vector>
#include <iostream>
#include <array>
#include <stdexcept>
#include <cassert>

class token_stream {
	friend class ts_trans;

public:

	token_stream( const std::vector<int> &input ) : token_(input), cur_(token_.begin()) {}

	int get() {
		if( cur_ == token_.end() ) {
			throw std::runtime_error( "end of token stream" );
		}
		return *cur_;

	}

	void next() {
		++cur_;
	}

	bool end_of_input() {
		return cur_ == token_.end();
	}

private:
	std::vector<int> token_;
	std::vector<int>::iterator cur_;

};

class ts_trans {

public:
	ts_trans( token_stream * ts ) : ts_(ts), iter_(ts->cur_), commit_(false)
	{

	}

	~ts_trans() {
		if( !commit_ ) {
			ts_->cur_ = iter_;
		}
	}

	inline void commit() {
		commit_ = true;
	}

private:
	token_stream *ts_;
	std::vector<int>::iterator iter_;
	bool commit_;
};


class bla {
public:

	class node : private std::vector<node> {
	public:
		node( int v ) : null_(false), is_term_(true), term_(v), prod_("term") {}

		node( const std::vector<node> &l, const char *prod ) : std::vector<node>(l), null_(false), is_term_(false), term_(-1), prod_(prod) {}

		node() : null_(true), is_term_(false), term_(-1), prod_("null") {}

		bool is_terminal() const {
			assert( is_term() );
			assert( !is_null() );
			return is_term_;
		}

		int get_terminal() const {
			assert( is_terminal() );
			return term_;
		}

		const std::vector<node> &get_list() const {

			assert( !is_term() );
			assert( !is_null() );
			return *this;
		}

		bool is_null() const {
			return null_;
		}

		const std::string &get_prod() const {
			return prod_;
		}

		void flatten( std::vector<int> *fl ) const {
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
	private:
		bool null_;
		bool is_term_;
		int term_;

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
			std::cout << "term: " << n.get_terminal() << "\n";
		} else {
			std::cout << "inner:" << n.get_prod() << "\n";

			for( const node &cn : n.get_list() ) {
				print_node( cn, indent+1 );
			}

		}
	}

	//typedef std::vector<node> node_list;

	typedef std::function<node (token_stream *)> rule_t;

	class token {
	public:
		token( int v ) : v_(v) {}

		bool match( int v) {
			return v == v_;
		}

		node operator()( token_stream *ts ) {
			if( ts->end_of_input() ) {
				return node();
			}

			if( match( ts->get() ) ) {

				int t = ts->get();
				ts->next();
				return node(t);
			} else {
				return node();
			}
		}

	private:
		int v_;
	};

	class match_list {

	public:
		match_list( std::initializer_list<rule_t> list ) : ml_(list) {}

		node operator()(token_stream *ts) {
			if( ts->end_of_input() ) {
				return node();
			}

			ts_trans tr( ts );

			std::vector<node> nodes;

			for( rule_t rule : ml_ ) {
				node n = rule(ts);

				if( n.is_null() ) {
					return node();
				}

				nodes.push_back( n );
			}

			tr.commit();


			return node(nodes, "list");

		}

	private:
		std::vector<rule_t> ml_;


	};


	class match_multi {
	public:
		match_multi( rule_t r ) : r_(r) {}

		node operator()( token_stream *ts ) {

			if( ts->end_of_input() ) {
				return node();
			}

			std::vector<node> nodes;

			while( true ) {
				node n = r_(ts);

				if( n.is_null() ) {
					break;
				}

				nodes.push_back( n );

			}

			return node(nodes, "multi");
		}

	private:
		rule_t r_;
	};


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

	bla( int v ) : v_(v) {}

	void test() {
		std::cout << "test: " << v_ << "\n";
	}


	std::function<void()> run() {
		std::function<void()> fn = std::bind( std::mem_fn( &bla::test ), this );

		return fn;
	}



	node expression() {

		ts_trans tr(ts_);

		if( ts_->end_of_input() ) {
			return node();
		}


		rule_t exp = match_any( {
			match_list( {

				token(1),
				token(2)
		    }),
		    match_list( {
				token(666),
				token(777)
			}),
		} );


		//std::cout << "exp: " << sizeof( exp ) << "\n";

		node n = exp(ts_);

		std::cout << "expression: " << n.is_null() << "\n";

		if( !n.is_null() ) {
			n.annotate( "expression" );
			tr.commit();
		}
		return n;
	}

	node statement() {
		ts_trans tr(ts_);

		if( ts_->end_of_input() ) {
			return node();
		}

		rule_t exp = match_list( {
			match_expression(),
			token(3)
		});

		node n = exp(ts_);

		std::cout << "statement: " << n.is_null() << "\n";

		if( !n.is_null() ) {
			n.annotate( "statement" );
			tr.commit();
		}
		return n;
	}

	std::function<node(token_stream *)> match_expression() {
		return std::bind( std::mem_fn( &bla::expression ), this );
	}
	std::function<node(token_stream *)> match_statement() {
		return std::bind( std::mem_fn( &bla::statement ), this );
	}

	node end_of_input() {

		if( ts_->end_of_input() ) {
			node n(-1);
			n.annotate("end_of_input");
			return n;
		} else {
			return node();
		}
	}

	bool match( token_stream * ts ) {

		ts_ = ts;
		//rule_t base = match_list( std::bind(std::ptr_fn(&bla::expression), this), token(4) } );

		rule_t base = match_list( {
			match_multi( match_statement() ),
			std::bind(std::mem_fn(&bla::end_of_input), this )
		});


		//std::cout << typeid(base).name() << "\n";


		std::cout << "base: " << sizeof( base ) << "\n";

		node m = base( ts );

		std::cout << "match: " << (!m.is_null()) << "\n";

		print_node( m );

		return (!m.is_null());
	}

private:
	int v_;

	token_stream *ts_;

};

int main() {


	bla b1(123);

	std::vector<int> t{ 1, 2, 3, 1, 2, 3, 666, 777, 3 };
	token_stream ts( t );

	b1.match(&ts);

}
