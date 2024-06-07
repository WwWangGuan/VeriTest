/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * \file     startup_riscv.S
 * \brief    NMSIS Nuclei N/NX Class Core based Core Device Startup File for
 *  Device pegasus
 * \version  V1.00
 * \date     26. Aug 2022
 *
 ******************************************************************************/

#include "riscv_encoding.h"

.macro DECLARE_INT_HANDLER  INT_HDL_NAME
#if defined(__riscv_xlen) && (__riscv_xlen == 32)
    .word \INT_HDL_NAME
#else
    .dword \INT_HDL_NAME
#endif
.endm

    .section .vtable

    .weak eclic_msip_handler
    .weak eclic_mtip_handler
    .weak riscv_irq21_handler
    .weak riscv_irq22_handler
    .weak riscv_irq23_handler
    .weak riscv_irq24_handler
    .weak riscv_irq25_handler
    .weak riscv_irq26_handler
    .weak riscv_irq27_handler
    .weak riscv_irq28_handler
    .weak riscv_irq29_handler
    .weak riscv_irq30_handler
    .weak riscv_irq31_handler
    .weak riscv_irq32_handler
    .weak riscv_irq33_handler
    .weak riscv_irq34_handler
    .weak riscv_irq35_handler
    .weak riscv_irq36_handler
    .weak riscv_irq37_handler
    .weak riscv_irq38_handler
    .weak riscv_irq39_handler
    .weak riscv_irq40_handler
    .weak riscv_irq41_handler
    .weak riscv_irq42_handler
    .weak riscv_irq43_handler
    .weak riscv_irq44_handler
    .weak riscv_irq45_handler
    .weak riscv_irq46_handler
    .weak riscv_irq47_handler
    .weak riscv_irq49_handler
    .weak riscv_irq50_handler
    .weak riscv_irq51_handler
    .weak riscv_irq52_handler
    .weak riscv_irq53_handler
    .weak riscv_irq54_handler
    .weak riscv_irq55_handler
    .weak riscv_irq56_handler
    .weak riscv_irq57_handler
    .weak riscv_irq58_handler
    .weak riscv_irq59_handler
    .weak riscv_irq76_handler
    .weak riscv_irq77_handler
    .weak riscv_irq78_handler
    .weak riscv_irq79_handler
    .weak riscv_irq80_handler
    .weak riscv_irq81_handler
    .weak riscv_irq82_handler
    .weak riscv_irq83_handler
    .weak riscv_irq84_handler
    .weak riscv_irq85_handler
    .weak riscv_irq86_handler
    .weak riscv_irq87_handler
    .weak riscv_irq88_handler
    .weak riscv_irq89_handler
    .weak riscv_irq90_handler
    .weak riscv_irq91_handler
    .weak riscv_irq92_handler
    .weak riscv_irq93_handler
    .weak riscv_irq94_handler
    .weak riscv_irq95_handler
    .weak riscv_irq96_handler
    .weak riscv_irq97_handler
    .weak riscv_irq98_handler
    .weak riscv_irq99_handler
    .weak riscv_irq100_handler
    .weak riscv_irq101_handler
    .weak riscv_irq102_handler
    .weak riscv_irq103_handler
    .weak riscv_irq104_handler
    .weak riscv_irq105_handler

    .globl vector_base
    .type vector_base, @object
vector_base:
    j _start                                                /* 0: Reserved, Jump to _start when reset for vector table not remapped cases.*/
    .align LOG_REGBYTES                                     /*    Need to align 4 byte for RV32, 8 Byte for RV64 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 1: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 2: Reserved */
    DECLARE_INT_HANDLER     eclic_msip_handler              /* 3: Machine software interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 4: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 5: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 6: Reserved */
    DECLARE_INT_HANDLER     eclic_mtip_handler              /* 7: Machine timer interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 8: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 9: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 10: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 11: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 12: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 13: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 14: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 15: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 16: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 17: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 18: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 19: Interrupt 19 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 20: Interrupt 20 */
    DECLARE_INT_HANDLER     riscv_irq21_handler          /* 21: Interrupt 21 */
    DECLARE_INT_HANDLER     riscv_irq22_handler          /* 22: Interrupt 22 */
    DECLARE_INT_HANDLER     riscv_irq23_handler          /* 23: Interrupt 23 */

    DECLARE_INT_HANDLER     riscv_irq24_handler          /* 24: Interrupt 24 */
    DECLARE_INT_HANDLER     riscv_irq25_handler          /* 25: Interrupt 25 */
    DECLARE_INT_HANDLER     riscv_irq26_handler          /* 26: Interrupt 26 */
    DECLARE_INT_HANDLER     riscv_irq27_handler          /* 27: Interrupt 27 */

    DECLARE_INT_HANDLER     riscv_irq28_handler          /* 28: Interrupt 28 */
    DECLARE_INT_HANDLER     riscv_irq29_handler          /* 29: Interrupt 29 */
    DECLARE_INT_HANDLER     riscv_irq30_handler          /* 30: Interrupt 30 */
    DECLARE_INT_HANDLER     riscv_irq31_handler          /* 31: Interrupt 31 */

    DECLARE_INT_HANDLER     riscv_irq32_handler          /* 32: Interrupt 32 */
    DECLARE_INT_HANDLER     riscv_irq33_handler          /* 33: Interrupt 33 */
    DECLARE_INT_HANDLER     riscv_irq34_handler          /* 34: Interrupt 34 */
    DECLARE_INT_HANDLER     riscv_irq35_handler          /* 35: Interrupt 35 */

    DECLARE_INT_HANDLER     riscv_irq36_handler          /* 36: Interrupt 36 */
    DECLARE_INT_HANDLER     riscv_irq37_handler          /* 37: Interrupt 37 */
    DECLARE_INT_HANDLER     riscv_irq38_handler          /* 38: Interrupt 38 */
    DECLARE_INT_HANDLER     riscv_irq39_handler          /* 39: Interrupt 39 */

    DECLARE_INT_HANDLER     riscv_irq40_handler          /* 40: Interrupt 40 */
    DECLARE_INT_HANDLER     riscv_irq41_handler          /* 41: Interrupt 41 */
    DECLARE_INT_HANDLER     riscv_irq42_handler          /* 42: Interrupt 42 */
    DECLARE_INT_HANDLER     riscv_irq43_handler          /* 43: Interrupt 43 */

    DECLARE_INT_HANDLER     riscv_irq44_handler          /* 44: Interrupt 44 */
    DECLARE_INT_HANDLER     riscv_irq45_handler          /* 45: Interrupt 45 */
    DECLARE_INT_HANDLER     riscv_irq46_handler          /* 46: Interrupt 46 */
    DECLARE_INT_HANDLER     riscv_irq47_handler          /* 47: Interrupt 47 */

    DECLARE_INT_HANDLER     default_intexc_handler       /* 48: Interrupt 48 */
    DECLARE_INT_HANDLER     riscv_irq49_handler          /* 49: Interrupt 49 */
    DECLARE_INT_HANDLER     riscv_irq50_handler          /* 50: Interrupt 50 */
    DECLARE_INT_HANDLER     riscv_irq51_handler          /* 51: Interrupt 51 */

    DECLARE_INT_HANDLER     riscv_irq52_handler          /* 52: Interrupt 52 */
    DECLARE_INT_HANDLER     riscv_irq53_handler          /* 53: Interrupt 53 */
    DECLARE_INT_HANDLER     riscv_irq54_handler          /* 54: Interrupt 54 */
    DECLARE_INT_HANDLER     riscv_irq55_handler          /* 55: Interrupt 55 */

    DECLARE_INT_HANDLER     riscv_irq56_handler          /* 56: Interrupt 56 */
    DECLARE_INT_HANDLER     riscv_irq57_handler          /* 57: Interrupt 57 */
    DECLARE_INT_HANDLER     riscv_irq58_handler          /* 58: Interrupt 58 */
    DECLARE_INT_HANDLER     riscv_irq59_handler          /* 59: Interrupt 59 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 60: Interrupt 60 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 61: Interrupt 61 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 62: Interrupt 62 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 63: Interrupt 63 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 64: Interrupt 64 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 65: Interrupt 65 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 66: Interrupt 66 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 67: Interrupt 67 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 68: Interrupt 68 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 69: Interrupt 69 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 70: Interrupt 70 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 71: Interrupt 71 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 72: Interrupt 72 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 73: Interrupt 73 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 74: Interrupt 74 */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 75: Interrupt 75 */

    DECLARE_INT_HANDLER     riscv_irq76_handler          /* 76: Interrupt 76 */
    DECLARE_INT_HANDLER     riscv_irq77_handler          /* 77: Interrupt 77 */
    DECLARE_INT_HANDLER     riscv_irq78_handler          /* 78: Interrupt 78 */
    DECLARE_INT_HANDLER     riscv_irq79_handler          /* 79: Interrupt 79 */

    DECLARE_INT_HANDLER     riscv_irq80_handler          /* 80: Interrupt 80 */
    DECLARE_INT_HANDLER     riscv_irq81_handler          /* 81: Interrupt 81 */
    DECLARE_INT_HANDLER     riscv_irq82_handler          /* 82: Interrupt 82 */
    DECLARE_INT_HANDLER     riscv_irq83_handler          /* 83: Interrupt 83 */

    DECLARE_INT_HANDLER     riscv_irq84_handler          /* 84: Interrupt 84 */
    DECLARE_INT_HANDLER     riscv_irq85_handler          /* 85: Interrupt 85 */
    DECLARE_INT_HANDLER     riscv_irq86_handler          /* 86: Interrupt 86 */
    DECLARE_INT_HANDLER     riscv_irq87_handler          /* 87: Interrupt 87 */

    DECLARE_INT_HANDLER     riscv_irq88_handler          /* 88: Interrupt 88 */
    DECLARE_INT_HANDLER     riscv_irq89_handler          /* 89: Interrupt 89 */
    DECLARE_INT_HANDLER     riscv_irq90_handler          /* 90: Interrupt 90 */
    DECLARE_INT_HANDLER     riscv_irq91_handler          /* 91: Interrupt 91 */

    DECLARE_INT_HANDLER     riscv_irq92_handler          /* 92: Interrupt 92 */
    DECLARE_INT_HANDLER     riscv_irq93_handler          /* 93: Interrupt 93 */
    DECLARE_INT_HANDLER     riscv_irq94_handler          /* 94: Interrupt 94 */
    DECLARE_INT_HANDLER     riscv_irq95_handler          /* 95: Interrupt 95 */

    DECLARE_INT_HANDLER     riscv_irq96_handler          /* 96: Interrupt 96 */
    DECLARE_INT_HANDLER     riscv_irq97_handler          /* 97: Interrupt 97 */
    DECLARE_INT_HANDLER     riscv_irq98_handler          /* 98: Interrupt 98 */
    DECLARE_INT_HANDLER     riscv_irq99_handler          /* 99: Interrupt 99 */

    DECLARE_INT_HANDLER     riscv_irq100_handler          /* 100: Interrupt 100 */
    DECLARE_INT_HANDLER     riscv_irq101_handler          /* 101: Interrupt 101 */
    DECLARE_INT_HANDLER     riscv_irq102_handler          /* 102: Interrupt 102 */
    DECLARE_INT_HANDLER     riscv_irq103_handler          /* 103: Interrupt 103 */

    DECLARE_INT_HANDLER     riscv_irq104_handler          /* 104: Interrupt 104 */
    DECLARE_INT_HANDLER     riscv_irq105_handler          /* 105: Interrupt 105 */

    .section .init

    .globl _start
    .type _start, @function

/**
 * Reset Handler called on controller reset
 */
_start:
    /* ===== Startup Stage 1 ===== */
    /* Disable Global Interrupt */
    csrc CSR_MSTATUS, MSTATUS_MIE

    /* Initialize GP and TP */
    .option push
    .option norelax
    la gp, __global_pointer$
    la tp, __tls_base
    .option pop

    la sp, _sp

    /*
     * Set the the NMI base mnvec to share
     * with mtvec by setting CSR_MMISC_CTL
     * bit 9 NMI_CAUSE_FFF to 1
     */
    li t0, MMISC_CTL_NMI_CAUSE_FFF
    csrs CSR_MMISC_CTL, t0

    /*
     * Initialize ECLIC vector interrupt
     * base address mtvt to vector_base
     */
    la t0, vector_base
    csrw CSR_MTVT, t0

    /*
     * Set ECLIC non-vector entry to be controlled
     * by mtvt2 CSR register.
     * Initialize ECLIC non-vector interrupt
     * base address mtvt2 to irq_entry.
     */
    la t0, irq_entry
    csrw CSR_MTVT2, t0
    csrs CSR_MTVT2, 0x1

    /*
     * Set Exception Entry MTVEC to early_exc_entry
     * Due to settings above, Exception and NMI
     * will share common entry.
     * This early_exc_entry is only used during early
     * boot stage before main
     */
    la t0, early_exc_entry
    csrw CSR_MTVEC, t0

    /* Set the interrupt processing mode to ECLIC mode */
    li t0, 0x3f
    csrc CSR_MTVEC, t0
    csrs CSR_MTVEC, 0x3

    /* ===== Startup Stage 2 ===== */

    /* Enable FPU Unit if f/d exist in march */
#if defined(__riscv_flen) && __riscv_flen > 0
    /* Enable FPU, and set state to initial */
    li t0, MSTATUS_FS
    csrc mstatus, t0
    li t0, MSTATUS_FS_INITIAL
    csrs mstatus, t0
#endif

    /* Enable mcycle and minstret counter */
    csrci CSR_MCOUNTINHIBIT, 0x5

    /* ===== Startup Stage 3 ===== */
    /*
     * Load text section from CODE ROM to CODE RAM
     * when text LMA is different with VMA
     */
    la a0, _text_lma
    la a1, _text
    /* If text LMA and VMA are equal
     * then no need to copy text section */
    beq a0, a1, 2f
    la a2, _etext
    bgeu a1, a2, 2f

1:
    /* Load code section if necessary */
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Load data section */
    la a0, _data_lma
    la a1, _data
    /* If data vma=lma, no need to copy */
    beq a0, a1, 2f
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Clear bss section */
    la a0, __bss_start
    la a1, _end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:

.globl _start_premain
.type _start_premain, @function
_start_premain:
    /*
     * Call vendor defined system_init to
     * initialize the micro-controller system
     */
    call premain_system_init

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    /* Call C/C++ constructor start up code */
    call __libc_init_array

    /* do pre-init steps before main */
    call _premain_init

    /*
     * When all initialization steps done
     * set exception entry to correct exception
     * entry and jump to main.
     * And set the interrupt processing mode to
     * ECLIC mode
     */
    la t0, exc_entry
    csrw CSR_MTVEC, t0
    li t0, 0x3f
    csrc CSR_MTVEC, t0
    csrs CSR_MTVEC, 0x3

    /* ===== Call Main Function  ===== */
    /* argc = argv = 0 */
    li a0, 0
    li a1, 0

    call main
    /* do post-main steps after main */
    call _postmain_fini

1:
    j 1b

/* Early boot exception entry before main */
.align 6
.global early_exc_entry
.type early_exc_entry, @function
early_exc_entry:
    wfi
    j early_exc_entry
