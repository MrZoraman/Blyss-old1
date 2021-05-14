#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boost/log/trivial.hpp>

#include <glad/glad.h>

#include "Rectangle.hpp"

#include <GLFW/glfw3.h>

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
    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow* window_o = glfwCreateWindow(640, 480, "Hello, world!", NULL, NULL);
    if (!window_o)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window_o);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        return EXIT_FAILURE;
    }
    
    while (!glfwWindowShouldClose(window_o))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_o);

        glfwPollEvents();
    }

    glfwDestroyWindow(window_o);
    window_o = NULL;
    glfwTerminate();
    return EXIT_SUCCESS;

}