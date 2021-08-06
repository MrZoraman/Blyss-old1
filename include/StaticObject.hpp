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

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace blyss
{
    class StaticObject
    {
        glm::vec3 position_;
        glm::vec3 scale_;
        glm::quat rotation_;

    public:
        StaticObject();

        void Draw();

        [[nodiscard]] glm::vec3 GetPosition() const;
        void SetPosition(glm::vec3 position);

        [[nodiscard]] glm::vec3 GetScale() const;
        void SetScale(glm::vec3 scale);

        [[nodiscard]] glm::quat GetRotation() const;
        void SetRotation(glm::quat rotation);
    };
}