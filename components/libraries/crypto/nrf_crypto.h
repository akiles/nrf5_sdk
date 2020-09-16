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

#ifndef NRF_CRYPTO_H__
#define NRF_CRYPTO_H__

#include <stdint.h>
#include "nrf_crypto_init.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_keys.h"
#include "nrf_crypto_hash.h"
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_rng.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_crypto Cryptography library
 * @ingroup app_common
 * @{
 *
 * @brief   Cryptography library (nrf_crypto).
 *
 * @details The cryptography library provides functions to compute keys, shared secrets, and hashes,
 *          and to sign and verify data using digital signatures.
 * @}
 *
 * @defgroup nrf_crypto_backends Backends
 * @ingroup nrf_crypto
 * @{
 *
 * @brief   Backends for the cryptography library.
 *
 * @details The cryptography library can be used with several backends that provide different functionality.
 * @}
 *
 * @defgroup nrf_crypto_backend_cryptocell Hardware-accelerated backend (CryptoCell)
 * @ingroup nrf_crypto_backends
 * @{
 *
 * @brief @tagAPI52840  Hardware-accelerated backend for the cryptography library based on CryptoCell (CC310).
 *
 * @details The CryptoCell backend is available on the nRF52840 SoC only, because it requires cryptography hardware. It uses the @ref cryptocell_api.
 * @}
 *
 * @defgroup nrf_crypto_backend_microecc Software backend (micro-ecc)
 * @ingroup nrf_crypto_backends
 * @{
 *
 * @brief Software backend for the cryptography library based on micro-ecc.
 *
 * @details The Software backend uses the external micro-ecc library. Make sure to install the library if you use this backend. See @ref lib_crypto_installing for details.
 *
 * @ref nrf_crypto_sw_hash "Hashing" and @ref nrf_crypto_sw_rng "random number generation" must be enabled separately.
 * @}
 *
 */


#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_H__

