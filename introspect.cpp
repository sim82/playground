#include <typeindex>

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using std::size_t;

namespace intro
{
class CMemberCollector;

class IIntrospectable
{
public:
    virtual void intro( CMemberCollector & c ) = 0;
};

class ILayout
{
public:
    virtual ~ILayout() {};
    virtual void printLayout(std::ostream &os ) = 0;

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
    }

private:
    int a_;
    std::array<int, 7> b_;
    CTest2 c_;
    std::array<CTest3, 4> d_;
    std::array<std::vector<CTest1>, 4> e_;

    std::map<int, CTest2> f_;
};

int main()
{
    //intro::CMemberCollector c;
    intro::CTraverser traverser;

    CTest1 t;
    traverser.probe(t);
    traverser.printTypes(std::cout);

    std::cout << "CTest1 size: " << sizeof(CTest1) << "\n";

}
