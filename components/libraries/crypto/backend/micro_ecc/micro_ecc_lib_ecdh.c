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

#if defined(NRF_CRYPTO_SUPPORTS_RNG) && NRF_CRYPTO_SUPPORTS_RNG == 1

#include "nrf_crypto.h"
#include "micro_ecc_lib_ecdh.h"
#include "micro_ecc_lib_keys.h"
#include "micro_ecc_lib_init.h"
#include "micro_ecc_lib_shared.h"

#include "uECC.h"


static void swap_array_endian(uint8_t * p_in, uint32_t len, uint8_t * p_out)
{
    uint32_t i;
    for(i = 0; i < len; i++)
    {
        p_out[len-i-1] = p_in[i];
    }
}


uint32_t nrf_crypto_ecdh_shared_secret_compute(nrf_crypto_curve_info_t    curve_info,
                                               nrf_value_length_t const * p_private_key,
                                               nrf_value_length_t const * p_public_key,
                                               nrf_value_length_t       * p_shared_secret)
{
    uint32_t            ret_val;
    uint32_t            public_key_size;
    uint32_t            private_key_size;
    uint32_t            shared_secret_size;
    const struct        uECC_Curve_t * p_curve;
    uint8_t             shared_secret[NRF_CRYPTO_ECDH_SHARED_SECRET_MAX_SIZE];
    
    // This function does not require initialized nrf_crypto for this backend.
    
    // Check private key
    if (p_private_key == NULL   || 
        p_public_key == NULL    || 
        p_shared_secret == NULL )
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_private_key->p_value == NULL      ||
        p_public_key->p_value == NULL       ||
        p_shared_secret->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Check type alignment
    if (!is_word_aligned(p_private_key->p_value)    || 
        !is_word_aligned(p_public_key->p_value)     ||
        !is_word_aligned(p_shared_secret->p_value)  )
    { 
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Check public key size
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_info.curve_type, &public_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (public_key_size != p_public_key->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check private key size
    ret_val = nrf_crypto_ecc_private_key_size_get(curve_info.curve_type, &private_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (private_key_size != p_private_key->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check shared secret size
    ret_val = nrf_crypto_ecdh_shared_secret_size_get(curve_info.curve_type, &shared_secret_size);
    if (ret_val != NRF_SUCCESS)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (shared_secret_size != p_shared_secret->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (!micro_ecc_curve_domain_get(curve_info.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    if (!uECC_shared_secret(p_public_key->p_value, 
                            p_private_key->p_value,
                            shared_secret, 
                            p_curve))
    {
        return NRF_ERROR_INTERNAL;
    }
    
    // Convert result to Little endian
    if (curve_info.endian_type == NRF_CRYPTO_ENDIAN_LE)
    {
        memcpy(p_shared_secret->p_value, shared_secret, shared_secret_size);
    }
    else
    {
        swap_array_endian(shared_secret, shared_secret_size, p_shared_secret->p_value);
    }
    
    
    return NRF_SUCCESS;
}

#endif // Supports RNG

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
