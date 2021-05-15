#include "GLFWContext.hpp"

#include <GLFW/glfw3.h>

#include "exceptions/GLFWException.hpp"

namespace Blyss
{
    GLFWContext::GLFWContext()
    {
        glfwInit(); GLFWException::Check();
    }

    GLFWContext::~GLFWContext()
    {
        // This does nothing if there is nothing to terminate.
        glfwTerminate();
    }

}