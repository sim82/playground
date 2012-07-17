#include <boost/math/tools/roots.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <iostream>


struct func {

    float f( float x ) {
        ;
        return cos(x);
    }

    boost::math::tuple<float,float> operator()( float x ) {
        //x -= 2;
        return boost::math::make_tuple( f(x), f(x+0.001) - f( x-0.001) );
    }
};

int main() {
    float x = boost::math::tools::newton_raphson_iterate( func(), 0.0f, -10.0f, 10.0f, 16 );

    std::cout << "x: " << x << "\n";
}
