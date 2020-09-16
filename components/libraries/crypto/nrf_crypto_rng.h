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
#ifndef NRF_CRYPTO_RNG_H__
#define NRF_CRYPTO_RNG_H__

/** @file
 *
 * @defgroup nrf_crypto_rng Random number generation related functions.
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides functions to initialize rng subsystem and generate random data.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/**@brief Initialize the random number generator
 *
 * @note This function is called by @ref nrf_crypto_init.
 *
 * @retval  NRF_SUCCESS             If random number generator was initialized successfully.
 * @retval  NRF_ERROR_INTERNAL      If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_rng_init(void);

/**@brief Generate random data into a buffer, given length as an input.
 *
 * @param[in,out]   p_target    Pointer to a buffer to accept the random generated data.
 *                              This buffer must be the same length as the length input.
 * @param[in]       length      Length (in bytes) to generate random data for.
 *
 * @retval  NRF_SUCCESS         Data was generated successfully.
 * @retval  NRF_ERROR_NULL      p_target was NULL.
 * @retval  NRF_ERROR_INTERNAL  If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_rng_vector_generate(uint8_t * p_target, uint32_t length);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_RNG_H__
