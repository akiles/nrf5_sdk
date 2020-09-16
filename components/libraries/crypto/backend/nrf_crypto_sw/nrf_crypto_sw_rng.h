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
#ifndef NRF_CRYPTO_SW_RNG_H__
#define NRF_CRYPTO_SW_RNG_H__

/** @file
 *
 * @defgroup nrf_crypto_sw_rng Random Number Generation using nrf_drv_rng
 * @{
 * @ingroup nrf_crypto_backend_microecc
 *
 * @brief Macros for type sizes for RNG in nrf_crypto backend.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Size of buffer required for initializing RNG.
 */
#define NRF_CRYPTO_RNG_INIT_SIZE        (0)

/** @brief Size of buffer required for RNG context object.
 */     
#define NRF_CRYPTO_RNG_CONTEXT_SIZE     (0)


#ifdef __cplusplus
}
#endif

/** @} */

#endif // #ifndef NRF_CRYPTO_SW_RNG_H__
