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

#include "wrappers/opengl/GLVertexArrayObject.hpp"

#include <cassert>
#include <cstdio>
#include <exception>

#include <glad/glad.h>

#include "Logging.hpp"

namespace blyss
{
    GLVertexArrayObject::GLVertexArrayObject()
        : handle_{0}
    {
        glGenVertexArrays(1, &handle_);

        /*
         * We have an error callback registered with Glad. If an opengl error occurs, that callback
         * should be called, and that callback should then throw an exception. If everything goes
         * right, then it should be impossible for handle_ to be 0 ("null") at this point.
         */
        assert(handle_ != 0);
    }

    GLVertexArrayObject::~GLVertexArrayObject()
    {
        // Nothing to do if the handle was never successfully created.
        if (handle_ == 0)
        {
            return;
        }

        try
        {
            glDeleteVertexArrays(1, &handle_);
        }
        catch (const std::exception& e)
        {
            LogErrorNoExcept(e.what());
        }
        catch (...)
        {
            LogErrorNoExcept("Unknown error occurred while deleting vertex array object.");
        }
    }

    void GLVertexArrayObject::Bind() const
    {
        glBindVertexArray(handle_);
    }

}