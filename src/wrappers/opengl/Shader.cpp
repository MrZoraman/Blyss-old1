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

#include <cstdio>
#include <cstring>
#include <exception>
#include <sstream>

#include <glad/glad.h>

#include "exceptions/OpenGLException.hpp"

const size_t INFO_LOG_SIZE = 512;

namespace blyss
{
    Shader::Shader(GLenum shader_type)
        : handle_{glCreateShader(shader_type)}
    {
        if (handle_ == 0)
        {
            throw OpenGLException("glCreateShader failed to create a shader!");
        }
    }

    Shader::~Shader()
    {
        try
        {
            glDeleteShader(handle_);
        }
        catch (const std::exception& e)
        {
            std::printf("Failed to delete shader %d: %s\n", handle_, e.what());
        }
        catch (...)
        {
            std::printf("Unknown error occurred when trying to delete shader %d\n", handle_);
        }
    }

    void Shader::set_source(const char* source_code) const
    {
        glShaderSource(handle_, 1, &source_code, nullptr);
    }

    void Shader::Compile() const
    {
        char info_log[INFO_LOG_SIZE];
        std::memset(&info_log, 0, sizeof(info_log));

        GLint success = 0;
        glCompileShader(handle_);
        glGetShaderiv(handle_, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(handle_, INFO_LOG_SIZE, nullptr, static_cast<char*>(info_log));
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
