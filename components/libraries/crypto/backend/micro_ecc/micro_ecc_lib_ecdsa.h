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
#ifndef MICRO_ECC_ECDSA_H__
#define MICRO_ECC_ECDSA_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_micro_ecc_lib_ecdsa micro-ecc backend ECDSA types.
 * @{
 * @ingroup nrf_crypto_backend_microecc
 *
 * @brief Provides types required for micro_ecc backend ECDSA.
 */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Size of ECDSA signing context.
 */    
#define NRF_CRYPTO_ECDSA_SIGN_CONTEXT_SIZE  (0)


/** @brief Size of ECDSA verification context.
 */
#define NRF_CRYPTO_ECDSA_VERIFY_CONTEXT_SIZE  (0)


#ifdef __cplusplus
}
#endif

/**@} */

#endif // MICRO_ECC_ECDSA_H__
