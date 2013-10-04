#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include <iostream>
#include <algorithm>

#include <typeinfo>

#include <chrono>
#include "buddy.h"

#include <cxxabi.h>


class perf_time {
    typedef std::chrono::high_resolution_clock clock;



public:
    perf_time( const char *name ) : name_(name), start_(clock::now())
    {

    }


    ~perf_time() {
        clock::duration dt = clock::now() - start_;
        std::cout << "perf_time: " << name_ << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() << "ms\n";
    }

public:
    const char *name_;
    clock::time_point start_;
};

std::string demangle( const char *tname ) {
    int status;
    char *realname = abi::__cxa_demangle(tname, 0, 0, &status);


    std::string sn( realname );

    free(realname);
    return sn;
}

class actor;
class game;

namespace {
game *s_game = nullptr;

game *get_game() {
    return s_game;
}
}

class persistable {
public:
    virtual void load() = 0;
    virtual void save() = 0;
};

class replication_stub {
public:
    virtual void delta() = 0;
};

class identifyable {
public:
    virtual int64_t get_id() const = 0;
    virtual game *get_game() const = 0;
};

class makeable {
public:
    virtual std::string get_url() const = 0;
};

template<typename T>
class cloneable {
public:
    /**
     * @brief Create a copy of this object.
     * @return Copy of this object.
     */
    virtual std::unique_ptr<T> clone() = 0;
};

static size_t s_size_dc = 0;

template<typename Tout, typename Tself>
class default_cloner : public virtual cloneable<Tout> {
public:
    std::unique_ptr<Tout> clone() {
        s_size_dc += sizeof(Tself);
        return std::unique_ptr<Tout>( new Tself( dynamic_cast<Tself&>(*this)));
    }
};

class actor : public persistable, public makeable, public virtual identifyable, public virtual cloneable<actor> {
public:
    virtual void think( double dt ) = 0;
    virtual ~actor() {}
};


class game {
    class actor_generation {
    public:
        actor_generation() : gen_count_(0) {

        }

//        actor_generation( actor_generation &other ) {
//            assign(other);
//        }

//        actor_generation &operator=(actor_generation &other) {
//            assign(other);
//            return *this;
//        }

        void clone_from( actor_generation &other ) {
            actors_.resize( other.actors_.size() );
            std::transform( other.actors_.begin(), other.actors_.end(), actors_.begin(), []( std::unique_ptr<actor> &a ) {
                return a->clone();
            });
            gen_count_ = other.gen_count_ + 1;
        }


        static void swap( actor_generation &g1, actor_generation &g2 ) {
            std::swap( g1.actors_, g2.actors_ );
            std::swap( g1.gen_count_, g2.gen_count_ );
        }
        std::vector<std::unique_ptr<actor>> actors_;
        size_t gen_count_;
    };

public:

    void increase_generation() {
        s_size_dc = 0;

        actor_generation::swap( gen_n1_, gen_n_ );
        gen_n_.clone_from( gen_n1_ );
       // std::cout << "gen size: " << s_size_dc << "\n";
    }

    void put( int64_t id, std::unique_ptr<actor> actor ) {
        gen_n_.actors_[id] = std::move(actor);
    }


    int64_t alloc_id() {
#if 0
        for( auto it = gen_n_.actors_.begin(); it != gen_n_.actors_.end(); ++it ) {
            if( it->get() == nullptr ) {
                return std::distance( gen_n_.actors_.begin(), it );
            }
        }

        gen_n_.actors_.push_back(nullptr);

        return gen_n_.actors_.size() - 1;
#else
        //TODO: test the buddy
        size_t id = bb_.allocate();
        if( gen_n_.actors_.size() <= id ) {
            gen_n_.actors_.resize( id + 1 );
        }

        assert( gen_n_.actors_[id] == nullptr );
        return gen_n_.actors_.size() - 1;
#endif
    }

    actor &get( int64_t id ) {
        return *(gen_n1_.actors_[id].get());
    }

private:
    actor_generation gen_n_;
    actor_generation gen_n1_;

    buddy::dynamic_buddy<512> bb_;

};




// actor interfaces

class id_keeper : public virtual identifyable {
public:
    id_keeper( int64_t id ) : id_(id) /*, game_(game) */{}

    id_keeper( const identifyable &other ) : id_(other.get_id()) /*, game_(other.get_game() )*/ {}

    int64_t get_id() const override {
        return id_;
    }

    game *get_game() const override {
        return ::get_game();
    }

private:
    int64_t id_;
   // game *game_;
};


class actor_ref : private id_keeper {
public:
    actor_ref() : id_keeper( 0 ) {}

    actor_ref( int64_t id ) : id_keeper(id) {}

    actor_ref( const identifyable &other ) : id_keeper (other) {

    }

    actor &operator*() {
        game *g = id_keeper::get_game();
        return g->get(id_keeper::get_id());
    }
    actor *operator->() {
        return &(*(*this));
    }

//{
//        game *g = identifyable::get_game();
//        return g->get(identifyable::get_id());
//    }
};


template<typename T>
class game_ref : private id_keeper {
public:
    game_ref() : id_keeper( 0 ) {}

    game_ref( int64_t id ) : id_keeper(id) {}

    game_ref( const identifyable &other ) : id_keeper (other) {

    }

    T &operator*() {
        game *g = id_keeper::get_game();

        auto &tmp = g->get(id_keeper::get_id());
        return dynamic_cast<T&>(tmp);
    }
    T *operator->() {
        return &(*(*this));
    }

//{
//        game *g = identifyable::get_game();
//        return g->get(identifyable::get_id());
//    }
};


class volumetric_actor : public actor {
public:
    virtual void affect_scene() = 0;
    virtual void volume() const = 0;

};


class moving_actor : public volumetric_actor {
public:
    virtual void setup_move() = 0;
    virtual void move( double dt ) = 0;
    virtual void velocity() const = 0;

};


// implementatons

class slidemover : public persistable {
public:

    void volume() const {

    }

    void move( double dt ) {

    }
};

class slidemove_actor : public moving_actor, protected slidemover, public id_keeper {
public:
    slidemove_actor( int64_t id ) : id_keeper(id) {}

//    std::unique_ptr<actor> clone() override {
//        return std::unique_ptr<actor>( new slidemove_actor(*this));
//    }

    void volume() const override {
        return slidemover::volume();
    }


    void think( double dt ) override {

    }

    void affect_scene() override {

    }

    void setup_move() override {

    }
    void move( double dt ) override {
        slidemover::move( dt );
    }

    void velocity() const override {

    }

    void load() override {
//        slidemover::load();
    }
    void save() override {
//        slidemover::save();
    }

    std::string get_url() const override {
        return "slidemove_actor";
    }

//    int64_t get_id() const override {
//        return id_keeper::get_id();
//    }
};


class monster : public slidemove_actor, public virtual default_cloner<actor, monster>  {
public:
//    std::unique_ptr<actor> clone() override {
//        s_size_dc += sizeof(*this);

//        return std::unique_ptr<actor>( new monster(*this));
//    }

    monster( int64_t id, int64_t enemy ) : slidemove_actor(id), enemy_(enemy) {}

    monster( int64_t id ) : slidemove_actor(id) {}


    std::string get_url() const override {
        return "monster";
    }

    void think( double dt ) override {
        std::cout << "enemy: " << demangle(typeid(*enemy_).name()) << " " << enemy_->get_id() << "\n";

    }

private:
    game_ref<volumetric_actor> enemy_;
    char payload_[128];
};


class scary_monster : public slidemove_actor , public virtual default_cloner<actor, scary_monster> {
public:
//    std::unique_ptr<actor> clone() override {
//        return std::unique_ptr<actor>( new scary_monster(*this));
//    }

    scary_monster( int64_t id, int64_t enemy ) : slidemove_actor(id), enemy_(enemy) {}

    scary_monster( int64_t id ) : slidemove_actor(id) {}


    std::string get_url() const override {
        return "scary_monster";
    }

    void think( double dt ) override {
        std::cout << "enemy: " << demangle(typeid(*enemy_).name()) << " " << enemy_->get_id() << "\n";

    }

private:
    game_ref<volumetric_actor> enemy_;
    char payload_[128];
};

class invisible_gadget : public actor, public id_keeper, public virtual default_cloner<actor,invisible_gadget> {
public:
    invisible_gadget( int64_t id ) : id_keeper(id) {}


    std::string get_url() const override {
        return "invisible_gadget";
    }

//    std::unique_ptr<actor> clone() {
//        return std::unique_ptr<actor>( new invisible_gadget(*this));
//    }
    void load() override {
//        slidemover::load();
    }
    void save() override {
//        slidemover::save();
    }

    void think(double dt) override {

    }

    char payload_[64];
};

class player : public persistable {
public:
    void volume() const {

    }

    void move( double dt ) {

    }

    void load() override {

    }

    void save() override {

    }
};

class player_actor : public moving_actor, protected player, public id_keeper , public default_cloner<actor, player_actor> {
public:
//    std::unique_ptr<actor> clone() override {
//        return std::unique_ptr<actor>( new player_actor(*this));
//    }


    player_actor( int64_t id ) : id_keeper(id) {}

    void volume() const override {
        return player::volume();
    }


    void think( double dt ) override {

    }

    void affect_scene() override {

    }
    void velocity() const override {

    }

    void setup_move() override {

    }
    void move( double dt ) override {
        player::move( dt );
    }

    void load() override {
//        slidemover::load();
    }
    void save() override {
//        slidemover::save();

    }

    std::string get_url() const override {
        return "player_actor";
    }

//    int64_t get_id() const override {
//        return id_keeper::get_id();
//    }

    char payload_[128];
};

template<typename... Args>
std::unique_ptr<actor> make_actor( int64_t id, const std::string &url, Args... args ) {
//    if( url == "slidemove_actor" ) {
//        return std::unique_ptr<actor>(new slidemove_actor( id ));
//    } else

  //  std::cout << "make: id: " << id << "\n";

    if( url == "player_actor" ) {
        return std::unique_ptr<actor>(new player_actor( id ));
    } else if( url == "monster" ) {
        return std::unique_ptr<actor>(new monster( id, args... ));
    } else if( url == "scary_monster" ) {
        return std::unique_ptr<actor>(new scary_monster( id, args... ));
    } else if( url == "invisible_gadget" ) {
        return std::unique_ptr<actor>(new invisible_gadget( id ));
    }

    return std::unique_ptr<actor>();

}





int main() {
    game g;

    s_game = &g;

    int64_t id1 = g.alloc_id();
    {
        auto ma = make_actor( id1, "scary_monster");
        g.put( id1, std::move(ma));
    }

    int64_t id2 = g.alloc_id();
    {
        auto ma = make_actor( id2, "player_actor");
        g.put( id2, std::move(ma));
    }

    g.increase_generation();

    game_ref<volumetric_actor> a2( id2 );

    int64_t id3 = g.alloc_id();
    {
        auto ma = make_actor( id3, "monster", a2->get_id());
        g.put( id3, std::move(ma));
    }


    game_ref<volumetric_actor> a( id1 );

    g.increase_generation();
    game_ref<monster> a3( id3 );


    std::cout << "type: " << demangle(typeid(*a).name()) << " " << a->get_id() << "\n";
    std::cout << "type: " << demangle(typeid(*a2).name()) << " " << a2->get_id() << "\n";
    std::cout << "type: " << demangle(typeid(*a3).name()) << " " << a3->get_id() << "\n";

    auto &ar = *a;
    auto &a2r = *a2;
    auto &a3r = *a3;


    a3->think(1);

    std::cout << "size: " << sizeof(slidemove_actor) << "\n";

    std::cout << "size: " << sizeof(monster) << "\n";

    std::cout << "size: " << sizeof(invisible_gadget) << "\n";

    std::vector<std::string> actor_classes{"player_actor", "monster", "scary_monster", "invisible_gadget" };
   // abort();

    {
        perf_time t1( "create" );
        for( int i = 0; i < 100000; ++i ) {
            int64_t id = g.alloc_id();
            const auto &type = actor_classes[rand() % actor_classes.size()];

            auto ma = make_actor( id, type.c_str() );
            g.put( id, std::move(ma));


        }
    }
    {
        perf_time t1( "generation" );

        for( int i = 0; i < 100; ++i ) {
            g.increase_generation();
        }
    }
  //  abort();
}
