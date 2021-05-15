#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cassert>

#include <boost/log/trivial.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rectangle.hpp"
#include "GLFWContext.hpp"
#include "wrappers/glfw/BGlfwWindowW.hpp"
#include "exceptions/GLFWException.hpp"


void blyss_post_gl_callback(const char *name, void *funcptr, int len_args, ...)
{
    GLenum error_code = GL_NO_ERROR;
    while (true)
    {
        error_code = glad_glGetError();
        switch (error_code)
        {
        case GL_INVALID_ENUM:
            BOOST_LOG_TRIVIAL(error) << "Invalid enum used in " << name << "!";
            break;
        case GL_INVALID_VALUE:
            BOOST_LOG_TRIVIAL(error) << "Invalid value used in " << name << "!";
            break;
        case GL_INVALID_OPERATION:
            BOOST_LOG_TRIVIAL(error) << "Invalid operation in " << name << "!";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            BOOST_LOG_TRIVIAL(error) << "Incomplete framebuffer object used in " << name << "!";
            break;
        case GL_OUT_OF_MEMORY:
            BOOST_LOG_TRIVIAL(error) << "OpenGL out of memory in " << name << "!";
            break;
        case GL_STACK_UNDERFLOW:
            BOOST_LOG_TRIVIAL(error) << "Attempted OpenGL stack underflow in " << name << "!";
            break;
        case GL_STACK_OVERFLOW:
            BOOST_LOG_TRIVIAL(error) << "Attempted OpenGL stack overflow in " << name << "!";
            break;
        default:
            break;
        }
    }
}

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

        while (!window.ShouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);

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