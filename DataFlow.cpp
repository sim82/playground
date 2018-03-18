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

#include <functional>

#include <glm/ext.hpp>
#include <glm/vec3.hpp>


template <typename GLMType, typename = decltype(glm::to_string(std::declval<GLMType>()))>
std::ostream &operator<<(std::ostream &out, const GLMType &g)
{
    return out << glm::to_string(g);
}

template <typename T>
class CBindSameType : public CAbstractTypedBinding<T, T>
{
public:
    void apply(void const *src, void *target)
    {
        *reinterpret_cast<T *>(target) = *reinterpret_cast<T const *>(src);
    }
private:
};

template <typename T>
class CBindToString : public CAbstractTypedBinding<T, std::string>
{
public:
    void apply(void const *src, void *target)
    {
        *reinterpret_cast<std::string *>(target) = std::to_string(*reinterpret_cast<T const *>(src));
    }
private:
};

class CVec3Interpolator
{
public:
    CVec3Interpolator(SHandle in1, SHandle in2, SHandle inF, SHandle out)
        : in1_(allocValue<glm::vec3>())
        , in2_(allocValue<glm::vec3>())
        , inF_(allocValue<float>())
        , out_(allocValue<glm::vec3>())

    {
        auto & groups = CDataGroups::getSingleton();

        groups.addBinding<CBindSameType<glm::vec3>>(in1, in1_);
        groups.addBinding<CBindSameType<glm::vec3>>(in2, in2_);
        groups.addBinding<CBindSameType<float>>(inF, inF_);
        groups.addBinding<CBindSameType<glm::vec3>>(out_, out);

        groups.addHandlerFunctor<glm::vec3>(in1_, std::bind(&CVec3Interpolator::dataChanged, this));
        groups.addHandlerFunctor<glm::vec3>(in2_, std::bind(&CVec3Interpolator::dataChanged, this));
        groups.addHandlerFunctor<float>(inF_, std::bind(&CVec3Interpolator::dataChanged, this));
    }


private:
    void dataChanged()
    {
        glm::vec3 d = *in2_- *in1_;

        out_.set(*in1_ + (d * *inF_));
    }

    CValue<glm::vec3> in1_;
    CValue<glm::vec3> in2_;
    CValue<float> inF_;

    CValue<glm::vec3> out_;
};

class CVec3InterpolatorNodup
{
public:
    CVec3InterpolatorNodup(CValue<glm::vec3> const& in1, CValue<glm::vec3> const& in2, CValue<float> const& inF, CValue<glm::vec3> const& out )
        : in1_(in1)
        , in2_(in2)
        , inF_(inF)
        , out_(out)

    {
        auto & groups = CDataGroups::getSingleton();

        groups.addHandlerFunctor<glm::vec3>(in1_, std::bind(&CVec3InterpolatorNodup::dataChanged, this));
        groups.addHandlerFunctor<glm::vec3>(in2_, std::bind(&CVec3InterpolatorNodup::dataChanged, this));
        groups.addHandlerFunctor<float>(inF_, std::bind(&CVec3InterpolatorNodup::dataChanged, this));
    }


private:
    void dataChanged()
    {
        glm::vec3 d = in2_.get() - in1_.get();

        out_.set(in1_.get() + (d*inF_.get()));
    }

    CValue<glm::vec3> in1_;
    CValue<glm::vec3> in2_;
    CValue<float> inF_;

    CValue<glm::vec3> out_;
};


int main()
{
    auto &groups = CDataGroups::getSingleton();

    groups.addType<int>();
    groups.addType<size_t>();
    groups.addType<glm::vec3>();
    groups.addType<std::string>();
    groups.addType<float>();
    groups.addType<double>();

    {
        auto v  = allocValue<int>(555);
        auto v2 = allocValue<int>(777);
        auto v3 = allocValue<std::string>("888");

        groups.addBinding<CBindSameType<int>>(v, v2);  //, std::make_unique<CBindSameType<int>>());
        groups.addBinding<CBindToString<int>>(v2, v3); //, std::make_unique<CBindToString<int>>());
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

    auto v      = allocValue<int>(555);
    std::vector<SHandle> garbage;

    SHandle src = v;
    for (size_t i = 0; i < 100000; ++i)
    {
        auto dest = groups.alloc<int>();
        groups.set(dest, int(i));
        groups.addBinding<CBindSameType<int>>(src, dest); //, std::make_unique<CBindSameType<int>>());
        src = dest;
        garbage.push_back(src);
    }

//    groups.addBinding<CBindSameType<int>>(src, v);

    for (size_t i = 0; i < 10; ++i)
    {
        v.set(int(666 + i));
        std::cout << "src: " << groups.get<int>(src) << "\n";
    }

    for (SHandle const& h : garbage)
    {
        groups.decRefcount(h);
    }


    CValue<glm::vec3>in1 = allocValue(glm::vec3(0.0, 0.2, 0.7));
    CValue<glm::vec3>in2 = allocValue(glm::vec3(1.0, 0.4, 0.2));
    CValue<float> inF = allocValue(0.0f);

    CValue<glm::vec3> out = allocValue<glm::vec3>();


    CVec3InterpolatorNodup interpolator(in1, in2, inF, out);

    for (float f = 0.0f; f <= 1.0f; f+=0.01f)
    {
        inF.set(f);
        std::cout << out.get() << "\n";
    }

    CVariant variant(100.0);
    variant.isA<int>();

    std::cout << "variant " << double(variant) << "\n";
}
