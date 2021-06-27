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
        , shader_program_{MakeShader()}
    {
    }

    void Renderer::Draw() const
    {
        for (const auto& object : static_objects_)
        {
            object->Draw();
        }
    }

    void Renderer::AddObject(std::shared_ptr<StaticSceneObject> object)
    {
        static_objects_.push_back(std::move(object));
    }

    std::shared_ptr<ShaderProgram> Renderer::GetStaticShader() const
    {
        return shader_program_;
    }

    std::shared_ptr<ShaderProgram> Renderer::MakeShader()
    {
        Shader vertex_shader(GL_VERTEX_SHADER);
        vertex_shader.set_source(kVertexShaderSource);
        vertex_shader.Compile();

        Shader fragment_shader(GL_FRAGMENT_SHADER);
        fragment_shader.set_source(kFragmentShaderSource);
        fragment_shader.Compile();

        auto program = std::make_shared<ShaderProgram>();
        program->AttachShader(vertex_shader);
        program->AttachShader(fragment_shader);
        program->Link();

        return program;
    }

}
