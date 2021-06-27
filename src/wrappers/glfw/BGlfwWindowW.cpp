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

#include <cstdio>
#include <exception>

#include "Logging.hpp"

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

        // This class can fire events. However, the event sender is a member variable. Thus,
        // we store the instance of this class as the user data for this window. When GLFW
        // calls callbacks, we can use that user pointer to get the instance of the window
        // that fired the event, and then call the event sender on that instance.
        glfwSetWindowUserPointer(window_, this);

        // This wrapper class has an event that fires when the window resizes. The callback will
        // fire that event.
        glfwSetWindowSizeCallback(window_, GlfwWindowResizeCallback);
    }

    BGlfwWindowW::~BGlfwWindowW()
    {
        try
        {
            if (window_ != nullptr)
            {
                glfwSetWindowUserPointer(window_, nullptr);
                glfwSetWindowSizeCallback(window_, nullptr);
                glfwDestroyWindow(window_);
            }

            on_window_resize.disconnect_all_slots();
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

    void BGlfwWindowW::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        // Get the instance that caused the callback to be called.
        auto* wrapper = static_cast<BGlfwWindowW*>(glfwGetWindowUserPointer(window));

        // Fire the event!
        wrapper->on_window_resize(*wrapper, width, height);
    }
}
