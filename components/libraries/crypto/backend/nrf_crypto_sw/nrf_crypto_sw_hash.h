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
#ifndef NRF_CRYPTO_SW_HASH_H__
#define NRF_CRYPTO_SW_HASH_H__

/** @file
 *
 * @defgroup nrf_crypto_sw_hash Software-based hashing using sha256
 * @{
 * @ingroup nrf_crypto_backend_microecc
 *
 * @brief Macros for type sizes in nrf_crypt SW backend.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "sha256.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Size of buffer required for hash context object.
 */     
#define NRF_CRYPTO_HASH_CONTEXT_SIZE sizeof(sha256_context_t)

#ifdef __cplusplus
}
#endif

/** @} */

#endif // #ifndef NRF_CRYPTO_HASH_H__
