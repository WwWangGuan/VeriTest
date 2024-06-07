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

#ifndef HAL_DMAC_H
#define HAL_DMAC_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DMAC
 *  DMAC HAL API and definition
 *  @ingroup HAL
 *  Hardware Abstraction Layer
 *  @{
 */

#include "stdint.h"
#include "stdbool.h"
#include "hal_common.h"

#define DMAC_INVALID_MUX_ID 0xff

/**
 * @brief ID definition of DMAC interface
 */
typedef enum DmacIdDef {
    DMAC_ID_0,
    DMAC_ID_1,
    DMAC_ID_MAX,
} DmacIdDef;

/**
 * @brief DMAC Peripheral type
 */
typedef enum DmacDevType {
    DMA_PERI_NON_MEM,
    DMA_PERI_MEM,
    DMA_I2S,
    DMA_I2C,
    DMA_I3C,
    DMA_FLASH,
    DMA_QSPI,
    DMA_UART,
    DMA_SPI,
    DMA_ADC,
    DMA_DAC,
    DMA_PDM,
    DMA_PERI_INVALID,
} DmacDevType;

/**
 * @brief DMAC transfer direction
 */
typedef enum DmacTransDir {
    DMA_MEM_TO_MEM,
    DMA_MEM_TO_DEV,
    DMA_DEV_TO_MEM,
    DMA_DEV_TO_DEV,
    DMA_TRANS_NONE,
} DmacTransDir;

/**
 * @brief Transfer Direction and Flow Control Type
 */
typedef enum DmacTransDirAndFc {
    TT_M2M_FC_DMA,   /**< M2M,DW_ahb_dmac is FC */
    TT_M2P_FC_DMA,   /**< M2P,DW_ahb_dmac is FC */
    TT_P2M_FC_DMA,   /**< P2M,DW_ahb_dmac is FC*/
    TT_P2P_FC_DMA,   /**< P2P,DW_ahb_dmac is FC*/
    TT_P2M_FC_PERP,  /**< P2M,Peripheral is FC */
    TT_P2P_FC_SPERP, /**< P2P,Source peripheral is FC */
    TT_M2P_FC_PERP,  /**< M2P,Peripheral is FC */
    TT_P2P_FC_DPERP, /**< P2P,Destination peripheral is FC */
} DmacTransDirAndFc;

/**
 * @brief Source&Destination address increment type
 */
typedef enum DmacAddrIncType {
    DMA_ADDR_INC,
    DMA_ADDR_DEC,
    DMA_ADDR_FIX,
} DmacAddrIncType;

/**
 * @brief Source&Destination Burst Transaction Length
 */
typedef enum DmacTransMaxsize {
    DMA_MSIZE_1_TRANS,
    DMA_MSIZE_4_TRANS,
    DMA_MSIZE_8_TRANS,
    DMA_MSIZE_16_TRANS,
    DMA_MSIZE_32_TRANS,
    DMA_MSIZE_64_TRANS,
    DMA_MSIZE_128_TRANS,
    DMA_MSIZE_256_TRANS,
} DmacTransMaxsize;

/**
 * @brief Flow Control Mode. Determines when source transaction
 * requests are serviced when the Destination Peripheral is the
 * flow controller
 */
typedef enum DmacFCMode {
    FCMODE_EN,
    FCMODE_DIS,
} DmacFCMode;

/**
 * @brief Channel priority: 7 is the highest priority, and 0
 * is the lowest
 */
typedef enum DmacChannelPriority {
    DMA_PRIORITY_0,
    DMA_PRIORITY_1,
    DMA_PRIORITY_2,
    DMA_PRIORITY_3,
    DMA_PRIORITY_4,
    DMA_PRIORITY_5,
    DMA_PRIORITY_6,
    DMA_PRIORITY_7,
    DMA_PRIORITY_DEFAULT = DMA_PRIORITY_4,
} DmacChannelPriority;

/**
 * @brief Interrupt Enable: 0:Disable; 1:Enable
 */
typedef enum DmacIntEnable {
    DMA_INTERRUPT_DISABLE,
    DMA_INTERRUPT_ENABLE,
} DmacIntEnable;

/**
 * @brief Link-List Transfer Enable: 0:Disable; 1:Enable
 */
typedef enum DmacLliEnable {
    DMA_LLI_DISABLE,
    DMA_LLI_ENABLE,
} DmacLliEnable;

/**
 * @brief Dynamic mode or fixed mode of channel allocate
 */
typedef enum ChnResourceMode {
    CH_FIXED_MODE,   /**< The channel resource type is fixed */
    CH_DYNAMIC_MODE, /**< The channel resource type is dynamic */
} ChnResourceMode;

/**
 * @brief Structure of DMAC channel src&dst device type
 */
typedef struct DmacChnType {
    uint8_t src; /**< Type of the source peripheral */
    uint8_t dst; /**< Type of the dst peripheral */
} DmacChnType;

/**
 * @brief Structure of DMAC channel status
 */
typedef struct DmacChnMap {
    DmacChnType type; /**< type of DMA channel,@see DmacChnType */
    uint8_t ch_id;    /**< Channel id */
    bool using;       /**< Status of channel */
} DmacChnMap;

/**
 * @brief Structure of describe DMAC control register for channel x
 */
typedef struct DmacCtlReg {
    /**
     * chn_intr: 0 disable dmac interrupt, 1 enable dmac interrupt
     */
    uint32_t chn_intr : 1;

    /**
     * Source or destination peripherals transfer width
     * Generally, we assign separately src_xfer_width and dst_xfer_width with the width of
     * peripherals FIFO
     */
    uint32_t dst_xfer_width : 3;
    uint32_t src_xfer_width : 3;

    /**
     * The change way of source or destination address, after every source or destination transfer
     * 00 = Increment; 01 = Decrement; 1x = No change
     */
    uint32_t dinc : 2;
    uint32_t sinc : 2;

    /**
     * Source or destination Burst Transaction Length, instead of AHB burst transfer length
     * it's meaning that Number of data items, each of width src_xfer_width or dst_xfer_width (NOT
     * BYTE NUMBER), to be read/write from/to the source/destination every time a source burst
     * transaction
     */
    uint32_t dst_msize : 3;
    uint32_t src_msize : 3;

    /**
     * Source gather enable:Scatter on the destination side is applicable only when the CTLx.DINC
     * bit indicates an incrementing or decrementing address control
     */
    uint32_t src_gth_en : 1;

    /**
     * Destination scatter enable:Gather on the source side is applicable only when the CTLx.SINC
     * bit indicates an incrementing or decrementing address control
     */
    uint32_t dst_sct_en : 1;

    /**
     * Transfer type and flow controller for this transfer. Value @see DmacTransDirAndFc
     */
    uint32_t tt_fc : 3;

    /**
     * Destination/Source Master Select. Identifies the Master Interface layer where the destination
     * device (peripheral or memory) resides
     * 00 = AHB master 1; 01 = AHB master 2; 10 = AHB master 3; 11 = AHB master 4
     */
    uint32_t dms : 2;
    uint32_t sms : 2;

    /**
     * Configure items of linked list multi-blocks transfer
     * you can separately enable blocking chaining either source or destination side by assigning
     * with llp_src_en and llp_dst_en
     * 1: enable    0: disable
     */
    uint32_t llp_dst_en : 1;
    uint32_t llp_src_en : 1;
} DmacCtlReg;

/**
 * @brief Structure of describe DMAC configuration register for channel x
 */
typedef struct DmacCfgReg {
    /**
     * Which priority level(0~7) do you want to assign to channel
     * A priority of 7 is the highest priority, and 0 is the lowest
     */
    uint32_t prio : 5;

    /**
     * Whether enable auto-reload multi-blocks transfer
     * 0 = disable     1 = enable
     */
    uint32_t src_auto_reload : 1;
    uint32_t dst_auto_reload : 1;

    /**
     * Flow Control Mode
     * Determines when source transaction requests are serviced when
     * the Destination Peripheral is the flow controller
     * for snps dmac, flow controller is always DW_ahb_dmac
     * 0x0 (FCMODE_0): Data pre-fetching is enabled(default)
     * 0x1 (FCMODE_1): Data pre-fetching is disabled
     */
    uint32_t fc_mode : 1;

    /**
     * Handshake signal id. Only used when peripherals are non-memory
     */
    uint32_t src_hs_id : 12;
    uint32_t dst_hs_id : 12;
} DmacCfgReg;

/**
 * @brief Structure of DMAC Channel_x Registers params
 * @note:
 *	In general, configuring the following items, then you can using DMA
 *		correctly. if you don't know what's means of other parameters,
 *		please leave them alone
 */
typedef struct DmacXferCfg {
    /**
     * chn_id will be assigned as the same with the handshake id, refer to the DmacHandShakeId
     * NOTE: channel number starts from 0,1...
     */
    uint16_t chn_id : 8;

    /**
     * Transfer direction for this transfer.@see DmacTransDir
     */
    uint16_t dir : 8;

    /**
     * How many bytes you want to transfer,be used to calculate block transfer size
     */
    uint32_t len;

    /**
     * Modify the mux of the selected channel
     */
    uint32_t mux_id;

    /**
     * Source or destination addresses
     * Note: corresponding to SARx & DARx Register
     */
    uint32_t src_addr;
    uint32_t dst_addr;

    /**
     * Channel control register for this transfer.@see DmacCtlReg
     */
    DmacCtlReg ctl_reg;

    /**
     * Channel config register for this transfer.@see DmacCfgReg
     */
    DmacCfgReg cfg_reg;

    /**
     * Configure items of linked list multi-blocks transfer. you can separately enable blocking
     * chaining either source or destination side by assigning with llp_src_en and llp_dst_en.
     * true(1): enable    false(0): disable
     * if you don't want to use linked list mode, please leave llpx = 0
     */
    void *llpx;

    /**
     * These parameters are used to config the gather feature of SNPS AHB DMAC. if you don't what
     * you are doing, please leave these arguments with 0. src_gth_cnt: Source contiguous transfer
     * count between successive gather boundaries. src_gth_intvl: interval of contiguous source
     * gather block. Note: corresponding to SGRx Register
     */
    uint16_t src_gth_cnt;
    uint16_t src_gth_intvl;

    /**
     * These parameters are used to config the scatter feature of SNPS AHB DMAC. if you don't what
     * you are doing, please leave these arguments with 0. dst_sct_cnt: Destination contiguous
     * transfer count between successive scatter boundaries. dst_sct_intvl: interval of contiguous
     * destination scatter block. Note: corresponding to DSRx Register
     */
    uint16_t dst_sct_cnt;
    uint16_t dst_sct_intvl;

    /**
     * Record the number of Linked list items of current transfer
     */
    uint32_t lli_num;

    /**
     * Limitation for CTLx.BLOCK_TS. Also, It limits channel scatter and gather count registers
     */
    uint32_t block_ts;

    /**
     * The trigger level of peripheral FIFO,src_msize and dst_msize be set according to it
     */
    uint32_t trigger_lvl;

    /**
     * Whether src/dst device type is memory or not
     * 0 = disable     1 = enable
     */
    bool src_is_mem;
    bool dst_is_mem;

    /**
     * Whether use cyclic mode when use link list
     * 0 = disable     1 = enable
     */
    bool is_cyclic;
} DmacXferCfg;

/**
 * @brief This structure is used contains parameters that must be initialized
 * for the transfer
 * @note:
 *  For src_addr and dst_addr which is memory type need to use
 *      non-cacheable RAM for the SoC who has no DLM
 * @note:
 *  If cyclic mode is used, ensure that each block size is at least 128 bytes
 *      in order for block interrupts to be normal
 */
typedef struct DmaInitCfg {
    DmacDevType src_type; /**< Source peripheral type */
    DmacDevType dst_type; /**< Destination peripheral type */
    uint16_t src_gth_cnt;
    uint16_t src_gth_intvl;
    uint16_t dst_sct_cnt;
    uint16_t dst_sct_intvl;
    uint32_t fifo_width; /**< Peripheral fifo width */
    /**
     * peripheral mux id, designed by soc,if direction is M2M,please use
     * macro DMAC_INVALID_MUX_ID
     */
    uint32_t mux_id;
    /**
     * the current transmission read/write times of each block which cannot
     * exceed max_blk_ts
     */
    uint32_t block_ts;
    uint32_t src_addr;    /**< The value of source address */
    uint32_t dst_addr;    /**< The value of destination address */
    uint32_t len;         /**< The length of transfer data */
    uint32_t trigger_lvl; /**< The trigger level of peripheral FIFO */
    bool is_cyclic;       /**< Use cyclic mode or not */
} DmaInitCfg;

/**
 * @brief This structure is used when creating Linked List Items,Linked List
 * Items — otherwise known as block descriptors
 */
typedef struct DmacLliItem {
    uint32_t sar;            /**< Source Address Register for Channel x */
    uint32_t dar;            /**< Destination Address Register for Channel x */
    struct DmacLliItem *llp; /**< Linked List Pointer Register for Channel x */
    uint32_t ctl_l;          /**< Control Register low bits for Channel x */
    uint32_t ctl_h;          /**< Control Register high bits for Channel x */
    uint32_t sstat;          /**< Source Status Register for Channel x */
    uint32_t dstat;          /**< Destination Status Register for Channel x */
} DmacLliItem;

/**
 * @brief DMAC channel mux select
 */
typedef void (*DmaChMux)(uint16_t chn_id, uint16_t hs_id);

/**
 * @brief DMAC channel mux resume
 */
typedef void (*DmaChMuxResume)(uint16_t chn_id);

/**
 * @brief Structure of DMAC hardware configuration
 */
typedef struct DmacHwConfig {
    uint32_t resource_mode : 4;      /**< Channel alloc mode, @see ChnResourceMode */
    uint32_t id : 3;                 /**< Device ID of this DMAC device */
    uint32_t lli_en : 1;             /**< Enable link list transfer */
    uint32_t width_capability : 4;   /**< Support 8/16/32bits width transfer */
    uint32_t ch_sum : 4;             /**< Index how many channel the DMAC holds */
    uint32_t clk_id : 8;             /**< Clock ID of DMAC interfce */
    uint32_t intr_id : 8;            /**< The system interrupt NO. to corresponding DMAC */
    uint32_t base_addr;              /**< The base address of DMAC */
    DmaChMux dmac_ch_mux_cfg;        /**< DMAC channel mux select */
    DmaChMuxResume dmac_ch_mux_free; /**< DMAC channel mux free */
} DmacHwConfig;

/**
 * @brief Define DMAC controller driver
 */
typedef struct DmacDevice {
    uint16_t device_id;         /**< DMAC device id */
    const DmacHwConfig *hw_cfg; /**< DMAC hardware configuration */
    DmacChnMap *ch_map;         /**< The channel status info map */
    DmacXferCfg *xfer_cfg;      /**< The channel configuration */
    /**
     * Indicates the maximum number of read/write operations from the source or destination for one
     * block. Each read/write operation is (1 << xfer_width) bytes
     */
    uint32_t max_blk_ts;
    /**
     * Maximum value of burst transaction size that can be programmed
     */
    uint32_t max_msize;
    const void *ops; /**< DMAC operations */
    void *ctx;       /**< Private context */
} DmacDevice;

/**
 * @brief Callback function that is used to be called after each complete
 * block in cyclic mode or after a transfer is complete. This function is
 * designed as required, such as to post semaphore and free selected channels in
 * synchronous mode
 * @param param Can be instances of peripherals device or other types
 */
typedef void (*DmaXferCallback)(const void *param);

typedef struct DmaCbAndParam {
    /**
     * The callback for DMA transfer done for normal mode; Or the callback for DMA block transfer
     * done for cyclic mode
     */
    DmaXferCallback callback;
    /**
     * The parameter required in the callback which can be instances of peripherals device or other
     * types
     */
    const void *param;
} DmaCbAndParam;

/**
 * @brief Structure of operations for DMAC
 */
typedef struct DmacOperation {
    int (*chan_init)(const DmacDevice *device, DmacXferCfg **xfer_cfg, DmaInitCfg *init_cfg);
    int (*chan_start)(const DmacDevice *device, DmacXferCfg *xfer_cfg, DmaCbAndParam *xfer_cb);
    int (*chan_stop)(const DmacDevice *device, DmacXferCfg *xfer_cfg);
    void (*isr_handler)(const DmacDevice *device);
} DmacOperation;

/**
 * @brief Add the Dmac controller device
 * @param[in]  device the dmac device
 * @note A Dmac controller should be added before using
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_dmac_add_dev(DmacDevice *device);

/**
 * @brief Remove the Dmac device
 * @param[in]  device the dmac device
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_dmac_remove_dev(DmacDevice *device);

/**
 * @brief Get the Dmac device by the id
 * @param[in] device_id the dmac device id, @see dmacIdDef
 * @return  DmacDevice pointer: on success,  NULL : error
 */
DmacDevice *hal_dmac_get_device(uint8_t device_id);

/**
 * @brief Get a free channel and init channel registers
 * @param[in] device the Dmac device
 * @param[in] xfer_cfg channel configuration
 * @param[in] init_cfg The value of channel config, @see DmaInitCfg
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_dmac_chan_init(const DmacDevice *device, DmacXferCfg **xfer_cfg, DmaInitCfg *init_cfg);

/**
 * @brief Start the specific DMA channel
 * @param[in] device the Dmac device
 * @param[in] xfer_cfg  - channel configuration
 * @param[in] xfer_cb  DMA transfer callback and param, the param of
 * callback should be device instance of peripheral, NULL for M2M
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_dmac_chan_start(const DmacDevice *device, DmacXferCfg *xfer_cfg, DmaCbAndParam *xfer_cb);

/**
 * @brief Stop the specific DMA channel
 * @param[in] device the Dmac device
 * @param[in] xfer_cfg  - channel configuration
 * @return Return VSD_SUCCESS for succeed, others for failure
 */
int hal_dmac_chan_stop(const DmacDevice *device, DmacXferCfg *xfer_cfg);

/**
 * @brief DMA ISR handler
 * @param[in] device The dmac device instance
 */
void hal_dmac_isr_handler(const DmacDevice *device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_DMAC_H */
