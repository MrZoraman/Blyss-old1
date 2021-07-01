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

#include <array>

#include <boost/signals2.hpp>

#include "GladGLFW.hpp"

#include "wrappers/glfw/BGlfwWindowW.hpp"

namespace blyss
{
    enum class InputButton
    {
        kNone = 0,
        kForward = 1,
        kReverse = 2,
        kLeft = 3,
        kRight = 4,
        kMouseCaptureToggle = 5,
        kLastValue
    };

    class InputSystem final
    {
    public:
        InputSystem();
        ~InputSystem() = default;

        // This class is move only
        InputSystem(const InputSystem&) = delete;
        InputSystem(InputSystem&&) = delete;
        InputSystem& operator=(const InputSystem&) = delete;
        InputSystem& operator=(InputSystem&&) = delete;

        typedef boost::signals2::signal<void(InputButton)> OnKeyPressType;

        void OnGlfwKey(BGlfwWindowW& window, int key, int scancode, int action, int mods);

        OnKeyPressType on_key_press;

    private:
        std::array<bool, static_cast<size_t>(InputButton::kLastValue)> pressed_buttons_;
        std::array<InputButton, GLFW_KEY_LAST> button_mapping_;
    };
}