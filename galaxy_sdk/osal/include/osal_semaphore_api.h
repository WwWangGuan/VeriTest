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

#ifndef __OSAL_SEMAPHORE_H__
#define __OSAL_SEMAPHORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "vs_conf.h"
#include "osal_adapter.h"

/** @addtogroup SEMAPHORE
 *  OSAL Semaphore API and definitions
 *  @ingroup OSAL
 *  @{
 */

/**
 * @brief Create a binary semaphore
 *
 * @param sem The semaphore to be created
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_create_sem(OsalSemaphore *sem);

/**
 * @brief Delete a binary semaphore
 *
 * @note Do not delete a semaphore that has tasks blocked on it (tasks that are
 * in the blocked state waiting for the semaphore to become available)
 * @param sem The semaphore being deleted
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_delete_sem(OsalSemaphore *sem);

/**
 * @brief Wait for or take a semaphore
 *
 * @note The semaphore can be taken only if it is available. This function must
 * not be used from an interrupt service routine.
 * @param sem The semaphore being taking
 * @param timeout The maximum amount of time the task should remain in the
 * blocked state to wait for the semaphore if it is not already available, in
 * millisecond
 * 1) If timeout is zero, then osal_sem_wait will return immediately if the
 * semaphore is not available.
 * 2) Setting timeout to OSAL_WAIT_FOREVER will cause the task to wait
 * indefinitely (without a timeout)
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_sem_wait(OsalSemaphore *sem, uint32_t timeout);

/**
 * @brief Post or give a semaphore
 *
 * @param sem The semaphore being given
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_sem_post(OsalSemaphore *sem);

/**
 * @brief Post or give a semaphore from ISR
 *
 * @note osal_sem_post_isr is the interrupt safe version of osal_sem_post
 * @param sem The semaphore being given
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_sem_post_isr(OsalSemaphore *sem);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OSAL_SEMAPHORE_H__ */
