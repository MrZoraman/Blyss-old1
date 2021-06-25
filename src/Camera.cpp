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

#include "Camera.hpp"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "wrappers/glfw/BGlfwWindowW.hpp"

namespace blyss
{
    const float kFovDegrees = 45.0f;
    const float kNear = 0.1f;
    const float kFar = 100.0f;

    Camera::Camera(float window_width, float window_height)
        : perspective_{MakePerspectiveMatrix(window_width, window_height)}
    {
    }

    glm::mat4 Camera::MakePerspectiveMatrix(float window_width, float window_height)
    {
        return glm::perspective(glm::radians(kFovDegrees), window_width / window_height, kNear, kFar);
    }

    void Camera::OnWindowResize(BGlfwWindowW&, int width, int height)
    {
        perspective_ = MakePerspectiveMatrix(static_cast<float>(width), static_cast<float>(height));
    }


}
