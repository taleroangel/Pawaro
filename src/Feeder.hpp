/**
 * @file Feeder.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Feeder(s) servomotor management
 * @version 1.0
 * @date 08-09-2021
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

#ifndef _FEEDER_HPP_
#define _FEEDER_HPP_

#define MAX_ANGLE 180
#define MIN_ANGLE 0

#include <Servo.h>
#include "Common.hpp"

/**
 * @class Feeder
 * @brief Feeder's servomotor manipulation abstraction layer
 */
class Feeder
{
    // Public Typedefs
public:
    using degree_t = uint8_t;
    enum STATUS : uint8_t
    {
        OPENED,
        CLOSED,
        TIMED,
        DISABLED
    };

    // Private attributes
private:
    Servo servoClass;
    pin_t servo_pin;
    degree_t aperture;
    STATUS status;

    // Public member function
public:
    Feeder(pin_t servo_pin, degree_t aperture = MAX_ANGLE);
    ~Feeder();
    void begin();
    STATUS getStatus() const;
    void open();
    void close();
    void timer(time_t timeout);
};

#endif //_FEEDER_HPP_