#include <iostream>

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "entity.h"
#include "entity_custom.h"
#include "entity_member1.h"
#include "entity_member3.h"



int main2() {
    entity_store es;
    
    
    auto a = es.create();
    
    return 0;
}




int main() {
    
    
    
//     boost::uuids::random_generator uuid_generator;
    
//     auto a(std::make_shared<entity>( uuid_generator() ));
//     auto c(std::make_shared<entity>());
    //std::shared_ptr<entity> a(std::make_shared<entity>());
    
    entity_store es;
    entity_ptr::global_store = &es;
    
    
    
    auto a = es.create();
    
    
    entity_ptr ap( a->id() );
    
    
    auto ax = ap.lock();
    
//     std::shared_ptr<entity> xp(es.create());
//     std::weak_ptr<entity> wp( xp );
//     std::cout << (wp.lock() == nullptr) << "\n";
    
    a->add_member( make_unique<member_type1>() );   
    //a.add_member<ID_TYPE2>( std::make_shared<member_type2>() );   
    ap.lock()->make_member<member_type2>( 7, 8 );   
//     auto b = std::make_shared<entity>(uuid_generator());
    
    auto b = es.create();
    
   // a.add_member<ID_TYPE1>( std::make_shared<member_type1>() );   
    //b.add_member<ID_TYPE3>( std::make_shared<member_type3>() );   
    b->fabricate_members( {ID_TYPE1, ID_TYPE3} );
//     b.add_member_unchecked( ID_TYPE3, std::make_shared<member_type2>() );   
    
    auto &x = a->member<ID_TYPE1>();
    member_type2 &y = a->member<member_type2>();
    
    //member_interaction<ID_TYPE1,ID_TYPE2>( a, a );
    member_interaction<ID_TYPE1,ID_TYPE3>( *a, *b );
    
    std::cout << &x << " " << &y << "\n";
    
//     entity xxx[1024];
    
//     std::cout << "size: " << sizeof( xxx ) << "\n";
    
    a->add_interaction( ID_TYPE1, a, ID_TYPE2 );
    a->add_interaction( ID_TYPE1, b, ID_TYPE3 );
    
    a->run_interactions();
    a->run_interactions();
    b.reset();
    a->run_interactions();
    
    
    a->print_info();
    
    return 0;
}