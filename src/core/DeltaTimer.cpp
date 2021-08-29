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

#include <stdexcept>
#include <string>

#include <boost/log/trivial.hpp>

namespace blyss
{
    const auto kTolerance = std::chrono::milliseconds(30);
    const auto kWarningMinInterval = std::chrono::seconds(5);

    DeltaTimer::DeltaTimer(std::string timer_name, std::chrono::milliseconds target_frame_time)
        : delta_{}
        , previous_time_{std::chrono::high_resolution_clock::now()}
        , last_warn_sent_{std::chrono::high_resolution_clock::now()}
        , target_frame_time_{target_frame_time}
        , timer_name_{std::move(timer_name)}
    {
    }

    void DeltaTimer::Update()
    {
        // Calculate delta, the amount of time that has passed since the last call to Update()
        auto now = std::chrono::high_resolution_clock::now();
        delta_ = now - previous_time_;
        previous_time_ = now;

        // Calculate how much time has elapsed since a warning message was sent
        auto warn_message_diff = now - last_warn_sent_;

        // Calculate the difference between our target frame time and actual frame time
        auto slowdown = delta_ - target_frame_time_;

        if (slowdown > kTolerance && warn_message_diff > kWarningMinInterval)
        {
            // The slowdown is longer than the tolerated amount, and a warning message hasn't been
            // sent in at least kWarningMinInterval seconds...
            auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(slowdown);
            BOOST_LOG_TRIVIAL(warning) << "Timer " << timer_name_ << " is running behind schedule by " << seconds.count() << " seconds!";

            // Update time our warning message was sent so it doesn't get spammed in the logs
            last_warn_sent_ = now;
        }
    }

    double DeltaTimer::DeltaSeconds() const
    {
        auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(delta_);
        return seconds.count();
    }

}