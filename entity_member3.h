#ifndef __entity_member3_h
#define __entity_member3_h

#include <vector>

#include "entity.h"

class member_type2 : public emember {
public:
    member_type2() : y(0), z(0) {}
    member_type2( int a, int b) : y(a), z(b) {}
    
    
    void test() ;
private:
    
    int y;
    int z;
};

class member_type3 : public emember {
    
public:
    member_type3() ;
    
    void test() ;
    
private:
    std::vector<int> v_;
};

#endif
