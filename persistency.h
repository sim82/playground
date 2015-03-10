#ifndef PERSISTENCY_H
#define PERSISTENCY_H

#include <fstream>
#include <cstdint>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <string>
#include <cassert>
#include <typeinfo>

namespace persist {

class oarchive {
public:
    oarchive( const char * name ) : os_(name) {

    }

    void persist( bool & v ) {
        int tmp = v ? 1 : 0;
        os_ << tmp << " ";
    }

    void persist( u_int8_t & v ) {
        os_ << int(v) << " ";
    }

    void persist( int8_t & v ) {
        os_ << int(v) << " ";
    }


    void persist( u_int16_t & v ) {
        os_ << v << " ";
    }

    void persist( int16_t & v ) {
        os_ << v << " ";
    }

    void persist( u_int32_t & v ) {
        os_ << v << " ";
    }

    void persist( int32_t & v ) {
        os_ << v << " ";
    }

    void persist( u_int64_t & v ) {
        os_ << v << " ";
    }

    void persist( int64_t & v ) {
        os_ << v << " ";
    }

    void persist( double & v ) {
        os_ << v << " ";
    }
    void persist( float & v ) {
        os_ << v << " ";
    }

    void persist( std::string & str ) {
        os_ << str.size() << " ";
        os_ << str << " ";
    }


#if 0
    // const versions

    void persist( const bool & v ) {
        int tmp = v ? 1 : 0;
        os_ << tmp << " ";
    }

    void persist( const u_int8_t & v ) {
        os_ << int(v) << " ";
    }

    void persist( const int8_t & v ) {
        os_ << int(v) << " ";
    }


    void persist( const u_int16_t & v ) {
        os_ << v << " ";
    }

    void persist( const int16_t & v ) {
        os_ << v << " ";
    }

    void persist( const u_int32_t & v ) {
        os_ << v << " ";
    }

    void persist( const int32_t & v ) {
        os_ << v << " ";
    }

    void persist( const u_int64_t & v ) {
        os_ << v << " ";
    }

    void persist( const int64_t & v ) {
        os_ << v << " ";
    }

    void persist( const double & v ) {
        os_ << v << " ";
    }
    void persist( const float & v ) {
        os_ << v << " ";
    }

    void persist( const std::string & str ) {
        os_ << str.size() << " ";
        os_ << str << " ";
    }

    // end const versions
#endif

//    void persist( const std::string & str ) {
//        os_ << str.size() << " ";
//        os_ << str << " ";
//    }

    template<typename T>
    void persist( T & v ) {
        const char *name = typeid(T).name();

        std::string tn(name);
        persist( tn );

        v.persist( *this );
    }

    template<typename Iter>
    void persist_range( Iter first, Iter last ) {
        for( ; first != last; ++first ) {
            persist( *first );
        }
    }

    template<typename T>
    void persist( std::vector<T> & v ) {
        os_ << v.size() << " ";
        persist_range( v.begin(), v.end() );
    }

    template<typename T>
    void persist( std::deque<T> & v ) {
        os_ << v.size() < " ";
        persist_range( v.begin(), v.end() );
    }

    // this is a special case such that persist_range can be used for std::map and friends...
    template<typename T1, typename T2>
    void persist( std::pair<const T1,T2> & p ) {
        // cast away constness of key type. we know (=trust) that oarchive::persist implementations treat their arguments as const, even without explicit const signature.
        // NOTE: otherwise we would have to provide const ans non-const versions for all 'persist' methods and the same metods could no longer be used for input and output.
        // It makes no sense to persist const memebers anyway...

        persist(*const_cast<T1 *>(&(p.first)));
        persist(p.second);
    }

    template<typename Tkey, typename Tvalue>
    void persist( std::map<Tkey, Tvalue> & v ) {
        os_ << v.size() << " ";
        persist_range( v.begin(), v.end() );
    }

    template<typename Tkey, typename Tvalue>
    void persist( std::unordered_map<Tkey, Tvalue> & v ) {
        os_ << v.size() << " ";
        persist_range( v.begin(), v.end() );
    }

    template<typename Tkey, typename Tvalue>
    void persist( std::multimap<Tkey, Tvalue> & v ) {
        os_ << v.size() << " ";
        persist_range( v.begin(), v.end() );
    }

    template<typename Tkey, typename Tvalue>
    void persist( std::unordered_multimap<Tkey, Tvalue> & v ) {
        os_ << v.size() << " ";
        persist_range( v.begin(), v.end() );
    }

private:
    template<typename T>
    void persist( T * v ) {

    }

//    void persist( char *v, size_t len ) {
//        os_ << len;
//        for( size_t i = 0; i < len; ++i ) {
//            os_ << v[i];
//        }
//    }


private:
    std::ofstream os_;
};


class iarchive {
public:
    iarchive( const char * name ) : is_(name) {

    }

    void persist( bool & v ) {
        int tmp;
        is_ >> tmp;

        v = tmp != 0;
    }

    void persist( u_int8_t & v ) {
        int tmp;
        is_ >> tmp;

        v = tmp;
    }

    void persist( int8_t & v ) {
        int tmp;
        is_ >> tmp;

        v = tmp;
    }


    void persist( u_int16_t & v ) {
        is_ >> v;
    }

    void persist( int16_t & v ) {
        is_ >> v;
    }

    void persist( u_int32_t & v ) {
        is_ >> v;
    }

    void persist( int32_t & v ) {
        is_ >> v;
    }

    void persist( u_int64_t & v ) {
        is_ >> v;
    }

    void persist( int64_t & v ) {
        is_ >> v;
    }

    void persist( float & v ) {
        is_ >> v;
    }

    void persist( double & v ) {
        is_ >> v;
    }

    void persist( std::string & str ) {
        size_t s;
        is_ >> s;
        is_.get(); // skip space
        str.reserve(s);

        for( size_t i = 0; i < s; ++i ) {
            char c = is_.get();
            str.push_back(c);
        }
        assert( s == str.size() );
    }

    template<typename T>
    void persist( T & v ) {
        const char *name = typeid(T).name();

        std::string tn;

        persist(tn);
        assert( tn == name );

        v.persist( *this );
    }

    template<typename Iter>
    void persist_range( Iter first, Iter last ) {
        for( ; first != last; ++first ) {
            persist( *first );
        }
    }

    template<typename T>
    void persist( std::vector<T> & v ) {
        size_t s = 0;
        is_ >> s;
        v.resize(s);
        persist_range( v.begin(), v.end() );
    }

    template<typename T>
    void persist( std::deque<T> & v ) {
        size_t s = 0;
        is_ >> s;
        v.resize(s);
        persist_range( v.begin(), v.end() );
    }

    template<typename T1, typename T2>
    void persist( std::pair<T1,T2> & p ) {
        persist(p.first);
        persist(p.second);
    }


//    template<typename Tiiter, typename Toiter>
//    void persist_range( Tiiter ifirst, ) {
//        size_t s = 0;
//        is_ >> s;

//        for( size_t i = 0; i < s; ++i ) {
//            std::pair<Tkey, Tvalue> p;
//            persist(p);
//            v.emplace( std::move(p));
//        }
//    }


    template<typename Tkey, typename Tvalue>
    void persist( std::map<Tkey, Tvalue> & v ) {
        size_t s = 0;
        is_ >> s;

        for( size_t i = 0; i < s; ++i ) {
            std::pair<Tkey, Tvalue> p;
            persist(p);
            v.emplace( std::move(p));
        }
    }


    template<typename Tkey, typename Tvalue>
    void persist( std::unordered_map<Tkey, Tvalue> & v ) {
        size_t s = 0;
        is_ >> s;

        for( size_t i = 0; i < s; ++i ) {
            std::pair<Tkey, Tvalue> p;
            persist(p);
            v.emplace( std::move(p));
        }
    }

private:
    template<typename T>
    void persist( T * v ) {

    }

//    void persist( char *v, size_t len ) {
//        os_ << len;
//        for( size_t i = 0; i < len; ++i ) {
//            os_ << v[i];
//        }
//    }


private:
    std::ifstream is_;
};



//template<typename T>
//class dynarray_wrap {
//public:
//    explicit dynarray_wrap( T * vp, size_t s ) : vp_(vp), s_(s) {

//    }


//    template<typename Archive>
//    void persist( Archive & ar ) {
//        ar & s_;
//        for( size_t i = 0; i < s_; ++i ) {
//            ar & vp_[i];
//        }
//    }

//private:
//    T *vp_;
//    size_t s_;
//};
//template<typename T>
//dynarray_wrap<T> dynarray( T *vp, size_t s ) {
//    return dynarray_wrap<T>(vp,s);
//}




} // namespace persist

template<typename Archive, typename T>
Archive & operator&( Archive &ar, T & v ) {
    ar.persist(v);

    return ar;
}


template<typename Archive, typename T, size_t s>
Archive & operator&( Archive & ar, T(&a)[s] ) {
    for( size_t i = 0; i < s; ++i ) {
        ar & a[i];
    }

    return ar;
}



#endif // PERSISTENCY_H
