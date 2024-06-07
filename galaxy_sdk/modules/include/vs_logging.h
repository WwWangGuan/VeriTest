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

#ifndef __VS_LOGGING_H__
#define __VS_LOGGING_H__

/** @addtogroup LOGGING
 *  logging API and definition.
 *  @ingroup VPI
 *  @{
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "vs_conf.h"
#include "uart_printf.h"

#define LOG_LVL_NONE     0
#define LOG_LVL_ERROR    1
#define LOG_LVL_CRITICAL 2
#define LOG_LVL_WARNING  3
#define LOG_LVL_INFO     4
#define LOG_LVL_DEBUG    5

extern int vs_logging_level;

#define vs_logging_inner(level, args...)   \
    do {                                   \
        if ((level) <= vs_logging_level) { \
            uart_printf(args);             \
        }                                  \
    } while (0)

#define logging_none(level, args...)

#define vs_log_LOG_LVL_DEBUG    logging_none
#define vs_log_LOG_LVL_INFO     logging_none
#define vs_log_LOG_LVL_WARNING  logging_none
#define vs_log_LOG_LVL_CRITICAL logging_none
#define vs_log_LOG_LVL_ERROR    logging_none
#define vs_log_LOG_LVL_NONE     logging_none

#define VS_LOG_LEVEL CONFIG_LOG_LEVEL

#if (VS_LOG_LEVEL >= LOG_LVL_ERROR)
#undef vs_log_LOG_LVL_ERROR
#define vs_log_LOG_LVL_ERROR vs_logging_inner
#endif

#if (VS_LOG_LEVEL >= LOG_LVL_CRITICAL)
#undef vs_log_LOG_LVL_CRITICAL
#define vs_log_LOG_LVL_CRITICAL vs_logging_inner
#endif

#if (VS_LOG_LEVEL >= LOG_LVL_WARNING)
#undef vs_log_LOG_LVL_WARNING
#define vs_log_LOG_LVL_WARNING vs_logging_inner
#endif

#if (VS_LOG_LEVEL >= LOG_LVL_INFO)
#undef vs_log_LOG_LVL_INFO
#define vs_log_LOG_LVL_INFO vs_logging_inner
#endif

#if (VS_LOG_LEVEL >= LOG_LVL_DEBUG)
#undef vs_log_LOG_LVL_DEBUG
#define vs_log_LOG_LVL_DEBUG vs_logging_inner
#endif

#define vs_logging(level, args...) vs_log_##level(level, args)

/**
 * @brief Set logging level
 * @param log_level log level
 */
void set_logging_level(int log_level);

/**
 * @brief print to memory
 * @param args log string
 */
void mem_printf(char *args, ...);

/**
 * @brief get print memory pointer
 * @return  memory pointer: on success,  NULL : error
 */
char *get_log_buffer(void);

/** @} */

#endif
