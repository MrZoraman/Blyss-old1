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

#pragma once

#include <cstdint>

#include "GladGLFW.hpp"

namespace blyss
{
    class Blyss;

    class BGlfwWindowW final
    {
    public:
        // This class is move only
        BGlfwWindowW(const BGlfwWindowW&) = delete;
        BGlfwWindowW(BGlfwWindowW&&) = delete;
        BGlfwWindowW& operator=(const BGlfwWindowW&) = delete;
        BGlfwWindowW& operator=(BGlfwWindowW&&) = delete;
        
        BGlfwWindowW(int width, int height, const char* title);

        ~BGlfwWindowW();
        
        void MakeContextCurrent();
        
        [[nodiscard]] bool ShouldClose() const;
        
        void SwapBuffers();
        
        [[nodiscard]] GLFWwindow* GetRawWinPtr() const;

        void GetWindowSize(std::int32_t* width, std::int32_t* height);

        void SetInputMode(int mode, int value);

        void SetUserPointer(void* ptr);

    private:
        GLFWwindow* const window_;
        
        static void GlfwWindowResizeCallback(GLFWwindow* window, int width, int height);

        static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}
