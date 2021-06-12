#ifndef BLYSS_EXCEPTIONS_GLFWEXCEPTION_H
#define BLYSS_EXCEPTIONS_GLFWEXCEPTION_H

#include <exception>

namespace blyss
{
    /**
     * @brief Thrown when a GLFW error occurs.
    */
    class GLFWException final : public std::exception
    {
    public:
        /**
         * @brief Throws a GLFWException, formatting it with the given error code and description.
         * @param error_code The GLFW error code.
         * @param description The GLFW error description.
        */
        [[noreturn]] static void OnGlfwError(int error_code, const char* description);

    private:
        explicit GLFWException(const char* message);
    };
}

#endif
