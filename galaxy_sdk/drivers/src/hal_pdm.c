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

#include <string.h>
#include "vsd_error.h"
#include "hal_pdm.h"
#include "bsp_common.h"

static PdmDevice *g_pdm_dev[PDM_PORT_MAX] = {NULL};

static inline PdmOperation *get_ops(const PdmDevice *pdm)
{
    return (PdmOperation *)pdm->ops;
}

int hal_pdm_add_dev(PdmDevice *pdm)
{
    int ret   = VSD_ERR_FULL;
    uint8_t i = 0;

    for (i = 0; i < ARRAY_SIZE(g_pdm_dev); i++) {
        if (g_pdm_dev[i] == NULL) {
            g_pdm_dev[i] = pdm;
            ret          = VSD_SUCCESS;
            break;
        }
    }

    return ret;
}

int hal_pdm_remove_dev(PdmDevice *pdm)
{
    int ret   = VSD_ERR_NON_EXIST;
    uint8_t i = 0;

    for (i = 0; i < ARRAY_SIZE(g_pdm_dev); i++) {
        if (g_pdm_dev[i] == pdm) {
            g_pdm_dev[i] = NULL;
            ret          = VSD_SUCCESS;
            break;
        }
    }

    return ret;
}

PdmDevice *hal_pdm_get_device(uint8_t dev_id)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(g_pdm_dev); i++) {
        if (g_pdm_dev[i] && g_pdm_dev[i]->hw_config && g_pdm_dev[i]->hw_config->id == dev_id)
            return g_pdm_dev[i];
    }

    return NULL;
}

int hal_pdm_init(const PdmDevice *pdm)
{
    if (get_ops(pdm)->init)
        return get_ops(pdm)->init(pdm);

    return VSD_SUCCESS;
}

int hal_pdm_start(const PdmDevice *pdm, PdmSubstream *stream)
{
    if (get_ops(pdm)->start)
        return get_ops(pdm)->start(pdm, stream);

    return VSD_SUCCESS;
}

void hal_pdm_stop(const PdmDevice *pdm, PdmSubstream *stream)
{
    if (get_ops(pdm)->stop)
        get_ops(pdm)->stop(pdm, stream);
}

int hal_pdm_set_gain(const PdmDevice *pdm, int gain)
{
    if (get_ops(pdm)->set_gain)
        get_ops(pdm)->set_gain(pdm, gain);

    return VSD_SUCCESS;
}

int hal_pdm_finalize(const PdmDevice *pdm)
{
    if (get_ops(pdm)->deinit)
        get_ops(pdm)->deinit(pdm);

    return VSD_SUCCESS;
}

DRV_ISR_SECTION
void hal_pdm_irq_handler(const PdmDevice *pdm)
{
    if (!pdm || !get_ops(pdm)->irq_handler)
        return;

    get_ops(pdm)->irq_handler(pdm);
}
