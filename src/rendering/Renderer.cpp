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

#include "rendering/Renderer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <boost/log/trivial.hpp>

#include "StaticObject.hpp"
#include "exceptions/OpenGLException.hpp"

namespace blyss
{
    Renderer::Renderer(GLFWwindow* window)
    {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Unable to initialize GLAD!");
        }

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    Renderer::~Renderer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Renderer::NewImGuiFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }


    void Renderer::Render()
    {
        try
        {
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            for (auto& static_object : static_objects_)
            {
                static_object->Draw();
            }
        }
        catch (const OpenGLException& e)
        {
            BOOST_LOG_TRIVIAL(error) << "Failed to render frame: " << e.what();
        }
    }

    void Renderer::AddStaticObject(std::unique_ptr<StaticObject> object)
    {
        static_objects_.push_back(std::move(object));
    }


}