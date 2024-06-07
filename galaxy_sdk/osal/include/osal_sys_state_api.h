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

#ifndef __OSAL_SYS_STATE_H__
#define __OSAL_SYS_STATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "vs_conf.h"
#include "osal_adapter.h"

/** @addtogroup STATE
 *  OSAL System State API and definitions
 *  @ingroup OSAL
 *  @{
 */

/* Macros used to indicate state of task */
#define TASK_RUNNING_CHAR   ('X')
#define TASK_BLOCKED_CHAR   ('B')
#define TASK_READY_CHAR     ('R')
#define TASK_DELETED_CHAR   ('D')
#define TASK_SUSPENDED_CHAR ('S')
/* Macros used to indicate indicate whether the task is alive */
#define TASK_ALIVE_CHAR ('Y')
#define TASK_DEAD_CHAR  ('N')

#define EACH_TASK_INFO_SIZE 64

/**
 * @brief Dump current status of all tasks
 */
void osal_dump_os_state(void);

/**
 * @brief Dump current status of system heap
 */
void osal_dump_heap_size(void);

/**
 * @brief Get the total amount of heap space that remains unallocated
 *
 * @return uint32_t Size of the free heap
 */
uint32_t osal_get_free_heap(void);

/**
 * @brief Get current task name
 *
 * @return task name
 */
char *osal_get_task_name(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OSAL_SYS_STATE_H__ */
