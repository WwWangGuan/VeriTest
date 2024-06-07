/*
 * Copyright 2022 - 2023 Verisilicon
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _LE_AUDIO_H_
#define _LE_AUDIO_H_

#include <string.h>
#include <stdio.h>
#include <stdint.h>

enum le_audio_evt_type {
    LE_AUDIO_EVT_CONFIG_RECEIVED,
    LE_AUDIO_EVT_STREAMING,
    LE_AUDIO_EVT_NOT_STREAMING,
    LE_AUDIO_EVT_SYNC_LOST,
    LE_AUDIO_EVT_NO_VALID_CFG,
    LE_AUDIO_EVT_NUM_EVTS
};

struct le_audio_evt {
    enum le_audio_evt_type le_audio_evt_type;
};

/**
 * @brief Callback for receiving Bluetooth LE Audio data
 *
 * @param data		Pointer to received data
 * @param size		Size of received data
 * @param bad_frame	Indicating if the frame is a bad frame or not
 * @param sdu_ref	ISO timestamp
 */
typedef void (*le_audio_receive_cb)(const uint8_t *const data, size_t size, bool bad_frame,
                                    uint32_t sdu_ref);

struct le_audio_datasource_cb {
    /** @brief data source initialize callback
     *
     *  init callback is called whenever a data source is requested to created
     *
     *  @param[in] None
     *
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*init)(void);

    /** @brief read request callback
     *
     *  read callback is called when read request from le audio profile
     *
     *  @param[in]  buff    target buf for read out.
     *  @param[in]  len     request length.
     *  @param[out] count   read out count
     *  @param[in]  idx     stream idx.
     *
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*read)(uint8_t *buff, uint32_t len, uint32_t *count, uint8_t idx);

    /** @brief write request callback
     *
     *  write callback is called when write request from le audio profile
     *
     *  @param[in]  buff    source buf for write into file.
     *  @param[in]  len     request length.
     *  @param[out] count   write count
     *
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*write)(uint8_t *buff, uint32_t len, uint32_t count);

    /** @brief seek request callback
     *
     *  seek callback is called whenever seek is requested to
     *  be accessed from a file.
     *
     *  @param seek_offset    offset value.
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*seek)(size_t seek_offset);

    /** @brief open request callback
     *
     *  open is called whenever a file is requested to
     *  be opened for read/write.
     *
     *  @param filename file name.
     *
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*open)(const char *filename);

    /** @brief close request callback
     *
     *  close is called whenever a file requested to be closed
     *
     *  @param  None
     *  @return 0 in case of success or negative value in case of error.
     */
    int (*close)(void);
};

/** @brief Register data source callbacks.
 *
 *  Only one callback structure can be registered, and attempting to
 *  registering more than one will result in an error.
 *
 *  @param cb  data source callback structure.
 *
 *  @return 0 in case of success or negative value in case of error.
 */
int le_audio_datasource_register_cb(struct le_audio_datasource_cb *cb);

/** @brief Unregister data source callbacks.
 *
 *  May only unregister a callback structure that has previously been
 *  registered by le_audio_datasource_register_cb().
 *
 *  @param cb  data source callback structure.
 *
 *  @return 0 in case of success or negative value in case of error.
 */
int le_audio_datasource_unregister_cb(struct le_audio_datasource_cb *cb);
/**
 * @brief Callback for receiving Bluetooth LE Audio data.
 *
 * @param       data            Pointer to received data.
 * @param       size            Size of received data.
 * @param       bad_frame       Indicating if the frame is a bad frame or not.
 * @param       sdu_ref         ISO timestamp.
 * @param       channel_index   Audio channel index.
 */
typedef void (*le_audio_receive_new_cb)(const uint8_t *const data, size_t size, bool bad_frame,
                                        uint32_t sdu_ref, uint8_t channel_index,
                                        size_t desired_size);

/**
 * @brief       Encoded audio data and information.
 *
 * @note        Container for SW codec (typically LC3) compressed audio data.
 */
struct le_audio_encoded_audio {
    uint8_t const *const data;
    size_t size;
    uint8_t num_ch;
};

struct sdu_ref_msg {
    uint32_t timestamp;
    bool adjust;
};
/**
 * @brief Callback for using the timestamp of the previously sent audio packet
 *
 * @note  Can be used for drift calculation/compensation
 *
 * @param timestamp     The timestamp
 * @param adjust        Indicate if the sdu_ref should be used to adjust timing
 */
typedef void (*le_audio_timestamp_cb)(uint32_t timestamp, bool adjust);

enum le_audio_user_defined_action {
    LE_AUDIO_USER_DEFINED_ACTION_1,
    LE_AUDIO_USER_DEFINED_ACTION_2,
    LE_AUDIO_USER_DEFINED_ACTION_NUM
};

/**
 * @brief Encoded audio data and information.
 * Container for SW codec (typically LC3) compressed audio data.
 */
struct encoded_audio {
    uint8_t const *const data;
    size_t size;
    uint8_t num_ch;
};

/**
 * @brief Generic function for a user defined button press
 *
 * @param action	User defined action
 *
 * @return	0 for success,
 *		error otherwise
 */
int le_audio_user_defined_button_press(enum le_audio_user_defined_action action);

/**
 * @brief Get configuration for audio stream
 *
 * @param bitrate	Pointer to bitrate used
 * @param sampling_rate	Pointer to sampling rate used
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_config_get(uint32_t *bitrate, uint32_t *sampling_rate, uint32_t *pres_delay);

/**
 * @brief	Increase volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_up(void);

/**
 * @brief	Decrease volume by one step
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_down(void);

/**
 * @brief	Mute volume
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_volume_mute(void);

/**
 * @brief	Either resume or pause the Bluetooth LE Audio stream,
 *              depending on the current state of the stream
 *
 * @return	0 for success, error otherwise
 */
int le_audio_play_pause(void);

/**
 * @brief Send Bluetooth LE Audio data
 *
 * @param data	Data to send
 * @param size	Size of data to send
 *
 * @return	0 for success,
 *		-ENXIO if the feature is disabled,
 *		error otherwise
 */
int le_audio_send(uint8_t const *const data, size_t size);

/**
 * @brief Enable Bluetooth LE Audio
 *
 * @param recv_cb	Callback for receiving Bluetooth LE Audio data
 * @param timestmp_cb	Callback for using the timestamp
 *
 * @return		0 for success, error otherwise
 */
int le_audio_enable(le_audio_receive_cb recv_cb, le_audio_timestamp_cb timestmp_cb);
/**
 * @brief Disable Bluetooth LE Audio
 *
 * @return	0 for success, error otherwise
 */
int le_audio_disable(void);

/**
 * @brief Select input source for Bluetooth LE Audio
 *
 * @param datasource  data source handler for Bluetooth LE Audio input data
 *
 * @return		0 for success, error otherwise
 */
int le_audio_set_data_source();

#endif /* _LE_AUDIO_H_ */
