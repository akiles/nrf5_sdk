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

#include "nrf_drv_rng.h"
#include "nrf_crypto_rng.h"

#if defined(NRF_CRYPTO_BACKEND_MICRO_ECC) && (NRF_CRYPTO_BACKEND_MICRO_ECC == 1)
#if defined(NRF_CRYPTO_SUPPORTS_RNG) && (NRF_CRYPTO_SUPPORTS_RNG == 1)

#include "uECC.h"

/** @brief  Function to greate random data conformant to the format of the
 *          micro_ecc API.
 */
static int rng_func(uint8_t * p_target, unsigned size)
{
    uint32_t err_code;
    err_code = nrf_crypto_rng_vector_generate(p_target, size);
    if (err_code == NRF_SUCCESS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


uint32_t nrf_crypto_rng_init(void)
{
    uint32_t ret_val;

    ret_val = nrf_drv_rng_init(NULL);
    if (ret_val == NRF_SUCCESS)
    {
        uECC_set_rng(rng_func);
    }

    return ret_val;
}


uint32_t nrf_crypto_rng_vector_generate(uint8_t * p_target, uint32_t length)
{
    uint32_t err_code;
    uint8_t  available;
    uint8_t  cur_len;
    uint8_t  left           = length;

    if (p_target == NULL)
    {
        return NRF_ERROR_NULL;
    }

    do
    {
        nrf_drv_rng_bytes_available(&available);
        cur_len = MIN(left, available);

        err_code = nrf_drv_rng_rand(p_target + (length - left), cur_len);
        if(err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        // Remove current length of generated data
        left -= cur_len;

    } while(left > 0);

    return NRF_SUCCESS;
}

#endif // NRF_CRYPTO_SUPPORTS_RNG

#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_CRYPTO_BACKEND_SW
