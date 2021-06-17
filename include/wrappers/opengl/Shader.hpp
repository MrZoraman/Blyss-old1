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

#include <glad/glad.h>

namespace blyss
{
    class Shader final
    {
    public:
        explicit Shader(GLenum shader_type);
        ~Shader();

        // This class is move only
        Shader(const Shader&) = delete;
        Shader(Shader&&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;

        void set_source(const char* source_code) const;

        void Compile() const;

        [[nodiscard]] GLuint get_handle() const;

    private:
        GLuint handle_;
    };
}
