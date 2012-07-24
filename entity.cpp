#include <cstdint>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "entity.h"
// #include "entity_member1.h"
// #include "entity_member3.h"

entity_store *entity_ptr::global_store = nullptr;
#if ENTITY_PTR_SHARED
std::shared_ptr<entity> entity_ptr::lock() {
    auto sp = wp_.lock();
    
    if( sp == nullptr ) {
        std::cout << "lookup\n";
        wp_ = ( global_store->get( *this ));
        sp = wp_.lock();
        
    }
    
    
    if( sp == nullptr ) {
        throw std::runtime_error( "bad entity ptr" );
    }
    
    return sp;
}
#else

entity* entity_ptr::lock() {
    if( ep_ == nullptr ) {
        ep_ = global_store->get(*this).get();
    }
    
    return ep_;
}
#endif

//typedef boost::uuids::random_generator uuid_generator;


class entity_store::uuid_generator : private boost::uuids::random_generator {
public:
    uuid_generator() : boost::uuids::random_generator(ran_) {
        // by default uuids::random_generator generator would use some (garbage) data to
        // seed the rng. I think this is a horrible idea, as it messes up valgrind 
        // (and I don't want to define valgrind exceptions for every rng). Also
        // how can they be sure that the garbage data is really less deterministic
        // than a simple timestamp... is there any proof or is this just handwaving?
        
        // If a simple time is no good enough I would rather depend on something 
        // timing dependent (like the number of nano seconds spent in a usleep(10) call etc.
        
        ran_.seed(time(NULL));
    }
    
    using boost::uuids::random_generator::operator();
private:
    boost::mt19937 ran_;
    //ran.seed(time(NULL)); // one should likely seed in a better way
};

entity_store::entity_store() 
  : uuid_generator_(make_unique<uuid_generator>()) 
{
    
}

std::shared_ptr<entity> entity_store::create() {
    auto id = (*uuid_generator_)();
    
    auto it = entity_map_.emplace( id, std::make_shared<entity>(id) );
    
    assert( it.second ); // make sure that there was not already an entity with the same uuid in the map
    return it.first->second; // it.first is a map iterator -> it.first->second is the value
}


std::shared_ptr<entity> entity_store::get(const uuid& id) {
    auto it = entity_map_.find( id );
    
    if( it == entity_map_.end() ) {
        return nullptr;
    }
    
    return it->second;
    
}













emember& entity::member_unchecked(size_t name) const {
#if 0
    assert( members_valid_ );
    auto it = std::lower_bound( members_.begin(), members_.end(), ipair( name, 0 ));
    
    assert( it != members_.end() ); // TODO: add real error handling
    assert( it->key_ == name );
    
    
    return *it->value_;
#endif
    auto mp = member_map_.find(name);
    
    assert( mp != member_map_.end() );
    
    return *(*mp);
}
emember& entity::member_unchecked(size_t name) {
    
#if 0
    if( !members_valid_ ) {
        std::sort( members_.begin(), members_.end() );
        members_valid_ = true;
    }
    
    auto it = std::lower_bound( members_.begin(), members_.end(), ipair( name, 0 ));
    
    assert( it != members_.end() ); // TODO: add real error handling
    assert( it->key_ == name );
    
    
    return *it->value_;
#endif
    auto mp = member_map_.find(name);
    
    assert( mp != member_map_.end() );
    
    return *(*(mp));
    
}
void entity::add_member_unchecked(size_t name, std::unique_ptr< emember > m) {
#if 0
    members_.push_back( ipair( name, std::move(m) ));
    members_valid_ = false;
    
    const bool do_immediate_resort = true;
    
    if( do_immediate_resort ) {
        std::sort( members_.begin(), members_.end() );
        members_valid_ = true;
    }
#endif
    m->set_entity( this );
    bool b = member_map_.set( name, std::move(m) );
    
    
    assert( b );
    

}
void entity::fabricate_member(size_t name) {
    add_member_unchecked( name, member_factory(name));
}
void entity::fabricate_members(std::initializer_list< size_t > names) {
        
        for( auto name : names ) {
            add_member_unchecked( name, member_factory(name));
        }
    }
void entity::add_interaction(size_t name1, std::shared_ptr< entity > entity2, size_t name2) {
        assert( entity2 != nullptr );
        
        
//         // if it is a pointer to this, don't actually store a shared_ptr to self, because it would be a circular 
//         // reference
//         if( entity2.get() == this ) {
//             entity2.reset(); 
//         }
        
        interactions_.emplace_back( name1, name2, entity2 );
    }
void entity::run_interactions() {
        for( auto &ip : interactions_ ) {
            
//             entity *other = ip.entity2_.get();
//             if( other == nullptr ) {
//                 other = this;
//             }
            auto other = ip.entity2_.lock();
            if( other == nullptr ) {
                //throw std::runtime_error( "interaction with expired entity" );
                std::cerr << "interaction with expired entity\n";
                continue;
                
            } 
            
            dispatch_interaction( *this, *other, ip.name1_, ip.name2_ );
            
        }
    }
entity::~entity() {
//     print_info();
    
//     std::cerr << "~entity\n";
}

void entity::print_info() {
    std::cout << "entity: " << id_ << "\n";
    
    for( size_t i = 0; i <= member_map_.max_id(); ++i ) {
        auto it = member_map_.find(i);
        if( it != member_map_.end() ) {
            std::cout << "member " << i << " " << it->get() << "\n";
        }
    }
}

emember::~emember() {}
entity_store::~entity_store() {}



