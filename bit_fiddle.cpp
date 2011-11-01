#include <iostream>

#include <cassert>

#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <sys/mman.h>

typedef int (*func_t)(int);

int call( func_t f ) {
	return f(2);
}

template<typename T1, typename T2>
std::pair<T1,T2> operator>>(T1 &&v1, T2 &&v2) {
	return std::pair<T1,T2>(v1,v2);
}

int main() {
	std::map<std::string,int> m1 = { "a" >> 1, std::string("b") >> 2, std::string("c") >> 3 };

	for( auto &x : m1 ) {
		std::cout << x.first << " " << x.second << "\n";
	}

	int fd = open( "test.bin", O_RDONLY );

	assert( fd > 0 );

	void *base = mmap(0, 4096, PROT_READ|PROT_EXEC, MAP_SHARED, fd, 0 );

	assert( base != 0 );

	std::cout << "base: " << base << "\n";


	func_t f = (func_t) base;

	int r = call(f);

	std::cout << r << "\n";

}
