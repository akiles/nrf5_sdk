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

#include "nrf_crypto.h"
#include "cc310_lib_shared.h"
#include "crys_ecpki_domain.h"

bool cc310_curve_domain_get(nrf_ecc_curve_type_t curve_type, CRYS_ECPKI_Domain_t ** p_domain)
{   
    CRYS_ECPKI_DomainID_t domain_id;
    switch(curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            domain_id = CRYS_ECPKI_DomainID_secp160r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192R1:
            domain_id = CRYS_ECPKI_DomainID_secp192r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224R1:
            domain_id = CRYS_ECPKI_DomainID_secp224r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP256R1:
            domain_id = CRYS_ECPKI_DomainID_secp256r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP384R1:
            domain_id = CRYS_ECPKI_DomainID_secp384r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP521R1:
            domain_id = CRYS_ECPKI_DomainID_secp521r1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP192K1:
            domain_id = CRYS_ECPKI_DomainID_secp160k1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP224K1:
            domain_id = CRYS_ECPKI_DomainID_secp224k1;
            break;
        
        case NRF_CRYPTO_CURVE_SECP256K1:
            domain_id = CRYS_ECPKI_DomainID_secp256k1;
            break;
        
        default:
            return false;
    }
    
    (*p_domain) = (CRYS_ECPKI_Domain_t*)CRYS_ECPKI_GetEcDomain(domain_id);
    return true;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
