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

#ifndef _HAL_PDM_H
#define _HAL_PDM_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup PDM
 * PDM HAL API and definition
 * @ingroup HAL
 * Hardware Abstraction Layer
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>
#include "hal_common.h"

/**
 * @brief Max PDM instance
 */
#define PDM_PORT_MAX (1)

/**
 * @enum PdmIdDef
 * @brief ID definition of PDM interface
 */
typedef enum PdmIdDef {
    PDM_ID_0 = 0,
    PDM_ID_MAX,
} PdmIdDef;

/**
 * @struct PdmBuffer
 * @brief Buffer definition of PDM interface
 */
typedef struct PdmBuffer {
    void *base;    /**< buffer base address */
    int size;      /**< buffer total size in bytes, it should be set to whole multiple of
                      sample_width * chan_num / 8 (in PdmSubstream) bytes */
    int pos;       /**< buffer read position, 0 default */
    int available; /**< available data size in bytes, only valid in interrupt
                  mode*/
} PdmBuffer;

/**
 * @struct PdmFifo
 * @brief FIFO definition of PDM interface
 */
typedef struct _PdmFifo {
    uint32_t offset;     /**< Fifo register */
    uint16_t handshake;  /**< Hardware handshake id */
    uint8_t depth;       /**< Fifo word width of PDM device */
    uint8_t width;       /**< Fifo depth of PDM device in word */
    uint8_t trigger_lvl; /**< Fifo trigger level*/
} PdmFifo;

/**
 * @struct PDMHWConfig
 * @brief Structure of PDM hardware configuration
 */
typedef struct _PDMHWConfig {
    uint32_t base;           /**< Base address of PDM device */
    uint16_t sclk_id;        /**< SCLK ID of this PDM device */
    uint16_t irq_id;         /**< IRQ ID of this PDM device */
    uint8_t id;              /**< Device ID of this PDM device, @see PdmIdDef */
    uint8_t xfer_capability; /**< PDM capability, @see XferCapability */

    PdmFifo rx_fifo; /**< OUT: rx fifo configuration */
} PDMHWConfig;

/**
 * @struct PdmDevice
 * @brief Define PDM controller driver
 */
typedef struct _PdmDevice {
    const PDMHWConfig *hw_config; /**< PDM hardware configuration */
    const void *ops;              /**< PDM operations */
    void *private_data;           /**< private data*/
} PdmDevice;

/**
 * @brief PDM interrupt callback function
 * @param pdm PDM device instance
 * @param size the size of data received in bytes
 * @param cb_ctx callback context
 */
typedef void (*pdm_irq_callback)(const PdmDevice *pdm, int size, void *cb_ctx);

/**
 * @struct PdmSubstream
 * @brief PDM device stream configuration
 */
typedef struct _PdmSubstream {
    uint32_t sample_rate; /**< sample rate */
    pdm_irq_callback cb;  /**< PDM irq callback */
    void *cb_context;     /**< Callback context */
    PdmBuffer buffer;     /**< PDM data buffer */
    uint8_t sample_width; /**< sample width, unit: bit, such as 8 16 24 32 */
    uint8_t chan_num;     /**< pdm channel number */
    uint8_t xfer_mode;    /**< transfer mode, @see XferModeDef */
} PdmSubstream;

/**
 * @struct PdmOperation
 * @brief Structure of operations for HAL of PDM
 */
typedef struct _PdmOperation {
    /**
     * PDM operation for init
     */
    int (*init)(const PdmDevice *pdm);

    /**
     * PDM operation to start PDM device
     */
    int (*start)(const PdmDevice *pdm, PdmSubstream *stream);

    /**
     * PDM operation to stop PDM device
     */
    void (*stop)(const PdmDevice *pdm, PdmSubstream *stream);

    /**
     * PDM operation to set gain
     */
    void (*set_gain)(const PdmDevice *pdm, int gain);

    /**
     * PDM operation for deinit
     */
    void (*deinit)(const PdmDevice *pdm);

    /**
     * PDM operation for interrupt handler.
     */
    void (*irq_handler)(const PdmDevice *pdm);
} PdmOperation;

/**
 * @brief Add PDM device instance
 * @param[in] pdm PDM device to be added
 * @return int @see VSD_SUCCESS for success, otherwise for error
 */
int hal_pdm_add_dev(PdmDevice *pdm);

/**
 * @brief Remove PDM device instance
 * @param[in] pdm PDM device to be removed
 * @return int @see VSD_SUCCESS for success, otherwise for error
 */
int hal_pdm_remove_dev(PdmDevice *pdm);

/**
 * @brief Get PDM device instance
 * @param dev_id The device ID of PDM, @see PdmIdDef
 * @return PdmDevice* PDM instance
 */
PdmDevice *hal_pdm_get_device(uint8_t dev_id);

/**
 * @brief Initialises the PDM interface
 * @param[in] pdm the device of PDM port which will be initialized
 * @return int @see VSD_SUCCESS for success, otherwise for error
 */
int hal_pdm_init(const PdmDevice *pdm);

/**
 * @brief Start the PDM device.
 * @param[in] pdm PDM device
 * @param[in] stream PDM device stream configuration
 * @return int @see VSD_SUCCESS for success, otherwise for error
 */
int hal_pdm_start(const PdmDevice *pdm, PdmSubstream *stream);

/**
 * @brief Stop the PDM device
 * @param[in] pdm PDM device
 * @param[in] stream PDM device stream configuration
 */
void hal_pdm_stop(const PdmDevice *pdm, PdmSubstream *stream);

/**
 * @brief Set PDM gain
 * @param[in] pdm PDM device
 * @param[in] gain ten times the gain of PDM, unit: dB
 * example: if you want to set 3.6dB, the gain should be 36
 */
int hal_pdm_set_gain(const PdmDevice *pdm, int gain);

/**
 * @brief Deinitialises the PDM device
 * @param[in] pdm PDM device
 * @return int @see VSD_SUCCESS for success, otherwise for error
 */
int hal_pdm_finalize(const PdmDevice *pdm);

/**
 * @brief Interrupt handler for external interrupt.
 * this function will be called by interrupt controller, userspace ignore.
 * @param[in] pdm PDM device
 */
void hal_pdm_irq_handler(const PdmDevice *pdm);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_PDM_H */
