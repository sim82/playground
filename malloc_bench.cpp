#include <chrono>
#include <array>
#include <vector>
#include <iostream>
#include <memory>

class perf_time {
    typedef std::chrono::high_resolution_clock clock;



public:
    perf_time( const char *name ) : name_(name), start_(clock::now())
    {

    }


    inline ~perf_time() {
        clock::duration dt = clock::now() - start_;
        //std::cout << "perf_time: " << name_ << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() << "ms\n";
        std::cout << "perf_time: " << name_ << ": " << std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count() << "ns\n";
    }

public:
    const char *name_;
    clock::time_point start_;
};



class test {
public:

    test() {
//        std::fill( buf_.begin(), buf_.end(), 1 );
    }

    //std::array<char, 128*2> buf_;
    char buf_[128];
};

int main() {



    const size_t num = 100;


    {
        std::vector<std::unique_ptr<test>> v;
        v.reserve( num );
        perf_time pt( "t1" );
        for( size_t i = 0; i < num; ++i ) {
            v.emplace_back( new test() );
        }
        new char[128];
    }

    {
        std::vector<std::unique_ptr<test>> v;
        v.reserve( num );
        perf_time pt( "t2" );
        for( size_t i = 0; i < num; ++i ) {
            v.emplace_back( new test() );
        }
    }

}
