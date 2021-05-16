#include <cstdlib>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <boost/log/trivial.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "exceptions/GLFWException.hpp"
#include "exceptions/OpenGLException.hpp"
#include "wrappers/glfw/BGlfwWindowW.hpp"
#include "GLFWContext.hpp"

int main()
{
    try
    {

        Blyss::GLFWContext glfw_context;
        Blyss::BGlfwWindowW window(640, 480, "Hello, world!");
        window.MakeContextCurrent();

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            return EXIT_FAILURE;
        }

        glad_set_post_callback(Blyss::OpenGLException::OpenGLPostCallback);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        window.InstallImGui();
        ImGui_ImplOpenGL3_Init("#version 130");


        while (!window.ShouldClose())
        {
            try
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::ShowDemoWindow(nullptr);

                ImGui::Render();
                int display_w = 0;
                int display_h = 0;
                window.GetFramebufferSize(display_w, display_h);
                glViewport(0, 0, display_w, display_h);
                glClear(GL_COLOR_BUFFER_BIT);

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
            catch (Blyss::OpenGLException& e)
            {
                BOOST_LOG_TRIVIAL(error) << "OpenGL Error: " << e.what();
            }

            window.SwapBuffers();
            
            glfwPollEvents();
        }

        ImGui::DestroyContext();
    }
    catch (const Blyss::GLFWException& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}