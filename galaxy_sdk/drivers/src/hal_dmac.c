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

#include <stdlib.h>
#include <string.h>
#include "hal_dmac.h"
#include "vsd_error.h"

static DmacDevice *g_dmac_dev[DMAC_ID_MAX] = {NULL};

static inline DmacOperation *get_ops(const DmacDevice *device)
{
    return (DmacOperation *)device->ops;
}

int hal_dmac_add_dev(DmacDevice *device)
{
    int ret = VSD_ERR_FULL;
    uint8_t i;

    for (i = 0; i < sizeof(g_dmac_dev) / sizeof(g_dmac_dev[0]); i++) {
        if (g_dmac_dev[i] == NULL) {
            g_dmac_dev[i] = device;
            ret           = VSD_SUCCESS;
            break;
        }
    }
    return ret;
}

int hal_dmac_remove_dev(DmacDevice *device)
{
    int ret = VSD_ERR_NON_EXIST;
    uint8_t i;

    for (i = 0; i < sizeof(g_dmac_dev) / sizeof(g_dmac_dev[0]); i++) {
        if (g_dmac_dev[i] == device) {
            g_dmac_dev[i] = NULL;
            ret           = VSD_SUCCESS;
            break;
        }
    }
    return ret;
}

DmacDevice *hal_dmac_get_device(uint8_t device_id)
{
    DmacDevice *dmac = NULL;
    uint8_t i;

    for (i = 0; i < sizeof(g_dmac_dev) / sizeof(g_dmac_dev[0]); i++) {
        if (g_dmac_dev[i] && (g_dmac_dev[i]->device_id == device_id)) {
            dmac = g_dmac_dev[i];
            break;
        }
    }
    return dmac;
}

int hal_dmac_chan_init(const DmacDevice *device, DmacXferCfg **xfer_cfg, DmaInitCfg *init_cfg)
{
    if (!device || !init_cfg) {
        return VSD_ERR_INVALID_POINTER;
    }

    if (!get_ops(device)->chan_init) {
        return VSD_ERR_UNSUPPORTED;
    }
    return (get_ops(device)->chan_init(device, xfer_cfg, init_cfg));
}

int hal_dmac_chan_start(const DmacDevice *device, DmacXferCfg *xfer_cfg, DmaCbAndParam *xfer_cb)
{
    if (!device || !xfer_cfg) {
        return VSD_ERR_INVALID_POINTER;
    }

    if (!get_ops(device)->chan_start) {
        return VSD_ERR_UNSUPPORTED;
    }
    return (get_ops(device)->chan_start(device, xfer_cfg, xfer_cb));
}

int hal_dmac_chan_stop(const DmacDevice *device, DmacXferCfg *xfer_cfg)
{
    if (!device || !xfer_cfg) {
        return VSD_ERR_INVALID_POINTER;
    }

    if (!get_ops(device)->chan_stop) {
        return VSD_ERR_UNSUPPORTED;
    }
    return (get_ops(device)->chan_stop(device, xfer_cfg));
}

DRV_ISR_SECTION
void hal_dmac_isr_handler(const DmacDevice *device)
{
    if (!device || !get_ops(device)->isr_handler) {
        return;
    }
    return get_ops(device)->isr_handler(device);
}
