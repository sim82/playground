#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <sys/mman.h>
#include <unistd.h>

typedef int (*func_t)(int);

int call( func_t f ) {
	return f(2);
}

template<typename iiter>
int64_t mycall( iiter first, iiter last, void *addr ) {
	int64_t x = 2;

	int64_t iaddr = int64_t(addr) + 0x0;

	int64_t y;


	assert( std::distance(first, last) == 3);

	iiter it = first;

	int64_t a = *it++;
	int64_t b = *it++;
	int64_t c = *it++;


	asm ("movq %0, %%rax;"
		 "push %%rax;"
		 "movq %1, %%rax;"
		 "push %%rax;"
		 "movq %2, %%rax;"
	     "push %%rax;"

			:
			: "r"(a), "r"(b), "r"(c)
			: "%rax"
	);
	asm(
		 "movq %1, %%rax;"
		 "callq *%%rax;"
		 "movq %%rax, %0;"
	            : "=r"(y)
	            :"r"(iaddr)        /* output */
	            :"%rax"        /* clobbered register */
    );

	while( first++ != last ) {
		asm( "pop %%rax;"
				: : : "%rax"
				);
	}

	return y;

}

template<typename T1, typename T2>
std::pair<T1,T2> kv(T1 &&v1, T2 &&v2) {
	return std::pair<T1,T2>(v1,v2);
}

class env {
public:
	class value {
	public:
		value( off_t sp_off ) : sp_off_ (sp_off) {}

		off_t sp_off() const {
			return sp_off_;
		}

	private:
		off_t sp_off_;

	};

	class scope {

	public:
		scope( off_t bottom ) : stack_bottom_(bottom), stack_top_(bottom )
		{

		}

		value declare( const std::string &name ) {
			if( std::find(names_.begin(), names_.end(), name) != names_.end() ) {
				throw std::runtime_error( "local value redeclared" );
			}

			names_.push_back(name);
			values_.push_back(value(stack_top_));
			stack_top_ += 4;

			return values_.back();
		}

		off_t stack_bottom() {
			return stack_bottom_;
		}
		off_t stack_top() {
			return stack_top_;
		}

		int find( const std::string &name ) {
			auto it = std::find( names_.begin(), names_.end(), name );

			if( it == names_.end() ) {
				return -1;
			} else {
				return std::distance( names_.begin(), it );
			}
		}

		value get(int idx) {
			return values_.at(idx);
		}
	private:

		//std::map<std::string,value> local_values_;

		std::vector<std::string> names_;
		std::vector<value> values_;
		off_t stack_bottom_;
		off_t stack_top_;

	};

	env() : stack_top_(0) {
		push_scope();

	}

	void push_scope() {

		off_t stack_top;
		if( scopes_.empty() ) {
			stack_top = 0;

		} else {
			stack_top = scopes_.back().stack_top();
		}

		scopes_.push_back(scope(stack_top));
	}
	void pop_scope() {
		scopes_.pop_back();
	}

	scope &cur_scope() {
		return scopes_.back();
	}

	value get_value( const std::string &name ) {
		for( auto rit = scopes_.rbegin(); rit != scopes_.rend(); ++rit ) {
			int idx = rit->find(name);
			if( idx != -1 ) {
				return rit->get(idx);
			}
		}

		throw std::runtime_error( "cannot find value");
	}

private:

	std::vector<scope> scopes_;

	off_t stack_top_;
};

template<typename T>
class carray {
public:

	typedef T              value_type;
	typedef T*             iterator;
	typedef const T*       const_iterator;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;


	carray( T * ptr, size_type size ) : ptr_(ptr), size_(size)
	{

	}

	// iterator support
	iterator begin() { return ptr_; }
	const_iterator begin() const { return ptr_; }
	iterator end() { return ptr_+size_; }
	const_iterator end() const { return ptr_+size_; }

	        // reverse iterator support
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

	// operator[]
	reference operator[](size_type i) { return ptr_[i]; }
	const_reference operator[](size_type i) const { return ptr_[i]; }

	// at() with range check
	reference at(size_type i) { rangecheck(i); return ptr_[i]; }
	const_reference at(size_type i) const { rangecheck(i); return ptr_[i]; }

	// front() and back()
	reference front() { return ptr_[0]; }
	const_reference front() const { return ptr_[0]; }
	reference back() { return ptr_[size_-1]; }
	const_reference back() const { return ptr_[size_-1]; }

	// size is constant
	size_type size() { return size_; }
	bool empty() { return false; }
	size_type max_size() { return size_; }




	// direct access to data (read-only)
	const T* data() const { return ptr_; }

	// use array as C array (direct read/write access to data)
	T* data() { return ptr_; }


	// assign one value to all elements
	void assign (const T& value)
	{
		std::fill_n(begin(),size(),value);
	}


private:

	// check range (may be private because it is static)
	void rangecheck (size_type i) {
		if (i >= size()) {
			throw std::out_of_range("array<>: index out of range");
		}
	}


	T *ptr_;
	size_t size_;


};


class posix_file {
public:
	posix_file() = delete;
	posix_file( const posix_file & ) = delete;

	posix_file( const char * name, int mode ) {
		fd_ = open( name, mode );

		std::cout << "open: " << fd_ << "\n";

		assert( fd_ > 0 );

	}

	~posix_file() {
		if( good() ) {
			::close( fd_ );
		}
	}

	bool good() {
		return fd_ >= 0;
	}

	int fd() const {
		std::cerr << "fd3: " << fd_ << "\n";

		return fd_;
	}

private:
	int fd_;

};


class mmapped_region {

public:
	mmapped_region( size_t len, int prot, int flags, int fd, off_t off ) {


		base_ = mmap( 0, len, prot, flags, fd, off );
		len_ = len;

		if( base_ == MAP_FAILED ) {
			std::cerr << "errno: " << strerror( errno ) << "\n";
			throw std::runtime_error( "mmap failed. bailing out");
		}
	}
	~mmapped_region() {
		if( base_ != 0 ) {
			munmap( base_, len_ );
		}
	}

	template<typename T = void>
	T *base() {
		return (T *) base_;
	}
private:
	void *base_;
	size_t len_;
};

int main2();

int main2() {
	env e;

	e.cur_scope().declare("a");
	e.cur_scope().declare("b");
	e.cur_scope().declare("c");

	e.push_scope();
	e.cur_scope().declare("d");
	e.cur_scope().declare("e");
	e.cur_scope().declare("f");

	for( std::string n : {"a","b","c","d","e","f"} ) {
		env::value v = e.get_value( n );
		std::cout << n << " " << v.sp_off() << "\n";
	}

	main2();

	return 0;
}

int main() {

	posix_file fd( "test2.bin", O_RDONLY );

	//int fd = open( "test2.bin", O_RDONLY );

	//assert( fd > 0 );
	assert( fd.good() );



	mmapped_region mr( 4096, PROT_READ|PROT_EXEC, MAP_SHARED, fd.fd(), 0 );
	void *base = mr.base<void>();

	//void *base = mmap(0, 4096, PROT_READ|PROT_EXEC, MAP_SHARED, fd, 0 );

	assert( base != 0 );

	std::cout << "base: " << base << "\n";


	std::array<int64_t,3> par = {1,2,3};

	int64_t r = mycall( par.begin(), par.end(), base );
	std::cerr << r << "\n";

//#if 1
//	int64_t x = 2;
//
//	int64_t addr = int64_t(base) + 0x0;
//
//	int64_t y;
//
//	asm ("movq %1, %%rax;"
//	   	 "push %%rax;"
//		 "movq %2, %%rax;"
//		 "callq *%%rax;"
//		 "movq %%rax, %0;"
//		 "pop %%rax;"
//	            : "=r"(y)
//	            :"r"(x), "r"(addr)        /* output */
//	            :"%rax"        /* clobbered register */
//    );
//
//
//
//
//	std::cerr << y << "\n";
//#else
//	func_t f = (func_t) base;
//
//	int r = call(f);
//
//	std::cout << r << "\n";
//
//#endif

	return 0;
}
