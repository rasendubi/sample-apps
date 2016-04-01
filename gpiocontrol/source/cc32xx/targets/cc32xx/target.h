/**
 *  Copyright 2014-2016 CyberVision, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

// TODO APP-63: this file will be moved to 'common' dir and likely that it will be reviewed
#ifndef CC32XX_SUPPORT_H_
#define CC32XX_SUPPORT_H_

#include "hw_types.h"
#include "uart_if.h"
#include "common.h"
#include "gpio.h"
#include "gpio_if.h"
#include "pin.h"

#define demo_printf(msg, ...)   UART_PRINT((msg), ##__VA_ARGS__)

/* Initialises a target. Zero value means success, negative - errors.
 *
 * For this particular target this will eventually try to connect to
 * the WiFi spot using SSID and password supplied during build.
 */
int target_initialise(void);

#endif //CC32XX_SUPPORT_H_
