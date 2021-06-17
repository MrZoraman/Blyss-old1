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

#include "Renderer.hpp"

#include <glad/glad.h>
#include <boost/log/trivial.hpp>

#include "ShaderSources.hpp"
#include "wrappers/opengl/Shader.hpp"

namespace blyss
{
    Renderer::Renderer()
        : vbo_{}
        , shader_program_{MakeShaderProgram()}
        , vao_{MakeVao()}
    {
        glBindVertexArray(vao_);
        vbo_.Bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glUseProgram(shader_program_);
    }

    void Renderer::Draw()
    {
        glUseProgram(shader_program_);
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    GLuint Renderer::MakeShaderProgram()
    {
        Shader vertex_shader(GL_VERTEX_SHADER);
        vertex_shader.set_source(kVertexShaderSource);
        vertex_shader.Compile();

        Shader fragment_shader(GL_FRAGMENT_SHADER);
        fragment_shader.set_source(kFragmentShaderSource);
        fragment_shader.Compile();

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertex_shader.get_handle());
        glAttachShader(shaderProgram, fragment_shader.get_handle());
        glLinkProgram(shaderProgram);

        int success = 0;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            BOOST_LOG_TRIVIAL(error) << infoLog;
        }

        return shaderProgram;
    }

    GLuint Renderer::MakeVao()
    {
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        return vao;
    }


}
