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

#include <glad/glad.h>

#include "Window.hpp"

#include <chrono>
#include <exception>
#include <memory>
#include <thread>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>

#include "Blyss.hpp"
#include "Camera.hpp"
#include "InputSystem.hpp"
#include "exceptions/OpenGLException.hpp"

namespace blyss
{
    Window::Window(int width, int height, const char* title)
        : glfw_window_{width, height, title}
    {
        glfw_window_.MakeContextCurrent();
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Unable to initialize GLAD!");
        }

        glad_set_post_callback(OpenGLException::OpenGLPostCallback);

        glfw_window_.on_window_resize.connect(OnWindowResize);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(glfw_window_.GetRawWinPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

    }

    Window::~Window()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Window::RunUntilClose()
    {
        std::int32_t window_width = 0;
        std::int32_t window_height = 0;
        glfw_window_.GetWindowSize(&window_width, &window_height);

        Blyss blyss(window_width, window_height);

        std::shared_ptr<Camera> camera = blyss.GetCamera();
        glfw_window_.on_window_resize.connect(BGlfwWindowW::OnWindowResizeType::slot_type(&Camera::OnWindowResize, camera.get(), _1, _2, _3).track_foreign(camera));

        std::shared_ptr<InputSystem> input = blyss.GetInput();
        glfw_window_.on_key.connect(BGlfwWindowW::OnKeyType::slot_type(&InputSystem::OnGlfwKey, input.get(), _1, _2, _3, _4, _5).track_foreign(input));

        auto previous_time = std::chrono::high_resolution_clock::now();
        while (!(glfw_window_.ShouldClose() || blyss.IsCloseRequested()))
        {

            try
            {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> delta_time = now - previous_time;
                previous_time = now;

                glClear(GL_COLOR_BUFFER_BIT);

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                blyss.Frame(delta_time.count());
                ImGui::Render();

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
            catch (OpenGLException& e)
            {
                BOOST_LOG_TRIVIAL(error) << "OpenGL Error: " << e.what();
            }

            glfw_window_.SwapBuffers();

            glfwPollEvents();
        }
    }

    void Window::OnWindowResize(BGlfwWindowW&, int width, int height)
    {
        if (width <= 0 || height <= 0)
        {
            BOOST_LOG_TRIVIAL(warning) << "Window was resized, and the new dimensions are " << width
                << ", " << height << ", which is strange. This resize operation will be ignored.";
            return;
        }

        glViewport(0, 0, width, height);
    }
}
