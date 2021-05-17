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
#include "Window.hpp"

int main()
{
    try
    {

        Blyss::GLFWContext glfw_context;
        Blyss::Window w(640, 480, "Hello, world!");
        w.RunUntilClose();
    }
    catch (const Blyss::GLFWException& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}