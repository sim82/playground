#include <cassert>

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <typeinfo>

//int pop() {
//
//	int f = 0;
//	int p = v[0];
//
//	v[0] = v[rsize()];
//
//	if (hSize() > 1) {
//		while (v[left(f)] < v[f] || v[right(f)] < v[f]) {
//			if (v[left(f)] < v[f] && v[right(f)] < v[f]) {
//				if (v[left(f)] < v[right(f)]) {
//					swap(left(f), f);
//					f = left(f);
//				} else {
//					swap(right(f), f);
//					f = right(f);
//				}
//			}
//
//			else {
//				if (v[left(f)] < v[f]) {
//					swap(left(f), f);
//					f = left(f);
//				} else {
//					swap(right(f), f);
//					f = right(f);
//				}
//			}
//		}
//	} else {
//	}
//
//	v.resize(rsize());
//	return p;
//}


template<typename T>
class trans_heap {
	std::vector<T> m_vec;
	friend class trans;


public:
	class trans {

//		std::vector<std::pair<size_t,size_t> > m_swaps;

		struct log {
			size_t i1;
			size_t i2;

			bool is_push() const {
				return i1 == size_t(-1) && i2 == 0;

			}
			bool is_pop() const {
				return i1 == 0 && i2 == size_t(-1);
			}

			bool is_swap() const {
				return i1 != size_t(-1) && i2 != size_t(-1);
			}

			log( size_t i1_, size_t i2_ ) : i1(i1_), i2(i2_) {}

		};

		std::vector<log> m_log;
		std::vector<T> m_pops;
		std::vector<T> &m_vec;
		trans_heap *m_th;
		bool m_commit;

		void rollback() {
			while( !m_log.empty() ) {
				const log &l = m_log.back();
				if( l.is_swap() ) {
					do_swap(m_vec[l.i1], m_vec[l.i2]);
				} else if( l.is_push() ) {
					m_vec.pop_back();
				} else {
					assert( l.is_pop() );
					assert( !m_pops.empty() );
					m_vec.push_back( std::move( m_pops.back() ));
					m_pops.pop_back();
				}

				m_log.pop_back();

			}

		}

		void do_swap( T &t1, T &t2 ) {

			std::swap( t1, t2 );
			size_t tmp = t1.get_pos();
			t1.set_pos( t2.get_pos() );
			t2.set_pos( tmp );
		}


	public:

		trans() = delete;
		trans( const trans & ) = delete;

		trans &operator=(const trans &) = delete;

		//trans( std::vector<T> &vec ) : m_vec(vec), m_commit(false) {}

		trans( trans_heap *th ) : m_vec( th->m_vec ), m_th(th), m_commit(false) {
			th->set_trans(this);
		}

		~trans() {
			if( !m_commit ) {
				rollback();
			}

			m_th->unset_trans();
		}


		void swap( size_t i1, size_t i2 ) {
			m_log.push_back( log(i1,i2));
			do_swap( m_vec[i1], m_vec[i2] );
		}

		void push_back( const T& v ) {

			m_log.push_back(log(-1, 0 ));
			m_vec.push_back( v );

		}

		const T &pop_back() {

			m_log.push_back(log(0, -1 ));
			m_pops.push_back( std::move( m_vec.back() ));
			m_vec.resize(m_vec.size() - 1 );
			return m_pops.back();
		}

		void commit() {
			m_commit = true;

		}

	};
private:
	trans *m_trans;

public:
	void set_trans( trans *t ) {
		assert( m_trans == 0 );

		m_trans = t;
	}

	void unset_trans() {
		assert( m_trans != 0 );
		m_trans = 0;
	}


	trans_heap() : m_trans(0) {}


	void push( const T &value ) {
		m_trans->push_back(value);

		size_t holeIndex = m_vec.size() - 1;
		size_t parent = (holeIndex - 1) / 2;

		while( holeIndex > 0 && m_vec[parent] < value ) {
			m_trans->swap( holeIndex, parent );

			holeIndex = parent;
			parent = (holeIndex - 1) / 2;
		}

	}

	std::vector<T> &get_vec() {
		return m_vec;
	}

};


template<typename iter, typename _Compare>
void my_push_heap(iter first, iter last, _Compare comp) {

	size_t holeIndex = last - first - 1;

	auto value = *(last - 1);

	size_t parent = (holeIndex - 1) / 2;
	while (holeIndex > 0 && comp(*(first + parent), value)) {
		//*(first + holeIndex) = std::move(*(first + parent));

		std::swap( *(first + holeIndex), *(first + parent) );
		size_t tmp = (first + holeIndex)->get_pos();
		(first + holeIndex)->set_pos( (first + parent)->get_pos() );
		(first + parent)->set_pos(tmp);

//		(first + holeIndex)->set_pos(holeIndex);

		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
//	*(first + holeIndex) = _GLIBCXX_MOVE(value);
//	(first + holeIndex)->set_pos(holeIndex);

}

struct heap_int {
	int v;
	mutable int pos;

	inline void set_pos(size_t pos_) const {
		pos = int(pos_);
	}

	inline size_t get_pos() const {
		return pos;
	}

	bool operator<(const heap_int &other) const {
		return v < other.v;

	}

	heap_int(int v_) :
			v(v_), pos(0) {
	}

	operator int() {
		return v;
	}
};

std::ostream &operator<<(std::ostream &os, const heap_int &hi) {
	os << hi.pos << ": " << hi.v;

	return os;
}

int main() {

	auto z = { 2, 7, 1, 4, 5, 2, 6, 7, 1, 3, 5 };
	trans_heap <heap_int>th;

	{
		trans_heap<heap_int>::trans t(&th);

		for( int v : z ) {
			th.push(heap_int(v));
		}




		auto hv = th.get_vec();
		std::copy(hv.begin(), hv.end(),std::ostream_iterator<heap_int>(std::cout, "\n"));

		assert( std::is_heap( hv.begin(), hv.end() ));

		t.commit();
	}

	{
		trans_heap<heap_int>::trans t(&th);

		for( int v : z ) {
			th.push(heap_int(v+1));
		}




		auto hv = th.get_vec();

		std::cout << "\n";
		std::copy(hv.begin(), hv.end(),std::ostream_iterator<heap_int>(std::cout, "\n"));

		assert( std::is_heap( hv.begin(), hv.end() ));


	}
	auto hv = th.get_vec();
	std::cout << "\n";
	std::copy(hv.begin(), hv.end(),std::ostream_iterator<heap_int>(std::cout, "\n"));

	assert( std::is_heap( hv.begin(), hv.end() ));

	return 0;

	std::vector<heap_int> v = { 2, 7, 1, 4, 5, 2, 6, 7, 1, 3, 5 };
	std::vector<heap_int> w;



	auto comp = std::less<heap_int>();

	for (heap_int x : v) {
		w.push_back(x);
		my_push_heap(w.begin(), w.end(), comp);



	}

//	std::cout << typeid(comp).name() << "\n";

	std::make_heap(v.begin(), v.end(), comp);

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));

	std::cout << "\n";
	std::copy(w.begin(), w.end(),
			std::ostream_iterator<heap_int>(std::cout, "\n"));

	for (int i = 0; i < 10000; i++) {

		size_t r = std::rand() % w.size();

		auto x = w.begin() + r;
		(*x).v++;
		my_push_heap(w.begin(), x + 1, comp);

		std::cout << "\n";
		std::copy(w.begin(), w.end(),
				std::ostream_iterator<heap_int>(std::cout, "\n"));

		std::cout << "is heap: " << std::is_heap(w.begin(), w.end(), comp)
				<< "\n";

		assert(std::is_heap(w.begin(), w.end(), comp));
	}
}
