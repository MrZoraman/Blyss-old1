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

#include "Gui.hpp"

#include <imgui.h>

namespace blyss
{
    Gui::Gui()
        : show_demo_window_{false}
        , is_close_requested_{false}
        , show_fps_overlay_{false}
    {
    }

    void Gui::Draw(double delta_seconds)
    {
        if (show_demo_window_)
        {
            ImGui::ShowDemoWindow(&show_demo_window_);
        }

        if (show_fps_overlay_)
        {
            DrawFPSWindow(delta_seconds);
        }

        DrawMainMenuBar();
    }

    void Gui::DrawMainMenuBar()
    {
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Show Demo Window"))
            {
                show_demo_window_ = true;
            }

            ImGui::MenuItem("Show FPS Overlay", nullptr, &show_fps_overlay_, true);

            if (ImGui::MenuItem("Exit"))
            {
                is_close_requested_ = true;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    bool Gui::IsCloseRequested() const
    {
        return is_close_requested_;
    }

    void Gui::DrawFPSWindow(double delta_seconds)
    {
        ImGuiWindowFlags window_flags = 
            ImGuiWindowFlags_NoDecoration | // NOLINT(hicpp-signed-bitwise)
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav;

        ImGui::Begin("FPS Overlay", nullptr, window_flags);

        ImGui::Text("Frame time: %.3f s", delta_seconds);
        ImGui::Text("%.3f FPS", 1 / delta_seconds);

        ImGui::End();
    }


}