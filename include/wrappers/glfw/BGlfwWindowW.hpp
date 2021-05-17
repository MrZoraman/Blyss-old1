#ifndef BLYSS_WRAPPERS_GLFW_BGLFWWINDOWW_H_
#define BLYSS_WRAPPERS_GLFW_BGLFWWINDOWW_H_

#include "GLFW/glfw3.h"

namespace Blyss
{
    class BGlfwWindowW final
    {
    public:
        BGlfwWindowW(const BGlfwWindowW&) = delete;
        BGlfwWindowW(BGlfwWindowW&&) = delete;
        BGlfwWindowW& operator=(const BGlfwWindowW&) = delete;
        BGlfwWindowW& operator=(BGlfwWindowW&&) = delete;

        BGlfwWindowW(int width, int height, const char* title);
        ~BGlfwWindowW();

        void MakeContextCurrent();
        [[nodiscard]] bool ShouldClose();
        void SwapBuffers();
        void GetFramebufferSize(int& w, int& h);
        GLFWwindow* GetRawWinPtr();

    private:
        GLFWwindow* const window_;

        static GLFWwindow* MakeWindow(int width, int height, const char* title);
    };
}

#endif