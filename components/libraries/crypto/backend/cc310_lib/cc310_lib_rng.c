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

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include "nrf_crypto.h"
#include "nrf_crypto_rng.h"
#include "cc310_lib_init.h"
#include "crys_rnd.h"

extern CRYS_RND_Context_t    *  gp_rnd_context;

static uint32_t rng_result_get(CRYSError_t crys_error)
{
    uint32_t        ret_val;
    
    switch(crys_error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;
        
        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;   
    }
    
    return ret_val;
}

uint32_t nrf_crypto_rng_init(void)
{
    // No need to do anything as library init takes care of initialization of rng.
    return NRF_SUCCESS;
}

uint32_t nrf_crypto_rng_vector_generate(uint8_t * p_target, uint32_t length)
{
    uint32_t        ret_val;
    CRYSError_t     crys_error;
    
    if (p_target == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    crys_error = CRYS_RND_GenerateVector(&gp_rnd_context->rndState, length, p_target);
    ret_val = rng_result_get(crys_error);
    return ret_val;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
