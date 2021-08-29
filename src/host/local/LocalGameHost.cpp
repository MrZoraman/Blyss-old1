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

#include "host/local/LocalGameHost.hpp"

#include <chrono>
#include <cstdint>
#include <thread>

#include <boost/log/trivial.hpp>

#include <uv.h>

namespace blyss
{
    const int kFrequency = 20; // hertz
    const auto kFrameTime = std::chrono::milliseconds(1000 / kFrequency);

    void LocalGameHostTimerCallback(uv_timer_t* handle)
    {
        auto* self = static_cast<LocalGameHost*>(uv_handle_get_data(reinterpret_cast<uv_handle_t*>(handle)));
        self->Frame();
    }

    LocalGameHost::LocalGameHost(uv_loop_t* loop)
        : loop_{loop}
        , timer_handle_{}
        , delta_timer_{"Local Game Host", kFrameTime}
    {
        uv_timer_init(loop, &timer_handle_);
        uv_handle_set_data(reinterpret_cast<uv_handle_t*>(&timer_handle_), this);
        BOOST_LOG_TRIVIAL(debug) << "kFrameTime: " << kFrameTime.count();
        uv_timer_start(&timer_handle_, &LocalGameHostTimerCallback, 0, kFrameTime.count());
    }

    void LocalGameHost::Frame()
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        delta_timer_.Update();

        BOOST_LOG_TRIVIAL(info) << "Delta: " << delta_timer_.DeltaSeconds();
    }

}