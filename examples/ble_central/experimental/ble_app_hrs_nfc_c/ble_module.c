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
 
#include "ble_module.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "ble_conn_params.h"
#include "ble_conn_state.h"
#include "peer_manager.h"
#include "nfc_pair_module.h"
#include "boards.h"
#include "fds.h"
#include "fstorage.h"
#include "ble_db_discovery.h"
#include "ble_hrs_c.h"
#include "ble_bas_c.h"
#include "nfc_ble_oob_advdata_parser.h"

#define NRF_LOG_MODULE_NAME "BLE_MODULE"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#if (NRF_SD_BLE_API_VERSION == 3)
#define NRF_BLE_MAX_MTU_SIZE      GATT_MTU_SIZE_DEFAULT                 /**< MTU size used in the softdevice enabling and to reply to a BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST event. */
#endif

#define CENTRAL_LINK_COUNT        1                                     /**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT     0                                     /**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define MIN_CONNECTION_INTERVAL   MSEC_TO_UNITS(7.5, UNIT_1_25_MS)      /**< Determines minimum connection interval in milliseconds. */
#define MAX_CONNECTION_INTERVAL   MSEC_TO_UNITS(30, UNIT_1_25_MS)       /**< Determines maximum connection interval in milliseconds. */
#define SLAVE_LATENCY             0                                     /**< Determines slave latency in terms of connection events. */
#define SUPERVISION_TIMEOUT       MSEC_TO_UNITS(4000, UNIT_10_MS)       /**< Determines supervision time-out in units of 10 milliseconds. */

#define SCAN_INTERVAL             0x00A0                                /**< Determines scan interval in units of 0.625 millisecond. */
#define SCAN_WINDOW               0x0050                                /**< Determines scan window in units of 0.625 millisecond. */
#define SCAN_TIMEOUT              0x0000                                /**< Timout when scanning. 0x0000 disables timeout. */

static bool     m_is_connected              = false;                    /**< Flag to keep track of BLE connections with peripheral devices */
static uint16_t m_conn_handle               = BLE_CONN_HANDLE_INVALID;  /**< Current connection handle. */
static bool     m_memory_access_in_progress = false;                    /**< Flag to keep track of ongoing operations on persistent memory. */

static ble_db_discovery_t m_ble_db_discovery;                           /**< Structure used to identify the DB Discovery module. */
static ble_hrs_c_t        m_ble_hrs_c;                                  /**< Structure used to identify the heart rate client module. */
static ble_bas_c_t        m_ble_bas_c;                                  /**< Structure used to identify the Battery Service client module. */

/**@brief Connection parameters requested for connection. */
static const ble_gap_conn_params_t m_connection_param =
{
    (uint16_t)MIN_CONNECTION_INTERVAL,
    (uint16_t)MAX_CONNECTION_INTERVAL,
    (uint16_t)SLAVE_LATENCY,
    (uint16_t)SUPERVISION_TIMEOUT
};

/**
 * @brief Parameters used when scanning.
 */
const ble_gap_scan_params_t m_scan_params =
{
    .active   = 1,
    .interval = SCAN_INTERVAL,
    .window   = SCAN_WINDOW,
    .timeout  = SCAN_TIMEOUT,
    #if (NRF_SD_BLE_API_VERSION == 2)
        .selective   = 0,
        .p_whitelist = NULL,
    #endif
    #if (NRF_SD_BLE_API_VERSION == 3)
        .use_whitelist = 0,
    #endif
};

/**@brief Function for handling database discovery events.
 *
 * @details This function is callback function to handle events from the database discovery module.
 *          Depending on the UUIDs that are discovered, this function should forward the events
 *          to their respective services.
 *
 * @param[in] p_event  Pointer to the database discovery event.
 */
static void db_disc_handler(ble_db_discovery_evt_t * p_evt)
{
    ble_hrs_on_db_disc_evt(&m_ble_hrs_c, p_evt);
    ble_bas_on_db_disc_evt(&m_ble_bas_c, p_evt);
}


bool ble_is_connected(void)
{
    return m_is_connected;
}

uint16_t ble_get_conn_handle(void)
{
    return m_conn_handle;
}

void ble_disconnect(void)
{
    uint32_t err_code;

    if(m_is_connected)
    {
        err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        APP_ERROR_CHECK(err_code);
    }
}


void scan_start(void)
{
    uint32_t err_code;
    uint32_t flash_busy;

    // If there is any pending write to flash, defer scanning until it completes.
    (void) fs_queued_op_count_get(&flash_busy);

    if (flash_busy != 0)
    {
        m_memory_access_in_progress = true;
        return;
    }

    err_code = sd_ble_gap_scan_stop();
    
    // It is okay to ignore this error since we are stopping the scan anyway.
    if (err_code != NRF_ERROR_INVALID_STATE)
    {
        APP_ERROR_CHECK(err_code);
    }

    err_code = sd_ble_gap_scan_start(&m_scan_params);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the scheduler in the main loop after a BLE stack event has
 * been received.
 *
 * @param[in] p_ble_evt Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    ble_conn_state_on_ble_evt(p_ble_evt);
    pm_on_ble_evt(p_ble_evt);
    ble_db_discovery_on_ble_evt(&m_ble_db_discovery, p_ble_evt);
    ble_hrs_c_on_ble_evt(&m_ble_hrs_c, p_ble_evt);
    ble_bas_c_on_ble_evt(&m_ble_bas_c, p_ble_evt);
    ble_conn_params_on_ble_evt(p_ble_evt);
    on_ble_evt(p_ble_evt);
    on_nfc_pair_evt(p_ble_evt);
}

void on_adv_report(const ble_evt_t * const p_ble_evt)
{
    uint32_t  err_code;
    uint8_t * p_adv_data;
    uint8_t   data_len;
    uint8_t * dev_name;

    // For readibility.
    const ble_gap_evt_t * const  p_gap_evt  = &p_ble_evt->evt.gap_evt;
    const ble_gap_addr_t * const peer_addr  = &p_gap_evt->params.adv_report.peer_addr;
    
    // Initialize advertisement report for parsing
    p_adv_data = (uint8_t *)p_gap_evt->params.adv_report.data;
    data_len   = p_gap_evt->params.adv_report.dlen;

    //search for advertising names
    err_code = nfc_ble_oob_advdata_parser_field_find(BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,
                                                     p_adv_data,
                                                     &data_len,
                                                     &dev_name);
    if (err_code != NRF_SUCCESS)
    {
        // Look for the short local name if it was not found as complete
        err_code = nfc_ble_oob_advdata_parser_field_find(BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME,
                                                         p_adv_data,
                                                         &data_len,
                                                         &dev_name);        
        if (err_code != NRF_SUCCESS)
        {
            // If we can't parse the data, then exit
            return;
        }
    }
    
    NRF_LOG_DEBUG("Found advertising device name: %s\r\n", nrf_log_push((char *)dev_name));

    // Check if device address is the same as address taken from the NFC tag
    if (nfc_oob_pairing_tag_match(peer_addr))
    {
        // If address is correct, stop scanning and initiate connection with peripheral device
        err_code = sd_ble_gap_scan_stop();
        APP_ERROR_CHECK(err_code);    
        
        err_code = sd_ble_gap_connect(peer_addr, &m_scan_params, &m_connection_param);
        APP_ERROR_CHECK(err_code);            
    }
}


void on_ble_evt(const ble_evt_t * const p_ble_evt)
{
    ret_code_t err_code;

    // For readability.
    const ble_gap_evt_t * const p_gap_evt = &p_ble_evt->evt.gap_evt;

    switch (p_ble_evt->header.evt_id)
    {
        // Upon connection, initiate secure bonding
        case BLE_GAP_EVT_CONNECTED:
            NRF_LOG_INFO("Connected.\r\n");

            // Discover peer's services.
            err_code = ble_db_discovery_start(&m_ble_db_discovery,
                                              p_ble_evt->evt.gap_evt.conn_handle);
            APP_ERROR_CHECK(err_code);
       
            m_is_connected = true;
            m_conn_handle  = p_ble_evt->evt.gap_evt.conn_handle;

            break; // BLE_GAP_EVT_CONNECTED

        // Upon disconnection, reset the connection handle of the peer which disconnected
        // and invalidate data taken from the NFC tag
        case BLE_GAP_EVT_DISCONNECTED:
            NRF_LOG_INFO("Disconnected.\r\n");
            m_conn_handle  = BLE_CONN_HANDLE_INVALID;
            m_is_connected = false;
            nfc_oob_pairing_tag_invalidate();
        
            memset(&m_ble_db_discovery, 0 , sizeof (m_ble_db_discovery));

            break; // BLE_GAP_EVT_DISCONNECTED

        case BLE_GAP_EVT_ADV_REPORT:
            on_adv_report(p_ble_evt);
            break; // BLE_GAP_EVT_ADV_REPORT

        case BLE_GAP_EVT_TIMEOUT:
            if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_SCAN)
            {
                NRF_LOG_DEBUG("Scan timed out.\r\n");
                scan_start();
            }
            else if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_CONN)
            {
                NRF_LOG_INFO("Connection Request timed out.\r\n");
            }
            break; // BLE_GAP_EVT_TIMEOUT

        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
            // Accept parameters requested by peer.
            err_code = sd_ble_gap_conn_param_update(p_gap_evt->conn_handle,
                                        &p_gap_evt->params.conn_param_update_request.conn_params);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
            NRF_LOG_DEBUG("GATT Client Timeout.\r\n");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTC_EVT_TIMEOUT

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
            NRF_LOG_DEBUG("GATT Server Timeout.\r\n");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_TIMEOUT

        case BLE_GAP_EVT_AUTH_STATUS:
            NRF_LOG_INFO("BLE_GAP_EVT_AUTH_STATUS\r\n");
            if(p_ble_evt->evt.gap_evt.params.auth_status.auth_status == BLE_GAP_SEC_STATUS_SUCCESS)
            {
                NRF_LOG_INFO("Authorization succeeded!\r\n");
            }
            else
            {
                NRF_LOG_INFO("Authorization failed with code: %u!\r\n", 
                             p_ble_evt->evt.gap_evt.params.auth_status.auth_status);                
            }
            break; // BLE_GAP_EVT_AUTH_STATUS

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            NRF_LOG_INFO("BLE_GAP_EVT_CONN_SEC_UPDATE\r\n");
            NRF_LOG_INFO("Security mode: %u\r\n", 
                         p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec.sec_mode.lv);
            break; // BLE_GAP_EVT_CONN_SEC_UPDATE

#if (NRF_SD_BLE_API_VERSION == 3)
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            err_code = sd_ble_gatts_exchange_mtu_reply(p_ble_evt->evt.gatts_evt.conn_handle,
                                                       NRF_BLE_MAX_MTU_SIZE);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST
#endif

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for handling the Application's system events.
 *
 * @param[in]   sys_evt   system event.
 */
static void on_sys_evt(uint32_t sys_evt)
{
    switch (sys_evt)
    {
        case NRF_EVT_FLASH_OPERATION_SUCCESS:
            /* fall through */
        
        case NRF_EVT_FLASH_OPERATION_ERROR:
            if (m_memory_access_in_progress)
            {
                m_memory_access_in_progress = false;
                scan_start();
            }
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for dispatching a system event to interested modules.
 *
 * @details This function is called from the System event interrupt handler after a system
 *          event has been received.
 *
 * @param[in]   sys_evt   System stack event.
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
    fs_sys_event_handler(sys_evt);
    on_sys_evt(sys_evt);
}


/**@brief Heart Rate Collector Handler.
 */
static void hrs_c_evt_handler(ble_hrs_c_t * p_hrs_c, ble_hrs_c_evt_t * p_hrs_c_evt)
{
    uint32_t err_code;

    switch (p_hrs_c_evt->evt_type)
    {
        case BLE_HRS_C_EVT_DISCOVERY_COMPLETE:
            err_code = ble_hrs_c_handles_assign(p_hrs_c ,
                                                p_hrs_c_evt->conn_handle,
                                                &p_hrs_c_evt->params.peer_db);
            APP_ERROR_CHECK(err_code);

            // Initiate bonding.
            err_code = pm_conn_secure(p_hrs_c_evt->conn_handle, false);
            if (err_code != NRF_ERROR_INVALID_STATE)
            {
                APP_ERROR_CHECK(err_code);
            }

            // Heart rate service discovered. Enable notification of Heart Rate Measurement.
            err_code = ble_hrs_c_hrm_notif_enable(p_hrs_c);
            APP_ERROR_CHECK(err_code);

            NRF_LOG_DEBUG("Heart rate service discovered \r\n");
            break;

        case BLE_HRS_C_EVT_HRM_NOTIFICATION:
            NRF_LOG_INFO("Heart Rate = %d\r\n", p_hrs_c_evt->params.hrm.hr_value);
            break;

        default:
            break;
    }
}


/**@brief Battery level Collector Handler.
 */
static void bas_c_evt_handler(ble_bas_c_t * p_bas_c, ble_bas_c_evt_t * p_bas_c_evt)
{
    uint32_t err_code;

    switch (p_bas_c_evt->evt_type)
    {
        case BLE_BAS_C_EVT_DISCOVERY_COMPLETE:
            err_code = ble_bas_c_handles_assign(p_bas_c,
                                                p_bas_c_evt->conn_handle,
                                                &p_bas_c_evt->params.bas_db);
            APP_ERROR_CHECK(err_code);

            // Initiate bonding.
            err_code = pm_conn_secure(p_bas_c_evt->conn_handle, false);
            if (err_code != NRF_ERROR_INVALID_STATE)
            {
                APP_ERROR_CHECK(err_code);
            }

            // Batttery service discovered. Enable notification of Battery Level.
            NRF_LOG_DEBUG("Battery Service discovered. Reading battery level.\r\n");

            err_code = ble_bas_c_bl_read(p_bas_c);
            APP_ERROR_CHECK(err_code);

            NRF_LOG_DEBUG("Enabling Battery Level Notification. \r\n");
            err_code = ble_bas_c_bl_notif_enable(p_bas_c);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_BAS_C_EVT_BATT_NOTIFICATION:
            NRF_LOG_DEBUG("Battery Level received %d %%\r\n", p_bas_c_evt->params.battery_level);
            break;

        case BLE_BAS_C_EVT_BATT_READ_RESP:
            NRF_LOG_INFO("Battery Level Read as %d %%\r\n", p_bas_c_evt->params.battery_level);
            break;

        default:
            break;
    }
}


/**
 * @brief Heart rate collector initialization.
 */
static void hrs_c_init(void)
{
    ble_hrs_c_init_t hrs_c_init_obj;

    hrs_c_init_obj.evt_handler = hrs_c_evt_handler;

    uint32_t err_code = ble_hrs_c_init(&m_ble_hrs_c, &hrs_c_init_obj);
    APP_ERROR_CHECK(err_code);
}


/**
 * @brief Battery level collector initialization.
 */
static void bas_c_init(void)
{
    ble_bas_c_init_t bas_c_init_obj;

    bas_c_init_obj.evt_handler = bas_c_evt_handler;

    uint32_t err_code = ble_bas_c_init(&m_ble_bas_c, &bas_c_init_obj);
    APP_ERROR_CHECK(err_code);
}


/**
 * @brief Database discovery collector initialization.
 */
static void db_discovery_init(void)
{
    uint32_t err_code = ble_db_discovery_init(db_disc_handler);

    APP_ERROR_CHECK(err_code);
}


void ble_stack_init(void)
{
    ret_code_t err_code;

    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;
    
    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

    ble_enable_params_t ble_enable_params;
    err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT,
                                                    PERIPHERAL_LINK_COUNT,
                                                    &ble_enable_params);
    APP_ERROR_CHECK(err_code);

    //Check the ram settings against the used number of links
    CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);

    // Enable BLE stack.
#if (NRF_SD_BLE_API_VERSION == 3)
    ble_enable_params.gatt_enable_params.att_mtu = NRF_BLE_MAX_MTU_SIZE;
#endif
    err_code = softdevice_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);
    
    // Register with the SoftDevice handler module for System events.
    err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
    APP_ERROR_CHECK(err_code);
    
    db_discovery_init();
    hrs_c_init();
    bas_c_init();
}
