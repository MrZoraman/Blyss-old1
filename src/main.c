#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rectangle.h"

#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window_o))
    {
        // glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_o);

        glfwPollEvents();
    }

    glfwDestroyWindow(window_o);
    window_o = NULL;
    glfwTerminate();
    return EXIT_SUCCESS;

}