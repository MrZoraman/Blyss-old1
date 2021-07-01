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

#include "InputSystem.hpp"

#include <cassert>

#include <gsl/gsl>

#include "GladGLFW.hpp"

#include <boost/log/trivial.hpp>

namespace blyss
{
    InputSystem::InputSystem()
        : pressed_buttons_{}
        , button_mapping_{}
    {
        for (bool& pressed_button : pressed_buttons_)
        {
            pressed_button = false;
        }

        for (InputButton& button : button_mapping_)
        {
            button = InputButton::kNone;
        }

        // These are the default mappings.
        button_mapping_[GLFW_KEY_W] = InputButton::kForward;
        button_mapping_[GLFW_KEY_S] = InputButton::kReverse;
        button_mapping_[GLFW_KEY_A] = InputButton::kLeft;
        button_mapping_[GLFW_KEY_D] = InputButton::kRight;
        button_mapping_[GLFW_KEY_TAB] = InputButton::kMouseCaptureToggle;
    }

    void InputSystem::OnGlfwKey(BGlfwWindowW& window, int key, int scancode, int action, int mods)
    {
        // Cast key (int) to the size_type used by the button_mapping array. This prevents a warning for
        // comparison of mismatched types.
        auto s_key = static_cast<decltype(button_mapping_)::size_type>(key);

        if (key < 0 || s_key >= button_mapping_.size())
        {
            // Complain, but don't do anything if a weird key press is received.
            BOOST_LOG_TRIVIAL(warning) << "Received a button press from GLFW that is outside the range of the button mapping: " << key;
            return;
        }
        
        InputButton button = gsl::at(button_mapping_, s_key);
        if (button == InputButton::kNone)
        {
            // There is no input mapped to this key.
            return;
        }

        // Cast button (type class) to an index used in the pressed buttons array.
        auto button_input_index = static_cast<decltype(pressed_buttons_)::size_type>(button);

        // The index should be a valid index in the pressed buttons array, since it is initialized
        // with a length equal to the number of InputButton enum values. If this is not the case,
        // then something is seriously wrong.
        assert(button_input_index > 0 && button_input_index < pressed_buttons_.size());

        // Update the button pressed state.
        if (action == GLFW_PRESS)
        {
            gsl::at(pressed_buttons_, button_input_index) = true;

            // Fire on key press event!
            on_key_press(button);
        }
        else if (action == GLFW_RELEASE)
        {
            gsl::at(pressed_buttons_, button_input_index) = false;
        }
        else if (action == GLFW_REPEAT)
        {
            // Ignore repeat events.
        }
        else
        {
            // GLFW gave me something weird. Complain about it, but move on.
            BOOST_LOG_TRIVIAL(warning) << "Got a strange key event action from GLFW: " << action;
        }
    }

}