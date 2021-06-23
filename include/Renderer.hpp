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

#pragma once

#include "wrappers/opengl/GLBuffer.hpp"
#include "wrappers/opengl/GLVertexArrayObject.hpp"
#include "wrappers/opengl/ShaderProgram.hpp"

namespace blyss
{
    class Renderer final
    {
    public:
        Renderer();
        void Draw();

    private:
        float vertices_[12] = {
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };

        unsigned int indices_[6] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        GLBuffer vbo_;
        GLBuffer ebo_;
        ShaderProgram shader_program_;
        GLVertexArrayObject vao_;
    };
}
