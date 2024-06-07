/*
 * Copyright (C) 2023 VeriSilicon Holdings Co., Ltd.
 * Copyright (c) 2011-2014, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Misc utilities
 *
 * Misc utilities usable by the kernel and application code.
 */

#ifndef ZEPHYR_INCLUDE_SYS_UTIL_H_
#define ZEPHYR_INCLUDE_SYS_UTIL_H_

#ifndef snprintk
#define snprintk snprintf
#endif

#define BTBIT(n)          (1UL << (n))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

/* concatenate the values of the arguments into one */
#define _DO_CONCAT(x, y) x##y
#define _CONCAT(x, y)    _DO_CONCAT(x, y)

#ifndef BUILD_ASSERT
/* Compile-time assertion that makes the build to fail.
 * Common implementation swallows the message.
 */
#define BUILD_ASSERT(EXPR, MSG...) _Static_assert(EXPR, "" MSG)
#endif

#ifndef __aligned
#define __aligned(x) __attribute__((__aligned__(x)))
#endif
#define Z_STRINGIFY(x) #x
#define ___in_section(a, b, c) \
    __attribute__((section("." Z_STRINGIFY(a) "." Z_STRINGIFY(b) "." Z_STRINGIFY(c))))
#define __in_section(a, b, c) ___in_section(a, b, c)
#define Z_DECL_ALIGN(type)    __aligned(__alignof(type)) type
#define STRUCT_SECTION_ITERABLE(struct_type, name) \
    Z_DECL_ALIGN(struct struct_type) name __in_section(_##struct_type, static, name)

typedef long atomic_t;
typedef atomic_t atomic_val_t;
#define ATOMIC_BITS                   (sizeof(atomic_val_t) * 8)
#define ATOMIC_BITMAP_SIZE(num_bits)  (1 + ((num_bits) - 1) / ATOMIC_BITS)
#define ATOMIC_DEFINE(name, num_bits) atomic_t name[ATOMIC_BITMAP_SIZE(num_bits)]

typedef struct {
    void *pxDummy1;
} sys_snode_t;

#endif /* ZEPHYR_INCLUDE_SYS_UTIL_H_ */
