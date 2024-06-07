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

#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup PEGASUS
 *  @brief Platform Definition of Pegasus.
 *  @ingroup SOC
 *  @{
 */

/** UART Baudrate set to 115200 as default */
#define UART_DEFAULT_BAUD_RATE 115200

/** CPU Internal Region Information */
typedef struct InteRegionInfoType {
    unsigned long iregion_base;  /*!< Internal region base address */
    unsigned long eclic_base;    /*!< eclic base address */
    unsigned long systimer_base; /*!< system timer base address */
    unsigned long smp_base;      /*!< smp base address */
    unsigned long idu_base;      /*!< idu base address */
} InteRegionInfoType;

typedef unsigned int IRQn_Type;

#define SysTimerSW_IRQn    3        /**<  System Timer SW interrupt */
#define SysTimer_IRQn      7        /**<  System Timer Interrupt */
#define TIMER16_0_IRQn     21       /**< Timer16_0 Interrupt */
#define TIMER16_1_IRQn     22       /**< Timer16_1 Interrupt */
#define TIMER16_2_IRQn     23       /**< Timer16_2 Interrupt */
#define TIMER16_3_IRQn     24       /**< Timer16_3 Interrupt */
#define TIMER16_4_IRQn     25       /**< Timer16_4 Interrupt */
#define TIMER32_0_IRQn     26       /**< Timer32_0 Interrupt */
#define TIMER32_1_IRQn     27       /**< Timer32_1 Interrupt */
#define TIMER32_2_IRQn     28       /**< Timer32_2 Interrupt */
#define TIMER32_3_IRQn     29       /**< Timer32_3 Interrupt */
#define TIMER32_4_IRQn     30       /**< Timer32_4 Interrupt */
#define PDM_IRQn           31       /**< PDM Interrupt */
#define ZSP_ACK_IRQn       32       /**< Mailbox ACK Interrupt */
#define ZSP_REQ_IRQn       33       /**< Mailbox REQ Interrupt */
#define I2C_A_IRQn         34       /**< I2C_A Interrupt */
#define BLE_IRQn           35       /**< BLE Interrupt */
#define USB_IRQn           36       /**< USB Interrupt */
#define DMAC_IRQn          37       /**< DMAC Interrupt */
#define CRYP0_IRQn         38       /**< Crypto0 Interrupt */
#define CRYP1_IRQn         39       /**< Crypto1 Interrupt */
#define CRYP2_IRQn         40       /**< Crypto2 Interrupt */
#define CRYP3_IRQn         41       /**< Crypto3 Interrupt */
#define QSPI_IRQn          42       /**< QSPI Interrupt */
#define SPI0_IRQn          43       /**< SPI0 Interrupt */
#define SPI1_IRQn          44       /**< SPI1 Interrupt */
#define SPI2_IRQn          45       /**< SPI2 Interrupt */
#define SPI3_IRQn          46       /**< SPI3 Interrupt */
#define RTC_IRQn           47       /**< RTC Interrupt */
#define GPIO0_IRQn         49       /**< GPIO0 Interrupt */
#define I2S_IRQn           50       /**< I2S Interrupt */
#define I2C_IRQn           51       /**< I2C Interrupt */
#define I3C_IRQn           52       /**< I3C Interrupt */
#define UART0_IRQn         53       /**< UART0 Interrupt */
#define UART1_IRQn         54       /**< UART1 Interrupt */
#define UART2_IRQn         55       /**< UART2 Interrupt */
#define UART3_IRQn         56       /**< UART3 Interrupt */
#define PWM_IRQn           57       /**< PWM Interrupt */
#define EFUSE_IRQn         58       /**< EFUSE Interrupt */
#define ADC_IRQn           59       /**< ADC Interrupt */
#define DS_EXT0_IRQn       76       /**< DS_EXT0 Interrupt */
#define DS_EXT1_IRQn       77       /**< DS_EXT1 Interrupt */
#define DS_EXT2_IRQn       78       /**< DS_EXT2 Interrupt */
#define DS_EXT3_IRQn       79       /**< DS_EXT3 Interrupt */
#define DS_EXT4_IRQn       80       /**< DS_EXT4 Interrupt */
#define DS_EXT5_IRQn       81       /**< DS_EXT5 Interrupt */
#define DS_EXT6_IRQn       82       /**< DS_EXT6 Interrupt */
#define DS_EXT7_IRQn       83       /**< DS_EXT7 Interrupt */
#define DS_EXT8_IRQn       84       /**< DS_EXT8 Interrupt */
#define DS_EXT9_IRQn       85       /**< DS_EXT9 Interrupt */
#define DS_EXT10_IRQn      86       /**< DS_EXT10 Interrupt */
#define DS_EXT11_IRQn      87       /**< DS_EXT11 Interrupt */
#define DS_EXT12_IRQn      88       /**< DS_EXT12 Interrupt */
#define DS_EXT13_IRQn      89       /**< DS_EXT13 Interrupt */
#define DS_EXT14_IRQn      90       /**< DS_EXT14 Interrupt */
#define DS_EXT15_IRQn      91       /**< DS_EXT15 Interrupt */
#define PDM_ERR_IRQn       92       /**< PDM_ERR Interrupt */
#define DACC_IRQn          93       /**< DAC Controller Interrupt */
#define GPIO1_IRQn         94       /**< GPIO1 Interrupt */
#define GPIO2_IRQn         95       /**< GPIO2 Interrupt */
#define TZF_APB0_IRQn      96       /**<  TZF_APB0 Interrupt */
#define TZF_APB1_IRQn      97       /**<  TZF_APB1 Interrupt */
#define TZF_APB2_IRQn      98       /**<  TZF_APB2 Interrupt */
#define TZF_APB3_IRQn      99       /**<  TZF_APB3 Interrupt */
#define TZF_QSPI_IRQn      100      /**< TZF_QSPI Interrupt */
#define TZF_USB_IRQn       101      /**< TZF_USB Interrupt */
#define TZF_DMA_IRQn       102      /**< TZF_DMA Interrupt */
#define TZF_PAR_SRAM_IRQn  103      /**< TZF_PAR_SRAM Interrupt */
#define TZF_ECC_SRAM_IRQn  104      /**< TZF_ECC_SRAM Interrupt */
#define TZF_CACHE_CFG_IRQn 105      /**< TZF_CACHE_CFG Interrupt */
#define SOC_INT_MAX        106      /**< MAX Interrupt ID */
#define INVALID_IRQn       (0xffff) /**< Invalid Interrupt */

typedef enum ExceptionType {
    /* =========== Nuclei N/NX Specific Exception Code =========== */
    INS_UNALIGN_EXC     = 0,     /*!<  Instruction address misaligned */
    INS_ACC_FAULT_EXC   = 1,     /*!<  Instruction access fault */
    ILLE_INS_EXC        = 2,     /*!<  Illegal instruction */
    BREAK_EXC           = 3,     /*!<  Beakpoint */
    LD_ADDR_UNALIGN_EXC = 4,     /*!<  Load address misaligned */
    LD_FAULT_EXC        = 5,     /*!<  Load access fault */
    ST_ADDR_UNALIGN_EXC = 6,     /*!<  Store or AMO address misaligned */
    ST_ACCESS_FAULT_EXC = 7,     /*!<  Store or AMO access fault */
    UMODE_ECALL_EXC     = 8,     /*!<  Environment call from User mode */
    MMODE_ECALL_EXC     = 11,    /*!<  Environment call from Machine mode */
    NMI_EXC             = 0xfff, /*!<  NMI interrupt*/
} ExceptionType;

#if __riscv_xlen == 32
#ifndef __NUCLEI_CORE_REV
#define __NUCLEI_N_REV 0x0104 /*!< Core Revision r1p4 */
#else
#define __NUCLEI_N_REV __NUCLEI_CORE_REV
#endif
#elif __riscv_xlen == 64
#ifndef __NUCLEI_CORE_REV
#define __NUCLEI_NX_REV 0x0100 /*!< Core Revision r1p0 */
#else
#define __NUCLEI_NX_REV __NUCLEI_CORE_REV
#endif
#endif /* __riscv_xlen == 64 */

/* ToDo: define the correct core features for the pegasus */

/*!< Set to 1 if ECLIC is present */
#define __ECLIC_PRESENT 1
/*!< Set to ECLIC baseaddr of your device */
#define __ECLIC_BASEADDR (0x18020000UL)

/*!< Set to 1 - 8, the number of hardware bits are actually implemented in the
 * clicintctl registers.
 * If not defined, it will be defined in core_feature_eclic.h */
// #define __ECLIC_INTCTLBITS 4
/*!< Set to 1 - 1024, total interrupt number of ECLIC Unit */
#define __ECLIC_INTNUM 51
/*!< Set to 1 if System Timer is present */
#define __SYSTIMER_PRESENT 1
/*!< Set to SysTimer baseaddr of your device */
#define __SYSTIMER_BASEADDR (0x18030000UL)

/*!< Set to 0, 1, or 2, 0 not present, 1 single floating point unit present, 2
 * double floating point unit present */
#if !defined(__riscv_flen)
#define __FPU_PRESENT 0
#elif __riscv_flen == 32
#define __FPU_PRESENT 1
#else
#define __FPU_PRESENT 2
#endif

/* __riscv_bitmanip/__riscv_dsp/__riscv_vector is introduced
 * in nuclei gcc 10.2 when b/p/v extension compiler option is selected.
 * For example:
 * -march=rv32imacb -mabi=ilp32 : __riscv_bitmanip macro will be defined
 * -march=rv32imacp -mabi=ilp32 : __riscv_dsp macro will be defined
 * -march=rv64imacv -mabi=lp64 : __riscv_vector macro will be defined
 */
#if defined(__riscv_bitmanip)
/*!< Set to 1 if Bitmainpulation extension is present */
#define __BITMANIP_PRESENT 1
#else
/*!< Set to 1 if Bitmainpulation extension is present */
#define __BITMANIP_PRESENT 0
#endif
#if defined(__riscv_dsp)
/*!< Set to 1 if Partial SIMD(DSP) extension is present */
#define __DSP_PRESENT 1
#else
/*!< Set to 1 if Partial SIMD(DSP) extension is present */
#define __DSP_PRESENT 0
#endif
#if defined(__riscv_vector)
/*!< Set to 1 if Vector extension is present */
#define __VECTOR_PRESENT 1
#else
/*!< Set to 1 if Vector extension is present */
#define __VECTOR_PRESENT 0
#endif

/*!< Set to 1 if PMP is present */
#define __PMP_PRESENT 1
/*!< Set to 8 or 16, the number of PMP entries */
#define __PMP_ENTRY_NUM 16

/*!< Set to 1 if I-Cache is present */
#define __ICACHE_PRESENT 1
/*!< Set to 1 if D-Cache is present */
#define __DCACHE_PRESENT 1
/*!< Set to 1 if Cache Control and Mantainence Unit is present */
#define __CCM_PRESENT 1

/*!< Set to 1 if intrinsic api header files need to be included */
#define __INC_INTRINSIC_API 0

/*!< Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig 0
/*!< Set to 1 if vendor exception handler is present */
#define __Vendor_EXCEPTION 0

#include "nmsis_compiler.h" /* NMSIS compiler specific defines */

/* Include core base feature header file */
#include "core_feature_base.h"
/* Include core fpu feature header file */
#include "core_feature_fpu.h"
/* Include core dsp feature header file */
#include "core_feature_dsp.h"
/* Include core cache feature header file */
#include "core_feature_cache.h"
/* Include core eclic feature header file */
#include "core_feature_eclic.h"
/* Include core systimer feature header file */
#include "core_feature_timer.h"

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _PLATFORM_H */
