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

#include "nrf_crypto_hash.h"
#include "nrf_crypto_mem.h"

#if NRF_CRYPTO_BACKEND_CC310_LIB
#include "cc310_lib_hash.h"
#endif

#if NRF_CRYPTO_BACKEND_SW
#include "nrf_crypto_sw_hash.h"
#endif

uint32_t nrf_crypto_hash_size_get(nrf_hash_type_t hash_type, uint32_t * p_hash_size)
{
    switch(hash_type)
    {
        case NRF_CRYPTO_HASH_TYPE_MD5:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_MD5;
            break;
        
        case NRF_CRYPTO_HASH_TYPE_SHA1:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_SHA1;
            break;
        
        case NRF_CRYPTO_HASH_TYPE_SHA224:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_SHA224;
            break;
            
        case NRF_CRYPTO_HASH_TYPE_SHA256:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_SHA256;
            break;
            
        case NRF_CRYPTO_HASH_TYPE_SHA384:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_SHA384;
            break;
        
        case NRF_CRYPTO_HASH_TYPE_SHA512:
            (*p_hash_size) = NRF_CRYPTO_HASH_SIZE_SHA512;
            break;
        
        default:
            return NRF_ERROR_NOT_SUPPORTED;
    }
    
    return NRF_SUCCESS;
}


uint32_t nrf_crypto_hash_context_allocate(nrf_crypto_hash_info_t    hash_info,
                                          nrf_value_length_t      * p_hash_context)
{
    uint32_t        ret_val;
    uint32_t        hash_context_size = NRF_CRYPTO_HASH_CONTEXT_SIZE;
    
    if (p_hash_context == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_mem_allocate(hash_context_size, p_hash_context);
    return ret_val;
}


uint32_t nrf_crypto_hash_context_free(nrf_value_length_t * p_hash_context)
{
    uint32_t        ret_val;
    
    if (p_hash_context == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_mem_free(p_hash_context);
    return ret_val;
}


uint32_t nrf_crypto_hash_allocate(nrf_crypto_hash_info_t        hash_info,
                                  nrf_value_length_t          * p_hash,
                                  nrf_value_length_t    const * p_raw_hash)
{
    uint32_t        ret_val;
    uint32_t        hash_size;
    
    if (p_hash == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_hash_size_get(hash_info.hash_type, &hash_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    ret_val = nrf_crypto_mem_allocate(hash_size, p_hash);
    if (ret_val == NRF_SUCCESS)
    {
        return ret_val;
    }
    
    return ret_val;
    
}


uint32_t nrf_crypto_hash_free(nrf_value_length_t * p_hash)
{
    uint32_t ret_val;
    
    if (p_hash == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_mem_free(p_hash);
    return ret_val;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
