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

#include "StaticShader.hpp"

#include <glad/glad.h>

#include "ShaderSources.hpp"

namespace blyss
{
    const char* const kProjectionUniformName = "projection";
    const char* const kModelUniformName = "model";
    const char* const kViewUniformName = "view";

    StaticShader::StaticShader()
        : program_(MakeProgram())
    {
    }

    void StaticShader::SetProjection(glm::mat4 projection) const
    {
        GLint uniform_location = program_->GetUniformLocation(kProjectionUniformName);
        program_->UniformMatrix(uniform_location, projection);
    }

    void StaticShader::SetModel(glm::mat4 model) const
    {
        GLint model_location = program_->GetUniformLocation(kModelUniformName);
        program_->UniformMatrix(model_location, model);
    }

    void StaticShader::SetView(glm::mat4 view) const
    {
        GLint view_location = program_->GetUniformLocation(kViewUniformName);
        program_->UniformMatrix(view_location, view);
    }

    void StaticShader::Draw(const Camera& camera, const StaticSceneObject& object) const
    {
        SetProjection(camera.GetProjection());
        SetModel(object.MakeModelMatrix());
        SetView(camera.MakeViewMatrix());

        object.Draw();
    }

    std::shared_ptr<ShaderProgram> StaticShader::GetProgram() const
    {
        return program_;
    }

    std::shared_ptr<ShaderProgram> StaticShader::MakeProgram()
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
