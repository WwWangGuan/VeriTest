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

#ifndef __OSAL_HEAP_H__
#define __OSAL_HEAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
#include "osal_adapter.h"
#include "vs_conf.h"

#if CONFIG_APP_SOC_QEMU
void osal_memset(char *buf, char byte, int len);
#else
#define osal_memset memset
#endif

/** @addtogroup HEAP
 *  OSAL Heap API
 *  @ingroup OSAL
 *  @{
 */

/**
 * @brief Allocate memory
 * @note Allocate cacheable memory for CPU which supports caching; Allocate
 * non-cacheable memory for CPU which does not support caching.
 *
 * @param len Memory size
 * @return void* Pointer of memory block, NULL for failure
 */
void *osal_malloc(size_t len);

/**
 * @brief Free the memory
 *
 * @note Free cacheable memory for CPU which supports caching; Free
 * non-cacheable memory for CPU which does not support caching.
 * @param pmem Pointer of memory block
 */
void osal_free(void *pmem);

/**
 * @brief Allocate non-cacheable memory
 * @param len Memory size
 * @return void* Pointer of memory block, NULL for failure
 */
void *osal_malloc_noncache(size_t len);

/**
 * @brief Free the non-cacheable memory
 * @param pmem Pointer of memory block
 */
void osal_free_noncache(void *pmem);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OSAL_HEAP_H__ */
