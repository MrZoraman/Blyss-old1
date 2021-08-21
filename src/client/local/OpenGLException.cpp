/*
 * Copyright (c) MrZoraman 2021
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "client/local/OpenGLException.hpp"

#include <exception>
#include <sstream>

#include <glad/glad.h>

namespace blyss
{
    OpenGLException::OpenGLException(const char* message)
        : std::exception(message)
    {
    }

    void OpenGLException::OpenGLPostCallback(const char* name, void*, int, ...)
    {
        std::stringstream ss;
        ss << "The following OpenGL error flags were set when calling " << name << ": ";

        /*
         * According to the OpenGL spec, glGetError() will keep returning error codes until
         * GL_NO_ERROR is returned, since some opengl calls can raise multiple errors.
         */

         /*
          * We keep track of a flag indicating if there is an error or not so that we can decide
          * if an exception should be thrown or not. This needs to happen after all the errors are
          * read, otherwise an exception with possibly incomplete info would be thrown.
          */
        auto has_error = false;

        /*
         * This flag is for looping until glGetError returns GL_NO_ERROR. This flag is used
         * instead of an infinite loop with a break because most of the loop body is in a switch
         * statement, which also uses the break keyword.
         */
        auto processing_errors = true;
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