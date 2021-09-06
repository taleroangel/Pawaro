/**
 * @file Scheduler.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Manage Clock and Schedule events
 * @version 1.0
 * @date 04-09-2021
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

#ifndef _SCHEDULER_HPP_
#define _SCHEDULER_HPP_

// Libraries
#include <RTClib.h>
#include "Common.hpp"

// Macros
#define _RTC_WAIT 5000
#define _MINUTE 60001

/**
 * @class Scheduler
 * @brief Manage Clock and Alarms to schedule events
 */
class Scheduler
{
    // Public typedefs
public:
    /**
     * @enum return_t
     * @brief CLock return values
     */
    enum return_t : uint8_t
    {
        SUCCESS,
        RTC_NOT_FOUND,
        CLK_OUTDATED,
    };

    // Constructors
public:
    Scheduler();
    ~Scheduler();

    // Private attributes
private:
    RTC_DS1307 clock; // Clock module
    DateTime *events; // Hours to trigger events
    int n_events = 0;
    boolean memory_allocated = false; // Memory was allocated flag
    boolean isListening = false;      // Currently listening

    // Public member functions
public:
    /**
     * @brief Start the Clock module
     * 
     * @return return_t Return state
     */
    return_t begin();

    /**
     * @brief Import hours from String in which Alerts will be generated
     * 
     * @param elements Number of hours to import
     * @param hours Hours in which Alerts will be generated
     * @return boolean False if invalid input
     */
    boolean importHours(int elements, String hours[]);

    /**
     * @brief Start listening for alerts
     * Blocks the system until an event happens, the returns the event ID
     * @return int Event ID, -1 if no event triggered the action
     */
    int listen();

    /**
     * @brief Stop the listening
     * (Use with Interrupts)
     */
    void stopListen();

    /**
     * @brief Grab current clock value
     * @param format Format to grab the value (Default: "DD/MM/YYYY - hh:mm:ss")
     * @return String with the value inside the clock
     */
    String grabValue(String format = "DD/MM/YYYY - hh:mm:ss");

    /**
     * @brief Update the clock
     * 
     */
    void updateClock();
};

#endif //_SCHEDULER_HPP_