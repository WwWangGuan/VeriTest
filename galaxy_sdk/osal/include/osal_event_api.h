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

#ifndef __OSAL_EVENT_H__
#define __OSAL_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <inttypes.h>
#include "vs_conf.h"
#include "vpi_list.h"
#include "osal_lock_api.h"
#include "osal_adapter.h"

/** @addtogroup EVENT
 *  OSAL Event API and definitions
 *  @ingroup OSAL
 *  @{
 */

typedef struct OsalEvent {
    uint32_t event_id;
    void *data;
} OsalEvent;

/**
 * @struct OsalEventEntry
 * @brief Event item in event system
 */
typedef struct OsalEventEntry {
    struct list_head event_entry; /**< List hook */
    OsalEvent event_data;         /**< Event */
#if CONFIG_DEBUG_EVENT_POOL_EMPTY
    char *owner_name;
#endif
} OsalEventEntry;

/**
 * @brief Create an event queue and and return a handle to it for reference in
 * event system
 *
 * @param length Length of event queue
 * @param item_size Size of each event queue item
 * @return void* Queue handle is for success, NULL is for failure
 */
void *osal_create_event_queue(int length, uint32_t item_size);

/**
 * @brief Delete an event queue
 *
 * @param queue A handle to the queue to be deleted
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_delete_event_queue(void *queue);

/**
 * @brief Send an event to the specific event queue
 *
 * @param queue Event queue handle
 * @param event_id Event ID
 * @param data Event data that needs to be sent
 * @param timeout Timeout time, in milliseconds
 * @return int EVENT_OK is for success, EVENT_ERROR is for failure
 */
int osal_send_event(void *queue, uint32_t event_id, void *data, uint32_t timeout);

/**
 * @brief Send an event to the specific event queue in isr
 *
 * @param queue Event queue handle
 * @param event_id Event ID
 * @param data Event data that needs to be sent
 * @param timeout Timeout time, in milliseconds
 * @return int EVENT_OK is for success, EVENT_ERROR is for failure
 */
int osal_send_event_from_isr(void *queue, uint32_t event_id, void *data, uint32_t timeout);

/**
 * @brief Wait for event data from the specific event queue
 *
 * @param queue Event queue handle
 * @param data Event data that needs to be received
 * @param timeout The maximum amount of time the task should remain in the
 * blocked state to wait for data to become available on the queue, in
 * milliseconds.
 * 1) If timeout is zero, then osal_wait_event will return immediately if the
 * queue is already empty
 * 2) Setting timeout to OSAL_WAIT_FOREVER will cause the
 * task to wait indefinitely (without a timeout)
 * @return int Event ID is for success, EVENT_INVALID is for failure
 */
int osal_wait_event(void *queue, void **data, uint32_t timeout);

/**
 * @brief Get free buffer length of event pool
 *
 * @return uint32_t Free buffer length
 */
uint32_t osal_get_event_pool_length(void);

/**
 * @brief Create a operating system raw event queue and and return a handle to
 * it for reference in event system.
 *
 * @param q_size The maximum number of items that the queue being created can
 * hold at any one time
 * @return void* Queue handle is for success, NULL is for failure
 */
void *osal_create_queue_raw(uint32_t q_size);

/**
 * @brief Delete a operating system raw event queue. Free all the memory
 * allocated for storing of items placed on the queue.
 *
 * @param queue A handle to the queue to be deleted
 * @return int OSAL_TRUE for success, others for failure
 */
int osal_delete_queue_raw(void *queue);

/**
 * @brief Send an event to the specific operating system raw event queue from
 * task
 *
 * @param queue Raw event queue handle
 * @param data A pointer to the data to be copied into the queue. The data size
 * must be 32 bits.
 * @return int EVENT_OK is for success, EVENT_ERROR is for failure
 */
int osal_send_event_raw(void *queue, void *data);

/**
 * @brief Send an event to the specific operating system raw event queue from
 * ISR
 *
 * @note osal_send_event_raw_from_isr is the interrupt safe version of
 * osal_send_event_raw
 * @param queue Raw event queue handle
 * @param data A pointer to the data to be copied into the queue. The data size
 * must be 32 bits.
 * @return int EVENT_OK is for success, EVENT_ERROR is for failure
 */
int osal_send_event_raw_from_isr(void *queue, void *data);

/**
 * @brief Wait for event data from the specific operating system raw event queue
 *
 * @note The task will wait indefinitely until the data is available
 * @param queue Raw event queue handle
 * @param data Event data that needs to be received
 */
void osal_wait_event_raw(void *queue, void **data);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OSAL_EVENT_H__ */
