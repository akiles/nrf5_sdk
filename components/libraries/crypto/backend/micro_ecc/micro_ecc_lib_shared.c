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

#include "micro_ecc_lib_shared.h"
#include "nrf_crypto_types.h"
#include "uECC.h"

bool micro_ecc_curve_domain_get(nrf_ecc_curve_type_t curve_type, struct uECC_Curve_t const ** p_curve)
{
    switch(curve_type)
    {
#if defined(uECC_SUPPORTS_secp160r1) && uECC_SUPPORTS_secp160r1 == 1
        case NRF_CRYPTO_CURVE_SECP160R1:
            *p_curve = uECC_secp160r1();
            break;
#endif

#if defined(uECC_SUPPORTS_secp192r1) && uECC_SUPPORTS_secp192r1 == 1
        case NRF_CRYPTO_CURVE_SECP192R1:
            *p_curve = uECC_secp192r1();
            break;
#endif

#if defined(uECC_SUPPORTS_secp224r1) && uECC_SUPPORTS_secp224r1 == 1
        case NRF_CRYPTO_CURVE_SECP224R1:
            *p_curve = uECC_secp224r1();
            break;

#endif

        case NRF_CRYPTO_CURVE_SECP256R1:
            *p_curve = uECC_secp256r1();
            break;

#if defined(uECC_SUPPORTS_secp256k1) && defined(NRF_CRYPTO_CURVE_SECP256R1)
#if NRF_CRYPTO_CURVE_SECP256R1 == 1
        case NRF_CRYPTO_CURVE_SECP256K1:
            *p_curve = uECC_secp256k1();
            break;
#endif
#endif

        default:
            return false;

    }

    return true;
}


#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
