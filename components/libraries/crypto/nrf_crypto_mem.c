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

#include "nrf_crypto_mem.h"
#include "mem_manager.h"

uint32_t nrf_crypto_mem_init(void)
{
    uint32_t ret_val;
    
    ret_val = nrf_mem_init();
    return ret_val;
}

uint32_t nrf_crypto_mem_allocate(uint32_t size, nrf_value_length_t * p_result)
{
    uint32_t    ret_val;
    uint32_t    allocated_size;
    
    if (p_result == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_mem_reserve(&p_result->p_value, &allocated_size);
    if (ret_val == NRF_SUCCESS)
    {
        p_result->length = size;
    }
    else
    {
        p_result->length = 0;
    }
    
    return ret_val;
}

uint32_t nrf_crypto_mem_free(nrf_value_length_t * p_mem)
{
    if (p_mem == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if(p_mem->length != 0)
    {
        nrf_free(p_mem->p_value);
    }
    
    return NRF_SUCCESS;
}
 
 
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
