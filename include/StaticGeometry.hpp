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

#include <cstdint>
#include <memory>
#include <vector>

#include "StaticShader.hpp"
#include "wrappers/opengl/GLBuffer.hpp"
#include "wrappers/opengl/GLVertexArrayObject.hpp"

namespace blyss
{
    class StaticGeometry final
    {
    public:
        StaticGeometry(const std::vector<float>& vertex_data, const std::vector<std::uint32_t>& index_data, std::shared_ptr<StaticShader> program);
        ~StaticGeometry() = default;

        // This class is move only
        StaticGeometry(const StaticGeometry&) = delete;
        StaticGeometry(StaticGeometry&&) = delete;
        StaticGeometry& operator=(const StaticGeometry&) = delete;
        StaticGeometry& operator=(StaticGeometry&&) = delete;

        void BindVao() const;

        void DrawTriangles() const;

        std::shared_ptr<StaticShader> GetShader() const;

    private:
        GLVertexArrayObject vao_;

        // These two variables are stored so that their destructors aren't called until the
        // geometry is destroyed. Otherwise the GPU resources they wrap will be freed while
        // they are still in use.
        GLBuffer vertex_buffer_;
        GLBuffer index_buffer_;

        std::shared_ptr<StaticShader> program_;
        size_t index_count_;
    };
}