#include <typeindex>

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <tuple>
#include <numeric>

using std::size_t;

namespace intro
{

class ILayout
{
public:
    virtual ~ILayout() {};
    virtual void printLayout(std::ostream &os ) = 0;

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
    }

    template <typename TTuple, size_t pos>
    inline void getTupleElements(CTupleLayout &collector, const TTuple& obj, int_<pos>)
    {

        constexpr size_t idx = std::tuple_size<TTuple>::value-pos-1;
        //size_t acc = 1;//get_size(std::get<idx>(obj));

        getTupleElements(collector, obj, int_<pos-1>());
//        ret.push_back(typeid(std::get<idx>(obj)));
        collector.addEntry(std::get<idx>(obj));
  //      return ret;
    }


    template <typename ...T>
    struct SGetElementsHelper<std::tuple<T...>>
    {
        static std::unique_ptr<CTupleLayout> value(const std::tuple<T...>& obj)
        {
            auto collector = std::make_unique<CTupleLayout>();

            collector->setBase(&obj);
            getTupleElements(*collector, obj, int_<sizeof...(T)-1>());
            return std::move(collector);
        }
    };

    template <typename T1, typename T2>
    struct SGetElementsHelper<std::pair<T1,T2>>
    {
        static std::unique_ptr<CTupleLayout> value(const std::pair<T1,T2>& obj)
        {
            auto collector = std::make_unique<CTupleLayout>();

            collector->setBase(&obj);
            collector->addEntry(obj.first);
            collector->addEntry(obj.second);
            return std::move(collector);
        }
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
    virtual void intro( CMemberCollector & c ) = 0;
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
private:
    std::type_index type_;
    std::type_index keyType_;
    std::type_index valueType_;
};



class CTraverser
{
public:
    bool probe( IIntrospectable & intro );

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
    typename std::enable_if<std::is_base_of<IIntrospectable,T>::value, bool>::type dispatchProbe( T & tref )
    {
        return probe(tref);
    }

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type dispatchProbe( T & tref )
    {
    }

    template<typename T, size_t Size>
    void dispatchProbe( std::array<T,Size> & tref )
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
    void dispatchProbe( std::vector<T> & tref )
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
    void dispatchProbe( std::map<TKey, TValue> & tref )
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
    void dispatchProbe( std::tuple<T...> & tuple )
    {
        auto const& tupleType = typeid(tuple);
        if( collectors_.find(tupleType) == collectors_.end() )
        {
            collectors_.emplace(tupleType, SGetElementsHelper<std::tuple<T...>>::value(tuple));
        }
    }

    template<typename T1, typename T2>
    void dispatchProbe( std::pair<T1, T2> & tuple )
    {
        auto const& tupleType = typeid(tuple);
        if( collectors_.find(tupleType) == collectors_.end() )
        {
            collectors_.emplace(tupleType, SGetElementsHelper<std::pair<T1,T2>>::value(tuple));
        }
    }
    void printTypes(std::ostream & os );

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
    void *basePtr_{nullptr};

    CTraverser &traverser_;

};

bool CTraverser::probe(IIntrospectable &intro)
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
    void intro( intro::CMemberCollector & c )
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
    void intro( intro::CMemberCollector & c )
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
    void intro( intro::CMemberCollector & c )
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
    int a_;
    std::array<int, 7> b_;
    CTest2 c_;
    std::array<CTest3, 4> d_;
    std::array<std::vector<CTest1>, 4> e_;

    std::map<int, CTest2> f_;

    using TTuple = std::tuple<int, int, size_t, std::tuple<int,int>, CTest3>;
    TTuple g_;
};



int main()
{
    //intro::CMemberCollector c;
    intro::CTraverser traverser;

    CTest1 t;
    traverser.probe(t);
    traverser.printTypes(std::cout);

    std::cout << "CTest1 size: " << sizeof(CTest1) << "\n";

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
