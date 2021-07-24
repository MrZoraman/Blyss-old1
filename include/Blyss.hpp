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

#include "GladGLFW.hpp"

#include <chrono>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include <boost/log/trivial.hpp>

#include "InputSystem.hpp"
#include "Listener.hpp"
#include "rendering/Renderer.hpp"

namespace blyss
{
    struct ListenerRegistration
    {
        std::type_index type;
    };

    class Blyss;

    class Blyss
    {
        std::unordered_map<std::type_index, std::unique_ptr<IListener>> listeners_;
        std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window_;
        Renderer renderer_;
        InputSystem input_;

        std::chrono::duration<double> delta_;
        
    public:

        Blyss();

        // This class is move only
        Blyss(const Blyss&) = delete;
        Blyss(Blyss&&) = delete;
        Blyss& operator=(const Blyss&) = delete;
        Blyss& operator=(Blyss&&) = delete;

        GLFWwindow* GetWindow();

        void Run();

        std::chrono::duration<double> GetDelta();

        InputSystem& GetInput();

        template<typename T>
        void SendEvent(T& evt)
        {
            auto key = std::type_index(typeid(T));

            if (listeners_.find(key) == listeners_.end())
            {
                BOOST_LOG_TRIVIAL(warning) << "No listener registered for type " << typeid(T).name();
                return;
            }

            IListener& generic_listener = *listeners_[key];
            Listener<T>& listener = dynamic_cast<Listener<T>&>(generic_listener);
            listener.Call(*this, evt);
        }

        template<typename T>
        void RegisterListener(void (*func)(Blyss&, T&))
        {
            auto key = std::type_index(typeid(T));

            if (listeners_.find(key) != listeners_.end())
            {
                BOOST_LOG_TRIVIAL(warning) << "A listener is already registered for type " << typeid(T).name();
                return;
            }

            listeners_.emplace(key, std::make_unique<Listener<T>>(func));
        }

    private:
        static void GlfwWindowResizeCallback(GLFWwindow* window, int width, int height);
    };
}