#include "exceptions/GLFWException.hpp"

#include <sstream>
#include <exception>

#include <GLFW/glfw3.h>

namespace Blyss
{
    void GLFWException::Check()
    {
        const char* error_message = nullptr;
        const int code = glfwGetError(&error_message);
        if (code == GLFW_NO_ERROR)
        {
            return;
        }

        std::stringstream ss;
        ss << "GLFW error: " << code << ": ";

        if (error_message)
        {
            ss << error_message;
        }
        else
        {
            ss << "No further information is available.";
        }

        throw GLFWException(ss.str().c_str());
    }

    GLFWException::GLFWException(const char* message)
        : std::exception(message)
    {
    }
    
}