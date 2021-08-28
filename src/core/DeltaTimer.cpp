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

    void DeltaTimer::TimerCallback(uv_timer_t*)
    {
        // Nothing happens here, tests are simply done to see if the timer is active or not.
    }

    DeltaTimer::DeltaTimer(uv_loop_t* loop, std::string timer_name, std::int32_t target_framerate)
        : delta_{}
        , previous_time_{std::chrono::high_resolution_clock::now()}
        , target_seconds_per_tick_{0} // Calculated after checks to prevent divide by 0 error.
        , loop_{loop}
        , timer_name_{std::move(timer_name)}
        , timer_handle_{}
    {
        if (target_framerate <= 0)
        {
            throw std::invalid_argument("Target framerate must be greater than 0!");
        }

        if (loop == nullptr)
        {
            throw std::invalid_argument("Loop cannot be null!");
        }

        target_seconds_per_tick_ = 1.0 / target_framerate;

        uv_timer_init(loop_, &timer_handle_);
        uv_handle_set_data(reinterpret_cast<uv_handle_t*>(&timer_handle_), this);
    }

    DeltaTimer::~DeltaTimer()
    {
        uv_timer_stop(&timer_handle_);
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
        if (uv_is_active(reinterpret_cast<uv_handle_t*>(&timer_handle_)))
        {
            return;
        }

        double slowdown_seconds = delta_.count() - target_seconds_per_tick_;

        if (slowdown_seconds > kToleranceSeconds)
        {
            BOOST_LOG_TRIVIAL(warning) << "Timer " << timer_name_ << " is running behind schedule by " << slowdown_seconds << " seconds!";
            uv_timer_start(&timer_handle_, &DeltaTimer::TimerCallback, kWarningMinIntervalMs, 0);
        }
    }

}