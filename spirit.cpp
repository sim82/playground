#include <cstdint>
#include <cstddef>
#include <cassert>
#include <typeindex>
#include <vector>
#include <iostream>


namespace spirit_traits {
typedef std::pair<std::type_index, const char *> type_name_pair;

#define pp(x) typeid(x), #x

const type_name_pair name_map[] = {
    {pp(int64_t)},
    {pp(uint64_t)},
    {pp(int32_t)},
    {pp(uint32_t)},
    {pp(int16_t)},
    {pp(uint16_t)},
    {pp(int8_t)},
    {pp(uint8_t)},
    {pp(float)},
    {pp(double)},
};

#undef pp

template<typename T, size_t s>
size_t array_length( const T(&)[s] ) {
    return s;
}

const char *get_name(std::type_index ti) {
    for( size_t i = 0; i < array_length(name_map); ++i ) {
        if( name_map[i].first == ti ) {
            return name_map[i].second;
        }
    }

    return "<NA>";
}

}

class schema
{
public:
    typedef uint32_t offs_type;

    schema()
        : next_(0)
    {

    }

    template<typename T>
    offs_type add( const char *name)
    {
        auto ret = next_;
        next_ += sizeof(T);

        offsets_.push_back(ret);
        types_.push_back(typeid(T));
        names_.push_back(name);
        return ret;
    }

    void print()
    {
        for( size_t i = 0; i < types_.size(); ++i )
        {
            const char *name = (names_[i] != nullptr) ? names_[i] : "<NA>";
            std::cout << spirit_traits::get_name(types_[i]) << " " << name << " @" << offsets_[i] << "\n";
        }
    }

    size_t size() const
    {
        return next_;
    }
private:
    std::vector<std::type_index>    types_;
    std::vector<offs_type>          offsets_;
    std::vector<const char *>       names_;
    offs_type next_;

};



namespace spirit
{
class base
{
public:

protected:
    uint32_t offset_;
};

template<typename T>
class primitive
    : private base
{
public:
    primitive(schema &s, const char *name = nullptr)
    {
        base::offset_ = s.add<T>(name);
    }
    schema::offs_type offset() const {
        return base::offset_;
    }
private:

};

}


namespace unaligned_copy
{
template<typename T>
void raw_to_type( const uint8_t *src, T &dest )
{
    auto * tsrc = reinterpret_cast<const T*>(src);
    dest = *tsrc;
}

template<typename T>
void type_to_raw( const T &src, uint8_t *dest )
{
    auto * tdest = reinterpret_cast<T*>(dest);
    *tdest = src;
}


}

class backing {
public:
    typedef schema::offs_type offs_type;

    backing(schema &s)
        : buf_(s.size())
    {

    }

    template<typename T>
    T get(offs_type offs)
    {
        T ret;
        assert(offs + sizeof(T) <= buf_.size());
        unaligned_copy::raw_to_type(buf_.data() + offs, ret );
        return ret;
    }


    template<typename T>
    void set(offs_type offs, const T& v)
    {
        assert(offs + sizeof(T) <= buf_.size());
        unaligned_copy::type_to_raw( v, buf_.data() + offs );
    }

    template<typename T>
    void init_wb( offs_type offs, uint8_t *&store, T &v )
    {
        store = buf_.data() + offs;
        unaligned_copy::raw_to_type(store, v);
    }

private:
    std::vector<uint8_t> buf_;
};

template<typename T>
class ref {
public:
    ref( backing &b, backing::offs_type offs )
        : b_(b)
        , offs_(offs)
    {}

    operator T()
    {
        return b_.get<T>(offs_);
    }

    T operator=(const T& other)
    {
        b_.set<T>(offs_, other);
        return *this;
    }

    ref & operator+=(const T& v)
    {
        this->operator=((*this) + v);
        return *this;
    }

    ref & operator-=(const T& v)
    {
        this->operator=((*this) - v);
        return *this;
    }

    ref & operator++()
    {
        T tmp = *this;
        ++tmp;
        *this = tmp;
        return *this;
    }

private:
    backing &b_;
    backing::offs_type offs_;
};

template<typename T>
ref<T> operator &( backing &b, spirit::primitive<T> &p )
{
    return ref<T>(b, p.offset());
}



template<typename T>
class wb_ref {
public:
    wb_ref( backing &b, backing::offs_type offs )
    {
        b.init_wb(offs, store_, cached_);
    }
    ~wb_ref() {
        unaligned_copy::type_to_raw(cached_, store_);
    }

    operator T()
    {
        return cached_;
    }

    T operator=(const T& other)
    {
        cached_ = other;
        return *this;
    }

    wb_ref & operator+=(const T& v)
    {
        cached_ += v;
        return *this;
    }

    wb_ref & operator-=(const T& v)
    {
        cached_ -= v;
        return *this;
    }

    wb_ref & operator++()
    {
        ++cached_;
        return *this;
    }

private:
    uint8_t *store_;
    T   cached_;
};

template<typename T>
wb_ref<T> operator |( backing &b, spirit::primitive<T> &p )
{
    return wb_ref<T>(b, p.offset());
}

#define sinit(x) x(s, #x)

class user_a
{
public:
    user_a( schema &s )
        : sinit(a_)
    {}
protected:
    spirit::primitive<int> a_;

};

class user_b : public user_a
{
public:
    user_b( schema &s )
        : user_a( s )
        , sinit(b_)
        , sinit(c_)
    {}

    void do_something(backing &b)
    {
        {
            auto a_acc = b | a_;
            a_acc = a_acc + 1;
            a_acc += 2;
            ++a_acc;

            ++(b&c_);
        }
        std::cout << "values: " << (b&a_) << " " << (b & b_) << " " << (b & c_) << "\n";
    }

private:
    spirit::primitive<int> b_;
    spirit::primitive<float> c_;
};
#undef sinit

int main() {

    schema s;
    user_b b(s);

    backing bs(s);

    user_b b2(b);
    backing bs2(s);
    s.print();

    b.do_something(bs);
    b2.do_something(bs2);
}
