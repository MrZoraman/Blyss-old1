#ifndef BLYSS_WINDOW_H
#define BLYSS_WINDOW_H

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
         * @exception ??? There are a lot of exceptions this constructor can throw.
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
         * @exception ??? There are a lot of exceptions this method can throw.
        */
        void RunUntilClose();

    private:

        BGlfwWindowW glfw_window_;

        /**
         * @brief Logic to be executed each frame.
        */
        void Frame();

        /**
         * @brief Executes all the ImGui function calls for creating the desired GUI.
        */
        void DoGuiCommands();

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

#endif
