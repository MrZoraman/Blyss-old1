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

#include "StaticGeometry.hpp"

#include <cstdint>
#include <vector>

#include "wrappers/opengl/GLBuffer.hpp"
#include "wrappers/opengl/GLVertexArrayObject.hpp"
#include "wrappers/opengl/ShaderProgram.hpp"

namespace blyss
{
    StaticGeometry::StaticGeometry(const std::vector<float>& vertex_data, const std::vector<std::uint32_t>& index_data, std::shared_ptr<ShaderProgram> program)
        : vao_{}
        , vertex_buffer_{}
        , index_buffer_{}
        , program_{std::move(program)}
        , index_count_{index_data.size()}
    {
        /*
         * Bind the VAO that is associated with this geometry/data to opengl's global state.
         */
        vao_.Bind();

        /*
         * Bind the vertex buffer to opengl's global state, upload data, set up attribute pointers,
         * and then unbind the vertex buffer. The instructions given in the next several function
         * calls are saved to the vao that we just bound above.
         */
        vertex_buffer_.Bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);
        GLuint aPos = program_->GetAttribLocation("aPos");
        glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(aPos);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /*
         * Bind the element array buffer to opengl's global state and upload index data. The
         * instructions given in the next few function calls are saved to the vao that we just
         * bound above.
         */
        index_buffer_.Bind(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(std::uint32_t), index_data.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /*
         * Unbind the vao to keep opengl's global state clean.
         */
        glBindVertexArray(0);
    }

    void StaticGeometry::Draw() const
    {
        // Use our shader program.
        program_->Use();

        // Bind the VAO with all the info that was written to it in the constructor.
        vao_.Bind();

        // The draw call itself.
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index_count_), GL_UNSIGNED_INT, nullptr);
    }


}