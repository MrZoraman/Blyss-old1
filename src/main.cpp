#include <cstdlib>

#include <boost/log/trivial.hpp>

#include "exceptions/GLFWException.hpp"
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