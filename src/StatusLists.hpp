/**
 * @file StatusLists.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Status lists for NotificationManager
 * @version 1.0
 * @date 28-08-2021
 * 
 * @copyright Copyright (c) 2021 Angel Talero. All rights reserved.
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License. 
 */

#ifndef _STATUSLISTS_HPP_
#define _STATUSLISTS_HPP_

#include "NotificationManager.hpp"

namespace STATUS
{
    constexpr time_t SHORT = _DEFAULT_ND;     // Short pulse duration
    constexpr time_t LARGE = _DEFAULT_ND * 2; // Default pulse duration
    constexpr time_t ALERT = _DEFAULT_ND * 3; // Long pulse duration

    // Colors
    enum : NotificationManager::color_t
    {
        // Generic
        FAILURE = 0xFF0000, // Red
        SUCCESS = 0x00FF00, // Green

        // Serial (Purple reserved)
        DEBUG_MODE = 0xCD00FF, // Purple
        SERIAL_FAILURE = 0xCD00FF,

        // Clock
        BEGIN_RTC = 0x0000FF,   // Blue
        CLOCK_SETUP = 0xffdc00, // Yellow
    };
}

#endif //_STATUSLISTS_HPP_