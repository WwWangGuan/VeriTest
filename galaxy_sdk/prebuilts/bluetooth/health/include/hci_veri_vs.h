/* hci_veri_vs.h - Bluetooth Host Control Interface Vendor Specific definitions */

/*
 * Copyright (C) 2023 VeriSilicon Holdings Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef VERISILICON_INCLUDE_BLUETOOTH_HCI_VS_H_
#define VERISILICON_INCLUDE_BLUETOOTH_HCI_VS_H_

#include <hci.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BT_VS_CMD_BIT_SET_TX_POWER                  0
#define BT_VS_CMD_BIT_GET_TX_POWER                  1
#define BT_VS_CMD_BIT_SET_CODED_SELECT              2
#define BT_VS_CMD_BIT_TEST_TX_START                 4
#define BT_VS_CMD_BIT_TEST_RX_START                 5
#define BT_VS_CMD_BIT_TEST_END                      6
#define BT_VS_CMD_BIT_SET_BD_ADDR                   7
#define BT_VS_CMD_BIT_GET_BD_ADDR                   8
#define BT_VS_CMD_BIT_GET_RANDOM_VALUE              9
#define BT_VS_CMD_BIT_WRITE_SCAN_CH_MAP            10
#define BT_VS_CMD_BIT_READ_SCAN_CH_MAP             11


#define BT_HCI_VS_TX_POWER_LEVEL_HIGH           0x00
#define BT_HCI_VS_TX_POWER_LEVEL_MID            0x01
#define BT_HCI_VS_TX_POWER_LEVEL_LOW            0x02
#define BT_HCI_OP_VS_SET_TX_POWER				BT_OP(BT_OGF_VS, 0x0201)
struct bt_hci_cp_vs_set_tx_power {
	uint16_t conn_handle;
	uint8_t  tx_power_level;
} __packed;

struct bt_hci_rp_vs_set_tx_power {
    uint8_t  status;
	uint16_t conn_handle;
	int8_t   tx_power;
} __packed;

#define BT_HCI_OP_VS_GET_TX_POWER				BT_OP(BT_OGF_VS, 0x0202)
struct bt_hci_cp_vs_get_tx_power {
	uint16_t conn_handle;
} __packed;

struct bt_hci_rp_vs_get_tx_power {
	uint8_t  status;
	uint16_t conn_handle;
    int8_t   current_tx_power;
    int8_t   max_tx_power;
} __packed;

#define BT_HCI_VS_PRI_CHAN_CODED_S2             BTBIT(0)
#define BT_HCI_VS_SEC_CHAN_CODED_S2             BTBIT(1)
#define BT_HCI_VS_DATA_CHAN_CODED_S2            BTBIT(2)
#define BT_HCI_OP_VS_SET_CODED_SELECT			BT_OP(BT_OGF_VS, 0x0203)
struct bt_hci_cp_vs_set_coded_select {
	uint8_t coding_scheme;
} __packed;

struct bt_hci_rp_vs_set_coded_select {
	uint8_t  status;
} __packed;

#define BT_HCI_VS_RF_POWER_OFF                  0x00
#define BT_HCI_VS_RF_POWER_ON                   0x01

#define BT_HCI_VS_RF_PARAM_NOT_CHANGE           0x00
#define BT_HCI_VS_RF_PARAM_CHANGE               0x01

#define BT_HCI_VS_SLOW_CLOCK_EXTERNAL           BTBIT(0)
/* this bit set frequence low means 16.384kHz, otherwise high means 32.768kHz */
#define BT_HCI_VS_SLOW_CLOCK_FREQUENCE_LOW      BTBIT(1)
/* this bit set means p205, otherwise means p109 */
#define BT_HCI_VS_SLOW_CLOCK_P205               BTBIT(2)
/* there are divisions of each level
   Level 0 means 251-500 ppm, Level 1 means 151-250 ppm
   Level 2 means 101-150 ppm, Level 3 means  75-100 ppm
   Level 4 means  51-75  ppm, Level 5 means  31-500 ppm
   Level 6 means  21-30  ppm, Level 7 means   0-20  ppm */
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L0        0x00
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L1        0x10
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L2        0x20
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L3        0x30
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L4        0x40
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L5        0x50
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L6        0x60
#define BT_HCI_VS_SLOW_CLOCK_ACCURACY_L7        0x70

#define BT_HCI_VS_TX_POWER_HIGH                 0x00
#define BT_HCI_VS_TX_POWER_MIDDLE               0x01
#define BT_HCI_VS_TX_POWER_LOW                  0x02

/* this bit set means use DC-DC converter , otherwise means use LDO */
#define BT_HCI_VS_RF_POWER_DC_DC_CONV           BTBIT(0)
/* this bit set means max tx power as 4 dBm , otherwise means 0 dBm */
#define BT_HCI_VS_MAX_TX_POWER_AS_4             BTBIT(1)
#define BT_HCI_OP_VS_SET_RF_CONTROL			    BT_OP(BT_OGF_VS, 0x0204)
struct bt_hci_cp_vs_set_rf_control {
	uint8_t rf_power;
	uint8_t option;
	uint8_t clval;
	uint8_t slow_clock;
	uint8_t tx_power_level;
	uint8_t rf_option;
} __packed;

struct bt_hci_rp_vs_set_rf_control {
	uint8_t  status;
} __packed;

#define BT_HCI_VS_CHANNEL(n)                    ((n) - 2402) / 2

#define BT_HCI_VS_PAYLOAD_PRBS9                 0x00
#define BT_HCI_VS_PAYLOAD_REPEATE_11110000      0x01
#define BT_HCI_VS_PAYLOAD_REPEATE_10101010      0x02
#define BT_HCI_VS_PAYLOAD_PRBS15                0x03
#define BT_HCI_VS_PAYLOAD_REPEATE_11111111      0x04
#define BT_HCI_VS_PAYLOAD_REPEATE_00000000      0x05
#define BT_HCI_VS_PAYLOAD_REPEATE_00001111      0x06
#define BT_HCI_VS_PAYLOAD_REPEATE_01010101      0x07

#define BT_HCI_VS_TX_LE_PHY_1M                  0x01
#define BT_HCI_VS_TX_LE_PHY_2M                  0x02
#define BT_HCI_VS_TX_LE_PHY_CODED_S8            0x03
#define BT_HCI_VS_TX_LE_PHY_CODED_S2            0x04

#define BT_HCI_VS_TEST_TX_OPTION_NON_MODUL      BTBIT(0)
#define BT_HCI_VS_TEST_TX_OPTION_CONT_TX        BTBIT(1)
#define BT_HCI_OP_VS_TEST_TX_START              BT_OP(BT_OGF_VS, 0x0205)
struct bt_hci_cp_vs_test_tx_start {
	uint8_t  channel;
    uint8_t  length;
    uint8_t  payload;
    uint8_t  phy;
    uint8_t  tx_power_level;
    uint8_t  option;
    uint16_t packet_num;														// original: pack_num
} __packed;

struct bt_hci_rp_vs_test_tx_start {
	uint8_t  status;
} __packed;

#define BT_HCI_VS_RX_LE_PHY_1M                  0x01
#define BT_HCI_VS_RX_LE_PHY_2M                  0x02
#define BT_HCI_VS_RX_LE_PHY_CODED               0x03
#define BT_HCI_OP_VS_TEST_RX_START              BT_OP(BT_OGF_VS, 0x0206)
struct bt_hci_cp_vs_test_rx_start {
	uint8_t  channel;
    uint8_t  phy;
} __packed;

struct bt_hci_rp_vs_test_rx_start {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_VS_TEST_END                   BT_OP(BT_OGF_VS, 0x0207)
struct bt_hci_rp_vs_test_end {
	uint8_t  status;
	uint16_t packet_num;														// pack_num
	uint16_t error_packet_num;													// error_pack_num
	int8_t   avg_rssi;
	int8_t   max_rssi;
	int8_t   min_rssi;
} __packed;

#define BT_HCI_VS_BD_ADDR_VOL_AREA              0x00
#define BT_HCI_VS_BD_ADDR_NONVOL_AREA           0x01

#define BT_HCI_VS_BD_ADDR_PUBLIC                0x00
#define BT_HCI_VS_BD_ADDR_RANDOM                0x01
#define BT_HCI_OP_VS_SET_BD_ADDR                BT_OP(BT_OGF_VS, 0x0208)
struct bt_hci_cp_vs_set_bd_addr {
	uint8_t  option;
	uint8_t  addr_type;
	uint8_t  addr_val[BT_ADDR_SIZE];
} __packed;

struct bt_hci_rp_vs_set_bd_addr {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_VS_GET_BD_ADDR                BT_OP(BT_OGF_VS, 0x0209)
struct bt_hci_cp_vs_get_bd_addr {
	uint8_t  option;
	uint8_t  addr_type;
} __packed;

struct bt_hci_rp_vs_get_bd_addr {
	uint8_t  status;
	uint8_t  option;
	uint8_t  addr_type;
	uint8_t  addr_val[BT_ADDR_SIZE];
} __packed;

#define BT_HCI_OP_VS_GET_RANDOM_NUM             BT_OP(BT_OGF_VS, 0x020a)
struct bt_hci_cp_vs_get_random_num {
	uint8_t  rand_size;
} __packed;

struct bt_hci_rp_vs_get_random_num {
	uint8_t  status;
	uint8_t  rand_size;
	uint8_t  p_rand[16];
} __packed;

#define BT_HCI_VS_CH_37_USED                    BTBIT(0)
#define BT_HCI_VS_CH_38_USED                    BTBIT(1)
#define BT_HCI_VS_CH_39_USED                    BTBIT(2)
#define BT_HCI_OP_VS_SET_SCAN_CH_MAP            BT_OP(BT_OGF_VS, 0x020b)
struct bt_hci_cp_vs_set_scan_ch_map {
	uint8_t  ch_map;
} __packed;

struct bt_hci_rp_vs_set_scan_ch_map {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_VS_GET_SCAN_CH_MAP            BT_OP(BT_OGF_VS, 0x020c)
struct bt_hci_rp_vs_get_scan_ch_map {
	uint8_t  status;
	uint8_t  ch_map;
} __packed;


/* Events */

struct bt_hci_evt_veri_vs {
	uint8_t  subevent;
} __packed;

#define BT_HCI_EVT_VS_LE_CONNECTION_TX_TERMINATE  0x80


/**
 * Test commands that defined in core spec but not defined by Zephyr
 */
#define BT_HCI_OP_LE_RECEIVER_TEST_V3											BT_OP(BT_OGF_LE, 0x004f)
#define BT_HCI_OP_LE_RECEIVER_TEST_V2											BT_OP(BT_OGF_LE, 0x0033)
#define BT_HCI_OP_LE_RECEIVER_TEST_V1											BT_OP(BT_OGF_LE, 0x001d)
struct bt_hci_cp_le_recv_test {
    uint8_t rx_ch;
    uint8_t phy;
    uint8_t mod_idx;
    uint8_t expect_cte_len;
    uint8_t expect_cte_type;
    uint8_t slot_duration;
    uint8_t switch_pattern_len;
    uint8_t ant_ids[0];
} __packed;

struct bt_hci_rp_le_recv_test {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_LE_TRANSMITTER_TEST_V4										BT_OP(BT_OGF_LE, 0x007b)
#define BT_HCI_OP_LE_TRANSMITTER_TEST_V3										BT_OP(BT_OGF_LE, 0x0050)
#define BT_HCI_OP_LE_TRANSMITTER_TEST_V2										BT_OP(BT_OGF_LE, 0x0034)
#define BT_HCI_OP_LE_TRANSMITTER_TEST_V1										BT_OP(BT_OGF_LE, 0x001e)
struct bt_hci_cp_le_trans_test_sub_param {
	uint8_t  tx_ch;
	uint8_t  test_data_len;
	uint8_t  packet_payload;
	uint8_t  phy;
	uint8_t  cte_len;
	uint8_t  cte_type;
	uint8_t  switch_pattern_len;
	uint8_t  ant_ids[0];
} __packed;

struct bt_hci_cp_le_trans_test {
	struct bt_hci_cp_le_trans_test_sub_param sub_param;
	int8_t tx_power_level;
} __packed;

struct bt_hci_rp_le_trans_test {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_LE_MODIFY_SLEEP_CLOCK_ACCURACY								BT_OP(BT_OGF_LE, 0x005f)
struct bt_hci_cp_le_modify_sleep_clk_accuracy {
	uint8_t  act;
} __packed;

struct bt_hci_rp_le_modify_sleep_clk_accuracy {
	uint8_t  status;
} __packed;

#define BT_HCI_OP_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL							BT_OP(BT_OGF_LE, 0x0077)
struct bt_hci_cp_le_read_remote_power_level {
	uint16_t conn_hdl;
	uint8_t  phy;
} __packed;

#define BT_HCI_OP_LE_SET_PATH_LOSS_REPORTING_PARAMETERS							BT_OP(BT_OGF_LE, 0x0078)
struct bt_hci_cp_le_set_path_loss_rpt_param {
	uint16_t conn_hdl;
	uint8_t  high_thr;
	uint8_t  high_hys;
	uint8_t  low_thr;
	uint8_t  low_hys;
	uint16_t min_time_spent;
} __packed;

struct bt_hci_rp_le_set_path_loss_rpt_param {
	uint8_t  status;
	uint16_t conn_hdl;
} __packed;

#define BT_HCI_OP_LE_SET_PATH_LOSS_REPORTING_ENABLE								BT_OP(BT_OGF_LE, 0x0079)
struct bt_hci_cp_le_set_path_loss_rpt_enable {
	uint16_t conn_hdl;
	uint8_t  enable;
} __packed;

struct bt_hci_rp_le_set_path_loss_rpt_enable {
	uint8_t  status;
	uint16_t conn_hdl;
} __packed;

#define BT_HCI_OP_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE						BT_OP(BT_OGF_LE, 0x007a)
struct bt_hci_cp_le_set_trans_power_rpt_enable {
	uint16_t conn_hdl;
	uint8_t  local_enable;
	uint8_t  remote_enable;
} __packed;

struct bt_hci_rp_le_set_trans_power_rpt_enable {
	uint8_t  status;
	uint16_t conn_hdl;
} __packed;

#define BT_HCI_OP_LE_SET_DATA_RELATED_ADDRESS_CHANGES							BT_OP(BT_OGF_LE, 0x007c)
struct bt_hci_cp_le_set_data_related_addr_change {
	uint8_t  adv_hdl;
	uint8_t  change_reason;
} __packed;

struct bt_hci_rp_le_set_data_related_addr_change {
	uint8_t  status;
} __packed;

#ifdef __cplusplus
}
#endif

#endif /* VERISILICON_INCLUDE_BLUETOOTH_HCI_VS_H_ */
