#include <cstddef>

#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <algorithm>
#include <initializer_list>

template <size_t Name>
struct member_traits {};

const static size_t ID_TYPE1 = 0;
const static size_t ID_TYPE2 = 1;
const static size_t ID_TYPE3 = 2;
const static size_t ID_TYPE_LAST = 3;



#define ENTITY_DECLARE_MEMBER_TRAITS(T, member_name ) \
template<>                                            \
struct member_traits<member_name>                     \
{                                                     \
    enum { value = member_name };                     \
    typedef T member_type;                            \
};

class emember;
class entity;
std::unique_ptr<emember> member_factory( size_t name );
void dispatch_interaction( const entity &e1, const entity &e2, size_t name1, size_t name2 );


class emember {
public:
    virtual ~emember() {}
};




template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class entity {
public:
    entity() : members_valid_(false) {}
    
    virtual ~entity() {
        std::cerr << "~entity\n";
    }
    
    typedef std::unique_ptr<emember> emember_ptr;
//     typedef std::pair<size_t,emember_ptr> ekv;
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
    
    
    ///////////////////////////////////////////////////////////////////////////
    // dynamic/unchecked member access methods (for automatic construction, 
    // e.g. deserialization/automatic initialization)
    ///////////////////////////////////////////////////////////////////////////
    
    emember &member_unchecked( size_t name ) const {
        assert( members_valid_ );
        auto it = std::lower_bound( members_.begin(), members_.end(), ipair( name, 0 ));
        
        assert( it != members_.end() ); // TODO: add real error handling
        assert( it->key_ == name );
        
        
        return *it->value_;
    }
    
    emember &member_unchecked( size_t name ) {
        if( !members_valid_ ) {
            std::sort( members_.begin(), members_.end() );
            members_valid_ = true;
        }
        
        auto it = std::lower_bound( members_.begin(), members_.end(), ipair( name, 0 ));
        
        assert( it != members_.end() ); // TODO: add real error handling
        assert( it->key_ == name );
        
        
        return *it->value_;
    }
    
    
    

    void add_member_unchecked( size_t name, std::unique_ptr<emember> m ) {
        members_.push_back( ipair( name, std::move(m) ));
        members_valid_ = false;
        
        const bool do_immediate_resort = true;
        
        if( do_immediate_resort ) {
            std::sort( members_.begin(), members_.end() );
            members_valid_ = true;
        }
    }
    
 

    ///////////////////////////////////////////////////////////////////////////
    // statically type-checked front end (=for 'human consuption')
    // 
    // these methods will ensure at compile time that the member 
    // type/id pair matches the definition made with ENTITY_DECLARE_MEMBER_TRAITS
    ///////////////////////////////////////////////////////////////////////////
    
    template<size_t name>
    typename member_traits<name>::member_type &member() const {
        emember &m = member_unchecked( member_traits<name>::value );
        
        auto p = dynamic_cast<typename member_traits<name>::member_type *>(&m);
       
        assert( p != nullptr );
        return *p;
        //         return std::static_pointer_cast<typename member_traits<name>::member_type>( member_unchecked( member_traits<name>::value ));
    }

    template<size_t name>
    typename member_traits<name>::member_type &member() {
        // doing the dynamic cast + error check here is just a precaution in case someone messes up the entity with 
        // an unchecked add. Ideally, a static cast is enough, because the members as statically checked
        // upon insertion.
        
        auto p = dynamic_cast<typename member_traits<name>::member_type *>( &member_unchecked( member_traits<name>::value ));
        assert( p != nullptr );
        return *p;
//         return std::static_pointer_cast<typename member_traits<name>::member_type>( member_unchecked( member_traits<name>::value ));
    }


    template<size_t name>
    void add_member( std::unique_ptr<typename member_traits<name>::member_type> m ) {
        // the call got through static typecheck, so it's safe to hand over to 'dynamic polymorphism mode'...
        add_member_unchecked( name, std::move(m) );
    }
    
    template<size_t Name,typename... Args>
    void make_member(Args&&... args) {
        return add_member<Name>(make_unique<typename member_traits<Name>::member_type>(std::forward<Args>(args)...));
    }
    
    
    // interaction management stuff
    void add_interaction( size_t name1, std::shared_ptr<entity> entity2, size_t name2 ) {
        assert( entity2 != nullptr );
        
        
//         // if it is a pointer to this, don't actually store a shared_ptr to self, because it would be a circular 
//         // reference
//         if( entity2.get() == this ) {
//             entity2.reset(); 
//         }
        
        interactions_.emplace_back( name1, name2, entity2 );
    }
    
    void run_interactions() {
        for( auto ip : interactions_ ) {
            
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
    
    
    /////////////////////////////////////////////////////////////
    // dynamic (but safe) factory functions for standard
    // constructed members
    /////////////////////////////////////////////////////////////
    
    void fabricate_member( size_t name ) {
        add_member_unchecked( name, member_factory(name));
    }
    
    void fabricate_members( std::initializer_list<size_t> names ) {
        
        for( auto name : names ) {
            add_member_unchecked( name, member_factory(name));
        }
    }
    
private:
    
    
    std::vector<ipair> members_;
    bool members_valid_;
    
    struct interaction {
        interaction( size_t name1, size_t name2, std::shared_ptr<entity> entity2 ) : name1_(name1), name2_(name2), entity2_(entity2) {}
        
        size_t name1_;
        size_t name2_;
        std::weak_ptr<entity> entity2_;
    };
    std::vector<interaction> interactions_;
};



class member_type1 : public emember {
public:
    member_type1() : x(0) {}
private:
    int x;
};

class member_type2 : public emember {
public:
    member_type2() : y(0), z(0) {}
    member_type2( int a, int b) : y(a), z(b) {}
    
    
    void test() {
        std::cout << y << " " << z << "\n";
    }
private:
    
    int y;
    int z;
};

class member_type3 : public emember {
    
public:
    member_type3() {
        v_.push_back(666);
    }
    
    void test() {
        std::cout << v_.front() << "\n";
    }
    
private:
    std::vector<int> v_;
};


ENTITY_DECLARE_MEMBER_TRAITS(member_type1, ID_TYPE1)
ENTITY_DECLARE_MEMBER_TRAITS(member_type2, ID_TYPE2)
ENTITY_DECLARE_MEMBER_TRAITS(member_type3, ID_TYPE3)

#undef ENTITY_DECLARE_MEMBER_TRAITS




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


template<size_t Name1, size_t Name2>
void member_interaction( const entity &e1, const entity &e2 ) {
    auto m1 = e1.member<Name1>();
    auto m2 = e2.member<Name2>();

//     std::cerr << "member_interction: " << Name1 << " " << Name2 << std::endl;
    
//     assert( m1 != nullptr );
//     assert( m2 != nullptr );
//     member_interaction_impl<Name1,Name2> inter;
//     inter( *m1, *m2 );
//     
    member_interaction( m1, m2 );
}

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

template<size_t Name,typename... Args>
std::unique_ptr<typename member_traits<Name>::member_type> member_factory(Args&&... args) {
    return make_unique<typename member_traits<Name>::member_type>(std::forward<Args>(args)...);
}


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

int main() {
    auto a(std::make_shared<entity>());
//     auto c(std::make_shared<entity>());
    //std::shared_ptr<entity> a(std::make_shared<entity>());
    
    a->add_member<ID_TYPE1>( make_unique<member_type1>() );   
    //a.add_member<ID_TYPE2>( std::make_shared<member_type2>() );   
    a->make_member<ID_TYPE2>( 7, 8 );   
    auto b = std::make_shared<entity>();
    
   // a.add_member<ID_TYPE1>( std::make_shared<member_type1>() );   
    //b.add_member<ID_TYPE3>( std::make_shared<member_type3>() );   
    b->fabricate_members( {ID_TYPE1, ID_TYPE3} );
//     b.add_member_unchecked( ID_TYPE3, std::make_shared<member_type2>() );   
    
    auto &x = a->member<ID_TYPE1>();
    member_type2 &y = a->member<ID_TYPE2>();
    
    //member_interaction<ID_TYPE1,ID_TYPE2>( a, a );
    member_interaction<ID_TYPE1,ID_TYPE3>( *a, *b );
    
    std::cout << &x << " " << &y << "\n";
    
//     entity xxx[1024];
    
//     std::cout << "size: " << sizeof( xxx ) << "\n";
    
    a->add_interaction( ID_TYPE1, a, ID_TYPE2 );
    a->add_interaction( ID_TYPE1, b, ID_TYPE3 );
    a->run_interactions();
    
    b.reset();
    a->run_interactions();
    
    
}