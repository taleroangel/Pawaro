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

/* ------------------------------- Libraries ------------------------------- */

// Essential
#include <Arduino.h>
#include "Common.hpp" // Common definitions between modules

// NotificationManager
#include "NotificationManager.hpp" // LED Notifications
#include "StatusLists.hpp"         // Notifications color list

// Scheduler
#include "Scheduler.hpp" // Event handler and Clock
#include "Schedule.h"    // Events

/* --------------------------------- Pines --------------------------------- */
// All pins
#define LOWEST 2
#define HIGHEST 13

// NotificationManager
#define RGB_R 5
#define RGB_G 6
#define RGB_B 9
#define RGB_ANODE true

// Feeder
#define FEEDER_BUTTON 2
#define _DEBOUNCING 200

/* ---------------------------- DEBUG VARIABLES ---------------------------- */
// Uncomment this line to enable Serial debugging
#define _PAWARO_DEBUG

// Debug settings
#ifdef _PAWARO_DEBUG
#define _SERIAL_BAUD 9600
#define _SERIAL_TIMEOUT 10000
#endif

/* ---------------------------- Global variables --------------------------- */
// Modules
NotificationManager notifier(RGB_R, RGB_G, RGB_B, RGB_ANODE);
Scheduler scheduler;

/* ----------------------------- Declarations ----------------------------- */
/**
 * @brief Event to be triggered by an Scheduler alarm
 * Put here the function to be triggered
 * SHOULD BE INTERRUPT FRIENDLY
 * @param alert_number Parameter passed by the Scheduler Alarm
 */
void EventInterface(int alert_number);

/**
 * @brief Enter in a HALT state
 * Stop all execution of the program
 */
void EnterHalt();

/**
 * @brief Hardware interrupt ISR
 * (PIN 2 is attached to this interrupt)
 * By default, the EventInterface will be called with the 'alert_number'
 * parameter set to 1
 */
void HardwareISR();

/* --------------------------------- Setup --------------------------------- */
void setup()
{
    // * Pin initialization
    pinMode(FEEDER_BUTTON, INPUT);

    // * Serial Initialization

#ifdef _PAWARO_DEBUG

    // Begin Serial communication
    Serial.begin(_SERIAL_BAUD);

    // Show a debug alert
    Serial.println(
        "ALERT: DEBUG mode is enabled!, \
don't leave it enabled for the final product!");

    // Wait for Serial to open
    while (!Serial)
        if (millis() > _SERIAL_TIMEOUT)
        {
            // Serial timedout
            notifier.sendNotification(
                STATUS::DEBUG,
                LENGTH::LONG_ALERT,
                EFFECT::FAST_BLINK);

            // Notify Serial does not work
            notifier.setStatus(STATUS::INVALID_CONF);
            break;
        }

    if (Serial)
    {
        // Serial successfully opened
        notifier.setStatus(STATUS::DEBUG);
        Serial.println("System: Serial connection successful");
    }

#endif

    // * Clock initialization

    // Clock initialization alert and delay
    notifier.sendNotification(
        STATUS::CLOCK,
        (time_t)_RTC_WAIT,
        EFFECT::BLINK);

    switch (scheduler.begin())
    {
    case Scheduler::RTC_NOT_FOUND: // RTC module is missing
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: RTC module not found (DS1307)");
#endif
        // CANNOT CONTINUE WITHOUT CLOCK
        EnterHalt(); // ! HALT STATE
        break;

    case Scheduler::CLK_OUTDATED:
        // LED will be Yellow alerting the user that the clock might have wrong
        // values, proper Clock update must be done with a computer. (This alert
        // will only be shown once)
        notifier.setStatus(STATUS::INVALID_CONF);
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: Clock is not up to date!");
        Serial.println("Clock: Setting up System time and date");
#endif
        break;

    case Scheduler::SUCCESS:
#ifdef _PAWARO_DEBUG
        Serial.println("Clock: Clock was successfully enabled");
#endif
        break;
    }

    // * Read Schedule Values

    if (!scheduler.importHours(elements, schedule))
    {
        // Wait a little bit before halting
        notifier.sendNotification(
            STATUS::SCHEDULER,
            LENGTH::ALERT,
            EFFECT::FAST_BLINK);

        notifier.sendNotification(
            STATUS::INVALID_CONF,
            LENGTH::LONG_ALERT);

#ifdef _PAWARO_DEBUG
        Serial.println("Sheduler: Schedule file is invalid!");
#endif
        EnterHalt(); // ! HALT STATE
    }

#ifdef _PAWARO_DEBUG
    else
    {
        Serial.println("Sheduler: Schedule file was read successfully");
        // Show current Clock time
        Serial.print("Clock: Current time is ");
        Serial.println(scheduler.grabValue());
    }
#endif

    // * Finish initialization

    // Notify about success
    notifier.sendNotification(STATUS::SUCCESS, LENGTH::SHORT, EFFECT::BLINK);
#ifndef _PAWARO_DEBUG
    notifier.stopStatus(); // Stop any previous status
#endif

    // * Enable interrupts (Leave last)
    attachInterrupt(
        digitalPinToInterrupt(FEEDER_BUTTON),
        HardwareISR,
        RISING);
}

/* --------------------------------- Loop --------------------------------- */
void loop()
{
    // Listen for an event to happen,
    // when the listener frees the system EventInterface picks the return value
    EventInterface(scheduler.listen());
}

/* ------------------------------ Definitions ------------------------------ */
void EventInterface(int alert_number)
{
    if (alert_number < 0)
        alert_number = 1;

    // Send an event notification
    notifier.sendNotification(STATUS::BUSY, EFFECT::FAST_BLINK);

#ifdef _PAWARO_DEBUG
    Serial.println("Scheduler: An event is being triggered by an Alarm!");
    Serial.print("Clock: Alert was triggered at ");
    Serial.println(scheduler.grabValue());
#endif
    // Put here the function to be triggered by the event
    //! ... event ... !//
}

void EnterHalt()
{
    // Send a HALT notification
    notifier.sendNotification(STATUS::HALT, LENGTH::ALERT, EFFECT::FAST_BLINK);
    notifier.setStatus(STATUS::HALT);

#ifdef _PAWARO_DEBUG
    Serial.println(
        "System: System experienced an unrecoverable error state (HALT)");
#endif

    // Disable all interrupts
    noInterrupts();

    // Destroy dynamic objects
    scheduler.~Scheduler();

    // Halt the system
    while (true)
        ;
}

void HardwareISR()
{
    static time_t lastInterrupt = 0;
    time_t interrupt_time = millis();

    // Error checking
    if (lastInterrupt > interrupt_time)
        lastInterrupt = interrupt_time;

    if (interrupt_time - lastInterrupt > _DEBOUNCING)
    {
        scheduler.stopListen(); // Disable the main loop
    }

    lastInterrupt = interrupt_time;
}