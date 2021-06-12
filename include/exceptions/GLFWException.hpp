#ifndef BLYSS_EXCEPTIONS_GLFWEXCEPTION_H
#define BLYSS_EXCEPTIONS_GLFWEXCEPTION_H

#include <exception>

namespace blyss
{
    class GLFWException final : public std::exception
    {
    public:
        [[noreturn]] static void OnGlfwError(int error_code, const char* description);

    private:
        explicit GLFWException(const char* message);
    };
}

#endif
