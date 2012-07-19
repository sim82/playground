#ifndef __entity_h
#define __entity_h

#include <cstddef>
#include <cassert>

#include <array>
#include <memory>
#include <vector>
#include <initializer_list>

#include <boost/uuid/uuid.hpp>
// #include <boost/random/mersenne_twister.hpp>
#include <unordered_map>
#include "id_map.h"



using boost::uuids::uuid;


class entity;
class entity_store;


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}





template <size_t Name>
struct member_traits {};

template <typename MType>
struct member_traits2 {};

#define ENTITY_DECLARE_MEMBER_TRAITS(T, member_name ) \
template<>                                            \
struct member_traits<member_name>                     \
{                                                     \
    enum { value = member_name };                     \
    typedef T member_type;                            \
};                                                    \
template<>                                            \
struct member_traits2<T>                              \
{                                                     \
   enum { value = member_name };                      \
    typedef T member_type;                            \
};


// #undef ENTITY_DECLARE_MEMBER_TRAITS


//////////////////////////////////////////////////
// entity member stuff
//////////////////////////////////////////////////

class emember {
public:
    virtual ~emember();
};

std::unique_ptr<emember> member_factory( size_t name );

void dispatch_interaction( const entity &e1, const entity &e2, size_t name1, size_t name2 );



//////////////////////////////////////////////////
// entity stuff
//////////////////////////////////////////////////

class entity_ptr : private uuid {
public:
    static entity_store *global_store;
    
    entity_ptr( const uuid &id ) : uuid(id) {
        
    }
    
    std::shared_ptr<entity>lock();
    
private:
    std::weak_ptr<entity> wp_;
};



class entity {
public:
    entity( const uuid &id ) : id_(id) {}
    
    virtual ~entity();
    
    const uuid &id() const {
        return id_;
    }
    
    typedef std::unique_ptr<emember> emember_ptr;
//     typedef std::pair<size_t,emember_ptr> ekv;
    
#if 0
    struct ipair {
        typedef size_t K;
        typedef emember_ptr V;
        K key_;
        V value_;
        
        ipair( const K &key, V &&value ) : key_(key), value_(std::move(value)) {}
        ipair() : key_(0), value_(nullptr) {}
        
        inline bool operator<( const ipair &other ) const {
            return key_ < other.key_;
        }
        
        
    };
#endif
    
    ///////////////////////////////////////////////////////////////////////////
    // dynamic/unchecked member access methods (for automatic construction, 
    // e.g. deserialization/automatic initialization)
    ///////////////////////////////////////////////////////////////////////////
    
    emember &member_unchecked( size_t name ) const ;
    emember &member_unchecked( size_t name ) ;
    void add_member_unchecked( size_t name, std::unique_ptr<emember> m ) ;
    
 

    ///////////////////////////////////////////////////////////////////////////
    // statically type-checked front end (=for 'human consuption')
    // 
    // these methods will ensure at compile time that the member 
    // type/id pair matches the definition made with ENTITY_DECLARE_MEMBER_TRAITS
    ///////////////////////////////////////////////////////////////////////////
    
    template<size_t name>
    typename member_traits<name>::member_type &member() const {
        emember &m = member_unchecked( member_traits<name>::value );
        
        
        // doing the dynamic cast + error check here is just a precaution in case someone messes up the entity with 
        // an unchecked add. Ideally, a static cast is enough, because the members as statically checked
        // upon insertion.
        // for release builds it could be replaced by a static cast.
        auto p = dynamic_cast<typename member_traits<name>::member_type *>(&m);
       
        if( p == nullptr ) {
            throw std::runtime_error( "dynamic_cast failed during statically checked member access. member map is messed up..." );
        }
        return *p;
        //         return std::static_pointer_cast<typename member_traits<name>::member_type>( member_unchecked( member_traits<name>::value ));
    }

    template<size_t name>
    typename member_traits<name>::member_type &member() {
        // dynamic_cast: d.t.o.
        
        auto p = dynamic_cast<typename member_traits<name>::member_type *>( &member_unchecked( member_traits<name>::value ));
        
        if( p == nullptr ) {
            throw std::runtime_error( "dynamic_cast failed during statically checked member access. member map is messed up..." );
        }
//         assert( p != nullptr );
        return *p;
//         return std::static_pointer_cast<typename member_traits<name>::member_type>( member_unchecked( member_traits<name>::value ));
    }

    
    template<typename MType>
    MType &member() {
         size_t name = member_traits2<MType>::value;
         auto p = dynamic_cast<MType *>( &member_unchecked( name ));
        
         if( p == nullptr ) {
             throw std::runtime_error( "dynamic_cast failed during statically checked member access. member map is messed up..." );
         }
//         assert( p != nullptr );
        return *p;
    }

    template<size_t name>
    void add_member( std::unique_ptr<typename member_traits<name>::member_type> m ) {
        // the call got through static typecheck, so it's safe to hand over to 'dynamic polymorphism mode'...
        add_member_unchecked( name, std::move(m) );
    }
    
    template<typename MType>
    void add_member( std::unique_ptr<MType> m ) {
        // the call got through static typecheck, so it's safe to hand over to 'dynamic polymorphism mode'...
        add_member_unchecked( member_traits2<MType>::value, std::move(m) );
    }
    
    template<size_t Name,typename... Args>
    void make_member(Args&&... args) {
        return add_member<Name>(make_unique<typename member_traits<Name>::member_type>(std::forward<Args>(args)...));
    }
    template<typename MType,typename... Args>
    void make_member(Args&&... args) {
        return add_member<member_traits2<MType>::value>(make_unique<MType>(std::forward<Args>(args)...));
    }
    
    // interaction management stuff
    void add_interaction( size_t name1, std::shared_ptr<entity> entity2, size_t name2 ) ;
    
    void run_interactions() ;
    
    
    /////////////////////////////////////////////////////////////
    // dynamic (but safe) factory functions for standard
    // constructed members
    /////////////////////////////////////////////////////////////
    
    void fabricate_member( size_t name ) ;
    
    void fabricate_members( std::initializer_list<size_t> names ) ;
    
    
    void print_info() ;
        
private:
    const uuid id_;
    
//     std::vector<ipair> members_;
//     bool members_valid_;
    
    id_map_dynamic<emember_ptr> member_map_;
    
    struct interaction {
        interaction( size_t name1, size_t name2, std::shared_ptr<entity> entity2 ) : name1_(name1), name2_(name2), entity2_(entity2->id()) {}
        
        size_t name1_;
        size_t name2_;
        //std::weak_ptr<entity> entity2_;
        entity_ptr entity2_;
    };
    std::vector<interaction> interactions_;
};






void dispatch_interaction( const entity &e1, const entity &e2, size_t name1, size_t name2 );


template<size_t Name,typename... Args>
std::unique_ptr<typename member_traits<Name>::member_type> member_factory(Args&&... args) {
    return make_unique<typename member_traits<Name>::member_type>(std::forward<Args>(args)...);
}




//////////////////////////////////////////////////////////////////////////
// entity store
//////////////////////////////////////////////////////////////////////////
namespace std {
    
    template<>
    struct hash<uuid> : public __hash_base<size_t, uuid>
    {
        size_t
        operator()( const uuid &id ) const noexcept
        {
            return hash_value( id );
        }
    };
}

// namespace boost { namespace uuids {
//     template<typename Rnd>
//     class basic_random_generator;
//     
//     typedef basic_random_generator<boost::random::mt19937> random_generator;
// }}

// uuid_generator is just an experiment to encapsulate the whole boost::random stuff
// in the implementation file.
// use a template free custom 'uuid_generator' class that is implemented 'in-terms-of'
// the boost class in the implementation file.


class entity_store {
class uuid_generator;
public:
    
    entity_store() ;
    ~entity_store() ;
    std::shared_ptr<entity> create() ;
    std::shared_ptr<entity> get( const uuid &id ) ;
    
private:
    std::unordered_map<uuid, std::shared_ptr<entity>> entity_map_;
    std::unique_ptr<uuid_generator> uuid_generator_;
};




#endif


