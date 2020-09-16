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

#include "micro_ecc_lib_keys.h"
#include "micro_ecc_lib_shared.h"
#include "micro_ecc_lib_init.h"
#include "nrf_crypto_types.h"

#include "uECC.h"


#if !defined(NRF_CRYPTO_BACKEND_SW)
#error Enable NRF_CRYPTO_BACKEND_SW in SDK config for key generation (required random number generator)
#endif

#if defined(NRF_CRYPTO_SUPPORTS_RNG) && NRF_CRYPTO_SUPPORTS_RNG == 1

uint32_t nrf_crypto_ecc_key_pair_generate(nrf_crypto_curve_info_t       curve_type,
                                          nrf_value_length_t          * p_private_key,
                                          nrf_value_length_t          * p_public_key)
{
    uint32_t                    ret_val;
    uint32_t                    private_key_size;
    uint32_t                    public_key_size;
    const struct uECC_Curve_t * p_curve;
    
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }
    
    if (p_private_key == NULL || 
        p_public_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_private_key->p_value == NULL      ||
        p_public_key->p_value == NULL       )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    if (!is_word_aligned(p_private_key->p_value) || !is_word_aligned(p_public_key->p_value))
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    ret_val = nrf_crypto_ecc_private_key_size_get(curve_type.curve_type, &private_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_private_key->length != private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_type.curve_type, &public_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_public_key->length != public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (!micro_ecc_curve_domain_get(curve_type.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    if (uECC_make_key(p_public_key->p_value, p_private_key->p_value, p_curve) == 0)
    {
        return NRF_ERROR_INTERNAL;
    }
    
    return NRF_SUCCESS;
}



uint32_t nrf_crypto_ecc_public_key_calculate(nrf_crypto_curve_info_t       curve_type,
                                             nrf_value_length_t    const * p_private_key,
                                             nrf_value_length_t          * p_public_key)
{
    uint32_t                    ret_val;
    uint32_t                    private_key_size;
    uint32_t                    public_key_size;
    const struct uECC_Curve_t * p_curve;
    
    // This function does not require initialized nrf_crypto backend library.
    
    if (p_private_key == NULL || p_public_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_private_key->p_value == NULL      ||
        p_public_key->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    ret_val = nrf_crypto_ecc_private_key_size_get(curve_type.curve_type, &private_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_private_key->length != private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_type.curve_type, &public_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_public_key->length != public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (!is_word_aligned(p_private_key->p_value) || !is_word_aligned(p_public_key->p_value))
    {
        return NRF_ERROR_INVALID_ADDR;
    }
        
    if (!micro_ecc_curve_domain_get(curve_type.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    if (uECC_compute_public_key(p_private_key->p_value, p_public_key->p_value, p_curve) == 0)
    {
        return NRF_ERROR_INTERNAL;
    }
    
    return NRF_SUCCESS;
}

#endif

uint32_t nrf_crypto_ecc_private_key_to_raw(nrf_crypto_curve_info_t          curve_info, 
                                           nrf_value_length_t       const * p_private_key,
                                           nrf_value_length_t             * p_private_key_raw)
{
    uint32_t        ret_val;
    uint32_t        private_key_size;
    
    if (p_private_key == NULL || p_private_key_raw == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_private_key->p_value == NULL      ||
        p_private_key_raw->p_value == NULL  )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    ret_val = nrf_crypto_ecc_private_key_size_get(curve_info.curve_type, &private_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_private_key_raw->length != private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (p_private_key->length != private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Copy the private key directly.
    memcpy(p_private_key_raw->p_value, p_private_key->p_value, private_key_size);
    return NRF_SUCCESS;
}

uint32_t nrf_crypto_ecc_public_key_to_raw(nrf_crypto_curve_info_t       curve_info,
                                          nrf_value_length_t    const * p_public_key,
                                          nrf_value_length_t          * p_raw_key)
{
    uint32_t        ret_val;
    uint32_t        public_key_size;
    
    if (p_public_key == NULL || p_raw_key == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_public_key->p_value == NULL   ||
        p_raw_key->p_value == NULL      )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    ret_val = nrf_crypto_ecc_public_key_size_get(curve_info.curve_type, &public_key_size);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    if (p_raw_key->length != public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    if (p_public_key->length != public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    memcpy(p_raw_key->p_value, p_public_key->p_value, p_raw_key->length);
    return NRF_SUCCESS;
}

uint32_t nrf_crypto_ecc_public_key_from_raw(nrf_crypto_curve_info_t   curve_type,
                                            nrf_value_length_t      * p_public_key_raw,
                                            nrf_value_length_t      * p_public_key)
{
    // TODO: Parameter testing
    memcpy(p_public_key->p_value, p_public_key_raw->p_value, p_public_key_raw->length);
    return NRF_SUCCESS;
}

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
