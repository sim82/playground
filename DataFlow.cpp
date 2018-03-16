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


#include "CDataGroups.h"

template <typename GLMType, typename = decltype(glm::to_string(std::declval<GLMType>()))>
std::ostream &operator<<(std::ostream &out, const GLMType &g)
{
    return out << glm::to_string(g);
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

    auto v = allocValue<int>(555);
    SHandle src = v;
    for( size_t i = 0; i < 100000; ++i )
    {
        auto dest = groups.alloc<int>();
        groups.set(dest, int(i));
        groups.addBinding(src, dest, std::make_unique<CBindSameType<int>>());
        src = dest;
    }

    for (size_t i = 0; i < 1000; ++i)
    {
        v.set(int(666 + i));
        std::cout << "src: " << groups.get<int>(src) << "\n";
    }
}
