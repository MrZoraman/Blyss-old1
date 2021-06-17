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

#include <cstdio>
#include <cstdlib>
#include <exception>

#include <boost/log/trivial.hpp>

#include "Window.hpp"
#include "wrappers/glfw/GLFWContext.hpp"

int main() noexcept
{
    try
    {
        const int default_width = 640;
        const int default_height = 480;

        blyss::GLFWContext glfw_context;
        blyss::Window w(default_width, default_height, "Hello, world!");
        w.RunUntilClose();
    }
    catch (const std::exception& e)
    {
        try
        {
            BOOST_LOG_TRIVIAL(fatal) << "Fatal exception: " << e.what();
        }
        catch (...)
        {
            std::fprintf(stderr, "Unable to print error message!");
        }
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::fprintf(stderr, "An unknown error occurred!");
    }

    return EXIT_SUCCESS;

}
