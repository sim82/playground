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

#include <glm/ext.hpp>
#include <glm/vec3.hpp>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/list_hook.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <type_traits>
#include <typeindex>
#include <unordered_set>
#include <vector>

size_t align(size_t n, size_t a)
{
    if (n % a == 0)
    {
        return n;
    }
    else
    {
        return n + (n - n % a);
    }
}

template <typename T>
struct tag
{
    using type = T;
};

class IStorage
{
public:
    virtual ~IStorage() {}

    virtual size_t getUnreferenced() = 0;
    virtual void incRefcount(size_t i) = 0;
    virtual bool decRefcount(size_t i) = 0;
    virtual uint8_t *operator[](size_t i) = 0;
    virtual size_t getCapacity() = 0;
    virtual uint32_t getRefcount(size_t i) = 0;
};

class CRawStorage : public IStorage
{
public:
    CRawStorage(size_t size, size_t alignment)
        : size_(size)
        , alignment_(align(size, alignment))
        , sizeInc_(4096)
        , capacity_(sizeInc_)
        , storage_(sizeInc_ * alignment_)
        , refcount_(sizeInc_)
    {
    }

    template <typename T>
    CRawStorage(tag<T>)
        : CRawStorage(sizeof(T), std::alignment_of<T>::value)
    {
    }

    size_t getUnreferenced() override
    {
        if (numAlloc_ == capacity_)
        {
            nextFree_ = capacity_;

            size_t newSize = capacity_ + sizeInc_;
            storage_.resize(newSize * alignment_);
            refcount_.resize(newSize);
        }

        while (refcount_[nextFree_])
        {
            ++nextFree_;
            if (nextFree_ >= capacity_)
            {
                nextFree_ = 0;
            }
        }
        return nextFree_;
    }

    void incRefcount(size_t i) override
    {
        ++refcount_[i];
    }

    bool decRefcount(size_t i) override
    {
        assert(refcount_[i] != 0);
        --refcount_[i];
        return refcount_[i] == 0;
    }

    uint8_t *operator[](size_t i) override
    {
        return storage_.data() + (i * alignment_);
    }

    size_t getCapacity() override
    {
        return capacity_;
    }

    uint32_t getRefcount(size_t i) override
    {
        return refcount_[i];
    }

private:
    const size_t size_;
    const size_t alignment_;
    const size_t sizeInc_;

    size_t capacity_;
    std::vector<uint8_t> storage_;
    //    std::vector<bool> bitmap_;
    std::vector<uint32_t> refcount_;
    size_t nextFree_;
    size_t numAlloc_;
};
#if 0
template<typename T>
class CTypedStorage : public IStorage
{
public:
    CRawStorage()
        : sizeInc_(4096)
        , capacity_(sizeInc_)
        , refcount_(sizeInc_)
    {
    }

    template <typename T>
    CRawStorage(tag<T>)
        : CRawStorage(sizeof(T), std::alignment_of<T>::value)
    {
    }

    size_t getUnreferenced() override
    {
        if (numAlloc_ == capacity_)
        {
            nextFree_ = capacity_;

            size_t newSize = capacity_ + sizeInc_;
            storage_.resize(newSize * alignment_);
            refcount_.resize(newSize);
        }

        while (refcount_[nextFree_])
        {
            ++nextFree_;
            if (nextFree_ >= capacity_)
            {
                nextFree_ = 0;
            }
        }
        return nextFree_;
    }

    void incRefcount(size_t i) override
    {
        ++refcount_[i];
    }

    bool decRefcount(size_t i) override
    {
        assert(refcount_[i] != 0);
        --refcount_[i];
        return refcount_[i] == 0;
    }

    uint8_t *operator[](size_t i) override
    {
        return storage_.data() + (i * alignment_);
    }

    size_t getCapacity() override
    {
        return capacity_;
    }

    uint32_t getRefcount(size_t i) override
    {
        return refcount_[i];
    }

private:
    const size_t size_;
    const size_t alignment_;
    const size_t sizeInc_;

    size_t capacity_;

    T *data_{nullptr};
    //    std::vector<bool> bitmap_;
    std::vector<uint32_t> refcount_;
    size_t nextFree_;
    size_t numAlloc_;
};
#endif

struct SHandle
{
    uint32_t type_;
    uint32_t index_;

    inline bool operator==(SHandle const &other) const
    {
        return type_ == other.type_ && index_ == other.index_;
    }

    inline bool operator!=(SHandle const &other) const
    {
        return !(operator==(other));
    }
};

std::ostream &operator<<(std::ostream &os, SHandle const &h)
{
    os << "handle(" << h.type_ << ":" << h.index_ << ")";
    return os;
}

const SHandle NullHandle = SHandle{uint32_t(-1), uint32_t(-1)};

struct SHandleHash
{
    size_t operator()(SHandle const &h) const
    {
        const std::hash<uint32_t> hash;
        return hash(h.type_) + hash(h.index_);
    }
};

// struct SHandleEqual
//{
//    bool operator()(SHandle const &h1, SHandle const &h2) const
//    {
//        return h1.type_ == h2.type_ && h1.index_ == h2.index_;
//    }
//};

class IBinding
{
public:
    virtual ~IBinding()
    {
    }
    virtual void apply(void const *src, void *target) = 0;

private:
};

using TListMemberHook = boost::intrusive::list_member_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>>;

class CAbstractBinding : public IBinding
{
public:
    TListMemberHook fromHook_;
    TListMemberHook toHook_;
    SHandle const &getTarget()
    {
        return target_;
    }

    void setTarget(SHandle const &target)
    {
        target_ = target;
    }

private:
    SHandle target_;
};

using TFromHook = boost::intrusive::member_hook<CAbstractBinding, TListMemberHook, &CAbstractBinding::fromHook_>;
using TToHook   = boost::intrusive::member_hook<CAbstractBinding, TListMemberHook, &CAbstractBinding::toHook_>;

class ITypeSupport
{
public:
    virtual ~ITypeSupport()
    {
    }

    virtual void construct(void *storage)       = 0;
    virtual void destruct(void *storage)        = 0;
    virtual std::string toString(void *storage) = 0;
    virtual std::string getTypename()           = 0;
};

template <typename GLMType, typename = decltype(glm::to_string(std::declval<GLMType>()))>
std::ostream &operator<<(std::ostream &out, const GLMType &g)
{
    return out << glm::to_string(g);
}

template <typename T>
class CTypeSupportDefault : public ITypeSupport
{
public:
    void construct(void *storage) override
    {
        new (storage) T();
    }

    void destruct(void *storage) override
    {
        reinterpret_cast<T *>(storage)->~T();
    }

    std::string toString(void *storage) override
    {
        std::ostringstream oss;
        oss << *reinterpret_cast<T *>(storage);
        return oss.str();
    }

    std::string getTypename() override
    {
        return typeid(T).name();
    }
};

using IBindingPtr         = std::unique_ptr<IBinding>;
using CAbstractBindingPtr = std::unique_ptr<CAbstractBinding>;

class CBindings
{

public:
    //    using TMap = std::multimap<uint32_t, IBindingPtr>;
    using TToList   = boost::intrusive::list<CAbstractBinding, TToHook, boost::intrusive::constant_time_size<false>>;
    using TFromList = boost::intrusive::list<CAbstractBinding, TFromHook, boost::intrusive::constant_time_size<false>>;
    using TIterator = typename TFromList::iterator;
    using TRange    = std::pair<TIterator, TIterator>;

    TRange rangeForSource(uint32_t src)
    {
        auto &links = bindings2_.at(src);
        return TRange(links.fromList_.begin(), links.fromList_.end());

        //        return TRange(bindings_.lower_bound(src), bindings_.upper_bound(src));
    }

    void addBindingFrom(uint32_t srcIndex, CAbstractBinding *binding)
    {
        bindings2_.at(srcIndex).fromList_.push_back(*binding);
    }

    void addBindingTo(uint32_t targetIndex, CAbstractBinding *binding)
    {
        bindings2_.at(targetIndex).toList_.push_back(*binding);
    }

    void setSize(size_t s)
    {
        bindings2_.resize(s);
    }

    struct SBindingDisposer
    {
        void operator()(CAbstractBinding *binding)
        {
            delete binding;
        }
    };

    void removeAll(uint32_t index)
    {
        auto &links = bindings2_.at(index);
        //        links.fromList_

        for (auto it = links.fromList_.begin(), eit = links.fromList_.end(); it != eit; ++it)
        {
            it->toHook_.unlink();
        }
        links.fromList_.clear_and_dispose(SBindingDisposer());

        for (auto it = links.toList_.begin(), eit = links.toList_.end(); it != eit; ++it)
        {
            it->fromHook_.unlink();
        }
        links.toList_.clear_and_dispose(SBindingDisposer());
    }

private:
    //    TMap bindings_;

    struct SBindingLinks
    {
        TFromList fromList_;
        TToList toList_;
    };

    std::vector<SBindingLinks> bindings2_;
};

class CDataGroups
{
    struct SType
    {
        std::type_index type;
        std::unique_ptr<IStorage> data;
        std::unique_ptr<CBindings> bindings;
        std::unique_ptr<ITypeSupport> typeSupport;
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

        types_.emplace_back(SType{typeId, std::make_unique<CRawStorage>(tag<T>{}), std::make_unique<CBindings>(),
                                  std::make_unique<CTypeSupportDefault<T>>()});
    }

    template <typename T>
    SHandle alloc()
    {
        std::type_index const typeId = typeid(T);

        auto it = findType(typeId);
        assert(it != types_.end());

        auto const type  = uint32_t(std::distance(types_.begin(), it));
        auto const index = uint32_t(it->data->getUnreferenced());
        it->data->incRefcount(index);
        it->bindings->setSize(it->data->getCapacity());
        it->typeSupport->construct((*it->data)[index]);

        return SHandle{type, index};
    }

    void addBinding(SHandle src, SHandle target, CAbstractBindingPtr binding)
    {
        auto &srcType    = types_.at(src.type_);
        auto &targetType = types_.at(target.type_);

        srcType.bindings->addBindingFrom(src.index_, binding.get());
        targetType.bindings->addBindingTo(target.index_, binding.get());
        binding->setTarget(target);
        binding.release();
    }

    void *get(SHandle const &handle)
    {
        auto &type = types_.at(handle.type_);
        return (*type.data)[handle.index_];
    }

    void updateBindings(SHandle const &handle)
    {
        std::deque<SHandle> q{handle};
        std::unordered_set<SHandle, SHandleHash /*, SHandleEqual*/> handles;

        while (!q.empty())
        {
            SHandle const &f = q.front();
            handles.emplace(f);

            auto &type       = types_.at(f.type_);
            auto const range = type.bindings->rangeForSource(f.index_);

            for (auto it = range.first; it != range.second; ++it)
            {
                auto const &target = it->getTarget();
                if (handles.find(target) != handles.end())
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

    void incRefcount(SHandle const &handle)
    {
        auto &type = types_.at(handle.type_);
        type.data->incRefcount(handle.index_);
    }

    void decRefcount(SHandle const &handle)
    {
        auto &type   = types_.at(handle.type_);
        bool lastRef = type.data->decRefcount(handle.index_);
        if (lastRef)
        {
            type.typeSupport->destruct((*type.data)[handle.index_]);
            type.bindings->removeAll(handle.index_);
        }
    }

    template <typename T>
    void printAll()
    {
        std::type_index const typeId = typeid(T);

        auto it = findType(typeId);
        assert(it != types_.end());

        auto const type = uint32_t(std::distance(types_.begin(), it));

        for (size_t i = 0, size = it->data->getCapacity(); i != size; ++i)
        {
            if (it->data->getRefcount(i) == 0)
            {
                continue;
            }

            std::cout << SHandle{type, uint32_t(i)} << it->typeSupport->toString((*it->data)[i]) << "\n";
        }
    }

private:
    TTypes types_;
};

template <typename T>
class CValue final
{
public:
    CValue()
        : handle_(NullHandle)
    {
    }

    explicit CValue(SHandle h)
        : handle_(h)
    {
    }

    CValue(CValue const &other)
        : handle_(other.handle_)
    {
        auto &groups = CDataGroups::getSingleton();
        groups.incRefcount(handle_);
    }

    CValue &operator=(CValue const &other)
    {
        auto &groups = CDataGroups::getSingleton();

        if (handle_ != NullHandle)
        {
            groups.decRefcount(handle_);
        }

        handle_ = other.handle_;
        groups.incRefcount(handle_);

        return *this;
    }

    CValue(CValue &&other)
        : handle_(other.handle_)
    {
        other.handle_ = NullHandle;
    }

    CValue &operator=(CValue &&other)
    {
        if (handle_ != NullHandle)
        {
            auto &groups = CDataGroups::getSingleton();
            groups.decRefcount(handle_);
        }

        handle_       = other.handle_;
        other.handle_ = NullHandle;
        return *this;
    }

    ~CValue()
    {
        auto &groups = CDataGroups::getSingleton();
        if (handle_ != NullHandle)
        {
            groups.decRefcount(handle_);
        }
    }

    T const &get()
    {
        auto &groups     = CDataGroups::getSingleton();
        void const *data = groups.get(handle_);

        return *reinterpret_cast<T const *>(data);
    }

    void set(T &&v)
    {
        auto &groups = CDataGroups::getSingleton();
        void *data   = groups.get(handle_);

        *reinterpret_cast<T *>(data) = std::move(v);
        groups.updateBindings(handle_);
    }

    operator SHandle()
    {
        return handle_;
    }

private:
    SHandle handle_;
};

template <typename T>
CValue<T> allocValue(T &&v = T())
{
    auto &groups = CDataGroups::getSingleton();
    CValue<T> value(groups.alloc<T>());
    value.set(std::move(v));
    return value;
}

template <typename T>
class CBindSameType : public CAbstractBinding
{
public:
    void apply(void const *src, void *target)
    {
        *reinterpret_cast<T *>(target) = *reinterpret_cast<T const *>(src);
    }

private:
};

template <typename T>
class CBindToString : public CAbstractBinding
{
public:
    void apply(void const *src, void *target)
    {
        *reinterpret_cast<std::string *>(target) = std::to_string(*reinterpret_cast<T const *>(src));
    }

private:
};

int main()
{
    auto &groups = CDataGroups::getSingleton();

    groups.addType<int>();
    groups.addType<size_t>();
    groups.addType<glm::vec3>();
    groups.addType<std::string>();

    {
        auto v  = allocValue<int>(555);
        auto v2 = allocValue<int>(777);
        auto v3 = allocValue<std::string>("888");

        groups.addBinding(v, v2, std::make_unique<CBindSameType<int>>());
        groups.addBinding(v2, v3, std::make_unique<CBindToString<int>>());
        //        groups.addBinding(v, v, std::make_unique<CBindToString<int>>());

        groups.printAll<int>();

        v.set(666);
        std::cout << "v3: " << v3.get() << "\n";
        groups.printAll<int>();

        v2 = allocValue<int>(333);
        v.set(444);
        std::cout << "v3: " << v3.get() << "\n";

        groups.printAll<int>();
        groups.printAll<std::string>();
    }
}
