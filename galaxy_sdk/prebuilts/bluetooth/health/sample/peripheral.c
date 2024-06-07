/*
 * Copyright (c) Verisilicon
 * SPDX-License-Identifier: Apache-2.0
 */
#include <vsbt_config.h>
#include <stddef.h>
#include <errno.h>

#include <bluetooth.h>
#include <conn.h>
#include <uuid.h>
#include <gatt.h>
#include <vs_util.h>

#include "FreeRTOS.h"
#include "task.h"

/** find implementation in bas.c */
int bt_bas_set_battery_level(uint8_t level);
uint8_t bt_bas_get_battery_level(void);

/** define print function here */

#define DEVICE_NAME     "vs peripheral sample"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define USE_PUBLIC_ADDR 1

// Default interval of Vega
#define BT_GAP_ADV_INT_MIN 0x0320 /* 500 ms   */
#define BT_GAP_ADV_INT_MAX 0x03C0 /* 600 ms   */

static struct bt_le_adv_param param = {
    .id                 = BT_ID_DEFAULT,
    .sid                = 0,
    .secondary_max_skip = 0,
    .options            = (BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_NAME),
    .interval_min       = (BT_GAP_ADV_FAST_INT_MIN_2),
    .interval_max       = (BT_GAP_ADV_FAST_INT_MAX_2),
    .peer               = NULL,
};

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR), BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),
    BT_DATA_BYTES(BT_DATA_SVC_DATA16, 0xaa, 0xfe, /* Eddystone UUID */
                  0x10,                           /* Eddystone-URL frame type */
                  0x00,                           /* Calibrated Tx power at 0m */
                  0x00,                           /* URL Scheme Prefix http://www. */
                  'z', 'e', 'p', 'h', 'y', 'r', 'p', 'r', 'o', 'j', 'e', 'c', 't', 0x08) /* .org */
};
/* Set Scan Response data */
static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

__unused static void beacon_start()
{
    char addr_s[BT_ADDR_LE_STR_LEN];
    bt_addr_le_t addr = {0};
    size_t count      = 1;
    int err;

    /* Start advertising */
    err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err) {
        printf("Advertising failed to start (err %d)\n", err);
        return;
    }

    /* For connectable advertising you would use
     * bt_le_oob_get_local().  For non-connectable non-identity
     * advertising an non-resolvable private address is used;
     * there is no API to retrieve that.
     */

    bt_id_get(&addr, &count);
    bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));

    printf("Beacon started, advertising as %s\n", addr_s);
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printf("Connection failed (err 0x%02x)\n", err);
    } else {
        printf("Connected\n");
    }

    bt_conn_le_data_len_update(conn, BT_LE_DATA_LEN_PARAM_MAX);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    printf("Disconnected (reason 0x%02x)\n", reason);
}

static struct bt_conn_cb conn_callbacks = {
    .connected    = connected,
    .disconnected = disconnected,
};

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
    printf("passkey %d\n", passkey);
}

static void auth_passkey_entry(struct bt_conn *conn)
{
    printf("request auth passkey entry");
}

static void auth_passkey_confirm(struct bt_conn *conn, unsigned int passkey)
{
    printf("passkey %d", passkey);
    bt_conn_auth_passkey_confirm(conn);
}

static void auth_cancel(struct bt_conn *conn)
{
    printf("auth canceled\n");
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
    printf("pairing completed %d\n", bonded);
}

static void auth_pair_failed(struct bt_conn *conn, enum bt_security_err reason)
{
    printf("pairing failed reason %d", reason);
}

static struct bt_conn_auth_cb auth_callbacks = {
    .cancel          = auth_cancel,
    .passkey_display = auth_passkey_display,
    .passkey_entry   = auth_passkey_entry,
    .passkey_confirm = auth_passkey_confirm,
};

__unused static struct bt_conn_auth_info_cb auth_cb_info = {
    .pairing_complete = pairing_complete,
    .pairing_failed   = auth_pair_failed,
};

static void adv_start(void)
{
    int err;

    err = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printf("Advertising failed to start (err %d)", err);
        return;
    }

    printf("Advertising successfully started");
}

void ble_app_start(void)
{
    int err;

    err = bt_enable(NULL);
    if (err) {
        printf("Bluetooth init failed (err %d)", err);
        return;
    }

#if USE_PUBLIC_ADDR
    /** Set user-specified public address */
    bt_addr_le_t pub_addr;
    bt_addr_le_from_str("07:07:06:06:06:06", "public", &pub_addr);
    err = bt_le_vs_hci_set_bd_addr(&pub_addr);
    param.options |= BT_LE_ADV_OPT_USE_IDENTITY;
#endif

    printf("Bluetooth initialized");

    bt_set_name("VSBT_Sample");

#if (CONFIG_VS_BT_SMP_LEGACY_PAIR_ONLY)
#else
    err = bt_conn_auth_cb_register(&auth_callbacks);
    if (err) {
        printf("Bluetooth auth register failed (err %d) %p ", err, &auth_callbacks);
        return;
    }
#endif

    adv_start();

    bt_conn_cb_register(&conn_callbacks);

    while (1) {
        static int lvl = 0;
        if (lvl > 100)
            lvl = 0;
        bt_bas_set_battery_level(lvl++);
        vTaskDelay(100);
    }
}
