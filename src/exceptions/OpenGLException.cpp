#include "exceptions/OpenGLException.hpp"

#include <exception>
#include <sstream>

#include <glad/glad.h>

namespace Blyss
{
    OpenGLException::OpenGLException(const char* message)
        : std::exception(message)
    {
    }

    void OpenGLException::OpenGLPostCallback(const char* name, void* funcptr, int len_args, ...)
    {
        std::stringstream ss;
        ss << "The following OpenGL error flags were set when calling " << name << ": ";

        auto processing_errors = true;
        auto has_error = false;
        while (processing_errors)
        {
            GLenum error_code = glad_glGetError();

            switch (error_code)
            {
            case GL_INVALID_ENUM:
                ss << "Invalid Enum, ";
                has_error = true;
                break;
            case GL_INVALID_VALUE:
                ss << "Invalid Value, ";
                has_error = true;
                break;
            case GL_INVALID_OPERATION:
                ss << "Invalid Operation, ";
                has_error = true;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                ss << "Invalid Frame Buffer Operation, ";
                has_error = true;
                break;
            case GL_OUT_OF_MEMORY:
                ss << "Out Of Memory, ";
                has_error = true;
                break;
            case GL_STACK_UNDERFLOW:
                ss << "Stack Underflow, ";
                has_error = true;
                break;
            case GL_STACK_OVERFLOW:
                ss << "Stack Overflow, ";
                has_error = true;
                break;
            case GL_NO_ERROR:
                processing_errors = false;
                break;
            default:
                ss << "Unknown (" << error_code << "), ";
                has_error = true;
                break;
            }
        }

        if (has_error)
        {
            throw OpenGLException(ss.str().c_str());
        }
    }

}