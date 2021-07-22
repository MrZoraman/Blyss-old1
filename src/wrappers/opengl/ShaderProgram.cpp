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

#include "wrappers/opengl/ShaderProgram.hpp"

#include <cassert>
#include <cstring>
#include <exception>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logging.hpp"
#include "exceptions/OpenGLException.hpp"

 // This is the size of the info log buffer that OpenGL will write to when a shader link
 // error occurs.
const size_t kInfoLogSize = 512;

namespace blyss
{
    ShaderProgram::ShaderProgram()
        : handle_{glCreateProgram()}
    {
        /*
         * We have an error callback registered with Glad. If an opengl error occurs, that callback
         * should be called, and that callback should then throw an exception. If everything goes
         * right, then it should be impossible for handle_ to be 0 ("null") at this point.
         */
        assert(handle_ != 0);
    }

    ShaderProgram::~ShaderProgram()
    {
        // Nothing to do if the handle was never successfully created.
        if (handle_ == 0)
        {
            return;
        }

        try
        {
            glDeleteProgram(handle_);
        }
        catch (const std::exception& e)
        {
            LogErrorNoExcept(e.what());
        }
        catch (...)
        {
            LogErrorNoExcept("Unknown error occurred while destroying shader program.");
        }
    }

    void ShaderProgram::AttachShader(const Shader& shader) const
    {
        glAttachShader(handle_, shader.get_handle());
    }

    void ShaderProgram::Link() const
    {
        // Create our error log buffer and zero it out.
        char info_log[kInfoLogSize];
        std::memset(&info_log, 0, sizeof(info_log));

        // Link the shader program.
        glLinkProgram(handle_);

        // Check if linking was successful or not.
        int success = 0;
        glGetProgramiv(handle_, GL_LINK_STATUS, &success);
        if (!success)
        {
            // Get the error message from OpenGL.
            glGetProgramInfoLog(handle_, kInfoLogSize, nullptr, static_cast<char*>(info_log));
            
            // Create the exception message and throw.
            std::stringstream ss;
            ss << "Failed to link shader program: ";
            ss << static_cast<char*>(info_log);
            throw OpenGLException(ss.str().c_str());
        }
    }

    void ShaderProgram::Use() const
    {
        glUseProgram(handle_);
    }

    GLint ShaderProgram::GetAttribLocation(const GLchar* name) const
    {
        return glGetAttribLocation(handle_, name);
    }

    GLint ShaderProgram::GetUniformLocation(const GLchar* name) const
    {
        return glGetUniformLocation(handle_, name);
    }

    void ShaderProgram::UniformMatrix(GLint model_loc, glm::mat4 matrix) const
    {
        Use();
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(matrix));
    }


}
