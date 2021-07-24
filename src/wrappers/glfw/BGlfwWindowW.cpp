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

#include "wrappers/glfw/BGlfwWindowW.hpp"

#include <cassert>
#include <exception>

#include "Blyss.hpp"
#include "GladGLFW.hpp"
#include "Logging.hpp"
#include "events/WindowResizedEvent.hpp"

namespace blyss
{
    BGlfwWindowW::BGlfwWindowW(int width, int height, const char* title)
        : window_{ glfwCreateWindow(width, height, title, nullptr, nullptr) }
    {
        /*
         * glfw SHOULD have raised an error and called my error callback, which then throws an
         * exception if glfwCreateWindow failed. If all of that is working then it should be
         * impossible for window_ to be null.
         */
        assert(window_ != nullptr);

        // This wrapper class uses boost signals instead of callbacks. The implementations of these
        // callbacks simply call their associated signals.
        glfwSetWindowSizeCallback(window_, GlfwWindowResizeCallback);
        glfwSetKeyCallback(window_, GlfwKeyCallback);
    }

    BGlfwWindowW::~BGlfwWindowW()
    {
        // Nothing to do if the window was never successfully created.
        if (window_ == nullptr)
        {
            return;
        }

        try
        {
            // These probably aren't necessary, but I don't think it hurts to call.
            glfwSetWindowUserPointer(window_, nullptr);
            glfwSetWindowSizeCallback(window_, nullptr);
            glfwSetKeyCallback(window_, nullptr);

            // Destroy the window itself.
            glfwDestroyWindow(window_);
        }
        catch (const std::exception& e)
        {
            LogErrorNoExcept(e.what());
        }
        catch (...)
        {
            LogErrorNoExcept("Unknown error while deconstructing GLFW window wrapper.");
        }
    }

    void BGlfwWindowW::MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_);
    }

    bool BGlfwWindowW::ShouldClose() const
    {
        return glfwWindowShouldClose(window_);
    }

    void BGlfwWindowW::SwapBuffers()
    {
        glfwSwapBuffers(window_);
    }

    GLFWwindow* BGlfwWindowW::GetRawWinPtr() const
    {
        return window_;
    }

    void BGlfwWindowW::GetWindowSize(std::int32_t* width, std::int32_t* height)
    {
        glfwGetWindowSize(window_, width, height);
    }

    void BGlfwWindowW::SetInputMode(int mode, int value)
    {
        glfwSetInputMode(window_, mode, value);
    }

    void BGlfwWindowW::SetUserPointer(void* ptr)
    {
        glfwSetWindowUserPointer(window_, ptr);
    }

    void BGlfwWindowW::SetShouldClose(int should_close)
    {
        glfwSetWindowShouldClose(window_, should_close);
    }

    void BGlfwWindowW::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        void* ptr = glfwGetWindowUserPointer(window);
        if(!ptr)
        {
            BOOST_LOG_TRIVIAL(warning) << "GLFW captured an event, but no user pointer for the window was set!";
            return;
        }

        auto* blyss = static_cast<Blyss*>(ptr);
        WindowResizedEventArgs args{width, height};
        blyss->SendEvent(args);
    }

    //void BGlfwWindowW::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    void BGlfwWindowW::GlfwKeyCallback(GLFWwindow*, int, int, int, int)
    {
        // // Get the instance that caused the callback to be called.
        // auto* wrapper = static_cast<BGlfwWindowW*>(glfwGetWindowUserPointer(window));
        //
        // // Fire the event!
        // wrapper->on_key(*wrapper, key, scancode, action, mods);
    }

}
