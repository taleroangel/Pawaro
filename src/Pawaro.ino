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

#include "Configuration.hpp"
#include "NotificationManager.hpp"

/* ---------------------------- Global variables --------------------------- */
NotificationManager notifier(3, 5, 6, true);

/* --------------------------------- Setup --------------------------------- */
void setup()
{
// Enable Serial for debugging
#ifdef _PAWARO_DEBUG
    Serial.begin(_SERIAL_BAUD);

    // Wait for Serial to open
    while (!Serial)
        if (millis() > _SERIAL_TIMEOUT)
        {
            //Send notification FAILURE
            break;
        }

    if (Serial)
    {
        // Send status DEBUG
        Serial.println("DEBUG: Serial connection successfull");
    }

#endif
}

/* --------------------------------- Loop --------------------------------- */
void loop()
{
    // Select random color
    NotificationManager::color_t color = (NotificationManager::color_t)random(0, 0xFFFFFF);
    Serial.print("Current value must be: ");
    Serial.print(color, HEX);
    Serial.println("");

    // Show color
    Serial.print("Printing value!");
    Serial.println(millis(), DEC);
    notifier.setStatus(color);

    // Sleeping
    delay(5000);

    Serial.println("Sending notification...");
    notifier.sendNotification(0xFF0000, 5000, NotificationManager::BLINK);
    notifier.sendNotification(0xFF00FF, 5000, NotificationManager::FAST_BLINK);
    // Turn LED down
    Serial.println("Good night!");
    notifier.setStatus(_STATUS_OFF);
    delay(10000);
}