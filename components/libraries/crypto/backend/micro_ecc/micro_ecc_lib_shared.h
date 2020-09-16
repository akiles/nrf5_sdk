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
#ifndef MICRO_ECC_LIB_SHARED_H__
#define MICRO_ECC_LIB_SHARED_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_micro_ecc_lib_shared micro-ecc backend shared functions.
 * @{
 * @ingroup nrf_crypto_backend_microecc
 *
 * @brief Provides shared functions required for micro_ecc backend.
 */

#include <stdint.h>
#include <stdbool.h>
#include "nrf_crypto_types.h"
#include "uECC.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function to get micro_ecc curve domain from curve_type
 *
 * @param[in] curve_type    Curve type get domain for.
 * @param[in] pp_domain     Double pointer to curve domain structure.
 *
 * @retval  True    True if curve domain was successfully located.
 */
bool micro_ecc_curve_domain_get(nrf_ecc_curve_type_t curve_type, struct uECC_Curve_t const ** pp_domain);    
    
    
#ifdef __cplusplus
}
#endif

/**@} */

#endif // MICRO_ECC_LIB_SHARED_H__
