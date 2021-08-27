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

#include "core/DeltaTimer.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

#include <boost/log/trivial.hpp>

#include <uv.h>

namespace blyss
{
    const double kToleranceSeconds = 0.03;
    const std::int32_t kWarningMinIntervalMs = 5000; // 5 seconds

    void DeltaTimerCallback(uv_timer_t* handle)
    {
        auto* timer = static_cast<DeltaTimer*>(uv_handle_get_data(reinterpret_cast<uv_handle_t*>(handle)));
        timer->ResetWarningMessage();
    }

    DeltaTimer::DeltaTimer(std::string timer_name, std::int32_t target_framerate)
        : delta_{}
        , previous_time_{std::chrono::high_resolution_clock::now()}
        , target_seconds_per_tick_{0}
        , is_behind_schedule_{false}
        , loop_{nullptr}
        , timer_name_{std::move(timer_name)}
        , timer_handle_{}
    {
        if (target_framerate <= 0)
        {
            throw std::invalid_argument("Target framerate must be greater than 0!");
        }

        target_seconds_per_tick_ = 1.0 / target_framerate;
    }

    void DeltaTimer::Start(uv_loop_t* loop)
    {
        loop_ = loop;
        uv_timer_init(loop_, &timer_handle_);
        uv_handle_set_data(reinterpret_cast<uv_handle_t*>(&timer_handle_), this);
    }

    void DeltaTimer::Update()
    {
        auto now = std::chrono::high_resolution_clock::now();
        delta_ = now - previous_time_;
        previous_time_ = now;

        CheckDelta();
    }

    std::chrono::duration<double> DeltaTimer::GetDelta() const
    {
        return delta_;
    }

    void DeltaTimer::CheckDelta()
    {
        if (!loop_)
        {
            BOOST_LOG_TRIVIAL(error) << "Delta timer hasn't been started yet!";
            return;
        }

        if (is_behind_schedule_)
        {
            return;
        }

        if (uv_is_active(reinterpret_cast<uv_handle_t*>(&timer_handle_)))
        {
            BOOST_LOG_TRIVIAL(warning) << "Delta timer handle is still active!";
            return;
        }

        double slowdown_seconds = delta_.count() - target_seconds_per_tick_;

        if (slowdown_seconds > kToleranceSeconds)
        {
            is_behind_schedule_ = true;
            BOOST_LOG_TRIVIAL(warning) << "Timer " << timer_name_ << " is running behind schedule by " << slowdown_seconds << " seconds!";
            uv_timer_start(&timer_handle_, &DeltaTimerCallback, kWarningMinIntervalMs, 0);
        }
    }

    void DeltaTimer::ResetWarningMessage()
    {
        is_behind_schedule_ = false;
    }

}