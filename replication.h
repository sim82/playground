#ifndef REPLICATION_H
#define REPLICATION_H
//#include "Shared/LinearMath.h"
#include <vector>

#define IMPLANT_BOILERPLATE \
    Trep rep_; \
public: \
    inline Trep &rep() { \
        return rep_; \
    } \
    inline Thost &host() { \
        return static_cast<Thost &>(*this); \
    } \


class send_replicator /*: public replicator*/ {
public:

    //read_replicator() : buf_int_(0) {}
    void start() {
        buf_int_.clear();
    }

//    send_replicator & operator&( int & v ) {
//        buf_int_.push_back(v);
//        return *this;
//    }

//    send_replicator & operator&( Vector3 & v ) {
//        buf_Vector3_.push_back(v);
//        return *this;
//    }

    void rep( int & v ) {
        buf_int_.push_back(v);

    }

//    void rep( Vector3 & v ) {
//        buf_Vector3_.push_back(v);

//    }

//private:
    std::vector<int> buf_int_;
//    std::vector<Vector3> buf_Vector3_;
};




class recv_replicator /*: public replicator*/ {
public:
    void start( const std::vector<int> &input ) {
        buf_int_ = input;
        iter_int_ = buf_int_.begin();
    }

    void rep( int & v ) {
        v = *iter_int_;
        ++iter_int_;

    }

//private:
    std::vector<int> buf_int_;
    std::vector<int>::iterator iter_int_;
};


template<typename T>
send_replicator &operator&( send_replicator &rep, T &v ) {
    rep.rep(v);
    return rep;
}

template<typename T>
recv_replicator &operator&( recv_replicator &rep, T &v ) {
    rep.rep(v);
    return rep;
}


#endif // REPLICATION_H
