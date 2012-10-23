#include "entity.h"

#include "game1_entity.h"

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

std::vector<entity_ptr> global_prey;

void member_interaction( member_type1 &m1, member_type2 &m2 ) {
    std::cout << "blub 1 2\n";
    
    std::cout << "m2: ";
    
}

void member_interaction( member_type1 &m1, member_type1 &m2 ) {
    std::cout << "blub 1 1\n";
}

void member_interaction( member_type1 &m1, member_type3 &m2 ) {
    std::cout << "blub 1 3\n";
    
}

static inline int clamp( int d ) {
    if( d > 1 ) {
        return 1;
    } else if( d < -1 ) {
        return -1;
    } else {
        return 0;
    }
}

static volatile bool do_nothing = true;

void member_hunter::think(double time) {
    
    
    
    assert( !global_prey.empty() );
    entity_ptr &best_prey = global_prey.front();
    
    
//     for( auto &p : global_prey ) {
//         
//     }
    
    auto prey_ent = best_prey.lock();
    auto &prey_pos = prey_ent->member<member_2d_point>();
    
    int x = prey_pos.x();
    int y = prey_pos.y();
    
    auto &my_pos = entity_->member<member_2d_point>();
    int my_x = my_pos.x();
    int my_y = my_pos.y();
    
    
    
    int dx = clamp(x - my_x);
    int dy = clamp(y - my_y);
    
    
    my_pos.move( dx, dy );
}
void member_player_character::think(double time) {
    
}


