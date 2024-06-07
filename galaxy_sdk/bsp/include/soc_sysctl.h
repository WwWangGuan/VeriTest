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

#ifndef __SOC_SYSCTL_H__
#define __SOC_SYSCTL_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SOC
 *  @brief SoC System Ctrl APIs
 *  @ingroup BSP
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"

/**
 * @brief SOC software reset
 */
void soc_sw_reset(void);

/**
 * @brief Software reset SOC by wdt
 */
void soc_sw_reset_wdt(void);

/**
 * @brief Software stop ZSP
 * @return VSD_SUCCESS on success, others on error
 */
int soc_sw_stop_zsp(void);

/**
 * @brief Software load ZSP
 * @return VSD_SUCCESS on success, others on error
 */
int soc_sw_load_zsp(void);

/**
 * @brief Software start ZSP
 * @return VSD_SUCCESS on success, others on error
 */
int soc_sw_start_zsp(void);

/**
 * @brief Get zsp boot status
 * @return The status of zsp boot
 */
int soc_get_zsp_boot_status(void);

/**
 * @brief Get CPU clock frequency
 * @return The clock frequency of CPU
 */
uint32_t soc_cpu_clock_get_freq(void);

/**
 * @brief Get RTC clock frequency
 * @return The clock frequency of RTC
 */
uint32_t soc_rtc_clock_get_freq(void);

/**
 * @brief Prepare for boot environment
 */
void soc_prepare_boot(void);

/**
 * @brief Check whether platform is processing IRQ
 * @return True for IRQ, false otherwise.
 */
bool soc_platform_in_isr(void);

/**
 * @brief reinit xip divisor
 */
void soc_qspi_set_divisor(uint32_t divisor);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __SOC_SYSCTL_H__ */
