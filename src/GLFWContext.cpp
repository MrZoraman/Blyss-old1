#include "GLFWContext.hpp"

#include <GLFW/glfw3.h>

#include "exceptions/GLFWException.hpp"

namespace blyss
{
    GLFWContext::GLFWContext()
    {
        glfwSetErrorCallback(GLFWException::OnGlfwError);
        glfwInit();
    }

    GLFWContext::~GLFWContext()
    {
        // This does nothing if there is nothing to terminate.
        glfwTerminate();
        glfwSetErrorCallback(nullptr);
    }

}