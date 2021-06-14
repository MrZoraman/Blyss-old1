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

namespace blyss
{
    BGlfwWindowW::BGlfwWindowW(int width, int height, const char* title)
        : window_{MakeWindow(width, height, title)}
    {
        glfwSetWindowUserPointer(window_, this);
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
            std::fprintf(stderr, "%s\n", e.what());
        }
        catch (...)
        {
            std::fprintf(stderr, "Unknown error.\n");
        }
    }

    void BGlfwWindowW::MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_);
    }

    bool BGlfwWindowW::ShouldClose() const
    {
        bool should_close = glfwWindowShouldClose(window_);
        return should_close;
    }

    void BGlfwWindowW::SwapBuffers()
    {
        glfwSwapBuffers(window_);
    }

    GLFWwindow* BGlfwWindowW::MakeWindow(int width, int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        return window;
    }

    GLFWwindow* BGlfwWindowW::GetRawWinPtr() const
    {
        return window_;
    }

    void BGlfwWindowW::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto* wrapper = static_cast<BGlfwWindowW*>(glfwGetWindowUserPointer(window));
        wrapper->on_window_resize(*wrapper, width, height);
    }
}
