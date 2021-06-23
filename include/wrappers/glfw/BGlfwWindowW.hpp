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

#include <boost/signals2.hpp>

#include "GLFW/glfw3.h"

namespace blyss
{
    /**
     * @brief Wrapper class around GLFW's window struct.
     *
     * Methods in this class will map directly to methods provided by GLFW. The constructor and
     * destructor allows this class to be used with RAII patterns. It contains various signals for
     * events that can happen, replacing C's more basic callback style used by GLFW.
    */
    class BGlfwWindowW final
    {
    public:
        // This class is move only
        BGlfwWindowW(const BGlfwWindowW&) = delete;
        BGlfwWindowW(BGlfwWindowW&&) = delete;
        BGlfwWindowW& operator=(const BGlfwWindowW&) = delete;
        BGlfwWindowW& operator=(BGlfwWindowW&&) = delete;

        /**
         * @brief Constructor.
         * @param width The width of the window, in pixels.
         * @param height The height of the window, in pixels.
         * @param title The title of the window.
         * @exception GLFWException If GLFW is not initialized.
         * @exception GLFWException If width or height are invalid.
         * @exception GLFWException If the platform does not support creating windows.
         * @exception GLFWException If the requested OpenGL version is unavailable.
         * @exception GLFWException If the machine does not support the requirements to make a window.
         * @exception GLFWException If an unspecified platform error occurs.
         * @sa https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344
        */
        BGlfwWindowW(int width, int height, const char* title);

        ~BGlfwWindowW();

        /**
         * @brief Makes this window's OpenGL context the current one.
         * @exception GLFWException If GLFW is not initialized.
         * @exception GLFWException If the window does not have an OpenGL context.
         * @exception GLFWException If an unspecified platform error occurs.
         * @sa https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157
        */
        void MakeContextCurrent();

        /**
         * @brief Returns whether or not the user has requested that the window should close.
         * @return True if the close button has been pressed, false if it has not.
         * @exception GLFWException If GLFW is not initialized.
         * @sa https://www.glfw.org/docs/latest/group__window.html#ga49c449dde2a6f87d996f4daaa09d6708
         */
        [[nodiscard]] bool ShouldClose() const;

        /**
         * @brief Swaps the window's buffers.
         * @exception GLFWException If GLFW is not initialized.
         * @exception GLFWException If the window does not have an OpenGL context.
         * @exception GLFWException If an unspecified platform error occurs.
        */
        void SwapBuffers();

        /**
         * @brief Gets the underlying pointer that this class wraps.
         *
         * This does NOT transfer ownership of the pointer. ImGui needs to hold onto a pointer to
         * the window instance, and I did not want to add ImGui code to an otherwise pure wrapper.
         *
         * @return The underlying GLFW window pointer. Do not destroy!
        */
        [[nodiscard]] GLFWwindow* GetRawWinPtr() const;

        /**
         * @brief Emitted when the window size is changed.
         *
         * The handler is given the window instance that emitted the event, the new width, and the
         * new height of the window. When an instance of this class is destroyed, all of its
         * signal handlers are cleared.
        */
        boost::signals2::signal<void(BGlfwWindowW&, int, int)> on_window_resize;

    private:
        GLFWwindow* const window_;

        /**
         * @brief This callback is called when the window is resized.
         * @param window The window that was resized.
         * @param width The new width of the window, in pixels.
         * @param height The new height of the window, in pixels.
        */
        static void GlfwWindowResizeCallback(GLFWwindow* window, int width, int height);
    };
}
