/*
 * Copyright (c) MrZoraman 2021
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <cstdlib>
#include <typeinfo>
#include <typeindex>

#include <boost/log/trivial.hpp>

#include "Blyss.hpp"

struct A
{
    virtual ~A(){}

    int num;
};

struct B : A
{
    int other;
};

void thing(A* a)
{
    const auto& hh_id = std::type_index(typeid(*a));
    BOOST_LOG_TRIVIAL(info) << "hh_id: " << hh_id.name() << ", " << hh_id.hash_code();
}

struct C
{
    
};


namespace blyss
{
    void DoThing(Blyss& b, A& a)
    {
        BOOST_LOG_TRIVIAL(info) << "Thing done with a: " << a.num;
    }

    void run()
    {
        Blyss b;
        b.RegisterListener<A>(&DoThing);
        auto thing = std::make_unique<A>();
        thing->num = 42;
        b.SendEvent(std::move(thing));
        
    }
}

int main()
{
    // const auto& a_id = typeid(A);
    // const auto& b_id = typeid(B);
    //
    // BOOST_LOG_TRIVIAL(info) << "a_id: " << a_id.name() << ", " << a_id.hash_code();
    // BOOST_LOG_TRIVIAL(info) << "b_id: " << b_id.name() << ", " << b_id.hash_code();
    //
    // B bi;
    // const auto& bi_id = typeid(bi);
    // BOOST_LOG_TRIVIAL(info) << "bi_id: " << bi_id.name() << ", " << bi_id.hash_code();
    //
    // thing(&bi);

    blyss::run();

    return EXIT_SUCCESS;
}