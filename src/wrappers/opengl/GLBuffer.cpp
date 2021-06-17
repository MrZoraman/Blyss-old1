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

#include "wrappers/opengl/GLBuffer.hpp"

#include <cstdio>

#include <glad/glad.h>

#include "exceptions/OpenGLException.hpp"

namespace blyss
{
    GLBuffer::GLBuffer()
        : handle_{0}
    {
        glGenBuffers(1, &handle_);
    }

    GLBuffer::~GLBuffer()
    {
        try
        {
            glDeleteBuffers(1, &handle_);
        }
        catch (const OpenGLException& e)
        {
            std::printf("Failed to delete buffer %d: %s\n", handle_, e.what());
        }
        catch (...)
        {
            std::printf("Unknown error occurred while deleting buffer %d\n", handle_);
        }
    }

    GLuint GLBuffer::get_handle() const
    {
        return handle_;
    }

    void GLBuffer::Bind(GLenum target) const
    {
        glBindBuffer(target, handle_);
    }

}
