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
#ifndef CC310_LIB_KEYS_H__
#define CC310_LIB_KEYS_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_cc310_lib_ecc_keys CC310 backend ECC key types.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides types required for CC310 backend ECC keys.
 */

#include "nrf_crypto_ecdsa.h"
#include "crys_ecpki_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/**@brief   Macro to get the size of the internal represenation of a private key
 *          in the CryptoCell API.
 */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_MAX_SIZE (sizeof(CRYS_ECPKI_UserPrivKey_t))

/**@brief   Macro to get the size of the internal represenation of a public key
 *          in the CryptoCell API.
 */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_MAX_SIZE (sizeof(CRYS_ECPKI_UserPublKey_t))

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_KEYS_H__
