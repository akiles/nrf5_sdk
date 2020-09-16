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
 * @defgroup nrf_crypto_backend_cc310_lib_shared CC310 backend shared functions.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides shared functions required for CC310 backend.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"
#include "crys_ecpki_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function to get micro_ecc curve domain from curve_type
 *
 * @param[in]       curve_type  Curve type get domain for.
 * @param[out]      pp_domain   Double pointer to curve domain structure.
 *
 * @retval  True    True if curve domain was successfully located.
 */
bool cc310_curve_domain_get(nrf_ecc_curve_type_t curve_type, CRYS_ECPKI_Domain_t ** pp_domain);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_HASH_H__
