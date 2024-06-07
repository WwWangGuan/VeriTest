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

#ifndef _VSD_ERROR_H_
#define _VSD_ERROR_H_

/** @addtogroup DRIVER
 *  - Error code definition
 *
 *  @{
 */

/** Error codes for VeriSilicon Driver (VSD)*/
typedef enum VsdError {
    VSD_ERR_GENERIC         = -1, /**< Generic errors */
    VSD_SUCCESS             = 0,  /**< Success */
    VSD_ERR_NOT_INITIALIZED = 1,  /**< Required initialization not complete */
    VSD_ERR_INVALID_POINTER = 2,  /**< Pointer to invalid memory location */
    VSD_ERR_INVALID_PARAM   = 3,  /**< Invalid input parameter */
    VSD_ERR_INVALID_DATA    = 4,  /**< Invalid input data */
    VSD_ERR_INVALID_CHANNEL = 5,  /**< Selected channel does not exist */
    VSD_ERR_INVALID_STATE   = 6,  /**< API or command not valid now */
    VSD_ERR_UNSUPPORTED     = 7,  /**< unsupported by this API */
    VSD_ERR_IO              = 8,  /**< IO error */
    VSD_ERR_BUSY            = 9,  /**< Channel/peripheral is running/busy */
    VSD_ERR_NO_MEMORY       = 10, /**< No enough memory */
    VSD_ERR_FULL            = 11, /**< Hardware overflow/full */
    VSD_ERR_EMPTY           = 12, /**< Hardware underflow/empty */
    VSD_ERR_ABORTED         = 13, /**< An operation was aborted */
    VSD_ERR_TIMEOUT         = 14, /**< Timeout error */
    VSD_ERR_NON_EXIST       = 15, /**< Hardware non-exist */
    VSD_ERR_HW              = 16, /**< Hardware error */
    VSD_ERR_LICENSE         = 17, /**< SDK license error */
} VsdError;
/** @} */
#endif // _VSD_ERROR_H_
