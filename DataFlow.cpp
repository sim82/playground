/*
 * Copyright (C) 2013 Simon A. Berger
 *
 *  This program is free software; you may redistribute it and/or modify its
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 */

#include <glm/vec3.hpp>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/list_hook.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <vector>
#include <deque>
#include <iostream>
#include <unordered_set>

size_t align(size_t n, size_t a)
{
    if ( n % a == 0 )
    {
        return n;
    }
    else
    {
        return n + (n - n % a);
    }
}

class CRawStorage
{
public:
    CRawStorage(size_t size, size_t alignment)
        : size_(size)
        , alignment_(align(size, alignment))
        , sizeInc_(4096 / alignment_)
        , storage_(sizeInc_)
        , bitmap_(sizeInc_)
    {
    }

    size_t alloc()
    {
        if (numAlloc_ == capacity_)
        {
            nextFree_ = capacity_;

            size_t newSize = capacity_ + sizeInc_;
            storage_.resize(newSize * alignment_);
            bitmap_.resize(newSize);
        }

        while (bitmap_[nextFree_])
        {
            ++nextFree_;
            if (nextFree_ >= storage_.size())
            {
                nextFree_ = 0;
            }
        }
        bitmap_[nextFree_] = true;
        return nextFree_++;
    }

    void dealloc(size_t i)
    {
        assert(bitmap_[i]);
        ++numAlloc_;
        bitmap_[i] = false;
    }

    uint8_t *operator[](size_t i)
    {
        return storage_.data() + (i * alignment_);
    }

    size_t getCapacity()
    {
        return capacity_;
    }

private:
    const size_t size_;
    const size_t alignment_;
    const size_t sizeInc_;

    size_t capacity_{sizeInc_};
    std::vector<uint8_t> storage_;
    std::vector<bool> bitmap_;
    size_t nextFree_;
    size_t numAlloc_;
};

template<typename T>
struct tag
{
    using type = T;
};


class CDataGroup
{
public:
    template<typename T>
    CDataGroup( tag<T> )
        : storage_(sizeof(T), std::alignment_of<T>::value)
    {
    }

    template<typename T>
    size_t alloc()
    {
        size_t index = storage_.alloc();
        auto *ptr = getPtr<T>(index);
        new (ptr)T();

        return index;
    }

    template<typename T>
    void dealloc(size_t index)
    {
        auto *ptr = getPtr<T>(index);
        ptr->~T();
    }

    template<typename T>
    T *getPtr(size_t i)
    {
        return reinterpret_cast<T*>(storage_[i]);
    }

    template<typename T>
    T &get(size_t i)
    {
        return *getPtr<T>(i);
    }

    size_t getCapacity()
    {
        return storage_.getCapacity();
    }
private:
    CRawStorage storage_; //{sizeof(T), std::alignment_of<T>::value};
};

struct SHandle
{
    uint32_t type_;
    uint32_t index_;
};

struct SHandleHash
{
    size_t operator()(SHandle const& h) const
    {
        const std::hash<uint32_t> hash;
        return hash(h.type_) + hash(h.index_);
    }
};

struct SHandleEqual
{
    bool operator()(SHandle const& h1, SHandle const& h2) const
    {
        return h1.type_ == h2.type_ && h1.index_ == h2.index_;
    }
};

class IBinding
{
public:
    virtual ~IBinding() {}
    virtual void apply( void const *src, void *target ) = 0;
private:
};

class CAbstractBinding : public IBinding
{
public:
    boost::intrusive::list_member_hook<> fromHook_;
    boost::intrusive::list_member_hook<> toHook_;
    SHandle const& getTarget()
    {
        return target_;
    }

    void setTarget(SHandle const& target )
    {
        target_ = target;
    }
private:

    SHandle target_;
};


using TFromHook = boost::intrusive::member_hook<CAbstractBinding, boost::intrusive::list_member_hook<>, &CAbstractBinding::fromHook_>;
using TToHook = boost::intrusive::member_hook<CAbstractBinding, boost::intrusive::list_member_hook<>, &CAbstractBinding::toHook_>;


using IBindingPtr = std::unique_ptr<IBinding>;
using CAbstractBindingPtr = std::unique_ptr<CAbstractBinding>;


class CBindings
{

public:
//    using TMap = std::multimap<uint32_t, IBindingPtr>;

    using TFromList = boost::intrusive::list<CAbstractBinding, TFromHook>;
    using TIterator = typename TFromList::iterator;
    using TRange = std::pair<TIterator, TIterator>;

    TRange rangeForSource(uint32_t src)
    {
        auto & links = bindings2_.at(src);
        return TRange(links.fromList_.begin(), links.fromList_.end());

//        return TRange(bindings_.lower_bound(src), bindings_.upper_bound(src));
    }

    void addBindingFrom( uint32_t srcIndex, CAbstractBinding *binding )
    {
        bindings2_.at(srcIndex).fromList_.push_back(*binding);
    }

    void addBindingTo( uint32_t targetIndex, CAbstractBinding *binding )
    {
        bindings2_.at(targetIndex).toList_.push_back(*binding);
    }

    void setSize( size_t s )
    {
        bindings2_.resize(s);
    }

private:
//    TMap bindings_;

    struct SBindingLinks
    {
          TFromList fromList_;
          boost::intrusive::list<CAbstractBinding, TToHook> toList_;
    };

    std::vector<SBindingLinks> bindings2_;
};

class CDataGroups
{
    struct SType
    {
        std::type_index type;
        std::unique_ptr<CDataGroup> data;
        std::unique_ptr<CBindings> bindings;
    };

    using TTypes = std::vector<SType>;

public:
    static CDataGroups &getSingleton()
    {
        static CDataGroups groups;
        return groups;
    }

    inline TTypes::iterator findType(std::type_index type)
    {
        return std::find_if(types_.begin(), types_.end(), [&](TTypes::value_type const &v) { return v.type == type; });
    }

    template <typename T>
    void addType()
    {
        std::type_index const typeId = typeid(T);

        auto it = findType(typeId);
        assert(it == types_.end());

        types_.emplace_back(SType{typeId, std::make_unique<CDataGroup>(tag<T>{}), std::make_unique<CBindings>()});
    }

    template <typename T>
    SHandle alloc()
    {
        std::type_index const typeId = typeid(T);

        auto it = findType(typeId);
        assert(it != types_.end());

        auto const type  = uint32_t(std::distance(types_.begin(), it));
        auto const index = uint32_t(it->data->alloc<T>());
        it->bindings->setSize(it->data->getCapacity());

        return SHandle{type, index};
    }

    void addBinding(SHandle src, SHandle target, CAbstractBindingPtr binding )
    {
        auto & srcType = types_.at(src.type_);
        auto & targetType = types_.at(target.type_);

        srcType.bindings->addBindingFrom(src.index_, binding.get());
        targetType.bindings->addBindingTo(target.index_, binding.get());
        binding->setTarget(target);
        binding.release();
    }

    void *get(SHandle const& handle)
    {
        auto & type = types_.at(handle.type_);
        return type.data->getPtr<void>(handle.index_);
    }


    void updateBindings( SHandle const& handle )
    {
        std::deque<SHandle> q{handle};
        std::unordered_set<SHandle, SHandleHash, SHandleEqual> handles;

        while (!q.empty())
        {
            SHandle const& f = q.front();
            handles.emplace(f);

            auto & type = types_.at(f.type_);
            auto const range = type.bindings->rangeForSource(f.index_);

            for ( auto it = range.first; it != range.second; ++it )
            {
                auto const& target = it->getTarget();
                if (handles.find(target) != handles.end() )
                {
                    std::cout << "cycle\n";
                    continue;
                }

                it->apply(get(f), get(target));
                q.push_back(target);
            }
            q.pop_front();
        }
    }
private:
    TTypes types_;
};




template<typename T>
class CValue
{
public:
    CValue(SHandle h)
        : handle_(h)
    {}

    T const& get()
    {
        auto & groups = CDataGroups::getSingleton();
        void const* data = groups.get(handle_);

        return *reinterpret_cast<T const*>(data);
    }

    void set( T && v )
    {
        auto & groups = CDataGroups::getSingleton();
        void * data = groups.get(handle_);

        *reinterpret_cast<T*>(data) = std::move(v);
        groups.updateBindings(handle_);
    }

    operator SHandle()
    {
        return handle_;
    }
private:
    SHandle handle_;
};


template<typename T>
CValue<T> allocValue( T && v = T() )
{
    auto & groups = CDataGroups::getSingleton();
    CValue<T> value(groups.alloc<T>());
    value.set(std::move(v));
    return value;
}

template<typename T>
class CBindSameType : public CAbstractBinding
{
public:
    void apply( void const* src, void *target )
    {
        *reinterpret_cast<T*>(target) = *reinterpret_cast<T const*>(src);
    }
private:
};


template<typename T>
class CBindToString : public CAbstractBinding
{
public:
    void apply( void const* src, void *target )
    {
        *reinterpret_cast<std::string*>(target) = std::to_string(*reinterpret_cast<T const*>(src));
    }
private:
};

int main()
{
    auto & groups = CDataGroups::getSingleton();

    groups.addType<int>();
    groups.addType<size_t>();
    groups.addType<glm::vec3>();
    groups.addType<std::string>();



    auto v = allocValue<int>(555);
    auto v2 = allocValue<int>(777);
    auto v3 = allocValue<std::string>("888");

    groups.addBinding(v, v2, std::make_unique<CBindSameType<int>>());
    groups.addBinding(v2, v3, std::make_unique<CBindToString<int>>());
//    groups.addBinding(v3, v, std::make_unique<CBindToString<int>>());

    v.set(666);
    std::cout << "v3: " << v3.get() << "\n";
}
