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

#pragma once

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

class IStorage
{
public:
    virtual ~IStorage()
    {
    }

    virtual size_t getUnreferenced()       = 0;
    virtual void incRefcount(size_t i)     = 0;
    virtual bool decRefcount(size_t i)     = 0;
    virtual uint8_t *operator[](size_t i)  = 0;
    virtual size_t getCapacity()           = 0;
    virtual uint32_t getRefcount(size_t i) = 0;
};
#if 0
struct SHandle
{
    SHandle(uint32_t type, uint32_t index)
        : type_(type)
        , index_(index)
    {
    }

    SHandle()
        : SHandle(uint32_t(-1), uint32_t(-1))
    {
    }

    SHandle(SHandle const&) = default;
    SHandle& operator=(SHandle const&) = default;

    SHandle(SHandle &&) = default;
    SHandle& operator=(SHandle &&) = default;


    inline uint32_t getType() const
    {
        return type_;
    }
    inline uint32_t getIndex() const
    {
        return index_;
    }

    inline bool operator==(SHandle const &other) const
    {
        return type_ == other.type_ && index_ == other.index_;
    }

    inline bool operator!=(SHandle const &other) const
    {
        return !(operator==(other));
    }
    inline bool operator<(SHandle const &other) const
    {
        return type_ < other.type_ || (!(other.type_ < type_) && index_ < other.index_);
    }

private:
    uint32_t type_;
    uint32_t index_;
};
#else
struct SHandle
{
    SHandle(uint32_t type, uint32_t index)
        : type_(type)
        , index_(index)
    {
    }

    SHandle()
        : SHandle(uint32_t(-1), uint32_t(-1))
    {
    }

    SHandle(SHandle const&) = default;
    SHandle& operator=(SHandle const&) = default;

    SHandle(SHandle &&) = default;
    SHandle& operator=(SHandle &&) = default;


    inline uint32_t getType() const
    {
        return type_;
    }
    inline uint32_t getIndex() const
    {
        return index_;
    }

    inline bool operator==(SHandle const &other) const
    {
        return type_ == other.type_ && index_ == other.index_;
    }

    inline bool operator!=(SHandle const &other) const
    {
        return !(operator==(other));
    }
    inline bool operator<(SHandle const &other) const
    {
        return type_ < other.type_ || (!(other.type_ < type_) && index_ < other.index_);
    }

private:
    uint32_t type_ : 8;
    uint32_t index_ : 24;
};
#endif

inline std::ostream &operator<<(std::ostream &os, SHandle const &h)
{
    os << "handle(" << h.getType() << ":" << h.getIndex() << ")";
    return os;
}

const SHandle NullHandle = SHandle{uint32_t(-1), uint32_t(-1)};

struct SHandleHash
{
    size_t operator()(SHandle const &h) const
    {
        const std::hash<uint32_t> hash;
        return hash(h.getType()) + hash(h.getIndex());
    }
};

// struct SHandleEqual
//{
//    bool operator()(SHandle const &h1, SHandle const &h2) const
//    {
//        return h1.getType() == h2.getType() && h1.index_ == h2.index_;
//    }
//};

// class IBinding
//{
// public:
//    virtual ~IBinding()
//    {
//    }
//    virtual void apply(void const *src, void *target) = 0;

// private:
//};

using TListMemberHook = boost::intrusive::list_member_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>>;

class CAbstractBinding /*: public IBinding*/
{
public:
    using TTypePair = std::pair<std::type_index, std::type_index>;

    virtual ~CAbstractBinding()
    {
    }

    TListMemberHook fromHook_;
    TListMemberHook toHook_;
    inline SHandle const &getTarget()
    {
        return target_;
    }

    inline void setTarget(SHandle const &target)
    {
        target_ = target;
    }

    virtual void apply(void const *src, void *target) = 0;
    virtual TTypePair getTypes()                      = 0;

private:
    SHandle target_;
};

template <typename TInput, typename TOutput>
class CAbstractTypedBinding : public CAbstractBinding
{
public:
    TTypePair getTypes() override
    {
        return {typeid(TInput), typeid(TOutput)};
    }
};

using CAbstractBindingPtr = std::unique_ptr<CAbstractBinding>;

class CAbstractDataHandler
{
public:
    TListMemberHook hook_;

    virtual ~CAbstractDataHandler()
    {
    }
    virtual void dataChanged()        = 0;
    virtual std::type_index getType() = 0;
};

template <typename T>
class CAbstractTypedDataHandler : public CAbstractDataHandler
{
public:
    std::type_index getType() override
    {
        return typeid(T);
    }
};

template <typename THandler, typename T>
class CDataHandlerCallFunctor : public CAbstractTypedDataHandler<T>
{
public:
    CDataHandlerCallFunctor(THandler f)
        : f_(std::move(f))
    {
    }

    void dataChanged() override
    {
        f_();
    }

private:
    THandler f_;
};

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
    virtual size_t getSize()                    = 0;
    virtual size_t getAlignment()               = 0;
    virtual std::type_index getTypeIndex()      = 0;
};

template <typename T>
class CTypeSupportDefault : public ITypeSupport
{
public:
    void construct(void *storage) override
    {
        auto *v = new (storage) T();
        (void)v; // debug
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

    size_t getSize() override
    {
        return sizeof(T);
    }
    size_t getAlignment() override
    {
        return std::alignment_of<T>::value;
    }
    std::type_index getTypeIndex() override
    {
        return typeid(T);
    }
};

// using IBindingPtr         = std::unique_ptr<IBinding>;

class CBindings;

// class CBindingFactory final
//{
// public:
//    template<typename T, typename = std::enable_if_t<std::is_base_of<CAbstractBinding, T>::value, void>>
//    std::shared_ptr<CAbstractBinding> getBinding()
//    {
//        auto binding = getBindingInternal(typeid (T), {});
//        return binding ? binding : getBindingInternal(typeid(T), std::make_shared<T>());
//    }
// private:
//    std::shared_ptr<CAbstractBinding> getBindingInternal(std::type_index type, std::shared_ptr<CAbstractBinding>
//    init);

//    std::map<std::type_index, std::shared_ptr<CAbstractBinding>> bindings_;
//};

class CDataGroups final
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
    static CDataGroups &getSingleton();

    TTypes::iterator findType(std::type_index type)
    {
        return std::find_if(types_.begin(), types_.end(), [&](TTypes::value_type const &v) { return v.type == type; });
    }

    template <typename T>
    void addType()
    {
#ifndef NDEBUG
        std::type_index const typeId = typeid(T);
        auto it                      = findType(typeId);
        assert(it == types_.end());
#endif

        addTypeInternal(std::make_unique<CTypeSupportDefault<T>>());
    }

    void addTypeInternal(std::unique_ptr<ITypeSupport> typeSupport);

    template <typename T>
    SHandle alloc()
    {
        std::type_index const typeId = typeid(T);
        auto it                      = findType(typeId);
        assert(it != types_.end());
        auto const type = uint32_t(std::distance(types_.begin(), it));
        return allocInternal(type);
    }

    SHandle allocInternal(uint32_t type);

    template <typename T>
    void addBinding(SHandle src, SHandle target)
    {
        //        addBindingInternal(src, target, bindingFactory_.getBinding<T>());
        addBindingInternal(src, target, std::make_unique<T>());
    }

    void addHandler(SHandle h, std::unique_ptr<CAbstractDataHandler> handler);

    template <typename T, typename THandler>
    void addHandlerFunctor(SHandle h, THandler f)
    {
        addHandler(h, std::make_unique<CDataHandlerCallFunctor<THandler, T>>(std::move(f)));
    }

    void *getStorage(SHandle const &handle);

    void updateBindings(SHandle const &handle);

    void incRefcount(SHandle const &handle);

    void decRefcount(SHandle const &handle);

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

    template <typename T>
    inline T const &get(SHandle const &handle)
    {
        auto *v = reinterpret_cast<T const *>(getStorage(handle));
        return *v;
    }

    template <typename T>
    inline void set(SHandle const &handle, T &&v)
    {
        *(reinterpret_cast<T *>(getStorage(handle))) = std::move(v);
        updateBindings(handle);
    }

    template <typename T>
    inline void set(SHandle const &handle, T const &v)
    {
        *(reinterpret_cast<T *>(getStorage(handle))) = v;
        updateBindings(handle);
    }

private:
    void addBindingInternal(SHandle src, SHandle target, std::unique_ptr<CAbstractBinding> binding);

    TTypes types_;

    std::vector<SHandle> tmpVec_;
    std::deque<SHandle> tmpDeque_;
    //    CBindingFactory bindingFactory_;
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
        return CDataGroups::getSingleton().get<T>(handle_);
    }

    void set(T &&v)
    {
        CDataGroups::getSingleton().set(handle_, std::move(v));
    }

    void set(T const &v)
    {
        CDataGroups::getSingleton().set(handle_, v);
    }

    operator SHandle()
    {
        return handle_;
    }

    T const &operator*()
    {
        return get();
    }

private:
    SHandle handle_;
};

class CVariant
{
public:
    template <typename T>
    explicit CVariant(T const &v)
        : handle_(CDataGroups::getSingleton().alloc<T>)
    {
    }

    template <typename T>
    explicit CVariant(T &&v)
        : handle_(CDataGroups::getSingleton().alloc<T>)
    {
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
CValue<T> introfumbleValue(SHandle h)
{
    auto &groups = CDataGroups::getSingleton();
    groups.incRefcount(h);
    CValue<T> value(h);
    return value;
}
