/**
 *
 * @defgroup nrf_crypto_config Cryptography library configuration
 * @{
 * @ingroup nrf_crypto
 */
/** @brief Cryptography module for nRF5 SDK
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_CRYPTO_ENABLED

/** @brief Enables the ARM Cryptocell CC310 backend
 *
 * The hardware-accelerated cryptography backend is available only on nRF52840.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_CRYPTO_BACKEND_CC310_LIB


/** @brief Enables the micro-ecc software backend
 *
 * The micro-ecc library provides a software implementation of ECC cryptography for nRF5 Series devices.
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_CRYPTO_BACKEND_MICRO_ECC

/** @brief Enables hashing
 *
 * If enabled, the cryptography library supports hashing (needed for signing).
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_CRYPTO_BACKEND_SW


/** @brief Enables RNG
 *
 * If enabled, the cryptography library supports random number generation (needed for key generation).
 *
 *  Set to 1 to activate.
 *
 * @note This is an NRF_CONFIG macro.
 */
#define NRF_CRYPTO_SUPPORTS_RNG




/** @} */
