#include "wrappers/glfw/BGlfwWindowW.hpp"

#include <GLFW/glfw3.h>

#include "exceptions/GLFWException.hpp"

namespace Blyss
{
    BGlfwWindowW::BGlfwWindowW(int width, int height, const char* title)
        : window_{MakeWindow(width, height, title)}
    {
    }

    BGlfwWindowW::~BGlfwWindowW()
    {
        if (window_ != nullptr)
        {
            glfwDestroyWindow(window_);
        }
    }

    void BGlfwWindowW::MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_); GLFWException::Check();
    }

    bool BGlfwWindowW::ShouldClose()
    {
        bool should_close = glfwWindowShouldClose(window_); GLFWException::Check();
        return should_close;
    }

    void BGlfwWindowW::SwapBuffers()
    {
        glfwSwapBuffers(window_); GLFWException::Check();
    }


    GLFWwindow* BGlfwWindowW::MakeWindow(int width, int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr); GLFWException::Check();
        return window;
    }


}