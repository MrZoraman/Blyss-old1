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

#include "StaticObject.hpp"

namespace blyss
{
    StaticObject::StaticObject()
        : position_{0, 0, 0}
        , scale_{1, 1, 1}
        , rotation_{0, 0, 0, 1}
    {
    }

    void StaticObject::Draw()
    {
        
    }

    glm::vec3 StaticObject::GetPosition() const
    {
        return position_;
    }

    void StaticObject::SetPosition(glm::vec3 position)
    {
        position_ = position;
    }

    glm::vec3 StaticObject::GetScale() const
    {
        return scale_;
    }

    void StaticObject::SetScale(glm::vec3 scale)
    {
        scale_ = scale;
    }

    glm::quat StaticObject::GetRotation() const
    {
        return rotation_;
    }

    void StaticObject::SetRotation(glm::quat rotation)
    {
        rotation_ = rotation;
    }

}