#include <typeindex>

#include <cassert>
#include <iostream>
#include <iomanip>
#include <map>
#include <memory>
#include <vector>
#include <tuple>
#include <numeric>
#include <functional>

struct SVec3
{
    float x;
    float y;
    float z;
};

using std::size_t;

namespace intro
{

class ILayout
{
public:
    class IVisitor
    {
    public:
        virtual ~IVisitor() {}
        virtual void acceptComplex(std::type_index, size_t, void *) = 0;
        virtual void acceptArithmetic(std::type_index, void *) = 0;
    };

    virtual ~ILayout() {};
    virtual void printLayout(std::ostream &os ) = 0;

    //using TVisitor = std::function<void(std::type_index, size_t, void *)>;
    using TVisitor = IVisitor;
    virtual void reinterpret( void *, TVisitor & visitor ) = 0;
};

// inspired by http://cpplove.blogspot.de/2013/05/my-take-on-c-serialization-part-i.html
    class CTupleLayout
            : public ILayout
    {
        struct SEntry
        {
            std::type_index type_;
            size_t offset_;
        };

    public:
        template<typename T>
        void addEntry( T & tref )
        {
            entries_.emplace_back(SEntry{typeid(T), getOffset(tref)});
        }

        //tem
        void setBase( const void *ptr )
        {
            base_ = ptr;
        }

        void printLayout( std::ostream & os )
        {
            os << "tuple of size " << size_ << "\n";
            for( auto rit = entries_.begin(), reit = entries_.end(); rit != reit; ++rit )
            {
                os << " @" << rit->offset_ << ": " << rit->type_.name() << " \n";
            }
        }

        void reinterpret( void *ptr, ILayout::TVisitor & visitor ) override
        {
            size_t baseOffs = size_t(ptr);
            for( auto &entry : entries_ )
            {
                visitor.acceptComplex(entry.type_, 1, reinterpret_cast<void*>(baseOffs + entry.offset_));
            }
        }

    private:
        template<typename T>
        size_t getOffset( T & tref )
        {
            size_t off = size_t((void*)&tref);
            size_t baseOffs = size_t(base_);
            assert( off >= baseOffs && off - baseOffs <= 1024 * 1024 );

            return off - baseOffs;
        }

        std::vector<SEntry> entries_;
        const void *base_{nullptr};
        size_t size_{0};
    };



//    template<typename ...T>
//    CTupleLayout getTupleElements( std::tuple<T...> & tuple )
//    {
//        return SGetElementsHelper<std::tuple<T...>>::value(tuple);
//    }

class CMemberCollector;

class IIntrospectable
{
public:
    virtual void intro( CMemberCollector & c ) const = 0;
};


class CArrayLayout
        : public ILayout
{
public:
    CArrayLayout( std::type_index type, size_t size, std::type_index innerType )

        : type_(type)
        , size_(size)
        , innerType_(innerType)
    {}
    void printLayout( std::ostream & os ) override
    {
        os << "array type: " << type_.name() << "\n";
        os << " " << size_ << " of " << innerType_.name() <<"\n";
    }

    void reinterpret( void *ptr, ILayout::TVisitor & visitor ) override
    {
        visitor.acceptComplex(innerType_, size_, ptr);
    }
//    template<typename T, size_t Size>
//    void intro( std::array<T, Size> & tref )
//    {
//        size_ = Size;
//        type_ = typeid(T);
//    }
private:
    std::type_index type_;
    size_t size_;
    std::type_index innerType_;

};

class CDynamicIteratable
        : public ILayout
{
public:
    CDynamicIteratable( std::type_index type, std::type_index innerType)
        : type_(type)
        , innerType_(innerType)
    {
    }

    void printLayout( std::ostream & os ) override
    {
        os << "dynamic iteratable type: " << type_.name() << "\n";
        os << " of " << innerType_.name() << "\n";
    }

    void reinterpret( void *ptr, ILayout::TVisitor & visitor ) override
    {
        // TODO: find way to solve dynamic size problem
     //   visitor(innerType_, size, ptr);
    }
private:
    std::type_index type_;
    std::type_index innerType_;
};

class CDynamicMap
        : public ILayout
{
public:
    CDynamicMap( std::type_index type, std::type_index keyType, std::type_index valueType )
        : type_(type)
        , keyType_(keyType)
        , valueType_(valueType)
    {
    }

    void printLayout( std::ostream & os ) override
    {
        os << "dynamic map type: " << type_.name() << "\n";
        os << " " << keyType_.name() << " -> " << valueType_.name() << " \n";
    }
    void reinterpret( void *ptr, ILayout::TVisitor & visitor ) override
    {
        // TODO: find way to solve dynamic size problem
    }
private:
    std::type_index type_;
    std::type_index keyType_;
    std::type_index valueType_;
};

class CArithmetic
        : public ILayout
{
    // ILayout interface
public:
    CArithmetic(std::type_index type)
        : type_(type)
    {}

    void printLayout(std::ostream &os)
    {
        os << "arithmetic type: " << type_.name() << "\n";
    }

    void reinterpret(void *ptr, TVisitor &visitor)
    {
        visitor.acceptArithmetic(type_, ptr);
    }

private:
    std::type_index type_;
};

class CTraverser
{
    template <int N> using int_ = std::integral_constant<size_t, N>;

    template <typename T>
    struct SGetElementsHelper;

    template <typename TTuple>
    inline void getTupleElements(CTupleLayout &collector, const TTuple& obj, int_<0>)
    {
        constexpr size_t idx = std::tuple_size<TTuple>::value-1;
    //    std::vector<std::type_index> ret;
        //ret.push_back(typeid(std::get<idx>(obj)));
//        return ret;//get_size(std::get<idx>(obj));
        collector.addEntry(std::get<idx>(obj));
        dispatchProbe(std::get<idx>(obj));
    }

    template <typename TTuple, size_t pos>
    inline void getTupleElements(CTupleLayout &collector, const TTuple& obj, int_<pos>)
    {

        constexpr size_t idx = std::tuple_size<TTuple>::value-pos-1;
        //size_t acc = 1;//get_size(std::get<idx>(obj));

        getTupleElements(collector, obj, int_<pos-1>());
//        ret.push_back(typeid(std::get<idx>(obj)));
        collector.addEntry(std::get<idx>(obj));
        dispatchProbe(std::get<idx>(obj));
  //      return ret;
    }


    template <typename ...T>
    struct SGetElementsHelper<std::tuple<T...>>
    {
        static std::unique_ptr<CTupleLayout> value(CTraverser &traverser, const std::tuple<T...>& obj)
        {
            auto collector = std::make_unique<CTupleLayout>();

            collector->setBase(&obj);
            traverser.getTupleElements(*collector, obj, int_<sizeof...(T)-1>());
            return std::move(collector);
        }
    };

    template <typename T1, typename T2>
    struct SGetElementsHelper<std::pair<T1,T2>>
    {
        static std::unique_ptr<CTupleLayout> value(CTraverser &traverser, const std::pair<T1,T2>& obj)
        {
            auto collector = std::make_unique<CTupleLayout>();

            collector->setBase(&obj);
            collector->addEntry(obj.first);
            collector->addEntry(obj.second);

            traverser.dispatchProbe(obj.first);
            traverser.dispatchProbe(obj.second);
            return std::move(collector);
        }
    };
public:
    bool probe( IIntrospectable const& intro );

    bool probeArray( std::type_index arrayType, std::type_index type, size_t size )
    {
        if( collectors_.find(arrayType) == collectors_.end() )
        {
            collectors_.emplace(arrayType, std::make_unique<CArrayLayout>(arrayType, size, type));
            return true;
        }
        return false;
    }
    bool probeDynamicIteratable( std::type_index outerType, std::type_index type )
    {
        if( collectors_.find(outerType) == collectors_.end() )
        {
            collectors_.emplace(outerType, std::make_unique<CDynamicIteratable>(outerType, type));
            return true;
        }
        return false;
    }

    bool probeDynamicMap( std::type_index outerType, std::type_index keyType, std::type_index valueType )
    {
        if( collectors_.find(outerType) == collectors_.end() )
        {
            collectors_.emplace(outerType, std::make_unique<CDynamicMap>(outerType, keyType, valueType));
            return true;
        }
        return false;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IIntrospectable,T>::value, bool>::type dispatchProbe( T const& tref )
    {
        return probe(tref);
    }

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type dispatchProbe( T const& tref )
    {
        auto it = collectors_.find(typeid(T));
        if( it == collectors_.end() )
        {
            collectors_.emplace(typeid(T), std::make_unique<CArithmetic>(typeid(T)));
        }
    }

    template<typename T, size_t Size>
    void dispatchProbe( std::array<T,Size> const& tref )
    {
        if( !probeArray(typeid(tref), typeid(T), Size) )
        {
            return;
        }
        dispatchProbe(tref[0]);

    }

    template<typename T, size_t Size>
    void dispatchProbe( T(&tref)[Size] )
    {
        if( !probeArray(typeid(tref), typeid(T), Size) )
        {
            return;
        }

        dispatchProbe(tref[0]);

    }


    template<typename T>
    void dispatchProbe( std::vector<T> const& tref )
    {
        if( !probeDynamicIteratable(typeid(tref), typeid(T)) )
        {
            return;
        }

        if( !tref.empty() )
        {
            dispatchProbe(tref[0]);
        }
        else
        {
            using TValue = typename std::vector<T>::value_type;
            auto v = TValue();
            dispatchProbe(v);
        }

    }


    template<typename TKey, typename TValue>
    void dispatchProbe( std::map<TKey, TValue> const& tref )
    {
        if( !probeDynamicMap(typeid(tref), typeid(TKey), typeid(TValue)) )
        {
            return;
        }

        if( !tref.empty() )
        {
            dispatchProbe(tref.begin()->first);
            dispatchProbe(tref.begin()->second);
        }
        else
        {
//            using TKey = typename std::map<T>::key_type;
//            using TValue = typename std::map<T>::value_type;
            auto k = TKey();
            auto v = TValue();
            dispatchProbe(k);
            dispatchProbe(v);
        }

    }

    template<typename ...T>
    void dispatchProbe( std::tuple<T...> const& tuple )
    {
        auto const& tupleType = typeid(tuple);
        if( collectors_.find(tupleType) == collectors_.end() )
        {
            collectors_.emplace(tupleType, SGetElementsHelper<std::tuple<T...>>::value(*this, tuple));
        }
    }

    template<typename T1, typename T2>
    void dispatchProbe( std::pair<T1, T2> const& tuple )
    {
        auto const& tupleType = typeid(tuple);
        if( collectors_.find(tupleType) == collectors_.end() )
        {
            collectors_.emplace(tupleType, SGetElementsHelper<std::pair<T1,T2>>::value(*this, tuple));
        }
    }

    void probeForeignInternal(std::type_index type, void const*ptr , std::function<void(CMemberCollector &)> f);

    template<typename T>
    void probeForeign( T const& v, std::function<void(CMemberCollector & memberCollector)> f)
    {
        auto const& type = typeid(v);
        probeForeignInternal(type, &v, f);
    }

    void printTypes(std::ostream & os );

    ILayout &getLayout( std::type_index type )
    {
        auto it = collectors_.find(type);
        if( it == collectors_.end() )
        {
            throw std::runtime_error( std::string("no layout for type: ") + type.name() );
        }

        return *it->second;
    }

private:

    std::map<std::type_index, std::unique_ptr<ILayout>> collectors_;
};



class CMemberCollector
        : public ILayout
{
    struct SEntry
    {
        size_t offset_;
        std::type_index type_;
    };

public:
    CMemberCollector( CTraverser &traverser )
        : traverser_(traverser)
    {}

    template<typename T>
    void setBase( T & basePtr )
    {
        basePtr_ = &basePtr;
        type_ = typeid(basePtr);
    }

    template<typename T>
    void addMember( T & tref )
    {
        traverser_.dispatchProbe(tref);
        auto const offs = calcOffset(tref);
        members_.emplace(offs, SEntry{offs, typeid(tref)});
    }

//    template<typename T>
//    typename std::enable_if<std::is_base_of<IIntrospectable,T>::value>::type addMember( T & tref )
//    {
//        traverser_.probe(tref);
//        auto const offs = calcOffset(tref);
//        members_.emplace(offs, SEntry{offs, typeid(tref)});
//    }

//    template<typename T>
//    typename std::enable_if<std::is_arithmetic<T>::value>::type addMember( T & tref )
//    {
//        auto const offs = calcOffset(tref);
//        members_.emplace(offs, SEntry{offs, typeid(tref)});
//    }


//    template<typename T, size_t Size>
//    void addMember( std::array<T,Size> & tref )
//    {
//        traverser_.probeArray(tref);
//        auto const offs = calcOffset(tref);
//        members_.emplace(offs, SEntry{offs, typeid(tref)});
//    }

    void printLayout( std::ostream & os ) override
    {
        os << "introspectable type: " << type_.name() << "\n";

        for( auto & p : members_ )
        {
            SEntry const& entry = p.second;
            os << " @" << entry.offset_ << ": " << entry.type_.name() << "\n";
        }
    }

    void reinterpret( void *ptr, ILayout::TVisitor & visitor ) override
    {
        auto const baseOffs = size_t(ptr);
        for( auto & p : members_ )
        {
            visitor.acceptComplex(p.second.type_, 1, reinterpret_cast<void*>(baseOffs + p.second.offset_));
        }
    }
private:
    template<typename T>
    inline size_t calcOffset( T & tref )
    {
        size_t moffs = size_t((void*)&tref);
        size_t baseOffs = size_t(basePtr_);

        auto constexpr sanity = size_t(1024 * 1024);
        assert( moffs >= baseOffs && moffs - baseOffs < sanity );

        return moffs - baseOffs;
    }



    std::map<size_t, SEntry> members_;
    std::type_index type_{typeid(nullptr)};
    void const* basePtr_{nullptr};

    CTraverser &traverser_;

};

bool CTraverser::probe(IIntrospectable const& intro)
{
    std::type_index type = typeid(intro);

    if( collectors_.find(type) == collectors_.end() )
    {
        auto collector = std::make_unique<CMemberCollector>(*this);

        collector->setBase(intro);
        intro.intro(*collector);
        collectors_.emplace(type, std::move(collector));
        return true;
    }
    return false;
}

void CTraverser::probeForeignInternal(std::type_index type, void const* ptr, std::function<void(CMemberCollector &)> f)
{
    if( collectors_.find(type) != collectors_.end() )
    {
        return;
    }
    auto c = std::make_unique<CMemberCollector>(*this);
    c->setBase(ptr);
    f(*c);
    collectors_.emplace(type, std::move(c));
}

void CTraverser::printTypes(std::ostream &os)
{
    os << "known types: " << collectors_.size() << "\n";

    for( auto & p : collectors_ )
    {
        p.second->printLayout(os);
    }
}


} // namespace intro

class CTest2
        : public intro::IIntrospectable
{
public:
    void intro( intro::CMemberCollector & c ) const
    {
        c.addMember(a_);
        c.addMember(b_);
    }

private:
    float a_;
    std::array<size_t, 5> b_;
};


class CTest3
        : public intro::IIntrospectable
{
public:
    void intro( intro::CMemberCollector & c ) const
    {
        c.addMember(a_);
        c.addMember(b_);
        c.addMember(c_);
        c.addMember(d_);
    }

private:
    bool a_;
    int b_[27];
    std::vector<CTest3> c_;
    std::vector<std::vector<CTest3>> d_;
};


class CTest1
        : public intro::IIntrospectable
{
public:
    void intro( intro::CMemberCollector & c ) const
    {
        c.addMember(a_);
        c.addMember(b_);
        c.addMember(c_);
        c.addMember(d_);
        c.addMember(e_);
        c.addMember(f_);
        c.addMember(g_);
    }

private:
    int a_{666};
    std::array<int, 7> b_;
    CTest2 c_;
    std::array<CTest3, 4> d_;
    std::array<std::vector<CTest1>, 4> e_;

    std::map<int, CTest2> f_;

    using TTuple = std::tuple<int, int, size_t, std::tuple<int,int>, CTest3>;
    TTuple g_;
};

class CArithmeticAdapter
        : public intro::ILayout::IVisitor
{
public:
    CArithmeticAdapter()
    {
#define ADD_TYPE(x) handlers_.emplace(typeid(x), [this](void *ptr){this->accept(*reinterpret_cast<x*>(ptr));})
        ADD_TYPE(bool);
        ADD_TYPE(int);
        ADD_TYPE(float);
        ADD_TYPE(size_t);
#undef ADD_TYPE

    }

    virtual void accept( bool & v ) = 0;
    virtual void accept( int & v ) = 0;
    virtual void accept( float & v ) = 0;
    virtual void accept( size_t & v ) = 0;

    void acceptArithmetic(std::type_index type, void *ptr) override
    {
        auto it = handlers_.find(type);
        if( it == handlers_.end() )
        {
            throw std::runtime_error( std::string( "unhandled type: ") + type.name() );
        }
        it->second(ptr);

    }
private:
    std::map<std::type_index, std::function<void(void*)>> handlers_;
};

class CTestVisitor
        : public CArithmeticAdapter
{
    // IVisitor interface
public:
    CTestVisitor( intro::CTraverser &traverser, void *base )
        : traverser_(traverser)
        , base_(base)
    {}

    void acceptComplex(std::type_index type, size_t size, void *ptr) override
    {
        indent(std::cout);
        std::cout << "complex: " << size << " of " << type.name() << " @ " << size_t(ptr) - size_t(base_) << "\n";
        ++indent_;
        traverser_.getLayout(type).reinterpret(ptr, *this);
        --indent_;
    }

//    void acceptArithmetic(std::type_index type, void *ptr)
//    {
//        indent(std::cout);
//        std::cout << "arithmetic type " << type.name() << " @ " << size_t(ptr) - size_t(base_) << "\n";
//    }

public:
    void accept(bool &v)
    {
        indent(std::cout);
        std::cout << "bool " << (v ? "true" : "false") << "\n";
    }

    void accept(int &v)
    {
        indent(std::cout);
        std::cout << "int " << v << "\n";
    }

    void accept(float &v)
    {
        indent(std::cout);
        std::cout << "float " << v << "\n";
    }

    void accept(size_t &v)
    {
        indent(std::cout);
        std::cout << "size_t " << v << "\n";
    }

    void indent( std::ostream &os )
    {
        for( size_t i = 0; i < indent_; ++i )
        {
            os << " ";
        }
    }

private:
    intro::CTraverser &traverser_;
    void *base_;
    size_t indent_{0};

    // CArithmeticAdapter interface

};

int main()
{
    //intro::CMemberCollector c;
    intro::CTraverser traverser;

    {
        SVec3 v;
        traverser.probeForeign<SVec3>(v, [&v]( intro::CMemberCollector & c)
        {
            c.addMember(v.x);
            c.addMember(v.y);
            c.addMember(v.z);
        });
    }

    traverser.printTypes(std::cout);


    CTest1 t;
    traverser.probe(t);
    traverser.printTypes(std::cout);

    std::cout << "CTest1 size: " << sizeof(CTest1) << "\n";

//    auto visitor = [&](std::type_index type, size_t num, void *ptr )
//    {
//        traverser.getLayout(type).reinterpret(ptr, visitor);
//    };

    CTestVisitor v(traverser, &t);

    traverser.getLayout(typeid(t)).reinterpret(&t, v);

    //using TTuple = std::tuple<int, int, size_t, std::tuple<int,int>>;

    //std::vector<std::type_index> types = magick::get_size_helper<TTuple>::value(TTuple());
//    TTuple tup;
//    //std::pair<int, int> tup;
//    intro::CTupleLayout collector = intro::getTupleElements(tup);
//    collector.printElements( std::cout );

//    for( auto rit = types.rbegin(), reit = types.rend(); rit != reit; ++rit )
//    {
//        std::cout << rit->name() << "\n";
//    }

}
