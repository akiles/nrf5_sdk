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

#ifndef NFC_BLE_PAIR_LIB_H__
#define NFC_BLE_PAIR_LIB_H__

#include <stdbool.h>
#include "sdk_errors.h"
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @addtogroup nfc_api
 *
 * @defgroup nfc_ble_pair_lib NFC BLE Pairing Lib
 * @ingroup  nfc_api
 * @brief    @tagAPI52 High level library for BLE Connection Handover pairing using NFC.
 * @{
 */

/**
 * @brief NFC pairing types
 */
typedef enum {
    NFC_PAIRING_MODE_JUST_WORKS,        /**< Legacy Just Works pairing without security key */
    NFC_PAIRING_MODE_OOB,               /**< Legacy OOB pairing with Temporary Key shared through NFC tag data */
    NFC_PAIRING_MODE_LESC_JUST_WORKS,   /**< LESC pairing without authentication data */
    NFC_PAIRING_MODE_LESC_OOB,          /**< LESC pairing with OOB authentication data */
    NFC_PAIRING_MODE_CNT                /**< Number of available pairing modes */
} nfc_pairing_mode_t;

/**
 * @brief Initializes NFC tag data and turns on tag emulation.
 * 
 * @warning It is assumed that Peer Manager has already been initialized before calling this function.
 *          It is also assumed that BLE advertising has already been initialized and it is configured
 *          to run in the BLE_ADV_MODE_FAST mode.
 *
 * @note    This library also controls BLE advertising, so @ref ble_advertising_on_ble_evt should not
 *          be called on BLE events.
 *
 * @param[in] mode                  Pairing mode, this is value of the @ref nfc_pairing_mode_t enum.
 *
 * @retval NRF_SUCCESS              If NFC has been initialized properly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval Other                    Other error codes might be returned depending on used modules.                              
 */
ret_code_t nfc_ble_pair_init(nfc_pairing_mode_t mode);

/**
 * @brief Sets pairing data and BLE security mode.
 *
 * @param[in] mode                  New pairing mode, this is value of the @ref nfc_pairing_mode_t enum.
 *
 * @retval NRF_SUCCESS              If new pairing mode has been set correctly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval Other                    Other error codes might be returned depending on used modules.                              
 */
ret_code_t nfc_ble_pair_mode_set(nfc_pairing_mode_t mode);

/**
 * @brief Funtion to obtain current pairing mode.
 *
 * @return Current pairing mode.
 */
nfc_pairing_mode_t nfc_ble_pair_mode_get(void);

/**
 * @brief NFC pairing BLE events handler
 *
 * @details Handles BLE authorization events, replying with OOB data.
 *
 * @note    This function should be called inside BLE event dispatcher as it response to the
 *          @ref BLE_GAP_EVT_AUTH_KEY_REQUEST and @ref BLE_GAP_EVT_LESC_DHKEY_REQUEST events.
 *          It also manages BLE advertising module based on @ref BLE_GAP_EVT_CONNECTED and
 *          @ref BLE_GAP_EVT_DISCONNECTED events.
 *
 * @param[in] p_ble_evt Bluetooth stack event.
 */
void on_nfc_ble_pair_evt(const ble_evt_t * const p_ble_evt);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_BLE_PAIR_LIB_H__
