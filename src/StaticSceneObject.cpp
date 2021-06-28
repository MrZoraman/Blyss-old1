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

#include "StaticSceneObject.hpp"

#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "StaticGeometry.hpp"
#include "wrappers/opengl/ShaderProgram.hpp"

namespace blyss
{
    StaticSceneObject::StaticSceneObject(std::shared_ptr<StaticGeometry> geometry)
        : geometry_{std::move(geometry)}
        , position_{0, 0, 0}
        , scale_{1, 1, 1}
    {
    }

    void StaticSceneObject::SetPosition(const glm::vec3& position)
    {
        position_ = position;
    }

    void StaticSceneObject::SetScale(const glm::vec3& scale)
    {
        scale_ = scale;
    }

    void StaticSceneObject::Draw() const
    {
        geometry_->Draw();
    }

    glm::mat4 StaticSceneObject::MakeModelMatrix() const
    {
        // build identity matrix
        glm::mat4 model{ 1.0 };

        // apply transforms
        model = glm::translate(model, position_);
        model = glm::scale(model, scale_);

        return model;
    }


}