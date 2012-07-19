#include "entity_custom.h"
#include "entity_member1.h"
#include "entity_member3.h"
// a small dose of preprocessor magick to remove redundancy
#define ENTITY_FACTORY_CASE( ID ) case ID: return member_factory<ID>();

std::unique_ptr<emember> member_factory( size_t name ) {
    
    switch( name ) {
        ENTITY_FACTORY_CASE( ID_TYPE1 )
        ENTITY_FACTORY_CASE( ID_TYPE2 )
        ENTITY_FACTORY_CASE( ID_TYPE3 )
    default:
        throw std::runtime_error( "unimplemented entity member factory" );
    
    };
}
#undef ENTITY_FACTORY_CASE


#define MEMBER_TYPE_PAIR_CASE( ID1, ID2 ) case ID1 * ID_TYPE_LAST + ID2: member_interaction<ID1,ID2>(e1,e2); break;

void dispatch_interaction( const entity &e1, const entity &e2, size_t name1, size_t name2 ) {
    switch( name1 * ID_TYPE_LAST + name2 ) {
        MEMBER_TYPE_PAIR_CASE(ID_TYPE1,ID_TYPE1)
        MEMBER_TYPE_PAIR_CASE(ID_TYPE1,ID_TYPE2)
        MEMBER_TYPE_PAIR_CASE(ID_TYPE1,ID_TYPE3)
        default:
            throw std::runtime_error( "unimplemented entity member interaction" );            
          
    }
}

#undef MEMBER_TYPE_PAIR_CASE



void member_interaction( member_type1 &m1, member_type2 &m2 ) {
    std::cout << "blub 1 2\n";
    
    std::cout << "m2: ";
    m2.test();
}

void member_interaction( member_type1 &m1, member_type1 &m2 ) {
    std::cout << "blub 1 1\n";
}

void member_interaction( member_type1 &m1, member_type3 &m2 ) {
    std::cout << "blub 1 3\n";
    m2.test();
}


