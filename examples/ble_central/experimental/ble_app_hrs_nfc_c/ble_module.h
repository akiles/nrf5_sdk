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

#ifndef BLE_MODULE_H__
#define BLE_MODULE_H__

#include <stdbool.h>
#include "sdk_errors.h"
#include "ble.h"
#include "softdevice_handler.h"
#include "ble_gap.h"

/**@brief Variable length data encapsulation in terms of length and pointer to data. */
typedef struct
{
    uint8_t * p_data;   /**< Pointer to data. */
    uint16_t  data_len; /**< Length of data. */
} data_t;

/**@brief Terminates connection with BLE peripheral device. 
 */
void ble_disconnect(void);

/**@brief Function for handling the advertising report BLE event.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
void on_adv_report(const ble_evt_t * const p_ble_evt);

/**@brief Function for handling BLE Stack events concerning central applications.
 *
 * @details This function keeps the connection handles of central applications up-to-date. It
 * parses scanning reports, initiating a connection attempt to peripherals when a target UUID
 * is found, and manages connection parameter update requests. Additionally, it updates the status
 * of LEDs used to report central applications activity.
 *
 * @note Since this function updates connection handles, @ref BLE_GAP_EVT_DISCONNECTED events
 *       should be dispatched to the target application before invoking this function.
 *
 * @param[in] p_ble_evt Bluetooth stack event.
 */
void on_ble_evt(const ble_evt_t * const p_ble_evt);

/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupts.
 */
void ble_stack_init(void);

/**@brief Function to start scanning.
 */
void scan_start(void);

/**@brief Returns connection state.
 */
bool ble_is_connected(void);

/**@breif Returns connection handle.
 */
uint16_t ble_get_conn_handle(void);

#endif // BLE_MODULE_H__
