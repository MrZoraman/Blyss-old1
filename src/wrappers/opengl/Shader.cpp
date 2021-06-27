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

#include "wrappers/opengl/Shader.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <exception>
#include <sstream>

#include <glad/glad.h>

#include "exceptions/OpenGLException.hpp"

#include "Logging.hpp"

// This is the size of the info log buffer that OpenGL will write to when a shader compile
// error occurs.
const size_t kInfoLogSize = 512;

namespace blyss
{
    Shader::Shader(GLenum shader_type)
        : handle_{glCreateShader(shader_type)}
    {
        /*
         * We have an error callback registered with Glad. If an opengl error occurs, that callback
         * should be called, and that callback should then throw an exception. If everything goes
         * right, then it should be impossible for handle_ to be 0 ("null") at this point.
         */
        assert(handle_ != 0);
    }

    Shader::~Shader()
    {
        // Nothing to do if the handle was never successfully created.
        if (handle_ == 0)
        {
            return;
        }

        try
        {
            glDeleteShader(handle_);
        }
        catch (const std::exception& e)
        {
            LogErrorNoExcept(e.what());
        }
        catch (...)
        {
            LogErrorNoExcept("Unknown error occurred while trying to delete shader.");
        }
    }

    void Shader::set_source(const char* source_code) const
    {
        glShaderSource(handle_, 1, &source_code, nullptr);
    }

    void Shader::Compile() const
    {
        // Create our info log buffer and zero it out.
        char info_log[kInfoLogSize];
        std::memset(&info_log, 0, sizeof(info_log));

        // Compile the shader.
        glCompileShader(handle_);

        // Check if compilation was successful or not.
        GLint success = 0;
        glGetShaderiv(handle_, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            // If not successful, get the error message from OpenGL.
            glGetShaderInfoLog(handle_, kInfoLogSize, nullptr, static_cast<char*>(info_log));

            // Create the exception message and throw.
            std::stringstream ss;
            ss << "Failed to compile shader: ";
            ss << static_cast<char*>(info_log);
            throw OpenGLException(ss.str().c_str());
        }
    }

    GLuint Shader::get_handle() const
    {
        return handle_;
    }

}
