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

#include "client/local/LocalGameClient.hpp"

#include <uv.h>

#include <core/Logging.hpp>
#include "client/local/GladGLFW.hpp"
#include "client/local/GLFWException.hpp"
#include "client/local/OpenGLException.hpp"

namespace blyss
{
    LocalGameClient::LocalGameClient(uv_loop_t* loop)
        : loop_{loop}
        , window_{nullptr, &glfwDestroyWindow}
        , renderer_{}
    {
        // Set Glad error callback so an exception is thrown whenever an OpenGL error occurrs.
        glad_set_post_callback(&OpenGLException::OpenGLPostCallback);

        // Set GLFW error callback. This is one of the only GLFW functions that can be called before
        // GLFW is initialized. The registered callback will throw an exception any time there is
        // a GLFW error.
        glfwSetErrorCallback(&GLFWException::OnGlfwError);

        glfwInit();

        window_ = WindowPtr{ glfwCreateWindow(640, 480, "Hello, world", nullptr, nullptr), &glfwDestroyWindow };
        glfwMakeContextCurrent(window_.get());
        glfwSwapInterval(1);

        renderer_ = std::make_unique<Renderer>(window_.get());
    }

    LocalGameClient::~LocalGameClient()
    {
        try
        {
            glfwTerminate();
        }
        catch (...)
        {
            LogErrorNoExcept("Failed to terminate GLFW!");
        }

        glfwSetErrorCallback(nullptr);
        glad_set_post_callback(nullptr);
    }

    void LocalGameClient::HostEventLoop()
    {
        auto* window = window_.get();
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            uv_run(loop_, UV_RUN_NOWAIT);
            renderer_->Frame();
        }
    }


}