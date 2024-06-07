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

#ifndef __OSAL_TIME_H__
#define __OSAL_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "osal_adapter.h"

/** @addtogroup TIME
 *  OSAL Time API and definitions
 *  @ingroup OSAL
 *  @{
 */

/**
 * @brief Get the number of milliseconds since the operating system(or
 * scheduler) started
 *
 * @note Invocation is not recommended when the SysTimer interrupt is masked.
 * For example, after entering the critical section through
 * osal_enter_critical(). This causes the RTOS to stop tick counting, which
 * affects the accuracy of the results returned by the function.
 */
uint64_t osal_get_uptime(void);

/**
 * @brief Get the number of microseconds since the operating system(or
 * scheduler) started
 *
 * @note Invocation is not recommended when the SysTimer interrupt is masked.
 * For example, after entering the critical section through
 * osal_enter_critical(). This causes the RTOS to stop tick counting, which
 * affects the accuracy of the results returned by the function.
 */
uint64_t osal_get_uptime_us(void);

/**
 * @brief Setup the systick timer to generate the tick interrupts at the
 * required frequency
 */
void osal_setup_timer(void);

/**
 * @brief Update the systick timer configurations to ensure accurate timing when
 * the operating system's base clock changes
 */
void osal_update_systick(void);

/**
 * @brief Convert time in milliseconds to ticks
 *
 * @note A fraction less then one tick will be counted as one tick
 * @param duration A period of time in milliseconds
 * @return uint32_t Number of ticks
 */
uint32_t osal_ms_to_tick(uint32_t duration);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OSAL_TIME_H__ */
