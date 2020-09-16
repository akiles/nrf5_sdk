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

#include "nrf_crypto_init.h"
#include "cc310_lib_init.h"
#include "cc310_lib_shared.h"
#include "crys_rnd.h"
#include "sns_silib.h"

// Temporary setting this before real handling of memory management
CRYS_RND_Context_t      g_rnd_context;

// Temporary setting this before real handling of memory management
CRYS_RND_WorkBuff_t     g_rnd_work_buffer;


/**@brief Pointer to contigious memory holding random number context data
 *
 * @note    The data pointed to must be available in the duration of the usage of Cryptocell api functions.
 */
CRYS_RND_Context_t    * gp_rnd_context          = &g_rnd_context;

/**@brief Pointer to contigious memory for the rnd initialization workspace
 *
 * @note    The Data pointed to must be available in the duration of the initialization of the Cryptocell
 *          or during reseeding of rng. 
 */
CRYS_RND_WorkBuff_t * gp_rnd_work_buffer        = &g_rnd_work_buffer;

static uint32_t init_result_get(uint32_t crys_error)
{
    uint32_t ret_val = NRF_ERROR_INTERNAL;
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


static uint32_t uninit_result_get(uint32_t crys_error)
{
    uint32_t ret_val;
    
    switch(crys_error)
    {
        default:
            ret_val = NRF_ERROR_INTERNAL;
    }
    
    return ret_val;
}


uint32_t nrf_crypto_init(void)
{
    //nrf_crypto_init_info_h * p_init_info
    uint32_t                ret_val;
    CRYSError_t             crys_error;

    // Initialize the cryptocell by setting hardware register
    NRF_CRYPTOCELL->ENABLE = 1;
    
    // Initialize the CC310 run-time library
    crys_error = SaSi_LibInit(gp_rnd_context, gp_rnd_work_buffer);
    ret_val = init_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_uninit(void)
{
    uint32_t        ret_val;
    CRYSError_t     crys_error;
    
    // Check that the library has been initialized. If not, exit.
    if (gp_rnd_context == NULL)
    {
        return NRF_SUCCESS;
    }
    
    crys_error = SaSi_LibFini(gp_rnd_context);
    
    // Set rnd context to zero to signal that the library is uninitialized
    gp_rnd_context = NULL;
    
    ret_val = uninit_result_get(crys_error);
    return ret_val;
}


bool nrf_crypto_is_initialized(void)
{
    return (gp_rnd_context != NULL);
}


#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

