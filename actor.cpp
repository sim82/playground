#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include <iostream>
#include <algorithm>

#include <typeinfo>

#include <cxxabi.h>


std::string demangle( const char *tname ) {
    int status;
    char *realname = abi::__cxa_demangle(tname, 0, 0, &status);


    std::string sn( realname );

    free(realname);
    return sn;
}

class actor;
class game;




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
    virtual std::unique_ptr<T> clone() = 0;
};

class actor : public persistable, public makeable, public virtual identifyable, public cloneable<actor> {
public:
    virtual void think( double dt ) = 0;
    virtual ~actor() {}
};


class game {
    class actor_generation {
    public:
        actor_generation() {

        }

        actor_generation( actor_generation &other ) {
            assign(other);
        }

        actor_generation &operator=(actor_generation &other) {
            assign(other);
            return *this;
        }

        void assign( actor_generation &other ) {
            actors_.resize( other.actors_.size() );
            std::transform( other.actors_.begin(), other.actors_.end(), actors_.begin(), []( std::unique_ptr<actor> &a ) {
                return a->clone();
            });
        }

        std::vector<std::unique_ptr<actor>> actors_;

    };

public:

    void increase_generation() {
        gen_n1_ = gen_n_;
    }

    void put( int64_t id, std::unique_ptr<actor> actor ) {
        gen_n_.actors_[id] = std::move(actor);
    }


    int64_t alloc_id() {
        for( auto it = gen_n_.actors_.begin(); it != gen_n_.actors_.end(); ++it ) {
            if( it->get() == nullptr ) {
                return std::distance( gen_n_.actors_.begin(), it );
            }
        }

        gen_n_.actors_.push_back(nullptr);

        return gen_n_.actors_.size() - 1;
    }

    actor &get( int64_t id ) {
        return *(gen_n1_.actors_[id].get());
    }

private:
    actor_generation gen_n_;
    actor_generation gen_n1_;

};




// actor interfaces

class id_keeper : public virtual identifyable {
public:
    id_keeper( int64_t id, game *game ) : id_(id), game_(game) {}

    id_keeper( const identifyable &other ) : id_(other.get_id()), game_(other.get_game() ) {}

    int64_t get_id() const override {
        return id_;
    }

    game *get_game() const override {
        return game_;
    }

private:
    int64_t id_;
    game *game_;
};


class actor_ref : private id_keeper {
public:
    actor_ref() : id_keeper( 0, nullptr ) {}

    actor_ref( int64_t id, game *game ) : id_keeper(id, game) {}

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
    game_ref() : id_keeper( 0, nullptr ) {}

    game_ref( int64_t id, game *game ) : id_keeper(id, game) {}

    game_ref( const identifyable &other ) : id_keeper (other) {

    }

    T &operator*() {
        game *g = id_keeper::get_game();
        return dynamic_cast<T&>(g->get(id_keeper::get_id()));
    }
    T *operator->() {
        return &(*(*this));
    }

//{
//        game *g = identifyable::get_game();
//        return g->get(identifyable::get_id());
//    }
};


class visible_actor : public actor {
public:
    virtual void affect_scene() = 0;
    virtual void visible_volume() const = 0;

};


class moving_actor : public visible_actor {
public:
    virtual void move( double dt ) = 0;
    virtual void moving_volume() const = 0;

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
    slidemove_actor( int64_t id, game *game ) : id_keeper(id, game) {}

    std::unique_ptr<actor> clone() override {
        return std::unique_ptr<actor>( new slidemove_actor(*this));
    }

    void visible_volume() const override {
        return slidemover::volume();
    }
    void moving_volume() const override {
        return slidemover::volume();
    }

    void think( double dt ) override {

    }

    void affect_scene() override {

    }

    void move( double dt ) override {
        slidemover::move( dt );
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


class monster : public slidemove_actor {
public:
    std::unique_ptr<actor> clone() override {
        return std::unique_ptr<actor>( new monster(*this));
    }

    monster( int64_t id, game *game, int64_t enemy ) : slidemove_actor(id, game), enemy_(enemy, game) {}

    monster( int64_t id, game *game ) : slidemove_actor(id, game) {}


    std::string get_url() const override {
        return "monster";
    }

    void think( double dt ) override {
        std::cout << "enemy: " << demangle(typeid(*enemy_).name()) << " " << enemy_->get_id() << "\n";

    }

private:
    game_ref<visible_actor> enemy_;
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

class player_actor : public moving_actor, protected player, public id_keeper {
public:
    std::unique_ptr<actor> clone() override {
        return std::unique_ptr<actor>( new player_actor(*this));
    }


    player_actor( int64_t id, game *game ) : id_keeper(id, game) {}

    void visible_volume() const override {
        return player::volume();
    }
    void moving_volume() const override {
        return player::volume();
    }

    void think( double dt ) override {

    }

    void affect_scene() override {

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
};

template<typename... Args>
std::unique_ptr<moving_actor> make_moving_actor( int64_t id, game *game, const std::string &url, Args... args ) {
    if( url == "slidemove_actor" ) {
        return std::unique_ptr<moving_actor>(new slidemove_actor( id, game ));
    } else if( url == "player_actor" ) {
        return std::unique_ptr<moving_actor>(new player_actor( id, game ));
    } else if( url == "monster" ) {
        return std::unique_ptr<moving_actor>(new monster( id, game, args... ));
    }

    return std::unique_ptr<moving_actor>();

}





int main() {
    game g;

    int64_t id1 = g.alloc_id();
    {
        auto ma = make_moving_actor( id1, &g, "slidemove_actor");
        g.put( id1, std::move(ma));
    }

    int64_t id2 = g.alloc_id();
    {
        auto ma = make_moving_actor( id2, &g, "player_actor");
        g.put( id2, std::move(ma));
    }

    g.increase_generation();

    game_ref<visible_actor> a2( id2, &g );

    int64_t id3 = g.alloc_id();
    {
        auto ma = make_moving_actor( id3, &g, "monster", a2->get_id());
        g.put( id3, std::move(ma));
    }


    game_ref<visible_actor> a( id1, &g );

    g.increase_generation();
    game_ref<monster> a3( id3, &g );


    std::cout << "type: " << demangle(typeid(*a).name()) << " " << a->get_id() << "\n";
    std::cout << "type: " << demangle(typeid(*a2).name()) << " " << a2->get_id() << "\n";
    std::cout << "type: " << demangle(typeid(*a3).name()) << " " << a3->get_id() << "\n";

    a3->think(1);

    std::cout << "size: " << sizeof(slidemove_actor) << "\n";

    std::cout << "size: " << sizeof(monster) << "\n";

}
