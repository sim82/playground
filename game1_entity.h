#ifndef __game1_entity_h
#define __game1_entity_h

#include "entity.h"


/////////////////////////////////////////////////////////////////
// define entity member types and map them to their traits
/////////////////////////////////////////////////////////////////

const static size_t ID_TYPE1 = 0;
const static size_t ID_TYPE2 = 1;
const static size_t ID_TYPE3 = 2;
const static size_t ID_2D_POINT = 3;
const static size_t ID_HUNTER = 4;
const static size_t ID_PLAYER_CHARACTER = 5;
const static size_t ID_THINKER = 6;
const static size_t ID_TYPE_LAST = 7;

class member_type2;
class member_type3;
class member_type1;
class member_2d_point;
class member_thinker;
class member_hunter;
class member_player_character;


ENTITY_DECLARE_MEMBER_TRAITS(member_type1, ID_TYPE1)
ENTITY_DECLARE_MEMBER_TRAITS(member_type2, ID_TYPE2)
ENTITY_DECLARE_MEMBER_TRAITS(member_type3, ID_TYPE3)
ENTITY_DECLARE_MEMBER_TRAITS(member_2d_point, ID_2D_POINT)
ENTITY_DECLARE_MEMBER_TRAITS(member_thinker, ID_THINKER)
// ENTITY_DECLARE_MEMBER_TRAITS(member_hunter, ID_HUNTER)
// ENTITY_DECLARE_MEMBER_TRAITS(member_player_character, ID_PLAYER_CHARACTER)


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


class member_type1 : public emember {
public:
    member_type1() : x(0) {}
private:
    int x;
};


class member_type2 : public emember {
public:
    member_type2() : x(0) {}
private:
    int x;
};

class member_type3 : public emember {
public:
    member_type3() : x(0) {}
private:
    int x;
};

class member_2d_point : public emember {
public:
    member_2d_point( int x, int y ) : x_(x), y_(y) {}
    
    int x() const {
        return x_;
    }
    
    int y() const {
        return y_;
    }
    
    void move( int dx, int dy ) {
        x_ += dx;
        y_ += dy;
    }
    
    void set( int x, int y ) {
        x_ = x;
        y_ = y;
    }
    
private:
    int x_;
    int y_;
};

class member_thinker : public emember {
public:
    virtual void think( double time ) = 0;
};

class member_hunter : public member_thinker {
public:
    virtual void think( double time ) ;
private:
};

class member_player_character : public member_thinker {
public:
    virtual void think( double time ) ;
private:
};


extern std::vector<entity_ptr> global_prey;

#endif