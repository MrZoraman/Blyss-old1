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

#include "Blyss.hpp"

#include <cstdint>

namespace blyss
{
    Blyss::Blyss(std::int32_t window_width, std::int32_t window_height)
        : gui_{}
        , renderer_{}
        , camera_{std::make_shared<Camera>(window_width, window_height)}
    {
    }

    void Blyss::Frame(double delta_seconds)
    {
        gui_.Draw(delta_seconds);

        renderer_.Draw();
    }

    bool Blyss::IsCloseRequested() const
    {
        return gui_.IsCloseRequested();
    }

    std::shared_ptr<Camera> Blyss::GetCamera()
    {
        return camera_;
    }


}