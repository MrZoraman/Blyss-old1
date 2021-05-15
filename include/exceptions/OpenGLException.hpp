#ifndef BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H_
#define BLYSS_EXCEPTIONS_OPENGLEXCEPTION_H_

#include <exception>

namespace Blyss
{
    class OpenGLException : public std::exception
    {
    public:
        static void OpenGLPostCallback(const char* name, void* funcptr, int len_args, ...);

    private:

        OpenGLException(const char* message);
    };
}

#endif