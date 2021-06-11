#include "Window.hpp"

#include <exception>

#include <boost/log/trivial.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "exceptions/OpenGLException.hpp"

namespace Blyss
{
    Window::Window(int width, int height, const char* title)
        : glfw_window_{width, height, title}
    {
        glfw_window_.MakeContextCurrent();

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Unable to initialize GLAD!");
        }

        glad_set_post_callback(Blyss::OpenGLException::OpenGLPostCallback);

        glfw_window_.OnWindowResize.connect(OnWindowResize);

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
        while (!glfw_window_.ShouldClose())
        {
            try
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                Frame();
                ImGui::Render();
                glClear(GL_COLOR_BUFFER_BIT);

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

    void Window::Frame()
    {
        ImGui::ShowDemoWindow(nullptr);
    }

    void Window::OnWindowResize(BGlfwWindowW&, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

}
