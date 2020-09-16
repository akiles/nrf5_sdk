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
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_types.h"
#include "micro_ecc_lib_ecdsa.h"
#include "micro_ecc_lib_keys.h"
#include "micro_ecc_lib_shared.h"
#include "nrf_log.h"

#include "uECC.h"

#if defined(NRF_CRYPTO_SUPPORTS_RNG) && NRF_CRYPTO_SUPPORTS_RNG == 1

uint32_t nrf_crypto_ecdsa_sign_hash(nrf_crypto_signature_info_t  sig_info,
                                    nrf_value_length_t   const * p_private_key,
                                    nrf_value_length_t   const * p_hash,
                                    nrf_value_length_t         * p_signature)
{
    uint32_t                    ret_val;
    nrf_crypto_ecdsa_sizes_t    sig_sizes;
    const struct uECC_Curve_t * p_curve = uECC_secp256r1();
    
    // Parameter NULL testing.
    if (p_private_key == NULL || 
        p_hash == NULL        ||
        p_signature == NULL   )
    {
        return NRF_ERROR_NULL;
    }

    if (p_private_key->p_value == NULL  ||
        p_hash->p_value == NULL         ||
        p_signature->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Ensure data is aligned
    if (!is_word_aligned(p_private_key->p_value)    || 
        !is_word_aligned(p_hash->p_value)           || 
        !is_word_aligned(p_signature->p_value)      )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Get the sizes for the keys, hash and signature
    ret_val = nrf_crypto_ecdsa_sizes_get(sig_info, &sig_sizes);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    // Check the private key size.
    if (p_private_key->length != sig_sizes.private_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check if hash size.
    if (p_hash->length != sig_sizes.hash_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check the signature size.
    if (p_signature->length != sig_sizes.signature_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Get the curve domain to use for signing
    if (!micro_ecc_curve_domain_get(sig_info.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    // Create a signature of the hash data.
    if(uECC_sign(p_private_key->p_value, p_hash->p_value, p_hash->length, p_signature->p_value, p_curve))
    {
        return NRF_ERROR_INTERNAL;
    }
    
    return NRF_SUCCESS;
}

#endif

uint32_t nrf_crypto_ecdsa_verify_hash(nrf_crypto_signature_info_t  sig_info,
                                      nrf_value_length_t   const * p_public_key,
                                      nrf_value_length_t   const * p_hash,
                                      nrf_value_length_t   const * p_signature)
{
    uint32_t                    ret_val;
    nrf_crypto_ecdsa_sizes_t    sig_sizes;
    const struct uECC_Curve_t * p_curve = uECC_secp256r1();
    
    // Parameter NULL testing
    if (p_public_key == NULL || 
        p_hash == NULL       ||
        p_signature == NULL   )
    {
        return NRF_ERROR_NULL;
    }
    
    if (p_public_key->p_value == NULL   ||
        p_hash->p_value == NULL         ||
        p_signature->p_value == NULL    )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Check alignment for data.
    if (!is_word_aligned(p_public_key->p_value)     || 
        !is_word_aligned(p_hash->p_value)           || 
        !is_word_aligned(p_signature->p_value)      )
    {
        return NRF_ERROR_INVALID_ADDR;
    }
    
    // Get the sizes for the keys, hash and signature
    ret_val = nrf_crypto_ecdsa_sizes_get(sig_info, &sig_sizes);
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    
    // Check the public key size.
    if (p_public_key->length != sig_sizes.public_key_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check the hash size.
    if (p_hash->length != sig_sizes.hash_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Check the signature size.
    if (p_signature->length != sig_sizes.signature_size)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    
    // Get the curve domain to use for verifying
    #if 0
    // Optimizer in keil/gcc not able to optimize away other unused curves. 
    // Setting to only supported curve type.
    if (!micro_ecc_curve_domain_get(sig_info.curve_type, &p_curve))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    #else
    if (sig_info.curve_type != NRF_CRYPTO_CURVE_SECP256R1)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    #endif
    
    // Verify the signature by the hash
    if (uECC_verify(p_public_key->p_value, p_hash->p_value, p_hash->length, p_signature->p_value, p_curve) == 0)
    {
        return NRF_ERROR_INVALID_DATA;
    }
    
    return NRF_SUCCESS;
}
    
#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
