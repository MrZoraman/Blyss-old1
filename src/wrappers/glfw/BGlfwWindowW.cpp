#include "wrappers/glfw/BGlfwWindowW.hpp"

#include <cstdio>
#include <exception>

namespace Blyss
{
    BGlfwWindowW::BGlfwWindowW(int width, int height, const char* title)
        : window_{MakeWindow(width, height, title)}
    {
        glfwSetWindowUserPointer(window_, this);
        glfwSetWindowSizeCallback(window_, GlfwWindowResizeCallback);
    }

    BGlfwWindowW::~BGlfwWindowW()
    {
        try
        {
            if (window_ != nullptr)
            {
                glfwSetWindowUserPointer(window_, nullptr);
                glfwSetWindowSizeCallback(window_, nullptr);
                glfwDestroyWindow(window_);
            }

            OnWindowResize.disconnect_all_slots();
        }
        catch (const std::exception& e)
        {
            std::fprintf(stderr, "%s\n", e.what());
        }
        catch (...)
        {
            std::fprintf(stderr, "Unknown error.\n");
        }
    }

    void BGlfwWindowW::MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_);
    }

    bool BGlfwWindowW::ShouldClose() const
    {
        bool should_close = glfwWindowShouldClose(window_);
        return should_close;
    }
    
    void BGlfwWindowW::SwapBuffers()
    {
        glfwSwapBuffers(window_);
    }

    GLFWwindow* BGlfwWindowW::MakeWindow(int width, int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        return window;
    }

    GLFWwindow* BGlfwWindowW::GetRawWinPtr() const
    {
        return window_;
    }

    void BGlfwWindowW::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto *wrapper = static_cast<BGlfwWindowW*>(glfwGetWindowUserPointer(window));
        wrapper->OnWindowResize(*wrapper, width, height);
    }


}