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

#include "Blyss.hpp"
#include "wrappers/glfw/BGlfwWindowW.hpp"

namespace blyss
{
    /**
     * @brief Represents the user that the user interacts with.
     *
     * This class contains a glfw window. While the glfw wrapper class is meant to be a pure
     * wrapper around the glfw window, this class provides Blyss related functionality.
    */
    class Window final
    {
    public:
        /**
         * @brief Constructor.
         * @param width The width of the window, in pixels.
         * @param height The height of the window, in pixels.
         * @param title The title of the window.
         * @exception runtime_error if GLAD cannot be initialized.
         * @exception Many There are a lot of exceptions this constructor can throw.
        */
        Window(int width, int height, const char* title);
        ~Window();

        // This class is move only
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        /**
         * @brief Runs the render loop until the user closes the window.
         * @exception Many There are a lot of exceptions this method can throw.
        */
        void RunUntilClose();

    private:

        BGlfwWindowW glfw_window_;
        Blyss blyss_;

        /**
         * @brief Called when the user resizes the window.
         * If width or height are <= 0, this method does nothing.
         *
         * @param glfw_window The window that was resized.
         * @param width The new window width in pixels.
         * @param height The new window height in pixels.
        */
        static void OnWindowResize(BGlfwWindowW& glfw_window, int width, int height);
    };
}
