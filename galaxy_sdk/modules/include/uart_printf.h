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

#ifndef _UART_PRINTF_H
#define _UART_PRINTF_H
#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup LOGGING
 *  uart printf API and definition.
 *  @ingroup VPI
 *  @{
 */

/*Check your function's parameter a & b by following function f's rule*/
#define CHECK_PARAM_FORMAT(f, a, b) __attribute__((__format__(f, a, b)))

/**
 * @brief Print string to UART
 * @param format C string that contains the text to be written to UART
 * @return On success, total number of characters written is returned
 */
int uart_printf(const char *format, ...) CHECK_PARAM_FORMAT(printf, 1, 2);
int uart_sprintf(char *out, const char *format, ...) CHECK_PARAM_FORMAT(printf, 2, 3);

/**
 * @brief API to init the UART interface for debug
 * @return return 0 for success
 */
int uart_debug_init(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _UART_PRINTF_H */
