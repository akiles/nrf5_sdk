/* Copyright (c) 2016 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef NFC_PART_H__
#define NFC_PART_H__

#include <stdbool.h>
#include "ble_advdata.h"
#include "sdk_errors.h"
#include "ble_gap.h"

/**
 * @brief Function used for initializing NFC part of application.
 *
 * @param[in] callback   Function pointer used for disconnecting from BLE peer device.
 */
void nfc_init(void);

/**
 * @brief Function used for reading NFC Tag content.
 *
 * @details If NFC tag has been readen, device turns off NFC reader and initiate 
 *          BLE scanning to find and connect to the device which tag has been found.
 */
void nfc_tag_process(void);

/**
 * @brief Function used for checking if given BLE device address matches the one which
 *        was found in Connection Handover NDEF Message.
 *
 * @param[in] p_peer_addr   BLE device address to check.
 *
 * @retval    true        If the device address was matched.
 * @retval    false       Otherwise.
 */
bool nfc_oob_pairing_tag_match(ble_gap_addr_t const * const p_peer_addr);

/**
 * @brief Function used for notifying NFC part of application that the read Connection Handover
 *        NDEF Message is no longer valid.
 */
void nfc_oob_pairing_tag_invalidate(void);

/**
 * @brief Function used to turn on NFC reader and BLE pairing with peripheral device.
 */
void nfc_pair_start(void);

/**
 * @brief Function used to turn off NFC reader and BLE pairing with peripheral device.
 */
void nfc_pair_stop(void);

/**
 * @brief NFC pairing BLE events handler
 *
 * @details Handles authorization events, replying with OOB data
 *
 * @param[in] p_ble_evt Bluetooth stack event.
 */
void on_nfc_pair_evt(const ble_evt_t * const p_ble_evt);

#endif // NFC_PART_H__
