#include <cstdlib>

#include <boost/log/trivial.hpp>

#include "exceptions/GLFWException.hpp"
#include "GLFWContext.hpp"
#include "Window.hpp"

int main()
{
    const int kDefaultWidth = 640;
    const int kDefaultHeight = 480;

    try
    {

        Blyss::GLFWContext glfw_context;
        Blyss::Window w(kDefaultWidth, kDefaultHeight, "Hello, world!");
        w.RunUntilClose();
    }
    catch (const Blyss::GLFWException& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}