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

#include "nrf_crypto_keys.h"
#include "nrf_crypto_mem.h"
 
#if NRF_CRYPTO_BACKEND_CC310_LIB
#include "cc310_lib_keys.h"
#endif

#if NRF_CRYPTO_BACKEND_MICRO_ECC
#include "micro_ecc_lib_keys.h"
#endif

 
uint32_t nrf_crypto_ecc_private_key_size_get(nrf_ecc_curve_type_t   curve_type,
                                             uint32_t             * p_key_size)
{
    if(p_key_size == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    switch(curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            (*p_key_size)= NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP160R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224R1;            
            break;
        
        case NRF_CRYPTO_CURVE_SECP256R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP384R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP384R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP521R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP521R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP192K1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP224K1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP256K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PRIVATE_KEY_SIZE_SECP256K1;
            break;
        
        default:
            (*p_key_size) = 0;
            return NRF_ERROR_NOT_SUPPORTED;
    }
    
    return NRF_SUCCESS;
}

uint32_t nrf_crypto_ecc_public_key_size_get(nrf_ecc_curve_type_t    curve_type,
                                            uint32_t              * p_key_size)
{
    if(p_key_size == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    switch(curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            (*p_key_size)= NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP160R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224R1;            
            break;
        
        case NRF_CRYPTO_CURVE_SECP256R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP384R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP384R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP521R1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP521R1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP192K1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP224K1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP256K1:
            (*p_key_size) = NRF_CRYPTO_ECC_PUBLIC_KEY_SIZE_SECP256K1;
            break;
        
        default:
            (*p_key_size) = 0;
            return NRF_ERROR_NOT_SUPPORTED;
    }
    
    return NRF_SUCCESS;
}


uint32_t nrf_crypto_ecc_private_key_allocate(nrf_crypto_curve_info_t    curve_info,
                                             nrf_value_length_t       * p_private_key,
                                             nrf_value_length_t const * p_raw_key)
{
    uint32_t        ret_val;
    uint32_t        key_size;
    
    if (p_private_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_ecc_private_key_size_get(curve_info.curve_type, &key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    ret_val = nrf_crypto_mem_allocate(key_size, p_private_key);
    if (ret_val == NRF_SUCCESS)
    {
        return ret_val;
    }
    
    return ret_val;
}

uint32_t nrf_crypto_ecc_private_key_free(nrf_value_length_t * p_private_key)
{
    uint32_t ret_val;
    
    if (p_private_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_mem_free(p_private_key);
    return ret_val;
}

uint32_t nrf_crypto_ecc_public_key_allocate(nrf_crypto_curve_info_t     curve_info,
                                            nrf_value_length_t        * p_public_key,
                                            nrf_value_length_t  const * p_raw_key)
{
    uint32_t        ret_val;
    uint32_t        key_size;
    
    if (p_public_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_info.curve_type, &key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    ret_val = nrf_crypto_mem_allocate(key_size, p_public_key);
    if (ret_val == NRF_SUCCESS)
    {
        return ret_val;
    }
    
    return ret_val;
}


uint32_t nrf_crypto_ecc_public_key_free(nrf_value_length_t * p_public_key)
{
    uint32_t ret_val;
    
    if (p_public_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    ret_val = nrf_crypto_mem_free(p_public_key);
    return ret_val;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
