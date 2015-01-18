#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

#include "openhash/hash_map.h"

template<typename value_type>
struct default_equal {
    inline bool operator()(const value_type &v1, const value_type &v2 ) const {
        return v1 == v2;
    }
};

template<typename value_type>
struct identity_func {
    inline const value_type& operator()(const value_type &v) {
        return v;
    }
};

template<typename entry_type
         , typename hash_func
         , typename empty
         , typename key_type = entry_type
         , typename entry_to_key_func = identity_func<entry_type>>
         //, typename equal_func = default_equal<entry_type>/*, typename deleted*/>
class hash_table {
    typedef empty empty_xxx;
public:
    template<typename empty_type>
    class iterator_impl /*: private std::vector<entry_type>::iterator*/ {
        typedef typename std::vector<entry_type>::iterator iterator_type;

    public:
        typedef typename  iterator_type::pointer pointer;
        typedef typename  iterator_type::reference reference;

        iterator_impl( iterator_type it, iterator_type end ) : it_(it), end_it_(end) {}

        inline void next_not_null()
        {
            empty e;
            while (true)
            {
                ++it_;
                if ( it_ == end_it_ || (!e.is(*it_)))
                {
                    break;
                }
            }
        }

//        using iterator_type::operator ==;
//        using iterator_type::operator *;
//        using iterator_type::operator->;

        inline bool operator==(iterator_impl other) const {
            return it_ == other.it_;
        }
        inline bool operator!=(iterator_impl other) const {
            return !operator==(other);
        }

        inline reference operator*() {
            return *it_;
        }
        inline pointer operator->() {
            return &(*it_);
        }


        inline iterator_impl& operator++()
        {
          this->next_not_null();
          return *this;
        }
        inline iterator_impl operator++(int)
        {
          iterator t = *this;
          ++(*this);
          return t;
        }
    private:
        iterator_type it_;
        iterator_type end_it_;
    };

    typedef iterator_impl<empty> iterator;

    hash_table( const size_t init_size = 8 )
        : table_(make_table(init_size))
        , num_used_(0)
    {
    }

    iterator begin() {
        iterator it(table_.begin(), table_.end());

        if( empty_.is(*it)) {
            it.next_not_null();
        }
        return it;
    }

    iterator end() {
        return iterator(table_.end(), table_.end());
    }

    void print() {
        std::cout << "size: " << table_.size() << " " << num_used_ << "\n";

        for( size_t i = 0, s = table_.size(); i != s; ++i ) {
            std::cout << i << " " << empty_.is(table_[i]) /*<< " " << deleted_.is(table_[i])*/ << "\n";
        }
    }

    std::vector<entry_type> to_vector() {
        std::vector<entry_type> vec;
        vec.reserve(num_used_);

        for( auto it = table_.begin(), eit = table_.end(); it != eit; ++it ) {
            auto &ent = *it;
            if( !empty_.is(ent) ) {
                vec.push_back(ent);
            }
        }

        return vec;
    }

    inline size_t find_slot(const key_type &entry ) {
        //const size_t s = table_.size();
        size_t i = ht_mod(hash_(entry));
        // search until we either find the key, or find an empty slot.
        while ( !empty_.is(table_[i]) && entry_to_key_(table_[i]) != entry ) {
            i = ht_mod(i + 1);
        }

        return i;
    }

    template<typename... Args>
    void emplace2(const key_type &key, Args&&... args)
    {
     //   return _M_t._M_emplace_unique(std::forward<_Args>(__args)...); }
        check_and_grow();

        const size_t i = find_slot(key);
        //if( empty_.is(table_[i]))
        {
            if( empty_.is(table_[i])) {
                ++num_used_;
            }

            table_[i] = {key, std::forward<Args>(args)...};
        }
    }

    template<typename... Args>
    void emplace(Args&&... args)
    {
        emplace2(std::forward<Args>(args)...);
     //   return _M_t._M_emplace_unique(std::forward<_Args>(__args)...); }
    }
    void insert( const entry_type &entry )
    {
        if( empty_.is(entry_to_key_(entry))) {
            abort();
        }

        check_and_grow();

        const size_t i = find_slot(entry_to_key_(entry));
        //if( empty_.is(table_[i]))
        {
            if( empty_.is(table_[i])) {
                ++num_used_;
            }
            table_[i] = entry;
            ++num_used_;
        }
    }

    void erase(const key_type &entry) {
         size_t i = find_slot(entry);
         if( empty_.is(table_[i])) {
             return;   // key is not in the table
         }
         --num_used_;
         //const size_t s = table_.size();
         size_t j = i;
         while(true) {
             table_[i] = empty_.make();
             r2:

             j = ht_mod(j+1);
             if( empty_.is(table_[j])) {
                 break;
             }
             const size_t k = ht_mod(hash_(entry_to_key_(table_[j])));
             // determine if k lies cyclically in ]i,j]
             // |    i.k.j |
             // |....j i.k.| or  |.k..j i...|
             if ( (i<=j) ? ((i<k)&&(k<=j)) : ((i<k)||(k<=j)) ) {
                 goto r2;
             }
             std::swap(table_[i], table_[j]);
             i = j;
         }

    }

    inline size_t size() const {
        return num_used_;
    }
private:
    void check_and_grow() {
        const static auto max_fill_factor = 0.7;
        if(num_used_ > max_fill_factor * table_.size()) {
            //std::cout << "grow " << table_.size() << "\n";
            std::vector<entry_type> old_table{make_table(table_.size() * 2)};
            table_.swap(old_table);
            num_used_ = 0;

            for( auto it = old_table.begin(), eit = old_table.end(); it != eit; ++it ) {
                auto &ent = *it;
                if( !empty_.is(ent) ) {
                    const size_t i = find_slot(entry_to_key_(ent));

                    if( empty_.is(table_[i]) ) {
                        //std::swap(table_[i], ent);
                        table_[i] = std::move(ent);
                        ++num_used_;
                    } else {
                        // duplicate in old table!?
                        abort();
                    }
                }
            }
        }
    }

    std::vector<entry_type> make_table(size_t size)
    {
        return std::vector<entry_type>(size, empty_.make());
    }

    inline size_t ht_mod(size_t v) {
        //return v % table_.size();
#if 0
        size_t v1 = v % table_.size();
        size_t v2 = v & (table_.size()-1);
        if( v1 != v2 ) {
            abort();
        }
#endif
        return v & (table_.size()-1);
    }

    std::vector<entry_type> table_;
    size_t  num_used_;
    empty   empty_;
    //equal_func equal_;
    entry_to_key_func entry_to_key_;
    hash_func hash_;
};


template<typename entry_type
         , typename hash_func
         , typename empty
         , typename impl_type = hash_table<entry_type, hash_func, empty>>
class set
        : private impl_type
{

public:
    using impl_type::insert;
    using impl_type::emplace;
    using impl_type::erase;
    using impl_type::print;
    using impl_type::to_vector;
private:

};

template<typename hash_func, typename key_type, typename value_type>
struct hash_adapter{
    inline size_t operator()( const std::pair<key_type, value_type> &p ) const {
        const static hash_func hash;
        return hash(p.first);
    }
};

template<typename key_type, typename value_type>
struct equal_adapter{
    inline bool operator()( const std::pair<key_type, value_type> &p1, const std::pair<key_type, value_type> &p2 ) const {
        return p1.first == p2.first;
    }
};


template<typename key_type, typename value_type>
struct entry_to_key_adapter{
    inline const key_type & operator()( const std::pair<key_type, value_type> &p) const {
        return p.first;
    }
};

template<typename empty, typename key_type, typename value_type>
struct empty_adapter{
    inline std::pair<key_type, value_type> make() const {
        const static empty e;
        return {e.make(), value_type()}; //size_t(-1);
    }

    inline bool is( const std::pair<key_type, value_type> &p ) const {
        const static empty e;
        return e.is(p.first);
    }
};

template<typename key_type
         , typename value_type
         , typename hash_func
         , typename empty
         , typename impl_type = hash_table<std::pair<key_type, value_type>
                                           , hash_func//, hash_adapter<hash_func, key_type, value_type>
                                           , empty_adapter<empty, key_type, value_type>
                                           , key_type
                                           , entry_to_key_adapter<key_type, value_type>>>
class map
        : private impl_type
{

public:
    typedef typename impl_type::iterator iterator;

    using impl_type::begin;
    using impl_type::end;
    using impl_type::insert;
    using impl_type::emplace;
    using impl_type::erase;
    using impl_type::print;
    using impl_type::to_vector;
    using impl_type::size;
private:

};

struct size_t_empty {
    inline size_t make() const {
        return 0;
    }

    inline bool is( const size_t &v ) const {
        return v == 0;
    }
};


struct size_t_deleted {
    inline size_t make() const {
        return 1; //size_t(-1);
    }

    inline bool is( const size_t &v ) const {
        return v == 1; // size_t(-1);
    }
};

void test();
void test_map();
void test_map2();


struct test_value {
    test_value() : x_(0) {}
    explicit test_value(size_t x) : x_(x) {}
    //std::array<size_t, 64> x_;
    size_t x_;
    test_value(const test_value &other ) {
        x_ = other.x_;
    }
    test_value(test_value &&other )
        : x_(other.x_)
    {
//        x_ = other.x_;
    }

    test_value &operator=(const test_value &other ) {
        x_ = other.x_;
        return *this;
    }

    test_value &operator=(test_value &&other) {
        std::swap(x_, other.x_);
        return *this;
    }

    bool operator==( const test_value &other ) const {
        return x_ == other.x_;

    }
};

int main() {
    //typedef hash_table<size_t, std::hash<size_t>, size_t_empty/*, size_t_deleted*/> ht_type;

    typedef map<size_t, test_value, std::hash<size_t>, size_t_empty/*, size_t_deleted*/> ht_type;
    ht_type ht;

    ht.emplace(2, test_value(2));
    ht.emplace(2, test_value(2));
    ht.erase(2);
    ht.emplace(2, test_value(2));

//    test_map();
   // test();
    test_map2();
    return 0;


    for( size_t i = 1; i < 10; ++i ) {
        ht.emplace(i, test_value(3));
        ht.print();
    }

    std::cout << ">>>>>>>>>>>>>> erase\n";
    for( size_t i = 1; i < 10; ++i ) {
        ht.erase(i);
        ht.print();
    }

}

void test() {
    typedef set<size_t, std::hash<size_t>, size_t_empty/*, size_t_deleted*/> ht_type;

    ht_type ht;
    typedef std::set<size_t> rm_type;
    rm_type refmap;

    size_t_empty bad1;
    //size_t_deleted bad2;
    typedef std::chrono::high_resolution_clock clock;

    auto t0 = clock::now();
    std::vector<uint32_t> rnum;
    const size_t num_iter = 10000000;
    rnum.reserve(num_iter);

    for(size_t i = 0; i < num_iter * 2; ++i ) {
        rnum.push_back(rand() % 1000);
    }

    auto t1 = clock::now();
#define MY_HT
#define REF_HT

    for( size_t i = 0; i < num_iter; ++i ) {
        size_t value = rnum[i*2];

        while( bad1.is(value ) /*|| bad2.is(value)*/ ) {
            ++value;
        }

        if( rnum[i*2 + 1] % 2 == 0 ) {
#ifdef MY_HT
            ht.insert(value);
#endif
#ifdef REF_HT
            refmap.insert(value);
#endif
        } else {
#ifdef MY_HT
            ht.erase(value);
#endif
#ifdef REF_HT
            refmap.erase(value);
#endif
        }

        if( refmap.size() > 1024 ) {
            std::cout << "big\n";
        }
    }
#undef MY_HT
#undef REF_HT
    auto dt0 = t1 - t0;
    auto dt = clock::now() - t1;

    std::cout << "ms0: " << std::chrono::duration_cast<std::chrono::milliseconds>(dt0).count() << "\n";
    std::cout << "ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() << "\n";

    auto vec = ht.to_vector();
    rm_type cs(vec.begin(), vec.end());

    std::cout << "equal: " << (cs == refmap) << "\n";

}


void test_map() {
    typedef map<size_t, test_value, std::hash<size_t>, size_t_empty/*, size_t_deleted*/> ht_type;

    ht_type m;

    for( size_t i = 1; i < 10; ++i ) {
        m.emplace( i, test_value(2));
    }
//    m.insert( {1, test_value(2)} );
//    //m.insert( {1, 3} );
//    m.emplace( 1, test_value(3) );
    m.print();
}

void test_map2() {
    typedef map<size_t, test_value, std::hash<size_t>, size_t_empty/*, size_t_deleted*/> ht_type;

    ht_type ht;
    //typedef std::unordered_map<size_t, test_value> rm_type;
    typedef std::map<size_t, test_value> rm_type;
    rm_type refmap;

    size_t_empty bad1;
    //size_t_deleted bad2;
    typedef std::chrono::high_resolution_clock clock;

    auto t0 = clock::now();
    std::vector<uint32_t> rnum;
    const size_t num_iter = 10000000;
    rnum.reserve(num_iter);

    for(size_t i = 0; i < num_iter * 2; ++i ) {
        rnum.push_back(rand() % 1000);
    }

    auto t1 = clock::now();
#define MY_HT
#define REF_HT

    for( size_t i = 0; i < num_iter; ++i ) {
        size_t value = rnum[i*2];

        while( bad1.is(value ) /*|| bad2.is(value)*/ ) {
            ++value;
        }

//        std::cout << "value: " << value <<"\n";
        if( rnum[i*2 + 1] % 2 == 0 ) {
#ifdef MY_HT
            ht.emplace(value, test_value(2));
#endif
#ifdef REF_HT
            refmap.emplace(value, test_value(2));
#endif
        } else {
#ifdef MY_HT
            ht.erase(value);
#endif
#ifdef REF_HT
            refmap.erase(value);
#endif
        }

#if defined(MY_HT) && defined(REF_HT)
        if( refmap.size() != ht.size() ) {
            abort();
        }
#endif
        if( refmap.size() > 1024 ) {
            std::cout << "big\n";
        }
    }
#undef MY_HT
#undef REF_HT
    auto dt0 = t1 - t0;
    auto dt = clock::now() - t1;

    std::cout << "ms0: " << std::chrono::duration_cast<std::chrono::milliseconds>(dt0).count() << "\n";
    std::cout << "ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() << "\n";

    //auto vec = ht.to_vector();
    //rm_type cs(vec.begin(), vec.end());
    rm_type cs(ht.begin(), ht.end());
//    if( ht.begin() == ht.end() ) {

//    }
    std::cout << "equal: " << (cs == refmap) << "\n";
}
