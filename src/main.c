#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#include <log.h>

#include "Rectangle.h"

#include <GLFW/glfw3.h>

void _post_call_callback(const char *name, void *funcptr, int len_args, ...)
{
    GLenum error_code = GL_NO_ERROR;
    while (true)
    {
        error_code = glad_glGetError();
        switch (error_code)
        {
        case GL_INVALID_ENUM:
            printf("Invalid enum");
            break;
        case GL_INVALID_VALUE:
            printf("Invalid value");
            break;
        case GL_INVALID_OPERATION:
            printf("Invalid operation");
            break;
        }
    }
}

int main()
{
    log_info("Hello, world!");

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