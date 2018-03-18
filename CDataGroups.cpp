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

#include "CDataGroups.h"
#include <algorithm>

using TFromHook = boost::intrusive::member_hook<CAbstractBinding, TListMemberHook, &CAbstractBinding::fromHook_>;
using TToHook   = boost::intrusive::member_hook<CAbstractBinding, TListMemberHook, &CAbstractBinding::toHook_>;
using TDataHandlerHook =
    boost::intrusive::member_hook<CAbstractDataHandler, TListMemberHook, &CAbstractDataHandler::hook_>;

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

class CRawStorageBlocked : public IStorage
{
    const static size_t blockSize = 4096;
    struct SBlock
    {
        SBlock(size_t alignment)
            : storage_(blockSize * alignment)
        {
            std::fill(refcount_.begin(), refcount_.end(), 0);
        }

        std::vector<uint8_t> storage_;
        std::array<uint32_t, blockSize> refcount_;
        size_t nextFree_{0};
        size_t numAlloc_{0};
    };

public:
    CRawStorageBlocked(size_t size, size_t alignment)
        : size_(size)
        , alignment_(align(size, alignment))
        , sizeInc_(blockSize)
    {
    }

    template <typename T>
    CRawStorageBlocked(tag<T>)
        : CRawStorageBlocked(sizeof(T), std::alignment_of<T>::value)
    {
    }

    size_t getUnreferenced() override
    {
        if (numAlloc_ == capacity_)
        {
            nextFree_ = capacity_;
            capacity_ += sizeInc_;
            blocks_.emplace_back(SBlock(alignment_));
        }

        while (refcountRef(nextFree_))
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
        auto &rc = refcountRef(i);
        if (rc == 0)
        {
            ++numAlloc_;
        }
        ++rc;
    }

    bool decRefcount(size_t i) override
    {
        auto &rc = refcountRef(i);
        assert(rc != 0);
        --rc;
        if (rc == 0)
        {
            --numAlloc_;
        }
        return rc == 0;
    }

    inline uint8_t *operator[](size_t i) override
    {
        auto const &address = elementAddress(i);
        return blocks_[address.first].storage_.data() + (address.second * alignment_);
    }

    size_t getCapacity() override
    {
        return capacity_;
    }

    uint32_t getRefcount(size_t i) override
    {
        return refcountRef(i);
    }

    inline std::pair<size_t, size_t> elementAddress(size_t i) const
    {
        return {i / blockSize, i % blockSize};
    }

private:
    uint32_t &refcountRef(size_t i)
    {
        auto const &address = elementAddress(i);
        return blocks_[address.first].refcount_[address.second];
    }

    std::vector<SBlock> blocks_;

    const size_t size_;
    const size_t alignment_;
    const size_t sizeInc_;
    size_t capacity_{0};
    size_t numAlloc_{0};
    size_t nextFree_{0};
};

class CBindings
{

public:
    //    using TMap = std::multimap<uint32_t, IBindingPtr>;
    using TToList   = boost::intrusive::list<CAbstractBinding, TToHook, boost::intrusive::constant_time_size<false>>;
    using TFromList = boost::intrusive::list<CAbstractBinding, TFromHook, boost::intrusive::constant_time_size<false>>;
    using TIterator = typename TFromList::iterator;
    using TRange    = std::pair<TIterator, TIterator>;

    using TDataHandlerList =
        boost::intrusive::list<CAbstractDataHandler, TDataHandlerHook, boost::intrusive::constant_time_size<false>>;

    using TDataHandlerInterator = typename TDataHandlerList::iterator;
    using TDataHandlerRange     = std::pair<TDataHandlerInterator, TDataHandlerInterator>;

    TRange rangeForSource(uint32_t src)
    {
        auto &links = bindings2_.at(src);
        return TRange(links.fromList_.begin(), links.fromList_.end());

        //        return TRange(bindings_.lower_bound(src), bindings_.upper_bound(src));
    }

    TDataHandlerRange dataHandlerRangeFor(uint32_t src)
    {
        auto &links = bindings2_.at(src);
        return TDataHandlerRange(links.handlerList_.begin(), links.handlerList_.end());
    }

    void addBindingFrom(uint32_t srcIndex, CAbstractBinding *binding)
    {
        bindings2_.at(srcIndex).fromList_.push_back(*binding);
    }

    void addBindingTo(uint32_t targetIndex, CAbstractBinding *binding)
    {
        bindings2_.at(targetIndex).toList_.push_back(*binding);
    }

    void addHandler(uint32_t index, CAbstractDataHandler *handler)
    {
        bindings2_.at(index).handlerList_.push_back(*handler);
    }

    void setSize(size_t s)
    {
        bindings2_.resize(s);
    }

    template <typename T>
    struct SDisposer
    {
        void operator()(T *ptr)
        {
            delete ptr;
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
        links.fromList_.clear_and_dispose(SDisposer<CAbstractBinding>());

        for (auto it = links.toList_.begin(), eit = links.toList_.end(); it != eit; ++it)
        {
            it->fromHook_.unlink();
        }
        links.toList_.clear_and_dispose(SDisposer<CAbstractBinding>());

        links.handlerList_.clear_and_dispose(SDisposer<CAbstractDataHandler>());
    }

private:
    //    TMap bindings_;

    struct SBindingLinks
    {
        TFromList fromList_;
        TToList toList_;
        TDataHandlerList handlerList_;
    };

    std::vector<SBindingLinks> bindings2_;
};

CDataGroups &CDataGroups::getSingleton()
{
    static CDataGroups groups;
    return groups;
}

void CDataGroups::addTypeInternal(std::unique_ptr<ITypeSupport> typeSupport)
{
    types_.emplace_back(SType{typeSupport->getTypeIndex(),
                              std::make_unique<CRawStorageBlocked>(typeSupport->getSize(), typeSupport->getAlignment()),
                              std::make_unique<CBindings>(), std::move(typeSupport)});
}

SHandle CDataGroups::allocInternal(uint32_t type)
{
    auto &typeRec = types_.at(type);

    auto const index = uint32_t(typeRec.data->getUnreferenced());
    typeRec.data->incRefcount(index);
    typeRec.bindings->setSize(typeRec.data->getCapacity());
    typeRec.typeSupport->construct((*typeRec.data)[index]);

    return SHandle{type, index};
}

void CDataGroups::addHandler(SHandle h, std::unique_ptr<CAbstractDataHandler> handler)
{
    auto &type = types_.at(h.getType());
    assert(type.type == handler->getType());

    type.bindings->addHandler(h.getIndex(), handler.get());
    handler.release();
}

void CDataGroups::addBindingInternal(SHandle src, SHandle target, std::unique_ptr<CAbstractBinding> binding)
{
    auto &srcType    = types_.at(src.getType());
    auto &targetType = types_.at(target.getType());

#ifndef NDEBUG
    auto typePair = binding->getTypes();
    assert(srcType.type == typePair.first);
    assert(targetType.type == typePair.second);
#endif

    srcType.bindings->addBindingFrom(src.getIndex(), binding.get());
    targetType.bindings->addBindingTo(target.getIndex(), binding.get());
    binding->setTarget(target);

    binding->apply(getStorage(src), getStorage(target));
    binding.release();
}

void *CDataGroups::getStorage(const SHandle &handle)
{
    auto &type = types_.at(handle.getType());
    return (*type.data)[handle.getIndex()];
}

void CDataGroups::updateBindings(const SHandle &handle)
{
    tmpDeque_.clear();
    tmpVec_.clear();

    std::deque<SHandle> &q = tmpDeque_;
    q.push_back(handle);

//    using TCycleCheckSet = std::unordered_set<SHandle, SHandleHash /*, SHandleEqual*/>;
//    std::unique_ptr<TCycleCheckSet> cycleCheckSet;

    std::vector<SHandle> &handles = tmpVec_;

    size_t numBindings               = 0;
    size_t const cycleCheckThreshold = 200000;

//    size_t qReadPos = 0
    while (!q.empty())
    {
        SHandle const &f = q.front();
        handles.emplace_back(f);

        auto &type       = types_.at(f.getType());
        auto const range = type.bindings->rangeForSource(f.getIndex());

        for (auto it = range.first; it != range.second; ++it)
        {
            auto const &target = it->getTarget();

#if 1
            auto &type1 = types_.at(f.getType());
            auto &type2 = types_.at(target.getType());
            it->apply((*type1.data)[f.getIndex()], (*type2.data)[target.getIndex()]);
#else
            it->apply(getStorage(f), getStorage(target));
#endif
            ++numBindings;
            if (numBindings >= cycleCheckThreshold)
            {
                std::sort(handles.begin(), handles.end());
                if( std::adjacent_find(handles.begin(), handles.end()) != handles.end())
                {
                    std::cout << "cycle\n";
                    return;
                }
                numBindings = 0;
            }

            q.push_back(target);
        }
        q.pop_front();
    }

    for (auto const &h : handles)
    {
        auto &type = types_.at(h.getType());

        auto range = type.bindings->dataHandlerRangeFor(h.getIndex());
        for (auto it = range.first; it != range.second; ++it)
        {
            it->dataChanged();
        }
    }
}

void CDataGroups::incRefcount(const SHandle &handle)
{
    auto &type = types_.at(handle.getType());
    type.data->incRefcount(handle.getIndex());
}

void CDataGroups::decRefcount(const SHandle &handle)
{
    auto &type   = types_.at(handle.getType());
    bool lastRef = type.data->decRefcount(handle.getIndex());
    if (lastRef)
    {
        type.typeSupport->destruct((*type.data)[handle.getIndex()]);
        type.bindings->removeAll(handle.getIndex());
    }
}

// std::shared_ptr<CAbstractBinding> CBindingFactory::getBindingInternal(std::type_index type,
// std::shared_ptr<CAbstractBinding> init)
//{
//    auto it = bindings_.find(type);
//    if (it != bindings_.end())
//    {
//        return it->second;
//    }

//    if (!init)
//    {
//        return {};
//    }
//    return bindings_.emplace(type, init).first->second;

//}
