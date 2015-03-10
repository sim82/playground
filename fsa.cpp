#include <vector>
#include "fsa.h"

using namespace fsa;

class test_base {
public:
};

class test1 : public test_base {
    std::array<char, 15> x_;
};

class test2 : public test_base {
    std::array<char, 17> x_;
};

class test3 : public test_base {
    std::array<char, 33> x_;
};

unique_ptr<test_base> alloc( allocator_chain &ac, size_t type ) {
    switch( type ) {
    case 0:
        return ac.allocate<test1>();
    case 1:
        return ac.allocate<test2>();
    default:
    case 2:
        return ac.allocate<test3>();
    }
}

int main() {
#if 1
    allocator_chain a;

    std::vector<unique_ptr<test_base>> v;
    for( size_t i = 0; i < 1024; ++i ) {
        v.push_back(alloc(a, i % 3));
    }


    for( size_t i = 0; i < 1024; ++i ) {
        //auto &p = v[i];
       // p.second->deallocate(p.first);
        v.pop_back();
    }
#else
    std::unique_ptr<test1> p1;

    allocator<> a(sizeof(test1));


    std::vector<test1 *> pa;
    for(size_t i = 0; i < 1024; ++i ) {
        pa.push_back(a.allocate<test1>());
        std::cout << "alloc: " << i << " " << pa.back() << "\n";
    }

    for( size_t i = 0; i < 1024; i+=2 ) {
        a.deallocate(pa[i]);
        std::cout << "dealloc: " << i << " " << pa[i] << "\n";
    }

    for( size_t i = 0; ;++i ) {
        pa.push_back(a.allocate<test1>());
        std::cout << "alloc2: " << i  << " " << pa.back() << "\n";
        if( pa.back() == nullptr ) {
            break;
        }
    }
#endif
}
