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
 #ifndef NRF_CRYPTO_MEM_H__
 #define NRF_CRYPTO_MEM_H__

/** @file
 *
 * @defgroup nrf_crypto_mem Dynamic memory management module
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Module to manage dynamically allocated memory used by nrf_crypto APIs
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

 #ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/** @brief Function to initialize the nrf_crypto memory module.
 * 
 * @retval NRF_SUCCESS     The nrf_crypto memory manager initialized successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_init(void);


/**@brief Function to allocate memory for use by the nrf_crypto API.
 * 
 * @param[in]       size        Length in bytes to allocate
 * @param[in,out]   p_result    Pointer to value length structure to hold information about the allocated memory.
 *
 * @retval  NRF_SUCCESS     The memory was allocated successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_allocate(uint32_t size, nrf_value_length_t * p_result);


/**@brief Function to free memory to use by nrf_crypto API.
 *
 * @param[in]   p_mem       Pointer to value length structure holding information about allocated memory to free
 *
 * @retval NRF_SUCCESS      The memory was freed successfully.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_mem_free(nrf_value_length_t * p_mem);

#ifdef __cplusplus
}
#endif
 
/**@} */
 
 #endif // NRF_CRYPTO_MEM_H__
