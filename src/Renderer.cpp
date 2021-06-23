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
        , ebo_{}
        , shader_program_{}
        , vao_{}
    {
        Shader vertex_shader(GL_VERTEX_SHADER);
        vertex_shader.set_source(kVertexShaderSource);
        vertex_shader.Compile();

        Shader fragment_shader(GL_FRAGMENT_SHADER);
        fragment_shader.set_source(kFragmentShaderSource);
        fragment_shader.Compile();

        shader_program_.AttachShader(vertex_shader);
        shader_program_.AttachShader(fragment_shader);
        shader_program_.Link();

        vao_.Bind();
        vbo_.Bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        ebo_.Bind(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        shader_program_.Use();
    }

    void Renderer::Draw()
    {
        shader_program_.Use();
        vao_.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}
