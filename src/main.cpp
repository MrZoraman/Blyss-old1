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
#include <imgui_impl_glfw.h>

#include "Blyss.hpp"

#include "exceptions/GLFWException.hpp"
#include "exceptions/OpenGLException.hpp"
#include "wrappers/glfw/GLFWContext.hpp"

int SafeRun()
{
    // Set Glad error callback so an exception is thrown whenever an OpenGL error occurrs.
    glad_set_post_callback(&blyss::OpenGLException::OpenGLPostCallback);

    // Set GLFW error callback. This is one of the only GLFW functions that can be called before
    // GLFW is initialized. The registered callback will throw an exception any time there is
    // a GLFW error.
    glfwSetErrorCallback(&blyss::GLFWException::OnGlfwError);

    // Ensure that ImGui is not linking with a different version for whatever reason.
    IMGUI_CHECKVERSION();

    // Start up the GLFW context. This is GLFW's internal global state, which will be cleaned up
    // when this context object goes out of scope. If this fails, an exception will be thrown.
    blyss::GLFWContext context;

    // Construct Blyss instance. This instance is going to live for the entire duration of the
    // application, so pointers and references to it are safe to pass around and store.
    blyss::Blyss b;

    // Set Blyss's user pointer for the internal GLFW window to blyss itself. This pointer is used
    // in the callbacks to convert GLFW's callbacks to Blyss's callbacks.
    glfwSetWindowUserPointer(b.GetWindow(), &b);

    // Start up ImGui GLFW implimentation. This needs to be run AFTER Blyss's internal window
    // instance is constructed, which happens when Blyss is constructed. Inside this function
    // ImGui will overwrite the callbacks Blyss has registered with GLFW in place of its own.
    // However, ImGui saves our callbacks and calls them within its own callbacks.
    //ImGui_ImplGlfw_InitForOpenGL(b.GetWindow().GetRawWinPtr(), true);

    // Run the program!
    b.Run();

    // If Run() exits, then everything went as expected. If Run() fails for any reason, an
    // exception will be thrown and this code will never get returned.
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