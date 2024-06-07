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

#ifndef __NUCLEI_UART_H__
#define __NUCLEI_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "platform.h"

/**
 * @brief UART
 */
typedef struct {
    volatile uint32_t TXFIFO;
    volatile uint32_t RXFIFO;
    volatile uint32_t TXCTRL;
    volatile uint32_t RXCTRL;
    volatile uint32_t IE;
    volatile uint32_t IP;
    volatile uint32_t DIV;
} UART_TypeDef;

#ifndef DEMOSOC_PERIPH_BASE
#define DEMOSOC_PERIPH_BASE (0x10000000UL) /*!< (Peripheral) Base Address */
#endif

#define UART0_BASE                                            \
    (DEMOSOC_PERIPH_BASE + 0x13000) /*!< (UART0) Base Address \
                                     */

#define UART0 ((UART_TypeDef *)UART0_BASE)

/* Register offsets */
#define UART_REG_TXFIFO 0x00
#define UART_REG_RXFIFO 0x04
#define UART_REG_TXCTRL 0x08
#define UART_REG_RXCTRL 0x0c
#define UART_REG_IE     0x10
#define UART_REG_IP     0x14
#define UART_REG_DIV    0x18

/* TXCTRL register */
#define UART_TXEN    0x1
#define UART_TXWM(x) (((x) & 0xffff) << 16)

/* RXCTRL register */
#define UART_RXEN    0x1
#define UART_RXWM(x) (((x) & 0xffff) << 16)

/* IP register */
#define UART_IP_TXWM 0x1
#define UART_IP_RXWM 0x2

#define UART_TXFIFO_FULL  (1u << 31)
#define UART_RXFIFO_EMPTY (1u << 31)

#define UART_TXCTRL_TXCNT_OFS  (16)
#define UART_TXCTRL_TXCNT_MASK (0x7 << UART_TXCTRL_TXCNT_OFS)
#define UART_TXCTRL_TXEN_OFS   (0)
#define UART_TXCTRL_TXEN_MASK  (0x1 << UART_TXCTRL_TXEN_OFS)
#define UART_TXCTRL_NSTOP_OFS  (1)
#define UART_TXCTRL_NSTOP_MASK (0x1 << UART_TXCTRL_TXEN_OFS)

#define UART_RXCTRL_RXCNT_OFS  (16)
#define UART_RXCTRL_RXCNT_MASK (0x7 << UART_RXCTRL_RXCNT_OFS)
#define UART_RXCTRL_RXEN_OFS   (0)
#define UART_RXCTRL_RXEN_MASK  (0x1 << UART_RXCTRL_RXEN_OFS)

#define UART_IE_TXIE_OFS  (0)
#define UART_IE_TXIE_MASK (0x1 << UART_IE_TXIE_OFS)
#define UART_IE_RXIE_OFS  (1)
#define UART_IE_RXIE_MASK (0x1 << UART_IE_RXIE_OFS)

#define UART_IP_TXIP_OFS  (0)
#define UART_IP_TXIP_MASK (0x1 << UART_IP_TXIP_OFS)
#define UART_IP_RXIP_OFS  (1)
#define UART_IP_RXIP_MASK (0x1 << UART_IP_RXIP_OFS)

typedef enum uart_stop_bit {
    UART_STOP_BIT_1 = 0,
    UART_STOP_BIT_2 = 1,
} UART_STOP_BIT;

int32_t e203_uart_init(UART_TypeDef *uart, uint32_t baudrate);
int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit);
int32_t uart_write(UART_TypeDef *uart, uint8_t val);
uint8_t uart_read(UART_TypeDef *uart);
int32_t uart_set_tx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_txint(UART_TypeDef *uart);
int32_t uart_disable_txint(UART_TypeDef *uart);
int32_t uart_set_rx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_rxint(UART_TypeDef *uart);
int32_t uart_disable_rxint(UART_TypeDef *uart);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __NUCLEI_UART_H__ */
