/**
 * Copyright (C) 2020 VeriSilicon Holdings Co., Ltd.
 * All rights reserved.
 *
 * @file heap_4_noncache.h
 * @brief Manage non cacheable memory regions using the heap_4 scheme
 */

#ifndef __HEAP_4_NONCACHE_H__
#define __HEAP_4_NONCACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "mpu_wrappers.h"
#include "portable.h"

/**
 * @brief Gets the current state of the non cacheable heap
 * @param pxHeapStats Pointer to record heap state, @see HeapStats_t
 */
void vPortGetNonCacheHeapStats(HeapStats_t *pxHeapStats);

/**
 * @brief Allocate memory in the non cacheable heap region
 * @param xSize memory size
 * @return void* Pointer to the memory block
 */
void *pvPortMallocNonCache(size_t xSize) PRIVILEGED_FUNCTION;

/**
 * @brief Free memory in the non cacheable heap region
 * @param pv Pointer to the memory block
 */
void vPortFreeNonCache(void *pv) PRIVILEGED_FUNCTION;

/**
 * @brief Initialize the non cacheable memory block
 */
void vPortInitialiseNonCacheBlocks(void) PRIVILEGED_FUNCTION;

/**
 * @brief Get the total amount of non cacheable heap space that remains
 * unallocated when the function is called
 * @return size_t Unallocated heap size
 */
size_t xPortGetFreeNonCacheHeapSize(void) PRIVILEGED_FUNCTION;

/**
 * @brief Get the lowest amount of free non cacheable heap space that has
 * existed system the FreeRTOS application booted
 * @return size_t The lowest heap space size
 */
size_t xPortGetMinimumEverFreeNonCacheHeapSize(void) PRIVILEGED_FUNCTION;

#ifdef __cplusplus
}
#endif

#endif /* __HEAP_4_NONCACHE_H__ */
