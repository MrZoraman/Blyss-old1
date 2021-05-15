#include "GLFWContext.hpp"

#include <GLFW/glfw3.h>

namespace Blyss
{
    GLFWContext::GLFWContext()
    {
        glfwInit();
    }

    GLFWContext::~GLFWContext()
    {
        // This does nothing if there is nothing to terminate.
        glfwTerminate();
    }

}