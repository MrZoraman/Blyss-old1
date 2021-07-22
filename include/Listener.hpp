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

#pragma once

#include <typeindex>
#include <typeinfo>

#include "Event.hpp"

namespace blyss
{
    class Blyss;

    class IListener
    {
    public:
        virtual ~IListener() = default;
        
        virtual std::type_index GetTypeIndex() = 0;
    };

    template<typename T>
    class Listener final : public IListener
    {
    public:
        explicit Listener(void (*func)(Blyss&, T&))
            : func_{func}
        {
        }

        void Call(Blyss& b, T& evt)
        {
            func_(b, evt);
        }

        std::type_index GetTypeIndex() override
        {
            return std::type_index(typeid(T));
        }
    private:
        void (*func_)(Blyss&, T&);
    };
}