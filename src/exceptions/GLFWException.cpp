#include "exceptions/GLFWException.hpp"

#include <exception>
#include <sstream>

namespace blyss
{
    GLFWException::GLFWException(const char* message)
        : std::exception(message)
    {
    }

    void GLFWException::OnGlfwError(int error_code, const char* description)
    {
        std::stringstream ss;
        ss << "GLFW error: " << error_code << ": ";

        if (description)
        {
            ss << description;
        }
        else
        {
            ss << "No further information is available.";
        }

        throw GLFWException(ss.str().c_str());
    }
}
