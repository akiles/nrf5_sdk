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
#ifndef CC310_LIB_HASH_H__
#define CC310_LIB_HASH_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_cc310_lib_hash CC310 backend hash types.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides types required for CC310 backend hash.
 */

#include "nrf_crypto_hash.h"
#include "crys_hash.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Size of hash context context.
 */    
#define NRF_CRYPTO_HASH_CONTEXT_SIZE  sizeof(CRYS_HASHUserContext_t)


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_HASH_H__
