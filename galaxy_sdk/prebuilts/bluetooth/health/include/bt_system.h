/**
 * Copyright (C) 2022 VeriSilicon Holdings Co., Ltd.
 *
 * @file bt_system.h
 * @brief bt module management
 * @author Hao Zhang <hao.zhang@verisilicon.com>
 */

#ifndef _BT_SYSTEM_H_
#define _BT_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief BT time window manager callback structure.
 *
 *  This structure is used for tracking the state of BT controller
 *  It is registered with the help of the bt_twm_cb_register() API.
 *  If a window manager  is not of interest for an instance, it may be set to NULL
 *  and will as a consequence not be used for that instance.
 */
struct bt_twm_cb {
    /** @brief A connection event ended.
     *
     *  This callback notifies the application of a connection event has ended.
     *  Application can use the idle period for power consumption operating.
     *
     *  @param state Connection state. Not used now.
     *  @param next_itv Interval from when this function is called to the next
     *  connection event.
     */
    void (*start_idle)(unsigned int state, unsigned int next_itv);
};

/** @brief BT sub system initilazation
 *
 *  Initialize bluetooth controller and host.
 *
 *  @param arg Reserve for future.
 */
extern void bt_subsys_start(void *arg);

/** @brief Register BT time window callbacks.
 *
 *  Initialize bluetooth controller and host.
 *
 *  @param arg Reserve for future.
 */
extern void bt_twm_register(struct bt_twm_cb *callbacks);

#ifdef __cplusplus
}
#endif

#endif /* _BT_SYSTEM_H_*/
