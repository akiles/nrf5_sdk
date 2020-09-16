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
#ifndef NRF_CRYPTO_ECDH_H__
#define NRF_CRYPTO_ECDH_H__

/** @file
 *
 * @defgroup nrf_crypto_ecdh ECDH related functions
 * @{
 * @ingroup nrf_crypto
 *
 * @brief Provides ECDH related functionality through nrf_crypto.
 */

#include <stdint.h>
#include "nrf_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif


/** @brief Macro to create an instance of a ECDH shared secret with a given name.
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the shared secret without using dynamically allocated memory.
 *
 * @param[in]   name    Name of the variable to hold an ECDH shared secret.
 * @param[in]   type    Either SECP160R1, SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 */
#define NRF_CRYPTO_ECDH_SHARED_SECRET_INSTANCE_CREATE(name, type)                               \
__ALIGN(4) static uint8_t                                                                       \
    name ## _backing[STRING_CONCATENATE(NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_, type)];            \
static nrf_value_length_t  name =                                                               \
{                                                                                               \
    .p_value = name ## _backing,                                                                \
    .length = STRING_CONCATENATE(NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_, type)                     \
}


/** @brief Macro to create an instance of a ECDH shared secret with a given name, type and input.
 *
 *  If the input is not of the correct size a static assert will be occur compile-time.
 *
 * @note    This creates the value length structure used for nrf_crypto APIs and a
 *          buffer to hold the shared secret without using dynamically allocated memory.
 *
 * @param[in]   name    Name of the variable to hold an ECDH shared secret.
 * @param[in]   type    Either SECP160R1, SECP192R1, SECP224R1, SECP256R1, SECP384R1,
 *                      SECP521R1, SECP192K1, SECP224K1, or SECP256K1.
 * @param[in]   input   Input must be an array of correct size according to the curve type.
 */
#define NRF_CRYPTO_ECDH_SHARED_SECRET_CREATE_FROM_ARRAY(name, type, input)                      \
STATIC_ASSERT(sizeof(input) == STRING_CONCATENATE(NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_, type));  \
static nrf_value_length_t  name =                                                               \
{                                                                                               \
    .p_value = input,                                                                           \
    .length = STRING_CONCATENATE(NRF_CRYPTO_ECDH_SHARED_SECRET_SIZE_, type)                     \
}


/**@brief Function to get the shared secret size given curve type.
 *
 * @param[in]       curve_type      Elliptic curve to use.
 * @param[in,out]   p_size          Pointer to variable to hold size of shared secret.
 *
 * @retval NRF_SUCCESS                  Shared secret size was calculated.
 * @retval NRF_ERROR_NOT_SUPPORTED      Selected curve was not supported.
 */
uint32_t nrf_crypto_ecdh_shared_secret_size_get(nrf_ecc_curve_type_t    curve_type,
                                                uint32_t              * p_size);


/**@brief Function to allocate dynamic memory for ECDH shared secret.
 *
 * @param[in]       curve_type          Elliptic curve to use.
 * @param[in,out]   p_shared_secret     Pointer to structure to hold a shared secret.
 * @param[in]       p_raw_shared_secret Pointer to structure holding a raw representation
 *                                      of a shared secret. If this is not NULL, the value
 *                                      will be copied to the allocated memory.
 *
 * @retval  NRF_SUCCESS     Memory for the public key was successfully allocated.
   @retval  NRF_ERROR_NULL  If any of the parameters was NULL.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecdh_shared_secret_allocate(nrf_crypto_curve_info_t     curve_type,
                                                nrf_value_length_t        * p_shared_secret,
                                                nrf_value_length_t  const * p_raw_shared_secret);


/**@brief Function to free allocated memory for ECDH shared secret.
 *
 * @param[in]       p_shared_secret
 *
 * @retval  NRF_SUCCESS     Memory for the ECDH shared secret was successfully freed.
 * @retval  Any other error code reported by the memory manager.
 */
uint32_t nrf_crypto_ecdh_shared_secret_free(nrf_value_length_t * p_shared_secret);


/**@brief Function for computing a shared secret from a key pair.
 *
 * @note    Length of allocated buffers for private key, public key and
 *          shared secret is taken as input.
 *
 * @param[in]       curve_info      Elliptic curve to use, and requested endianness of @p p_shared_secret.
 * @param[in]       p_private_key   Pointer to structure holding private key.
 * @param[in]       p_public_key    Pointer to structure holding public key.
 * @param[in,out]   p_shared_secret Pointer to structure to hold the calculated shared secret.
 *                                  After the call the length variable will be updated to the
 *                                  actual length of the shared secret data
 *
 * @retval  NRF_SUCCESS                 If the shared secret was computed successfully.
 * @retval  NRF_ERROR_INVALID_STATE     If the function was called when nrf_crypto was uninitialized.
 * @retval  NRF_ERROR_NULL              If the provided key, hash or signature parameters was NULL.
 * @retval  NRF_ERROR_NOT_SUPPORTED     If the selected elliptic curve is not supported.
 * @retval  NRF_ERROR_INVALID_ADDR      If any of the provided pointers are invalid.
 * @retval  NRF_ERROR_INVALID_DATA      If any of the keys or result data is deemed invalid by the
 *                                      nrf_crypto backend.
 * @retval  NRF_ERROR_INVALID_LENGTH    If the length of allocated data for keys or result is 
 *                                      incorrect.
 * @retval  NRF_ERROR_INTERNAL          If an internal error occured in the nrf_crypto backend.
 */
uint32_t nrf_crypto_ecdh_shared_secret_compute(nrf_crypto_curve_info_t    curve_info,
                                               nrf_value_length_t const * p_private_key,
                                               nrf_value_length_t const * p_public_key,
                                               nrf_value_length_t       * p_shared_secret);


/**@brief Macro to express curve information for Bluetooth LE Secure Connection (LESC)
 */
#define NRF_CRYPTO_BLE_ECDH_CURVE_INFO (nrf_crypto_curve_info_t)    \
{                                                                   \
    .curve_type = NRF_CRYPTO_CURVE_SECP256R1,                       \
    .endian_type = NRF_CRYPTO_ENDIAN_LE                             \
}


#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef NRF_CRYPTO_ECDH_H__
