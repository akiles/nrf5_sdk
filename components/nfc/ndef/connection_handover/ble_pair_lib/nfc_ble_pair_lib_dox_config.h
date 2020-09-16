/**
 *
 * @defgroup nfc_ble_pair_lib_config Library parameters configuration
 * @{
 * @ingroup nfc_ble_pair_lib
 */
/** @brief Enables NFC pairing library.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_ENABLED

/** @brief Enables logging in the module.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_LOG_ENABLED

/** @brief Default Severity level
 *
 *  Following options are available:
 * - 0 - Off
 * - 1 - Error
 * - 2 - Warning
 * - 3 - Info
 * - 4 - Debug
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_LOG_LEVEL


/** @brief ANSI escape code prefix.
 *
 *  Following options are available:
 * - 0 - Default
 * - 1 - Black
 * - 2 - Red
 * - 3 - Green
 * - 4 - Yellow
 * - 5 - Blue
 * - 6 - Magenta
 * - 7 - Cyan
 * - 8 - White
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_INFO_COLOR


/** @brief ANSI escape code prefix.
 *
 *  Following options are available:
 * - 0 - Default
 * - 1 - Black
 * - 2 - Red
 * - 3 - Green
 * - 4 - Yellow
 * - 5 - Blue
 * - 6 - Magenta
 * - 7 - Cyan
 * - 8 - White
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_DEBUG_COLOR



/** @brief Common Peer Manager security parameters.
 *
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NFC_BLE_PAIR_LIB_SECURITY_PARAMETERS

/** @brief Enables device bonding.
 *
 * If bonding is enabled at least one of the BLE_NFC_SEC_PARAM_KDIST options must be enabled.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_BOND

/** @brief Enables Long Term Key and Master Identification distribution by device.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_KDIST_OWN_ENC


/** @brief Enables Identity Resolving Key and Identity Address Information distribution by device.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_KDIST_OWN_ID


/** @brief Enables Long Term Key and Master Identification distribution by peer.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_KDIST_PEER_ENC


/** @brief Enables Identity Resolving Key and Identity Address Information distribution by peer.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_KDIST_PEER_ID



/** @brief Minimal size of a security key.
 *
 *  Following options are available:
 * - 7
 * - 8
 * - 9
 * - 10
 * - 11
 * - 12
 * - 13
 * - 14
 * - 15
 * - 16
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_MIN_KEY_SIZE


/** @brief Maximal size of a security key.
 *
 *  Following options are available:
 * - 7
 * - 8
 * - 9
 * - 10
 * - 11
 * - 12
 * - 13
 * - 14
 * - 15
 * - 16
 *
 * @note This is an NRF_CONFIG macro.
 */
#define BLE_NFC_SEC_PARAM_MAX_KEY_SIZE




/** @} */
