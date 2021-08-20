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

#include <memory>

#include <boost/log/trivial.hpp>

#include <uv.h>

#include "client/local/LocalGameClient.hpp"
#include "core/App.hpp"
#include "host/local/LocalGameHost.hpp"



int main()
{
    //auto host = std::make_unique<blyss::LocalGameHost>();
    //auto frontend = std::make_unique<blyss::LocalGameClient>();
    //blyss::App app(std::move(host), std::move(frontend));
    //app.run();
    uv_loop_t* loop = new uv_loop_t;
    uv_loop_init(loop);
    BOOST_LOG_TRIVIAL(info) << "Now quitting.";
    uv_loop_close(loop);
    delete loop;

    return 0;
}