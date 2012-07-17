#include <iostream>
#include <valarray>
#include <boost/io/ios_state.hpp>
#include "fixed.h"


int main() {
    //std::vector<fixed16> xa(1024 * 1024)
    //typedef float fp_t;
    auto & os = std::cout;
    {
        float m_x = 0.0;
        float m_y =-1343.13423412312312;
        float m_z = 1.0;
        
        auto m_ele = "FUK";
        
        boost::io::ios_all_saver ias( os );
        os << std::fixed << std::setprecision(4) <<  std::setw(10) <<  m_x <<  std::setw(10) << m_y << std::setw(10) << m_z <<  m_ele[0] << m_ele[1] << m_ele[2] << "  0  0  0  0  0  0  0  0  0  0  0  0\n";
    }
//     std::cout << "'" << std::fixed << std::setw(10) << std::setprecision(4) << 123.1234567890 << "'\n";
//     std::cout << "'" << std::fixed << std::setw(10) << std::setprecision(4) << float(0.0) << "'\n";
//     std::cout << 0.0 << "\n";
    typedef fixed22 fp_t;
#if 0
    
    std::valarray<fp_t> xa(1024 * 1024);
    std::valarray<fp_t> xb(1024 * 1024);
    
    std::valarray<fp_t> xc(1024 * 1024);
    for( size_t i = 0; i < 100; ++i ) {
        xa = 1.11;
        xb = 2.21;
        
        xc = xa + xb;
        
        long sum = xc.sum();
        std::cout << "sum: " << sum << "\n";
    }
#endif
    
    for( float i = -2.0;  i < 2.0; i+= (1/(1024.0*2)) ) {
        fp_t a = i;
        std::cout << i << " " << float(a) << " " << a << "\n";
    }
    
    {
        fp_t a = 1.001;
        fp_t b = 2.0;
        
        std::cout << a << " " << b << "\n";
    }    
    
}