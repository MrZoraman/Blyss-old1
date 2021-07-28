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

#include "GladGLFW.hpp"

#include <chrono>

#include "Blyss.hpp"

#include <imgui.h>
#include <boost/log/trivial.hpp>

#include "events/WindowResizedEvent.hpp"
#include "rendering/Renderer.hpp"

namespace blyss
{
    Blyss::Blyss()
        : window_{glfwCreateWindow(640, 480, "Blyss", nullptr, nullptr), &glfwDestroyWindow}
        , renderer_{window_.get()}
    {
        glfwSetWindowSizeCallback(window_.get(), &GlfwWindowResizeCallback);
        glfwSetKeyCallback(window_.get(), &InputSystem::GlfwKeyCallback);
    }

    void Blyss::Run()
    {
        GLFWwindow* window = window_.get();

        auto previous_time = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(window))
        {
            auto now = std::chrono::high_resolution_clock::now();
            delta_ = now - previous_time;
            previous_time = now;

            // The ImGui frame is started at the beginning of each loop iteration so that ImGui
            // functions can be used anywhere at any time in a blyss frame or callback.
            renderer_.NewImGuiFrame();

            glfwPollEvents();
            ImGui::ShowDemoWindow();

            renderer_.Render();

            glfwSwapBuffers(window);
        }
    }


    GLFWwindow* Blyss::GetWindow()
    {
        return window_.get();
    }

    std::chrono::duration<double> Blyss::GetDelta()
    {
        return delta_;
    }

    InputSystem& Blyss::GetInput()
    {
        return input_;
    }

    void Blyss::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        void* ptr = glfwGetWindowUserPointer(window);
        if (!ptr)
        {
            BOOST_LOG_TRIVIAL(warning) << "GLFW captured an event, but no user pointer for the window was set!";
            return;
        }
        
        auto* blyss = static_cast<Blyss*>(ptr);
        WindowResizedEventArgs args{ width, height };
        WindowResizedEventHandler(*blyss, args);
    }


}