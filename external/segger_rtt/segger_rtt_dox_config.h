/**
 *
 * @defgroup segger_rtt_config SEGGER RTT configuration
 * @{
 * @ingroup segger_rtt
 */
/** @brief Size of upstream buffer.
 *
 * Note that either @ref NRF_LOG_BACKEND_RTT_OUTPUT_BUFFER_SIZE
 * or this value is actually used. It depends on which one is bigger.
 *
 *
 * @note This is an NRF_CONFIG macro.
 */
#define SEGGER_RTT_CONFIG_BUFFER_SIZE_UP


/** @brief Size of upstream buffer.
 *
 *
 * @note This is an NRF_CONFIG macro.
 */
#define SEGGER_RTT_CONFIG_MAX_NUM_UP_BUFFERS


/** @brief Size of upstream buffer.
 *
 *
 * @note This is an NRF_CONFIG macro.
 */
#define SEGGER_RTT_CONFIG_BUFFER_SIZE_DOWN


/** @brief Size of upstream buffer.
 *
 *
 * @note This is an NRF_CONFIG macro.
 */
#define SEGGER_RTT_CONFIG_MAX_NUM_DOWN_BUFFERS


/** @brief RTT behavior if the buffer is full.
 *
 * The following modes are supported:
 * - SKIP  - Do not block, output nothing.
 * - TRIM  - Do not block, output as much as fits.
 * - BLOCK - Wait until there is space in the buffer.
 *
 *  Following options are available:
 * - 0 - SKIP
 * - 1 - TRIM
 * - 2 - BLOCK_IF_FIFO_FULL
 *
 * @note This is an NRF_CONFIG macro.
 */
#define SEGGER_RTT_CONFIG_DEFAULT_MODE


/** @} */
