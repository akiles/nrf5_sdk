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

#include "cc310_lib_hash.h"
#include "cc310_lib_init.h"
#include <stdbool.h>
#include "crys_hash.h"
#include "crys_hash_error.h"
#include "nrf_error.h"
#include "crys_rnd.h"

bool hash_algorithm_get(nrf_hash_type_t hash_type, CRYS_HASH_OperationMode_t * p_hash_mode)
{
    if (p_hash_mode == NULL)
    {
        return false;
    }

    switch(hash_type)
    {
        case NRF_CRYPTO_HASH_TYPE_MD5:
            (*p_hash_mode) = CRYS_HASH_MD5_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA1:
            (*p_hash_mode) = CRYS_HASH_SHA1_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA224:
            (*p_hash_mode) = CRYS_HASH_SHA224_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA256:
            (*p_hash_mode) = CRYS_HASH_SHA256_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA384:
            (*p_hash_mode) = CRYS_HASH_SHA384_mode;
            break;

        case NRF_CRYPTO_HASH_TYPE_SHA512:
            (*p_hash_mode) = CRYS_HASH_SHA512_mode;
            break;

        default:
            return NRF_ERROR_NOT_SUPPORTED;
    }

    return NRF_SUCCESS;
}


static uint32_t hash_result_get(CRYSError_t error)
{
    uint32_t ret_val;

    switch(error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        case CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        case CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR:
            ret_val = NRF_ERROR_INVALID_DATA;
            break;

        case CRYS_HASH_DATA_IN_POINTER_INVALID_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_DATA_SIZE_ILLEGAL:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_INVALID_RESULT_BUFFER_POINTER_ERROR:
            ret_val = NRF_ERROR_INVALID_ADDR;
            break;

        case CRYS_HASH_DATA_SIZE_IS_ILLEGAL_FOR_CSI_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR:
            ret_val = NRF_ERROR_INVALID_STATE;
            break;

        case CRYS_HASH_ILLEGAL_PARAMS_ERROR:
            ret_val = NRF_ERROR_INTERNAL;
            break;

        case CRYS_HASH_CTX_SIZES_ERROR:
            ret_val = NRF_ERROR_INVALID_LENGTH;
            break;

        case CRYS_HASH_IS_NOT_SUPPORTED:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;
}


uint32_t nrf_crypto_hash_init(nrf_crypto_hash_info_t    hash_info,
                              nrf_value_length_t      * p_hash_context)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASH_OperationMode_t   hash_type = CRYS_HASH_OperationModeLast;
    CRYS_HASHUserContext_t    * p_hash_context_user;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_hash_context == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash_context->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if (p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (!hash_algorithm_get(hash_info.hash_type, &hash_type))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (hash_info.endian_type != NRF_CRYPTO_ENDIAN_LE)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    crys_error = CRYS_HASH_Init(p_hash_context_user, hash_type);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_update(nrf_value_length_t   * p_hash_context,
                                uint8_t        const * p_data,
                                uint32_t               len)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASHUserContext_t    * p_hash_context_user;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_hash_context == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (p_hash_context->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if (p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    crys_error = CRYS_HASH_Update(p_hash_context_user, (uint8_t*)p_data, len);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_finalize(nrf_crypto_hash_info_t    hash_info,
                                  nrf_value_length_t      * p_hash_context,
                                  nrf_value_length_t      * p_hash)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASHUserContext_t    * p_hash_context_user;
    CRYS_HASH_Result_t *        p_hash_result = (CRYS_HASH_Result_t *)p_hash->p_value;

    // Check if library has been initialized
    if (!nrf_crypto_is_initialized())
    {
        return NRF_ERROR_INVALID_STATE;
    }

    // Check the parameters
    if (p_hash_context == NULL  ||
        p_hash == NULL          )
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash_context->p_value == NULL ||
        p_hash->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    // Check the length of the hash context
    if(p_hash_context->length != NRF_CRYPTO_HASH_CONTEXT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Check the length of the hash


    // Convert hash context to cc310 user format
    p_hash_context_user = (CRYS_HASHUserContext_t *)p_hash_context->p_value;

    // Not sure about this
    crys_error = CRYS_HASH_Finish(p_hash_context_user, *p_hash_result);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_hash_compute(nrf_crypto_hash_info_t    hash_info,
                                 uint8_t           const * p_data,
                                 uint32_t                  len,
                                 nrf_value_length_t      * p_hash)
{
    uint32_t                    ret_val;
    CRYSError_t                 crys_error;
    CRYS_HASH_OperationMode_t   hash_type = CRYS_HASH_OperationModeLast;
    CRYS_HASH_Result_t        * p_hash_result;

    if (p_data == NULL || p_hash == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_hash->p_value == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if(!hash_algorithm_get(hash_info.hash_type, &hash_type))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Currently only supporting LE hash
    if(hash_info.endian_type != NRF_CRYPTO_ENDIAN_LE)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Convert output buffer to valid.
    p_hash_result = (CRYS_HASH_Result_t *)p_hash->p_value;


    crys_error = CRYS_HASH(hash_type, (uint8_t*)p_data, len, *p_hash_result);
    ret_val = hash_result_get(crys_error);
    return ret_val;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

