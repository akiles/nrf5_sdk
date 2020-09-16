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

#if defined(NRF_CRYPTO_BACKEND_MICRO_ECC) && (NRF_CRYPTO_BACKEND_MICRO_ECC == 1)

#include "micro_ecc_lib_init.h"
#include "nrf_crypto_rng.h"
#include "uECC.h"

static bool g_is_initialized = false;

uint32_t nrf_crypto_init(void)
{
    uint32_t ret_val = NRF_SUCCESS;
    
#if defined(NRF_CRYPTO_SUPPORTS_RNG) && (NRF_CRYPTO_SUPPORTS_RNG == 1)
    
    ret_val = nrf_crypto_rng_init();

#endif
    
    if (ret_val == NRF_SUCCESS)
    {
        g_is_initialized = true;
    }
    else
    {
        g_is_initialized = false;
    }
    
    return ret_val;
}

uint32_t nrf_crypto_uninit(void)
{
    // Not possible in this nrf_crypto backend. 
    return NRF_SUCCESS;
}

bool nrf_crypto_is_initialized(void)
{
    return g_is_initialized;
}

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
