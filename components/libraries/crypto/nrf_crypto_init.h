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
#ifndef NRF_CRYPTO_INIT_H__
#define NRF_CRYPTO_INIT_H__

/** @file
 *
 * @defgroup nrf_crypto_initialization Initialization.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides nrf_crypto initialization related functions.
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "nrf_crypto_types.h"

/**@brief Function for initializing the cryptography library.
 *
 * @retval  NRF_SUCCESS     If initialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypt backend.
 */
uint32_t nrf_crypto_init(void);


/**@brief Function for uninitializing the cryptography library.
 * 
 * @retval  NRF_SUCCESS         If unititialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypt backend.
 */
uint32_t nrf_crypto_uninit(void);


/**@brief Function reporting if nrf_crypto has been initialized.
 *
 * @retval  True    If cryptographic library is initialized.
 * @retval  False   If cryptographic library isn't initialized.
 */
bool nrf_crypto_is_initialized(void);


#ifdef __cplusplus
}
#endif

/**@} */

#endif // NRF_CRYPTO_INIT_H__
