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

#ifndef _VPI_ERROR_H_
#define _VPI_ERROR_H_

/** @addtogroup VPI
 *  VPI error API
 *  @{
 */

/** Error codes for VeriSilicon Platform Interface(VPI) */
typedef enum VpiError {
    VPI_ERR_DEFAULT = -2,   /**< Default error */
    VPI_ERR_GENERIC = -1,   /**< Generic Error */
    VPI_SUCCESS     = 0,    /**< Success */
    VPI_ERR_INVALID,        /**< Invalid input parameter */
    VPI_ERR_NOMEM,          /**< No memory error */
    VPI_ERR_FULL,           /**< Resource is full */
    VPI_ERR_EMPTY,          /**< Resource is empty */
    VPI_ERR_IO,             /**< IO error */
    VPI_ERR_BUSY,           /**< Device is busy */
    VPI_ERR_TIMEOUT,        /**< Timeout */
    VPI_ERR_NODEVICE,       /**< No device error */
    VPI_ERR_LOST_CON,       /**< Lost connection */
    VPI_ERR_NO_ACK,         /**< No ACK */
    VPI_ERR_NOT_READY,      /**< System or data is not ready */
    VPI_ERR_LACK,           /**< Not enough data */
    VPI_ERR_BAD_DATA,       /**< Bad data */
    VPI_ERR_EXCEPTION_DATA, /**< Exception data */
    VPI_ERR_FREE,           /**< Free error */
    VPI_ERR_LICENSE,        /**< SDK license error */
} VpiError;

/**
 * @brief convert vsd error code to vpi error code
 * @param vsd_err the vsd error code
 * @return vpi error code
 */
int vsd_to_vpi(int vsd_err);

/**
 * @brief print error message through vpi error code
 * @param vpi_err the vpi error code
 * @param s       message
 * @return VPI_SUCCESS
 */
int vpi_error_print(int vpi_err, const char *s);

/**
 * @brief convert vsa error code to vpi error code
 * @param vsa_err the vsa error code
 * @return vpi error code
 */
int vsa_to_vpi(int vsa_err);

/** @} */

#endif // _VPI_ERROR_H_
