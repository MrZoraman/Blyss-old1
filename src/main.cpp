#include <cstdlib>

#include <boost/log/trivial.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

        while (!window.ShouldClose())
        {
            try
            {
                glClear(GL_COLOR_BUFFER_BIT);
            }
            catch (Blyss::OpenGLException& e)
            {
                BOOST_LOG_TRIVIAL(error) << "OpenGL Error: " << e.what();
            }

            window.SwapBuffers();
            
            glfwPollEvents();
        }
    }
    catch (const Blyss::GLFWException& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Fatal GLFW exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}