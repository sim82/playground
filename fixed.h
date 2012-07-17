/*
Copyright (c) 2006 Henry Strickland & Ryan Seto

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

        (* http://www.opensource.org/licenses/mit-license.php *)
*/
#include <iomanip>
#include <cstdlib>
#include <stdint.h>
template<typename T, const size_t BP>
class fixed {

private:

    T g; // the guts

    //     const static int BP= 16;  // how many low bits are right of Binary Point
    const static int BP2= BP*2;  // how many low bits are right of Binary Point
    const static int BPhalf= BP/2;  // how many low bits are right of Binary Point

    static double STEP() { return 1.0 / (1LL<<BP); }  // smallest step we can represent

    // for private construction via guts
    enum FixedRaw { RAW };
    fixed(FixedRaw, T guts) : g(guts) {}


public:
    fixed() : g(0) {}
    fixed(const fixed& a) : g( a.g ) {}
    fixed(float a) : g( T(a / (float)STEP()) ) {}
    fixed(double a) : g( T(a / (double)STEP()) ) {}
    fixed(int a) : g( a << BP ) {}
    fixed(long a) : g( a << BP ) {}
    fixed& operator =(const fixed& a) { g= a.g; return *this; }
    fixed& operator =(float a) { g= fixed(a).g; return *this; }
    fixed& operator =(double a) { g= fixed(a).g; return *this; }
    fixed& operator =(int a) { g= fixed(a).g; return *this; }
    fixed& operator =(long a) { g= fixed(a).g; return *this; }

    operator float() { return g * (float)STEP(); }
    operator double() { return g * (double)STEP(); }
    operator int() { return g>>BP; }
    operator long() { return g>>BP; }

    fixed operator +() const { return fixed(RAW,g); }
    fixed operator -() const { return fixed(RAW,-g); }

    fixed operator +(const fixed& a) const { return fixed(RAW, g + a.g); }
    fixed operator -(const fixed& a) const { return fixed(RAW, g - a.g); }
#if 1
    // more acurate, using long long
    fixed operator *(const fixed& a) const { return fixed(RAW,  (T)( ((long long)g * (long long)a.g ) >> BP)); }
#else
    // faster, but with only half as many bits right of binary point
    fixed operator *(const fixed& a) const { return fixed(RAW, (g>>BPhalf) * (a.g>>BPhalf) ); }
#endif
    fixed operator /(const fixed& a) const { return fixed(RAW, T( (((long long)g << BP2) / (long long)(a.g)) >> BP) ); }

    fixed operator +(float a) const { return fixed(RAW, g + fixed(a).g); }
    fixed operator -(float a) const { return fixed(RAW, g - fixed(a).g); }
    fixed operator *(float a) const { return fixed(RAW, (g>>BPhalf) * (fixed(a).g>>BPhalf) ); }
    fixed operator /(float a) const { return fixed(RAW, T( (((long long)g << BP2) / (long long)(fixed(a).g)) >> BP) ); }

    fixed operator +(double a) const { return fixed(RAW, g + fixed(a).g); }
    fixed operator -(double a) const { return fixed(RAW, g - fixed(a).g); }
    fixed operator *(double a) const { return fixed(RAW, (g>>BPhalf) * (fixed(a).g>>BPhalf) ); }
    fixed operator /(double a) const { return fixed(RAW, T( (((long long)g << BP2) / (long long)(fixed(a).g)) >> BP) ); }

    fixed& operator +=(fixed a) { return *this = *this + a; return *this; }
    fixed& operator -=(fixed a) { return *this = *this - a; return *this; }
    fixed& operator *=(fixed a) { return *this = *this * a; return *this; }
    fixed& operator /=(fixed a) { return *this = *this / a; return *this; }

    fixed& operator +=(int a) { return *this = *this + (fixed)a; return *this; }
    fixed& operator -=(int a) { return *this = *this - (fixed)a; return *this; }
    fixed& operator *=(int a) { return *this = *this * (fixed)a; return *this; }
    fixed& operator /=(int a) { return *this = *this / (fixed)a; return *this; }

    fixed& operator +=(long a) { return *this = *this + (fixed)a; return *this; }
    fixed& operator -=(long a) { return *this = *this - (fixed)a; return *this; }
    fixed& operator *=(long a) { return *this = *this * (fixed)a; return *this; }
    fixed& operator /=(long a) { return *this = *this / (fixed)a; return *this; }

    fixed& operator +=(float a) { return *this = *this + a; return *this; }
    fixed& operator -=(float a) { return *this = *this - a; return *this; }
    fixed& operator *=(float a) { return *this = *this * a; return *this; }
    fixed& operator /=(float a) { return *this = *this / a; return *this; }

    fixed& operator +=(double a) { return *this = *this + a; return *this; }
    fixed& operator -=(double a) { return *this = *this - a; return *this; }
    fixed& operator *=(double a) { return *this = *this * a; return *this; }
    fixed& operator /=(double a) { return *this = *this / a; return *this; }

    bool operator ==(const fixed& a) const { return g == a.g; }
    bool operator !=(const fixed& a) const { return g != a.g; }
    bool operator <=(const fixed& a) const { return g <= a.g; }
    bool operator >=(const fixed& a) const { return g >= a.g; }
    bool operator  <(const fixed& a) const { return g  < a.g; }
    bool operator  >(const fixed& a) const { return g  > a.g; }

    bool operator ==(float a) const { return g == fixed(a).g; }
    bool operator !=(float a) const { return g != fixed(a).g; }
    bool operator <=(float a) const { return g <= fixed(a).g; }
    bool operator >=(float a) const { return g >= fixed(a).g; }
    bool operator  <(float a) const { return g  < fixed(a).g; }
    bool operator  >(float a) const { return g  > fixed(a).g; }

    bool operator ==(double a) const { return g == fixed(a).g; }
    bool operator !=(double a) const { return g != fixed(a).g; }
    bool operator <=(double a) const { return g <= fixed(a).g; }
    bool operator >=(double a) const { return g >= fixed(a).g; }
    bool operator  <(double a) const { return g  < fixed(a).g; }
    bool operator  >(double a) const { return g  > fixed(a).g; }
    
    const T&guts() const { return g; }
        
};

template<typename T, const size_t BP>
inline fixed<T,BP> operator +(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)+b; }

template<typename T, const size_t BP>
inline fixed<T,BP> operator -(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)-b; }

template<typename T, const size_t BP>
inline fixed<T,BP> operator *(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)*b; }

template<typename T, const size_t BP>
inline fixed<T,BP> operator /(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)/b; }

template<typename T, const size_t BP>
inline bool operator ==(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a) == b; }
template<typename T, const size_t BP>
inline bool operator !=(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a) != b; }
template<typename T, const size_t BP>
inline bool operator <=(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a) <= b; }
template<typename T, const size_t BP>
inline bool operator >=(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a) >= b; }
template<typename T, const size_t BP>
inline bool operator  <(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)  < b; }
template<typename T, const size_t BP>
inline bool operator  >(float a, const fixed<T,BP>& b) { return fixed<T,BP>(a)  > b; }


template<typename T, const size_t BP>
inline fixed<T,BP> operator +(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)+b; }
template<typename T, const size_t BP>
inline fixed<T,BP> operator -(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)-b; }
template<typename T, const size_t BP>
inline fixed<T,BP> operator *(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)*b; }
template<typename T, const size_t BP>
inline fixed<T,BP> operator /(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)/b; }

template<typename T, const size_t BP>
inline bool operator ==(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a) == b; }
template<typename T, const size_t BP>
inline bool operator !=(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a) != b; }
template<typename T, const size_t BP>
inline bool operator <=(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a) <= b; }
template<typename T, const size_t BP>
inline bool operator >=(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a) >= b; }
template<typename T, const size_t BP>
inline bool operator  <(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)  < b; }
template<typename T, const size_t BP>
inline bool operator  >(double a, const fixed<T,BP>& b) { return fixed<T,BP>(a)  > b; }

template<typename T, const size_t BP>
int& operator +=(int& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a + b; return a; }
template<typename T, const size_t BP>
int& operator -=(int& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a - b; return a; }
template<typename T, const size_t BP>
int& operator *=(int& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a * b; return a; }
template<typename T, const size_t BP>
int& operator /=(int& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a / b; return a; }

template<typename T, const size_t BP>
long& operator +=(long& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a + b; return a; }
template<typename T, const size_t BP>
long& operator -=(long& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a - b; return a; }
template<typename T, const size_t BP>
long& operator *=(long& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a * b; return a; }
template<typename T, const size_t BP>
long& operator /=(long& a, const fixed<T,BP>& b) { a = (fixed<T,BP>)a / b; return a; }

template<typename T, const size_t BP>
float& operator +=(float& a, const fixed<T,BP>& b) { a = a + b; return a; }
template<typename T, const size_t BP>
float& operator -=(float& a, const fixed<T,BP>& b) { a = a - b; return a; }
template<typename T, const size_t BP>
float& operator *=(float& a, const fixed<T,BP>& b) { a = a * b; return a; }
template<typename T, const size_t BP>
float& operator /=(float& a, const fixed<T,BP>& b) { a = a / b; return a; }

template<typename T, const size_t BP>
double& operator +=(double& a, const fixed<T,BP>& b) { a = a + b; return a; }
template<typename T, const size_t BP>
double& operator -=(double& a, const fixed<T,BP>& b) { a = a - b; return a; }
template<typename T, const size_t BP>
double& operator *=(double& a, const fixed<T,BP>& b) { a = a * b; return a; }
template<typename T, const size_t BP>
double& operator /=(double& a, const fixed<T,BP>& b) { a = a / b; return a; }


template<const size_t BP>
struct base_helper {
};

template<>
struct base_helper<10> {
    const static size_t base = 10000;
    const static size_t width = 4;
};

template<>
struct base_helper<16> {
    const static size_t base = 100000;
};

template<>
struct base_helper<32> {
    const static size_t base = 10000000000;
};




template<typename T,const size_t BP>
std::ostream &operator<<( std::ostream &os, fixed<T,BP> v ) {
    
    const T dec_max = 1 << BP;
    const T dec_mask = dec_max - 1;
//     std::cout << "x: " << x << "\n";
    T g = v.guts();
    T gz = (g & dec_mask);
    
    T ga;
    if( g >= 0 ) {
        ga = g>>BP;
    } else {
        gz = dec_max - gz;
        ga = -((g>>BP) + 1);
//         if( ga == 0 ) {
            os << "-";
//         }
    }
    
    const T base = base_helper<BP>::base;
    const T width = base_helper<BP>::width;
    
    os << ga << "." << std::setw(width) << std::setfill('0');
    
    T r = (base * gz)/dec_max;
//     
//     for( T p = base / 10; p != 1; p /= 10 ) {
//         if( r < p ) {
//             os << '0';
//         }
//     }
    os << r;
//     if( r < 10 ) {
//         os << "000" << r;
//     } else if( r < 100 ) {
//         os << "00" << r;
//     } else if( r < 1000 ) {
//         os << "0" << r;
//     } else {
//         os << r;
//     }
    return os;
    
}


typedef fixed<int,16> fixed16;
typedef fixed<int64_t,32> fixed32;

typedef fixed<int64_t,10> fixed48;
typedef fixed<int32_t,10> fixed22;
