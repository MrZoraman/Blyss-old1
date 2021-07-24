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

#include "rendering/Renderer.hpp"


namespace blyss
{
    Blyss::Blyss()
        : window_{640, 480, "Blyss"}
        , renderer_{window_}
    {
    }

    void Blyss::Run()
    {
        auto previous_time = std::chrono::high_resolution_clock::now();

        while (!window_.ShouldClose())
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

            window_.SwapBuffers();
        }
    }


    BGlfwWindowW& Blyss::GetWindow()
    {
        return window_;
    }

    std::chrono::duration<double> Blyss::GetDelta()
    {
        return delta_;
    }


}