/**
 * @file Configuration.hpp
 * @author Ángel David Talero Peñuela (angelgotalero@outlook.com)
 * @brief Configuration and Debug flags
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

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

// Settings imported flag
#define _PAWARO_CONFIG_LOADED

/* ---------------------------- TIME VARIABLES ----------------------------- */
#define _PAWARO_WAIT_RTC 3000           // Wait for the RTC module to be ready

/* ---------------------------- DEBUG VARIABLES ---------------------------- */
// Uncomment this line to enable Serial debugging
#define _PAWARO_DEBUG

// Debug settings
#ifdef _PAWARO_DEBUG
#define _SERIAL_BAUD 9600
#define _SERIAL_TIMEOUT 10000
#endif

#endif //_CONFIGURATION_HPP_