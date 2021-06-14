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

#ifndef BLYSS_EXCEPTIONS_GLFWEXCEPTION_H
#define BLYSS_EXCEPTIONS_GLFWEXCEPTION_H

#include <exception>

namespace blyss
{
    /**
     * @brief Thrown when a GLFW error occurs.
    */
    class GLFWException final : public std::exception
    {
    public:
        /**
         * @brief Throws a GLFWException, formatting it with the given error code and description.
         * @param error_code The GLFW error code.
         * @param description The GLFW error description.
        */
        [[noreturn]] static void OnGlfwError(int error_code, const char* description);

    private:
        explicit GLFWException(const char* message);
    };
}

#endif
