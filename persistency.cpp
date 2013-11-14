#include <iostream>
#include "persistency.h"

class test1 {
public:
    test1( int x ) : a_(x), b_(x), c_(x) {}

    template<typename Archive>
    void persist( Archive &ar ) {
        ar & a_ & b_ & c_;
    }

//private:
    int a_, b_, c_;
};

class test2 : private test1 {
public:
    test2( int x ) : test1(x+1), d_(x == 666) {}

    template<typename Archive>
    void persist( Archive &ar ) {
        test1::persist(ar);
        ar & d_;
    }

//private:
    bool d_;
};

int main() {
    {
        persist::oarchive ar( "save.txt" );

        int a = 1;
        int b[10];

        std::fill( b, b + 10, 123 );

        std::vector<int> c(10, 5);

        std::string d = "abcde space";

        test1 e(666);
        test2 f(666);

        std::map<std::string, std::string> g;
        g["a"] = "x";
        g["b"] = "y";
        g["c"] = "z";

        std::map<int, std::string> h;
        h[1] = "x";
        h[2] = "y";
        h[3] = "z";

        ar & a & b & c & d & e & f & g & h;
    }
    {
        persist::iarchive ar( "save.txt" );

        int a = 0;
        int b[10];

        std::fill( b, b + 10, 0 );

        std::vector<int> c(10, 0);

        std::string d;
        test1 e(0);
        test2 f(0);
        std::map<std::string, std::string> g;
        std::map<int, std::string> h;
        ar & a & b & c & d & e & f & g & h;

        std::cout << a << " " << b[9] << " " << c[9] << " " << d << " " << e.a_ << " " << f.d_ << " " << g["a"] << " " << h[1] << "\n";


    }

    //& dynarray(c, 5);


}
