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
 
#include "pm_module.h"
#include "ble_advdata.h"
#include "sdk_errors.h"
#include "peer_manager.h"
#include "ble_conn_state.h"
#include "ble_module.h"
#include "ecc.h"

#define NRF_LOG_MODULE_NAME "PM_MODULE"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define SEC_PARAM_BOND            1                     /**< Perform bonding. */
#define SEC_PARAM_MITM            1                     /**< Man In The Middle protection required. */
#define SEC_PARAM_IO_CAPABILITIES BLE_GAP_IO_CAPS_NONE  /**< No I/O capabilities. */
#define SEC_PARAM_OOB             1                     /**< Out Of Band pairing available. */
#define SEC_PARAM_MIN_KEY_SIZE    7                     /**< Minimum encryption key size in octets. */
#define SEC_PARAM_MAX_KEY_SIZE    16                    /**< Maximum encryption key size in octets. */
#define SEC_PARAM_LESC            1                     /**< LE Secure Connections enabled. */
#define SEC_PARAM_KEYPRESS        0                     /**< Keypress notifications not enabled. */
#define SEC_PARAM_KDIST_OWN_ENC   1                     /**< Enable Long Term Key and Master Identification distribution by device. */
#define SEC_PARAM_KDIST_OWN_ID    1                     /**< Enable Identity Resolving Key and Identity Address Information distribution by device. */
#define SEC_PARAM_KDIST_PEER_ENC  1                     /**< Enable Long Term Key and Master Identification distribution by peer. */
#define SEC_PARAM_KDIST_PEER_ID   1                     /**< Enable Identity Resolving Key and Identity Address Information distribution by peer. */

/**@brief Function for handling Peer Manager events.
 *
 * @param[in] p_evt  Peer Manager event.
 */
static void pm_evt_handler(pm_evt_t const * p_evt)
{
    ret_code_t err_code;
    
    switch(p_evt->evt_id)
    {
        case PM_EVT_BONDED_PEER_CONNECTED:
            NRF_LOG_DEBUG("Connected to previoulsy bonded device\r\n");
            err_code = pm_peer_rank_highest(p_evt->peer_id);
            if (err_code != NRF_ERROR_BUSY)
            {
                    APP_ERROR_CHECK(err_code);
            }
            break;

        case PM_EVT_CONN_SEC_SUCCEEDED:
            NRF_LOG_DEBUG("Link secured. Role: %d. conn_handle: %d, Procedure: %d\r\n",
                           ble_conn_state_role(p_evt->conn_handle),
                           p_evt->conn_handle,
                           p_evt->params.conn_sec_succeeded.procedure);
            
            if (p_evt->params.conn_sec_succeeded.procedure == PM_LINK_SECURED_PROCEDURE_BONDING)
            {
                err_code = pm_peer_rank_highest(p_evt->peer_id);
                if (err_code != NRF_ERROR_BUSY)
                {
                    APP_ERROR_CHECK(err_code);
                }                
            }
            break;

        case PM_EVT_CONN_SEC_FAILED:
            /** In some cases, when securing fails, it can be restarted directly. Sometimes it can
             *  be restarted, but only after changing some Security Parameters. Sometimes, it cannot
             *  be restarted until the link is disconnected and reconnected. Sometimes it is
             *  impossible, to secure the link, or the peer device does not support it. How to
             *  handle this error is highly application dependent. */
            NRF_LOG_DEBUG("PM_EVT_CONN_SEC_FAILED: %u\r\n", p_evt->params.conn_sec_failed.error);

            if (p_evt->params.conn_sec_failed.error == PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING)
            {
                // Rebond if one party has lost its keys.
                err_code = pm_conn_secure(p_evt->conn_handle, true);
                if (err_code != NRF_ERROR_INVALID_STATE)
                {
                    APP_ERROR_CHECK(err_code);
                }
            }
            break;

        case PM_EVT_PEERS_DELETE_SUCCEEDED:
            scan_start();
            break;

        case PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED:
            // The local database has likely changed, send service changed indications.
            pm_local_database_has_changed();
            break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
        case PM_EVT_PEER_DELETE_FAILED:
        case PM_EVT_PEERS_DELETE_FAILED:
        case PM_EVT_ERROR_UNEXPECTED:
            // Assert.
            APP_ERROR_CHECK_BOOL(false);
            break;

        case PM_EVT_CONN_SEC_START:
            NRF_LOG_DEBUG("PM_EVT_CONN_SEC_START\r\n");
            break;

        // Events that do not need to be implemented
        case PM_EVT_STORAGE_FULL:
        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
        case PM_EVT_PEER_DELETE_SUCCEEDED:
        case PM_EVT_LOCAL_DB_CACHE_APPLIED:
        case PM_EVT_SERVICE_CHANGED_IND_SENT:
        case PM_EVT_SERVICE_CHANGED_IND_CONFIRMED:
        default:
            // No implementation needed.
            break;
    }
}

void peer_manager_init(bool erase_bonds)
{
    ble_gap_sec_params_t sec_param;
    ret_code_t           err_code;

    err_code = pm_init();
    APP_ERROR_CHECK(err_code);

    if (erase_bonds)
    {
        err_code = pm_peers_delete();
        APP_ERROR_CHECK(err_code);
    }

    memset(&sec_param, 0, sizeof(ble_gap_sec_params_t));

    // Security parameters to be used for all security procedures.
    sec_param.bond              = SEC_PARAM_BOND;
    sec_param.mitm              = SEC_PARAM_MITM;
    sec_param.lesc              = SEC_PARAM_LESC;
    sec_param.keypress          = SEC_PARAM_KEYPRESS;
    sec_param.io_caps           = SEC_PARAM_IO_CAPABILITIES;
    sec_param.oob               = SEC_PARAM_OOB;
    sec_param.min_key_size      = SEC_PARAM_MIN_KEY_SIZE;
    sec_param.max_key_size      = SEC_PARAM_MAX_KEY_SIZE;
    sec_param.kdist_own.enc     = SEC_PARAM_KDIST_OWN_ENC;
    sec_param.kdist_own.id      = SEC_PARAM_KDIST_OWN_ID;
    sec_param.kdist_peer.enc    = SEC_PARAM_KDIST_PEER_ENC;
    sec_param.kdist_peer.id     = SEC_PARAM_KDIST_PEER_ID;

    err_code = pm_sec_params_set(&sec_param);
    APP_ERROR_CHECK(err_code);

    err_code = pm_register(pm_evt_handler);
    APP_ERROR_CHECK(err_code);
}
