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

#include "Logging.hpp"

#include <cstdio>
#include <exception>
#include <string>

#include <boost/log/trivial.hpp>

namespace blyss
{
    void LogErrorNoExcept(const std::string& message) noexcept
    {
        try
        {
            BOOST_LOG_TRIVIAL(error) << message;
        }
        catch (const std::exception& e)
        {
            printf("Unable to print error message: %s\n", e.what());
            printf("Original error message: %s\n", message.c_str());
        }
        catch (...)
        {
            printf("Unknown error while printing error message.\n");
            printf("Original error message: %s\n", message.c_str());
        }
    }

}