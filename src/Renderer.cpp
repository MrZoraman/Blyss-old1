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

#include "Renderer.hpp"

#include <glad/glad.h>
#include <boost/log/trivial.hpp>

#include "GeometryLoader.hpp"
#include "ShaderSources.hpp"
#include "wrappers/opengl/Shader.hpp"

namespace blyss
{
    Renderer::Renderer()
        : static_objects_{}
        , static_shader_{std::make_unique<StaticShader>()}
    {
    }

    void Renderer::Draw(const Camera& camera) const
    {
        for (const auto& object : static_objects_)
        {
            object->Draw(camera);
        }
    }

    void Renderer::AddObject(std::shared_ptr<StaticSceneObject> object)
    {
        static_objects_.push_back(std::move(object));
    }

    std::shared_ptr<StaticShader> Renderer::GetStaticShader() const
    {
        return static_shader_;
    }


}
