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

#include "wrappers/glfw/BGlfwWindowW.hpp"

#include "InputSystem.hpp"

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

        bool is_mouse_captured_;

        void ToggleMouseCapture();

        void OnKeyPress(InputButton button);
        
        static void OnWindowResize(BGlfwWindowW& glfw_window, int width, int height);
    };
}
