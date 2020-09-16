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
#ifndef CC310_LIB_ECDSA_H__
#define CC310_LIB_ECDSA_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_cc310_lib_ecdsa CC310 backend ECDSA types.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides types required for CC310 backend ECDSA.
 */

#include "nrf_crypto_ecdsa.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Size of ECDSA signing context.
 */    
#define NRF_CRYPTO_ECDSA_SIGN_CONTEXT_SIZE  sizeof(ECDSA_SignUserContext_t)


/** @brief Size of ECDSA verification context.
 */
#define NRF_CRYPTO_ECDSA_VERIFY_CONTEXT_SIZE  sizeof(ECDSA_VerifyUserContext_t)


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_ECDSA_H__
