/**
 * Copyright (C) 2023 VeriSilicon Holdings Co., Ltd.
 *
 * @file ipc_core_sync.h
 * @brief Header of core sync definition
 */

#ifndef __IPC_CORE_SYNC_H__
#define __IPC_CORE_SYNC_H__

/**
 * @brief Core Sync callback function definition
 */
typedef int (*ipc_service_callback)(void);

/**
 * @brief IPC register callback function
 */
void ipc_register_callback(ipc_service_callback cb);

#endif
