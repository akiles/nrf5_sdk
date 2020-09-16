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
#ifndef CC310_LIB_INIT_H__
#define CC310_LIB_INIT_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_cc310_lib_init CC310 backend initialization types.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides types required for CC310 backend initialization.
 */

#include "nrf_crypto_init.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Size of buffer required to initalize nrf_crypto CC310 backend.
 */    
#define NRF_CRYPTO_INIT_RAM_BUFFER  (0)

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_INIT_H__
