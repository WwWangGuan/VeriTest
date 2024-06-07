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
#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup GPIO
 *  GPIO hal API
 *  @ingroup HAL
 *  Hardware Abstraction Layer
 *  @{
 */

#include <stdint.h>

typedef enum GpioIdDef {
    GPIO_ID_0,
    GPIO_ID_1,
    GPIO_ID_2,
    GPIO_ID_MAX,
} GpioIdDef;

/**
 * @brief GPIO pin configuration
 */
typedef enum {
    IO_MODE_IRQ = 0,        /**< Used to trigger interrupt */
    IO_MODE_IRQ_PU,         /**< Used to trigger interrupt with pull-up */
    IO_MODE_IRQ_PD,         /**< Used to trigger interrupt with pull-down */
    IO_MODE_IN_PU,          /**< Input with an internal pull-up resistor */
    IO_MODE_IN_PD,          /**< Input with an internal pull-down resistor */
    IO_MODE_IN_FLOAT,       /**< Input without internal resistor */
    IO_MODE_OUT_PULL,       /**< Output actively driven high or driven low */
    IO_MODE_OUT_OPEN_DRAIN, /**< Output open drain mode */
} GpioConfigType;

/**
 * @brief GPIO interrupt trigger modes
 */
typedef enum {
    IRQ_TRIGGER_NONE = 0,     /**< None  */
    IRQ_TRIGGER_LEVEL_LOW,    /**< Trigger on low level  */
    IRQ_TRIGGER_LEVEL_HIGH,   /**< Trigger on high level  */
    IRQ_TRIGGER_RISING_EDGE,  /**< Trigger at rising edge  */
    IRQ_TRIGGER_FALLING_EDGE, /**< Trigger at falling edge */
    IRQ_TRIGGER_BOTH_EDGES,   /**< Trigger at both falling/rising edges */
} GpioIrqTrigger;

/**
 * @brief Define the pull-up/down of gpio pin
 */
typedef enum {
    GPIO_PULL_FLOAT = 0, /**< GPIO without internal resistor */
    GPIO_PULL_UP,        /**< GPIO with an internal pull-up resistor */
    GPIO_PULL_DOWN,      /**< GPIO with an internal pull-down resistor */
} IoPullCtrl;

/**
 * @brief Define the output level of gpio
 */
typedef enum {
    GPIO_OUT_HIGH = 0, /**< GPIO Output high level */
    GPIO_OUT_LOW,      /**< GPIO Output low level */
    GPIO_OUT_TOGGLE,   /**< GPIO Output toggle from current level */
} IoOutCtrl;

/**
 * @brief Define the capability of gpio trigger mode
 */
typedef enum {
    GPIO_TRIG_LEVEL_LOW    = (0x1 << IRQ_TRIGGER_LEVEL_LOW),
    GPIO_TRIG_LEVEL_HIGH   = (0x1 << IRQ_TRIGGER_LEVEL_HIGH),
    GPIO_TRIG_RISING_EDGE  = (0x1 << IRQ_TRIGGER_RISING_EDGE),
    GPIO_TRIG_FALLING_EDGE = (0x1 << IRQ_TRIGGER_FALLING_EDGE),
    GPIO_TRIG_BOTH_EDGES   = (0x1 << IRQ_TRIGGER_BOTH_EDGES),
} GpioTrigCapability;

/**
 * @brief Structure of GPIO hardware configuration
 */
typedef struct GpioHwConfig {
    uint32_t base;            /**< Base address of GPIO device */
    uint32_t irq_num;         /**< Interrupt number for a GPIO group */
    uint16_t irq_id;          /**< Interrupt ID which defined by SoC */
    uint16_t trig_capability; /**< The capability of gpio trigger mode */
} GpioHwConfig;

/**
 * @brief Structure of a GPIO port
 */
typedef struct GpioPort {
    uint8_t group : 6;      /**< Gpio group id */
    uint8_t irq_reload : 1; /**< Re-enable interrupt after trigger */
    uint8_t invert : 1;     /**< Invert the pin, 0 for no invert,1 for invert */
    uint8_t port;           /**< Gpio port id in the group */
    uint8_t trigger;        /**< Trigger mode for interrupt, @see GpioIrqTrigger */
    uint8_t type;           /**< Gpio config, @see GpioConfigType */
} GpioPort;

/**
 * @brief Structure of GPIO device
 */
typedef struct GpioDevice {
    uint8_t group_id;              /**< Gpio group id */
    const GpioHwConfig *hw_config; /**< Gpio hardware configuration */
    const void *soc_ops;           /**< Gpio soc extent operations */
    const void *ops;               /**< Gpio operations */
    void *ctx;                     /**< Private context */
} GpioDevice;

/**
 * @brief Structure of operations for GPIO
 */
typedef struct GpioOperations {
    int (*io_dir)(const GpioDevice *device, unsigned char io_idx, uint8_t b_out, IoPullCtrl pull);
    uint8_t (*get_dir)(const GpioDevice *device, unsigned char io_idx);
    int (*io_irq)(const GpioDevice *device, unsigned char io_idx, uint8_t b_irq);
    int (*irq_set)(const GpioDevice *device, unsigned char io_idx, uint8_t b_st,
                   GpioIrqTrigger trig);
    int (*output_set)(const GpioDevice *device, unsigned char io_idx, uint8_t level);
    uint8_t (*output_get)(const GpioDevice *device, unsigned char io_idx);
    uint8_t (*input_get)(const GpioDevice *device, unsigned char io_idx);
    int (*irq_enable)(const GpioDevice *device, unsigned char io_idx, uint8_t reolad,
                      void *handler);
    int (*irq_disable)(const GpioDevice *device, unsigned char io_idx);
    void (*irq_grp_handler)(const GpioDevice *device);
    void (*irq_ind_handler)(const GpioDevice *device, unsigned char irq_id);
} GpioOperations;

/**
 * @brief GPIO interrupt callback handler
 */
typedef void (*GpioIrqHandler)(void);

/**
 * @brief Add GPIO device instance
 * @note This API should be called by GPIO IP driver to add initialized instance
 * to HAL, not for application usage
 * @param device The device of GPIO will be added
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_add_dev(GpioDevice *device);

/**
 * @brief Get Gpio Group device instance
 * @param group_id Gpio group id
 * @return Return the Gpio instance
 */
GpioDevice *hal_gpio_get_device(uint8_t group_id);

/**
 * @brief Initialize a GPIO pin
 * @param gpio The gpio which need to be initialized
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_init(const GpioPort *gpio);

/**
 * @brief Sets an output GPIO pin to high
 * @param gpio The gpio which need to be set high
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_output_high(const GpioPort *gpio);

/**
 * @brief Sets an output GPIO pin to low
 * @param gpio The gpio which need to be set low
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_output_low(const GpioPort *gpio);

/**
 * @brief Toggle an output GPIO pin's output
 * @param gpio The gpio pin which need to be toggled
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_output_toggle(const GpioPort *gpio);

/**
 * @brief Get the state of an input GPIO pin
 * @param gpio The gpio pin which need to be read
 * @param value Gpio value read
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_input_get(const GpioPort *gpio, uint32_t *value);

/**
 * @brief Enable interrupt trigger for an input GPIO pin
 * @param gpio The gpio pin which provides the interrupt trigger
 * @param handler  A function pointer to the interrupt handler
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_enable_irq(const GpioPort *gpio, GpioIrqHandler handler);

/**
 * @brief Disables interrupt trigger for an input GPIO pin
 * @param gpio The gpio pin which provides the interrupt trigger
 * @return Return result
 *   @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_disable_irq(const GpioPort *gpio);

/**
 * @brief Get the state of an output GPIO pin
 * @param gpio The gpio pin which need to be read
 * @param value Gpio value read
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_output_get(const GpioPort *gpio, uint32_t *value);

/**
 * @brief Get the direction of an GPIO pin
 * @param gpio The gpio pin which need to be read
 * @param value Gpio value read
 * @return Return result
 * @retval VSD_SUCCESS for succeed, others for failure
 */
int hal_gpio_dir_get(const GpioPort *gpio, uint32_t *value);

/**
 * @brief Interrupt handler for an External Interrupt
 * @param device The gpio group device instance
 */
void hal_gpio_irq_handler(const GpioDevice *device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_GPIO_H_ */
