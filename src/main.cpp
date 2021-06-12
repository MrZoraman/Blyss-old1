#include <cstdio>
#include <cstdlib>

#include <boost/log/trivial.hpp>

#include "GLFWContext.hpp"
#include "Window.hpp"
#include "exceptions/GLFWException.hpp"

int main() noexcept
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
        try
        {
            BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        }
        catch (...)
        {
            std::fprintf(stderr, "Unable to print error message!");
        }
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::fprintf(stderr, "An unknown error occurred!");
    }

    return EXIT_SUCCESS;

}
