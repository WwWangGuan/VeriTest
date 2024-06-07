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
#ifndef __C_EVENT_VPI_H__
#define __C_EVENT_VPI_H__

#include <inttypes.h>
#include "vs_conf.h"

/** @addtogroup EVENT_SYSTEM
 *  Event system
 *  @ingroup VPI
 *  @{
 */

/**
 * @brief Event handler definition
 * @param cobj The pointer of manager
 * @param event_id The event need to be handled
 * @param param The pointer of param for event
 */
typedef int (*EventHandler)(void *cobj, uint32_t event_id, void *param);

#define EVENT_OK    0  /**< Event OK */
#define EVENT_ERROR -1 /**< Event generic error code */

/**
 * @enum CobjId
 * @brief Predefined managers
 */
enum CobjId {
    COBJ_NULL = 0,
    COBJ_SYS_MGR,    /**< System manager */
    COBJ_BLE_MGR,    /**< BLE manager */
    COBJ_PWR_MGR,    /**< Power manager */
    COBJ_BAT_MGR,    /**< Battery manager */
    COBJ_SEN_MGR,    /**< Sensor manager */
    COBJ_OTA_MGR,    /**< OTA manager */
    COBJ_STG_MGR,    /**< Storage manager */
    COBJ_AUD_MGR,    /**< Audio manager */
    COBJ_IPC_MGR,    /**< IPC manager */
    COBJ_KEY_MGR,    /**< Key manager */
    COBJ_ALGO_MGR,   /**< Algorithm manager */
    COBJ_CUSTOM_MGR, /**< Custom manager */
};

/**
 * @enum EventId
 * @brief Predefined events
 */
enum EventId {
    EVENT_INVALID = 0,

    EVENT_BAT_LEVEL,           /**< Battery level event */
    EVENT_CHARGER_UPDATE,      /**< Charger update event */
    EVENT_BLE_TRAN_REQ,        /**< BLE transfer request event */
    EVENT_BLE_TRANSFERRED,     /**< BLE packet transferred event */
    EVENT_BLE_COMMON_TRAN_REQ, /**< BLE common transfer request */
    EVENT_BLE_MTU,             /**< BLE MTU change event */
    EVENT_AUD_PCM_DATA,        /**< Audio pcm data event */
    EVENT_AUD_ENC_DATA,        /**< Audio encoded data event */
    EVENT_IPC_MESSAGE,         /**< ipc message event */
    EVENT_CMD_UPDATE,          /**< Cmd update event */
    EVENT_KEY_INPUT,           /**< Key input event */
    EVENT_OTA_ACTION_REQ,      /**< OTA action request event */
    EVENT_PWR_MODE,            /**< Power mode event */
    EVENT_PWR_MODE_REQ,        /**< Power mode request event */
    EVENT_SEN_DATA_READY,      /**< Sensor data ready event */
    EVENT_SEN_COMMON,          /**< Common event for sensor */
    EVENT_SEN_SW_TIMEOUT,      /**< Sensor SW timer timeout event */
    EVENT_SEN_IMU_TAP,         /**< IMU tap event */
    EVENT_ALGO_SW_TIMEOUT,     /**< Algorithm SW timer timeout event */
    EVENT_ALGO_RES,            /**< Algorithm result data event */
    EVENT_SYS_PING,            /**< System ping event */
    EVENT_SYS_STATE_UPDATE,    /**< System state update event */
    EVENT_SYS_REBOOT_START,    /**< System reboot start event */
    EVENT_SYS_REBOOT_REQ,      /**< System reboot request event */
    EVENT_SYS_REBOOT_STATE,    /**< System reboot state event */
    EVENT_SYS_WOKE_UP,         /**< System wake up event */
    EVENT_USER_INFO,           /**< User info event */
    EVENT_USER_SEDENTARY_CFG,  /**< Sedentary config event */
    EVENT_USER_PPG_BP_HIS,     /**< PPG blood pressure history event */
    EVENT_USER_PPG_BP_CALIB,   /**< PPG blood pressure calibration event */
    EVENT_USER_PPG_BP_CALCU,   /**< PPG blood pressure calculation event */
    EVENT_SYS_TEST,            /**< System test event */
    EVENT_SDK_END,             /**< Last one on SDK side */
};
/**
 * @brief Get event name, easy for debug
 *
 * @param event_id Event id, @see EventId
 * @return event name
 */
char *vpi_get_event_name(uint32_t event_id);

/**
 * @brief Get manager name, easy for debug
 *
 * @param obj_id manager id, @see CobjId
 * @return manager name
 */
const char *vpi_get_manager_name(uint32_t obj_id);

/**
 * @brief Get manager ID
 *
 * @param manager manager pointer
 * @return manager ID
 */
uint32_t vpi_get_manager_id(void *manager);

/**
 * @brief Register listener to event.
 *
 * @param event_id Event id, @see EventId
 * @param listener Listener who wants to receive event.
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_register(uint32_t event_id, void *listener);

/**
 * @brief Unregister listener from event.
 *
 * @param event_id Event id, @see EventId
 * @param listener Listener who doesn't want to receive event.
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_unregister(uint32_t event_id, void *listener);

/**
 * @brief Notify all listeners the event
 *
 * @param event_id Event id, @see EventId
 * @param param Event parameter
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_notify(uint32_t event_id, void *param);

/**
 * @brief Notify all listeners the event in isr
 *
 * @param event_id Event id, @see EventId
 * @param param Event parameter
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_notify_from_isr(uint32_t event_id, void *param);

/**
 * @brief Create new event manager.
 *
 * @param manager_id manager ID, refer to @see CobjId for predefined managers
 * @param handler Event handler of manager.
 * @return Manager pointer
 */
void *vpi_event_new_manager(uint32_t manager_id, EventHandler handler);

/**
 * @brief Create new event manager group, group is in one task
 *
 * @return Group pointer
 */
void *vpi_event_new_group(void);

/**
 * @brief Add event manager to group
 *
 * @param manager Event manager
 * @param group Event manager group
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_add_to_group(void *manager, void *group);

/**
 * @brief Event Manager or event manager group start to listen to the event
 *
 * @param listener Event manager or event manager group
 * @return EVENT_OK on success, EVENT_ERROR when fail
 */
int vpi_event_listen(void *listener);

/** @} */

#endif
