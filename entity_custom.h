#ifndef __entity_custom_h
#define __entity_custom_h

#include "entity.h"



/////////////////////////////////////////////////////////////////
// define entity member types and map them to their traits
/////////////////////////////////////////////////////////////////

const static size_t ID_TYPE1 = 0;
const static size_t ID_TYPE2 = 1;
const static size_t ID_TYPE3 = 2;
const static size_t ID_TYPE_LAST = 3;

class member_type2;
class member_type3;
class member_type1;

ENTITY_DECLARE_MEMBER_TRAITS(member_type1, ID_TYPE1)
ENTITY_DECLARE_MEMBER_TRAITS(member_type2, ID_TYPE2)
ENTITY_DECLARE_MEMBER_TRAITS(member_type3, ID_TYPE3)


///////////////////////////////////////////////////////
// member interaction stuff
///////////////////////////////////////////////////////


void member_interaction( member_type1 &m1, member_type2 &m2 );
void member_interaction( member_type1 &m1, member_type1 &m2 );
void member_interaction( member_type1 &m1, member_type3 &m2 );



std::unique_ptr<emember> member_factory( size_t name );
void dispatch_interaction( const entity &e1, const entity &e2, size_t name1, size_t name2 );
    

///////////////////////////////////////////////////////
// member interaction stuff
///////////////////////////////////////////////////////


void member_interaction( member_type1 &m1, member_type2 &m2 );
void member_interaction( member_type1 &m1, member_type1 &m2 );
void member_interaction( member_type1 &m1, member_type3 &m2 );



template<size_t Name1, size_t Name2>
void member_interaction( const entity &e1, const entity &e2 ) {
    auto m1 = e1.member<Name1>();
    auto m2 = e2.member<Name2>();

    member_interaction( m1, m2 );
}


#endif