#ifndef BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H
#define BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H

#include <exception>

namespace blyss
{
    /**
     * @brief Thrown when an OpenGL error occurs.
    */
    class OpenGLException final : public std::exception
    {
    public:
        static void OpenGLPostCallback(const char* name, void* funcptr, int len_args, ...);

    private:

        explicit OpenGLException(const char* message);
    };
}

#endif
