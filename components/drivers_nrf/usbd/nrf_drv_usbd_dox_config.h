/**
 *
 * @defgroup nrf_drv_usbd_config USB driver configuration
 * @{
 * @ingroup nrf_drv_usbd
 */
/** @brief Enable USB driver
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define USBD_ENABLED

/** @brief Interrupt priority
 *
 * Priorities 0,2 (nRF51) and 0,1,4,5 (nRF52) are reserved for SoftDevice
 *
 *  Following options are available:
 * - 0 - 0 (highest)
 * - 1 - 1
 * - 2 - 2
 * - 3 - 3
 * - 4 - 4 (except nRF51 family)
 * - 5 - 5 (except nRF51 family)
 * - 6 - 6 (except nRF51 family)
 * - 7 - 7 (except nRF51 family)
 *
 * @note This is an NRF_CONFIG macro.
 */
#define USBD_CONFIG_IRQ_PRIORITY


/** @brief USBD SMA scheduler working scheme
 *
 *  Following options are available:
 * - 0 - Prioritized access
 * - 1 - Round Robin
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_DRV_USBD_DMASCHEDULER_MODE


/** @brief Enable logging.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_USBD_DRV_LOG_ENABLED



/** @} */
