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

#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_
#include <stdlib.h>
#include <stdbool.h>
#include "sys_common.h"
#include "hal_gpio.h"
#include "osal_heap_api.h"
/** @addtogroup HAL
 *  Hardware Abstraction Layer
 *  @{
 */

#define DRV_MALLOC osal_malloc_noncache
#define DRV_FREE   osal_free_noncache

/** Define the wait forever timeout macro */
#define HAL_WAIT_FOREVER 0xFFFFFFFFU

/**
 * @brief Callback handler for transfer complete
 * @param param Parameter of callback API
 */
typedef void (*XferCallback)(void *param);

/**
 * @enum DeviceProperty
 * @brief Device property, indicate it's a HW or SW device
 */
enum DeviceProperty {
    DEVICE_PROP_HW, /**< A hardware device */
    DEVICE_PROP_SW, /**< A software device */
};

/**
 * @enum DeviceWorkMode
 * @brief Device work mode, master or slave
 */
enum DeviceWorkMode {
    DEVICE_MASTER_MODE, /**< Device works on master mode */
    DEVICE_SLAVE_MODE,  /**< Device works on slave mode */
};

/**
 * @enum XferModeDef
 * @brief Define common transfer modes
 */
typedef enum XferModeDef {
    XFER_MODE_POLLING = 0, /**< polling mode */
    XFER_MODE_INTR    = 1, /**< interrupt mode */
    XFER_MODE_DMA     = 2, /**< dma mode */
    XFER_MODE_MAX,
    XFER_MODE_DEFAULT = XFER_MODE_MAX
} XferModeDef;

/**
 * @enum XferCapability
 * @brief Define the capability of transfer modes
 */
enum XferCapability {
    XFER_CAP_POLLING = (0x1 << XFER_MODE_POLLING), /**< Capability of polling
                                                      mode */
    XFER_CAP_INTR = (0x1 << XFER_MODE_INTR),       /**< Capability of interrupt mode
                                                    */
    XFER_CAP_DMA = (0x1 << XFER_MODE_DMA),         /**< Capability of DMA mode */
};

/**
 * @enum FifoWidthDef
 * @brief Define common fifo width
 */
typedef enum FifoWidthDef {
    WIDTH_8_BITS_TYPE  = 0, /**< fifo width is 8 bits */
    WIDTH_16_BITS_TYPE = 1, /**< fifo width is 16 bits */
    WIDTH_32_BITS_TYPE = 2, /**< fifo width is 32 bits */
    WIDTH_64_BITS_TYPE = 3, /**< fifo width is 64 bits */
    WIDTH_TYPE_MAX,
    WIDTH_TYPE_DEFAULT = WIDTH_TYPE_MAX
} FifoWidthDef;

/**
 * @enum DmacWidthCapability
 * @brief Define the transfer width capability of DMAC
 */
enum DmacWidthCapability {
    WIDTH_CAP_8_BIT = (0X1 << WIDTH_8_BITS_TYPE),   /**< DMA supports 8bit
                                                       read/write */
    WIDTH_CAP_16_BIT = (0X1 << WIDTH_16_BITS_TYPE), /**< DMA supports 16bit
                                                     * read/write */
    WIDTH_CAP_32_BIT = (0X1 << WIDTH_32_BITS_TYPE), /**< DMA supports 32bit
                                                       read/write */
    WIDTH_CAP_64_BIT = (0X1 << WIDTH_64_BITS_TYPE), /**< DMA supports 64bit
                                                       read/write */
};

typedef struct {
    const GpioPort *power_pin;      /**< gpio of power pin */
    const GpioPort *data_ready_pin; /**< gpio of interrupt pin */
    const GpioPort *reset_pin;      /**< gpio of reset pin  */
    bool rx_data_cont;              /**< Data read continues mode */
} SensorHwConfig;

typedef struct {
    XferCallback callback; /**< callback handler for transfer complete */
    bool is_async;         /**< use asynchronous or synchronous mode */
} XferInfo;

/** @} */

#endif // _HAL_COMMON_H_
