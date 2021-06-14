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

#ifndef BLYSS_RECTANGLE_H
#define BLYSS_RECTANGLE_H

#include <cstdint>

namespace blyss
{
    class Rectangle
    {
    public:
        Rectangle(std::int32_t width, std::int32_t height);

        [[nodiscard]] std::int32_t Area() const;

    private:
        std::int32_t width_;
        std::int32_t height_;
    };
}

#endif
