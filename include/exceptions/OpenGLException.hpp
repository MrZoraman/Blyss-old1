#ifndef BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H
#define BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H

#include <exception>

namespace blyss
{
    class OpenGLException final : public std::exception
    {
    public:
        static void OpenGLPostCallback(const char* name, void* funcptr, int len_args, ...);

    private:

        explicit OpenGLException(const char* message);
    };
}

#endif
