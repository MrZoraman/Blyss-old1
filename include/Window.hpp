#ifndef BLYSS_WINDOW_H_
#define BLYSS_WINDOW_H_

#include <glad/glad.h>
#include "wrappers/glfw/BGlfwWindowW.hpp"

namespace Blyss
{
    class Window final
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void RunUntilClose();

    private:

        BGlfwWindowW glfw_window_;

        void Frame();

        static void OnWindowResize(BGlfwWindowW& glfw_window, int width, int height);
        
    };
}

#endif