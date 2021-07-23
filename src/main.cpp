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

#include "GladGLFW.hpp"

#include <cstdio>
#include <cstdlib>
#include <exception>

#include <imgui.h>
#include <boost/log/trivial.hpp>

#include "Blyss.hpp"

#include "ListenerRegistrar.hpp"
#include "exceptions/GLFWException.hpp"
#include "exceptions/OpenGLException.hpp"
#include "wrappers/glfw/BGlfwWindowW.hpp"
#include "wrappers/glfw/GLFWContext.hpp"

int SafeRun()
{
    glad_set_post_callback(&blyss::OpenGLException::OpenGLPostCallback);
    glfwSetErrorCallback(&blyss::GLFWException::OnGlfwError);

    IMGUI_CHECKVERSION();

    blyss::GLFWContext context;
    blyss::Blyss b;
    b.GetWindow().SetUserPointer(&b);
    RegisterListeners(b);
    b.Run();
    return EXIT_SUCCESS;
}

int main() noexcept
{
    try
    {
        return SafeRun();
    }
    catch (const std::exception& e)
    {
        std::fprintf(stderr, "Uncaught exception occurred while running: %s\n", e.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::fprintf(stderr, "Uncaught exception of an unknown type occurred while running!\n");
        return EXIT_FAILURE;
    }
}