/**
 * @file Schedule.h
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Hours in which the feeder will be activated
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

//! This file should only be included in the Pawaro.ino main file

/* --------------------- INSTRUCTIONS - INSTRUCCIONES --------------------- */
/*

! English (EN):

! Español (ES):

*/

#ifndef _SCHEDULE_HPP_
#define _SCHEDULE_HPP_

/* ------------------------- ELEMENTS - ELEMENTOS ------------------------- */
constexpr int elements = 4;

/* ----------------------------- HOURS - HORAS ----------------------------- */

String schedule[elements] = {
    "23:49:00",
    "23:51:00",
    "23:52:00",
    "23:53:00"};

/* -------------------------- SERVINGS - RACIONES -------------------------- */

uint8_t servings[elements] = {
    1,
    2,
    3,
    1};

/* ----------------------------- TIME - TIEMPO ----------------------------- */
constexpr time_t time = 1000;

#endif //_SCHEDULE_HPP_