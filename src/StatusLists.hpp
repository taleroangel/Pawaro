/**
 * @file StatusLists.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Custom status lists for NotificationManager
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
    // Colors
    enum : NotificationManager::color_t
    {
        // Generic
        SUCCESS = 0x00FF00,      // Green
        HALT = 0xFF0000,         // Red
        BUSY = 0xFFFFFF,         // White
        INVALID_CONF = 0xffff00, // Yellow

        // Yellow usually indicates you need to connect the system
        // to a computer and re-upload the sketch

        // Modules
        DEBUG = 0x7400ff,     // DEBUG and Serial (Purple)
        CLOCK = 0x0083ff,     // Clock (Cyan)
        SCHEDULER = 0x00ffee, // Scheduler (Blue)
    };
}

namespace LENGTH
{
    constexpr time_t SHORT = _DEFAULT_ND;           // Short pulse duration
    constexpr time_t LARGE = _DEFAULT_ND * 2;       // Default pulse duration
    constexpr time_t ALERT = _DEFAULT_ND * 5;       // Long pulse duration
    constexpr time_t LONG_ALERT = _DEFAULT_ND * 10; // Long pulse duration
}

#endif //_STATUSLISTS_HPP_