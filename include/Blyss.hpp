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
#include <memory>

#include "Camera.hpp"
#include "Gui.hpp"
#include "InputSystem.hpp"
#include "Renderer.hpp"

namespace blyss
{

    class Blyss final
    {
    public:
        Blyss(std::int32_t window_width, std::int32_t window_height);

        void Frame(double delta_seconds);

        [[nodiscard]] bool IsCloseRequested() const;

        std::shared_ptr<Camera> GetCamera();

        std::shared_ptr<InputSystem> GetInput();

    private:
        Gui gui_;
        Renderer renderer_;

        std::shared_ptr<Camera> camera_;
        std::shared_ptr<InputSystem> input_;
    };

}
