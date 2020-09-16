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

#include "nrf_crypto_hash.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_sw_hash.h"
#include "sha256.h"
#include "nrf_log.h"

uint32_t nrf_crypto_hash_init(nrf_crypto_hash_info_t    hash_info,
                              nrf_value_length_t      * p_hash_context)
{
    uint32_t            ret_val;
    sha256_context_t  * p_hash_context_user;
    
    if (p_hash_context == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_hash_context->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    if (p_hash_context->length < NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Currently SHA256 is the only available hash algorithm
    if(hash_info.hash_type != NRF_CRYPTO_HASH_TYPE_SHA256)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    p_hash_context_user = (sha256_context_t *)p_hash_context->p_value;
    
    ret_val = sha256_init(p_hash_context_user);
    return ret_val;
}

uint32_t nrf_crypto_hash_update(nrf_value_length_t   * p_hash_context, 
                                uint8_t        const * p_data,
                                uint32_t               len)
{
    uint32_t            ret_val;
    sha256_context_t  * p_hash_context_user;
    
    if (p_hash_context == NULL || p_data == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    
    if (p_hash_context->length < NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    p_hash_context_user = (sha256_context_t *)p_hash_context->p_value;
    
    ret_val = sha256_update(p_hash_context_user, p_data, len);
    return ret_val;
}


uint32_t nrf_crypto_hash_finalize(nrf_crypto_hash_info_t    hash_info,
                                  nrf_value_length_t      * p_hash_context, 
                                  nrf_value_length_t      * p_hash)
{
    uint32_t            ret_val;
    sha256_context_t  * p_hash_context_user;
    uint8_t             endian_type;
    uint32_t            hash_size;
    
    if (p_hash_context == NULL || p_hash == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    
    // Check hash context size
    if (p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    p_hash_context_user = (sha256_context_t *)p_hash_context->p_value;
    
    // Check if hash is correct size
    ret_val = nrf_crypto_hash_size_get(hash_info.hash_type, &hash_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (hash_size != p_hash->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (hash_info.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        endian_type = 1;
    }
    else
    {
        endian_type = 0;
    }
    
    ret_val = sha256_final(p_hash_context_user, p_hash->p_value, endian_type);
    return ret_val;
}


uint32_t nrf_crypto_hash_compute(nrf_crypto_hash_info_t    hash_info,
                                 uint8_t           const * p_data,
                                 uint32_t                  len,
                                 nrf_value_length_t      * p_hash)
{
    uint32_t            ret_val;
    uint32_t            hash_size;
    sha256_context_t    hash_context;
    nrf_value_length_t  hash_context_desc = 
    { 
        .p_value = (uint8_t*)&hash_context,
        .length  = sizeof(hash_context)
    };
    
    // Basic parameter testing.
    if (p_hash == NULL || p_data == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_hash->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Currently SHA256 is the only available hash algorithm
    if (hash_info.hash_type != NRF_CRYPTO_HASH_TYPE_SHA256)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    // Check if hash is correct size.
    ret_val = nrf_crypto_hash_size_get(hash_info.hash_type, &hash_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (hash_size != p_hash->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    ret_val = nrf_crypto_hash_init(hash_info, &hash_context_desc);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    ret_val = nrf_crypto_hash_update(&hash_context_desc, p_data, len);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    ret_val = nrf_crypto_hash_finalize(hash_info, &hash_context_desc, p_hash);
    return ret_val;
}


#endif // NRF_CRYPTO_BACKEND_SW

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
