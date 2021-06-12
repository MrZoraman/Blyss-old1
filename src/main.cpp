#include <cstdlib>

#include <boost/log/trivial.hpp>

#include "exceptions/GLFWException.hpp"
#include "GLFWContext.hpp"
#include "Window.hpp"

int main()
{
    try
    {
        const int default_width = 640;
        const int default_height = 480;

        blyss::GLFWContext glfw_context;
        blyss::Window w(default_width, default_height, "Hello, world!");
        w.RunUntilClose();
    }
    catch (const blyss::GLFWException& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}