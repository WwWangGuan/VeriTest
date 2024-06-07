/** @file
 *  @brief Buffer management.
 */

/*
 * Copyright (C) 2023 VeriSilicon Holdings Co., Ltd.
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_NET_BUF_H_
#define ZEPHYR_INCLUDE_NET_BUF_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Simple network buffer representation.
 *
 * This is a simpler variant of the net_buf object (in fact net_buf uses
 * net_buf_simple internally). It doesn't provide any kind of reference
 * counting, user data, dynamic allocation, or in general the ability to
 * pass through kernel objects such as FIFOs.
 *
 * The main use of this is for scenarios where the meta-data of the normal
 * net_buf isn't needed and causes too much overhead. This could be e.g.
 * when the buffer only needs to be allocated on the stack or when the
 * access to and lifetime of the buffer is well controlled and constrained.
 */
struct net_buf_simple {
    /** Pointer to the start of data in the buffer. */
    uint8_t *data;

    /**
     * Length of the data behind the data pointer.
     *
     * To determine the max length, use net_buf_simple_max_len(), not #size!
     */
    uint16_t len;

    /** Amount of data that net_buf_simple#__buf can store. */
    uint16_t size;

    /** Start of the data storage. Not to be accessed directly
     *  (the data pointer should be used instead).
     */
    uint8_t *__buf;
};

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_NET_BUF_H_ */
