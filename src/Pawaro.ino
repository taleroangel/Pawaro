/**
 * @file Pawaro.ino
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 *         @taleroangel on GitHub
 * @brief Pet automatic Feeder using Arduino (Circuit described above)
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

/* Circuit ->
* Using an Arduino Pro Mini (ATmega328P, 5V 16MHz)
| Arduino 	| Module                       	|
|---------	|------------------------------	|
| VCC0    	| Source 5V                    	|
| VCC1    	| Servo(VCC), RTC(VCC), Button 	|
| GND     	| Ground                       	|
| 2       	| 10K resistor to ground       	|
| 3~      	| RGB Red                      	|
| 5~      	| RGB Green                    	|
| 6~      	| RGB Blue                     	|
| 9~      	| Servo(SIG)                   	|
| RST     	| Button to ground             	|
*/

/* ------------------------------- Libraries ------------------------------- */
#include <Arduino.h>
#include <RTClib.h>

#include "Common.hpp"              // Common definitions between modules
#include "Configuration.hpp"       // Has to go first (Macros for configurations)
#include "NotificationManager.hpp" // LED Notifications
#include "StatusLists.hpp"         // Notifications color list

/* --------------------------------- Pines --------------------------------- */
#define RGB_R 3
#define RGB_G 5
#define RGB_B 6
#define RGB_ANODE true

/* ---------------------------- Global variables --------------------------- */
// Notification module
NotificationManager notifier(RGB_R, RGB_G, RGB_B, RGB_ANODE);
RTC_DS1307 clock;

/* --------------------------------- Setup --------------------------------- */
void setup()
{
#ifdef _PAWARO_DEBUG

    //! Serial Initialization

    Serial.begin(_SERIAL_BAUD);

    // Wait for Serial to open
    while (!Serial)
        if (millis() > _SERIAL_TIMEOUT)
        {
            // Serial timedout
            notifier.sendNotification(
                STATUS::SERIAL_FAILURE,
                STATUS::ALERT,
                NotificationManager::FAST_BLINK);
            break;
        }

    if (Serial)
    {
        // Serial successfully opened
        notifier.sendNotification(
            STATUS::DEBUG_MODE,
            STATUS::SHORT,
            NotificationManager::FAST_BLINK);
        notifier.setStatus(STATUS::DEBUG_MODE);
        Serial.println("DEBUG: Serial connection successful");
    }
#endif

    //! Clock Initialization

    // RTC Module initialization and wait for RTC
    notifier.sendNotification(STATUS::BEGIN_RTC, (time_t)_PAWARO_WAIT_RTC,
                              NotificationManager::FAST_BLINK);

    if (!clock.begin()) // Clock was not connected
    {
        notifier.setStatus(STATUS::FAILURE);
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: RTC module not found (DS1307)");
#endif
        while (true) // STOP EXECUTION (Can't continue without Clock)
            ;
    }

    //! Clock adjust

    if (!clock.isrunning()) // Clock is outdated
    {
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: Clock is not up to date!");
        Serial.println("Clock: Setting up System time and date");
#endif
        // Clock adjust up to date
        clock.adjust(DateTime(F(__DATE__), F(__TIME__)));

        // Send clock adjust notification
        notifier.sendNotification(STATUS::CLOCK_SETUP, STATUS::LARGE,
                                  NotificationManager::FAST_BLINK);

        // LED will be Yellow alerting the user that the clock might have wrong
        // values, proper Clock update must be done with a computer. (This alert
        // will only be shown once)
        notifier.setStatus(STATUS::CLOCK_SETUP);

#ifdef _PAWARO_DEBUG
        Serial.println("Clock: Clock updated!");
#endif
    }
    else // Clock is successfully working
    {
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: Clock is up to date and running");
#endif

        // * All basic Initialization successfully completed
        notifier.sendNotification(STATUS::SUCCESS);
    }
}

/* --------------------------------- Loop --------------------------------- */
void loop() {}