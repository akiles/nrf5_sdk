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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "nrf_crypto_init.h"

#if NRF_CRYPTO_BACKEND_CC310_LIB
#include "cc310_lib_init.h"
#endif

#if NRF_CRYPTO_BACKEND_MICRO_ECC
#include "micro_ecc_lib_init.h"
#endif


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
