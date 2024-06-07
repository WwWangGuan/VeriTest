/*
 * Copyright (c) 2024, VeriSilicon Holdings Co., Ltd. All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hal_gpio.h"

/** @addtogroup DEVICE
 *  - Device definition
 *  @ingroup BOARD
 *  @{
 */

/**
 * @brief Device ID definitions for board
 */
typedef enum DeviceID {
    PWR_KEY_DEV_ID = 0, /**< Power key */
    CAMERA_SENSOR_ID,   /**< CAMERA sensor */
    LED_PWM_DEV_ID,     /**< PWM for LED */
    LED_GPIO_DEV0_ID,   /**< GPIO for LED0 */
    LED_GPIO_DEV1_ID,   /**< GPIO for LED1 */
    FUN_KEY_DEV0_ID,    /**< GPIO for KEY0 to trigger function */
    FUN_KEY_DEV1_ID,    /**< GPIO for KEY1 to trigger function */
    MAX_DEVICE_ID,
} DeviceID;

/** @} */

#ifdef __cplusplus
}
#endif
#endif // _DEVICE_H_
