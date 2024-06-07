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
#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "device.h"

/** @addtogroup BOARD
 *  - Board API and definition
 *  @ingroup BSP
 *  @{
 */

/**
 * @brief Structure of board handler
 */
typedef struct BoardDevice {
    const char *name;  /**< name of board */
    uint32_t reserved; /**< reserved */
    void *priv;        /**< priv data */
} BoardDevice;

/**
 * @brief Structure of operations for board
 */
typedef struct BoardOperations {
    int (*init)(BoardDevice *board);
    void *(*find_device)(uint8_t device_id);
    void (*get_wakeup_src)(uint8_t port, uint8_t *wakeup_src);
} BoardOperations;

/**
 * @brief Get board ops
 * @return Return result
 * @retval Board ops
 */
const BoardOperations *board_get_ops(void);

/**
 * @brief Register the board
 * @param ops operations for board
 * @note This api must be called before all of board api
 * @return Return result
 * @retval 0 for succeed, others for failure
 */
int board_register(const BoardOperations *ops);

/**
 * @brief Init the board
 * @param board_cfg configuration of board
 * @return Return result
 * @retval 0 for succeed, others for failure
 */
int board_init(void *board_cfg);

/**
 * @brief Get device from board
 * @param device_id id of device
 * @return Return result
 * @retval Pointor to device which was found, NULL for no device
 */
void *board_find_device_by_id(uint8_t device_id);

/**
 * @brief Get wakeup source from board
 * @param port GPIO port id of power key
 * @param wakeup_src Wake up source from deepsleep mode
 */
void get_wakeup_src(uint8_t port, uint8_t *wakeup_src);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
