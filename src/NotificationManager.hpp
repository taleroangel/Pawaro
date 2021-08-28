/**
 * @file NotificationManager.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Send Notifications and show status via an RGB LED
 * @version 1.0
 * @date 27-08-2021
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

#ifndef _NOTIFICATIONMANAGER_HPP_
#define _NOTIFICATIONMANAGER_HPP_

// Macros
#define _STATUS_OFF 0x000000  // OFF VALUE
#define _STATUS_ON 0xFFFFFF   // ON VALUE
#define _RGB_RED 0xFF0000     // Extract RED with AND bitwise operator
#define _RGB_GRN 0x00FF00     // Extract GREEN with AND bitwise operator
#define _RGB_BLE 0x0000FF     // Extract BLUE with AND bitwise operator
#define _RGB_DIV_RED 0x010000 // Extract RED value by dividing
#define _RGB_DIV_GRN 0x000100 // Extract GREEN value by dividing
#define _RGB_DIV_BLE 0x000001 // Extract BLUE value by dividing
#define _BLINK_SEC 1000       // What a millisecond is to Blink

#include "Common.hpp"

class NotificationManager
{

    // Public typedefs
public:
    using color_t = uint32_t; // HEX Color value (0x000000 - 0xFFFFFF)

    enum effect_t : uint8_t // LED effect (Status changes per second)
    {
        ON = 1,        // Keep the LED on (Default)
        BLINK = 3,     // Blink the LED
        FAST_BLINK = 4 // Fast blink the LED
    };

    // Private attributes
private:
    // Pin values for the LED
    struct led_t
    {
        bool anode;
        pin_t R;
        pin_t G;
        pin_t B;
    } led;

    // Status of the LED (starts in 0)
    color_t status = _STATUS_OFF;

    // Constructor
public:
    /**
     * @brief Construct a new Notification Manager object
     * Requires a RGB LED connected to PWM pins, if common anode please set up
     * the last optional flag as true, pinMode is handled automatically
     * 
     * @param R RGB Red pin
     * @param G RGB Green pin
     * @param B RGB Blue pin
     * @param anode Is common anode? (default: Common Cathode)
     */
    NotificationManager(pin_t R, pin_t G, pin_t B, bool anode = false);

    // Private member functions
private:
    /**
     * @brief Set the Color of the LED
     * 
     * @param color RGB hex value
     * @return true Success
     * @return false Failure
     */
    bool setColor(color_t color);

    // Public member functions
public:
    /**
     * @brief Set the Status of the LED
     * Set LED color indefinitely
     * 
     * @param color_t Color of the new status
     * @return color_t Color of the previous status
     */
    color_t setStatus(color_t status);

    /**
     * @brief Get the Status of the LED
     * 
     * @return color_t Color of the status
     */
    color_t getStatus() const;

    /**
     * @brief Stop current status
     * Turn off the LED
     * 
     * @return color_t Previous status
     */
    color_t stopStatus();

    /**
     * @brief 
     * 
     * @param status Color to be sent
     * @param time Time in ms to show the notification (2000 by default)
     * @param type Animation (No animation [ON] by default)
     */
    void sendNotification(color_t status,
                          time_t time = 2000,
                          effect_t effect = ON);
};

#endif //_NOTIFICATIONMANAGER_HPP_