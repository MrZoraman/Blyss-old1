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

#include "core/App.hpp"

#include <iostream>

#include <uv.h>

namespace blyss
{
    App::App(std::unique_ptr<IGameHost> game_host, std::unique_ptr<IAppFrontend> app_frontend)
        : game_host_(std::move(game_host))
        , app_frontend_(std::move(app_frontend))
    {
    }

    void App::Run()
    {
        uv_loop_t loop;
        uv_loop_init(&loop);

        app_frontend_->HostEventLoop(&loop);
    }

}