#ifndef BLYSS_EXCEPTIONS_GLFWEXCEPTION_H_
#define BLYSS_EXCEPTIONS_GLFWEXCEPTION_H_

#include <exception>

namespace Blyss
{
    class GLFWException : public std::exception
    {
    public:
        static void Check();

    private:
        GLFWException(const char* message);
    };
}

#endif