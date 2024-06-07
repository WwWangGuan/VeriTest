/** @file
 *  @brief Verisilicon utility interface
 */

/*
 * Copyright (C) 2023 VeriSilicon Holdings Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <addr.h>

struct bt_vs_set_rf_ctrl_param_t
{
    /**
     *  @brief RF power on/off.
     */
    uint8_t power;

    /**
     *  @brief This field indicates whether the parameters change in RF power on.
     */
    uint8_t option;

    /**
     *  @brief RF rapid clock frequency adjust value(OSC internal CL adjust).
     */
    uint8_t clval;

    /**
     *  @brief RF slow clock configurations.
     */
    uint8_t slow_clock;

    /**
     *  @brief Set tx power in power on.
     */
    uint8_t tx_power;

    /**
     *  @brief Set RF option.
     */
    uint8_t rf_option;
};

#if (CONFIG_VS_BLE_CTLR_V3)
/**
 * @brief Set BD Address
 *
 * Set BD Address, include public address or random address.
 *
 * Call the function provided by the controller directly.
 *
 * @param l_addr address to be set.
 *
 * @return Zero on success or (negative) error code otherwise.
 * @return -EINVAL address type is invalid. Valid range is 0x00 - 0x01.
 *                 or l_addr is NULL.
 */
int bt_le_vs_set_bd_addr(bt_addr_le_t * l_addr);
#endif

/**
 * @brief Set BD Address by VS HCI command
 *
 * Set BD Address, include public address or random address.
 *
 * @param l_addr address to be set.
 *
 * @return Zero on success or (negative) error code otherwise.
 * @return -ENOMEM No free buffer to send HCI command.
 * @return -EINVAL address type is invalid. Valid range is 0x00 - 0x01.
 *                 or l_addr is NULL.
 * @return -ECONNREFUSED When connectable advertising is requested and there
 *                       is already maximum number of connections established
 *                       in the controller.
 *                       This error code is only guaranteed when using Zephyr
 *                       controller, for other controllers code returned in
 *                       this case may be -EIO.
 */
int bt_le_vs_hci_set_bd_addr(bt_addr_le_t * l_addr);

/**
 * @brief Set RF control by VS HCI command
 *
 * This function performs power control on RF.
 *
 * @param p_rf_ctrl the rf control param.
 *
 * @return Zero on success or (negative) error code otherwise.
 * @return -ENOMEM No free buffer to send HCI command.
 * @return -EINVAL address type is invalid. Valid range is 0x00 - 0x01.
 *                 or l_addr is NULL.
 * @return -ECONNREFUSED When connectable advertising is requested and there
 *                       is already maximum number of connections established
 *                       in the controller.
 *                       This error code is only guaranteed when using Zephyr
 *                       controller, for other controllers code returned in
 *                       this case may be -EIO.
 */
int bt_le_vs_hci_set_rf_control(struct bt_vs_set_rf_ctrl_param_t * p_rf_ctrl);
