#ifndef BLYSS_WINDOW_H
#define BLYSS_WINDOW_H

#include <glad/glad.h>
#include "wrappers/glfw/BGlfwWindowW.hpp"

namespace blyss
{
    class Window final
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        // This class is move only
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void RunUntilClose();

    private:

        BGlfwWindowW glfw_window_;

        void Frame();

        static void OnWindowResize(BGlfwWindowW& glfw_window, int width, int height);
    };
}

#endif
