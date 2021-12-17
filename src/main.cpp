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

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory>

#include <uv.h>
#include <boost/log/trivial.hpp>

#include "client/local/LocalGameClient.hpp"
#include "core/App.hpp"
#include "host/local/LocalGameHost.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/string_cast.hpp>

int RunUnsafe()
{
    double width = 800.0;
    double height = 600.0;
    auto mat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    // BOOST_LOG_TRIVIAL(info) << glm::to_string(mat);

    auto vec = glm::vec4(200.0f, 200.0f, 0.0f, 1.0f);


    auto vec2 = mat * vec;

    BOOST_LOG_TRIVIAL(info) << to_string(vec2);

    auto uk = glm::inverse(mat);
    auto hhh = uk * vec2;

    BOOST_LOG_TRIVIAL(info) << to_string(hhh);


    // uv_loop_t loop;
    // uv_loop_init(&loop);
    //
    // auto game_host = std::make_unique<blyss::LocalGameHost>(&loop);
    // auto app_frontend = std::make_unique<blyss::LocalGameClient>(&loop);
    //
    // blyss::App app(std::move(game_host), std::move(app_frontend));
    // app.Run();
    return EXIT_SUCCESS;
}

int main() noexcept
{
    try
    {
        return RunUnsafe();
    }
    catch (const std::exception& e)
    {
        std::fprintf(stderr, "Uncaught exception occurred while running: %s\n", e.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::fprintf(stderr, "Uncaught exception of an unknown type occurred while running!\n");
        return EXIT_FAILURE;
    }
}