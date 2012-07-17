#ifndef __entity_member1_h
#define __entity_member1_h

#include "entity.h"

class member_type1 : public emember {
public:
    member_type1() : x(0) {}
private:
    int x;
};

#endif