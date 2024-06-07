/**
 * Copyright (C) 2023. VeriSilicon Holdings Co., Ltd.
 * All rights reserved.
 *
 * @file bsp_common.h
 * @brief public header for bsp common
 */

#ifndef __BSP_COMMON_H__
#define __BSP_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup COMMON
 *  BSP common
 *  @ingroup BSP
 *  @{
 */

#include <stdint.h>

#ifndef ROUND_DOWN
#define ROUND_DOWN(a, b) (((a) / (b)) * (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef DIV_ROUND_UP
#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))
#endif

#ifndef BIT
#define BIT(b) (1UL << (b))
#endif

#ifndef MASK
#define MASK(b_hi, b_lo) (((1ULL << ((b_hi) - (b_lo) + 1ULL)) - 1ULL) << (b_lo))
#endif

#ifndef SET_BIT
#define SET_BIT(x, b) ((x) |= (1 << (b)))
#endif

#ifndef SET_BITS
#define SET_BITS(x, b_hi, b_lo) ((x) | (MASK(b_hi, b_lo) << (b_lo)))
#endif

#ifndef GET_BIT
#define GET_BIT(x, b) (((x) & (1ULL << (b))) >> (b))
#endif

#ifndef GET_BITS
#define GET_BITS(x, b_hi, b_lo) (((x) & MASK(b_hi, b_lo)) >> (b_lo))
#endif

#ifndef CLEAR_BIT
#define CLEAR_BIT(x, b) ((x) &= ~(1 << (b)))
#endif

#ifndef CLEAR_BITS
#define CLEAR_BITS(x, b_hi, b_lo) ((x) &= ~(MASK(b_hi, b_lo) << (b_lo)))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/**
 * @brief         cast a member of a structure out to the containing structure
 * @param ptr     the pointer to the member.
 * @param type    the type of the container struct this is embedded in.
 * @param member  the name of the member within the struct.
 *
 */
#ifndef container_of
#define container_of(ptr, type, member)                    \
    ({                                                     \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    })
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __BSP_COMMON_H__
