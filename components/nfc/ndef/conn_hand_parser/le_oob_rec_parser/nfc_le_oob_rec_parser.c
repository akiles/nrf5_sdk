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

#include "nfc_le_oob_rec_parser.h"
#include "sdk_errors.h"

/**
 * @brief Function for parsing LE OOB record payload.
 *
 * This function parses LE OOB record payload and extracts BLE OOB Advertising data structure.
 *
 * @param[in]     p_buff                       Pointer to the record payload.
 * @param[in]     p_len                        Pointer to the record payload length.
 * @param[in,out] p_nfc_ble_oob_pairing_data   Pointer to the structure that will be used to hold
 *                                             parsed data.
 * 
 * @retval NRF_SUCCESS              If the function completed successfully.
 * @retval Other                    An error code that might have been returned by
 *                                  @ref nfc_ble_oob_advdata_parse function.
 */
static ret_code_t nfc_le_oob_payload_parse(uint8_t                    * p_buff, 
                                           uint32_t                   * const p_len,
                                           nfc_ble_oob_pairing_data_t * const p_nfc_ble_oob_pairing_data)
{
    ret_code_t err_code = nfc_ble_oob_advdata_parse(p_buff,
                                                    *p_len, 
                                                    p_nfc_ble_oob_pairing_data);
    return err_code;
}

ret_code_t nfc_le_oob_rec_parse(nfc_ndef_record_desc_t     const * const p_rec_desc, 
                                nfc_ble_oob_pairing_data_t       * const p_nfc_ble_oob_pairing_data)
{
    ret_code_t err_code;
    
    if (p_rec_desc->tnf != TNF_MEDIA_TYPE)
    {
        return NRF_ERROR_INVALID_DATA;
    }
    
    if (p_rec_desc->type_length != sizeof(le_oob_rec_type_field))
    {
        return NRF_ERROR_INVALID_DATA;
    }
    
    if (memcmp(p_rec_desc->p_type, le_oob_rec_type_field, sizeof(le_oob_rec_type_field)) != 0)
    {
        return NRF_ERROR_INVALID_DATA;
    }
    
    if (p_rec_desc->payload_constructor != (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    
    uint8_t const * p_payload = ((nfc_ndef_bin_payload_desc_t*)(p_rec_desc->p_payload_descriptor))->p_payload;
    uint32_t payload_lenght   = ((nfc_ndef_bin_payload_desc_t*)(p_rec_desc->p_payload_descriptor))->payload_length;

    err_code = nfc_le_oob_payload_parse((uint8_t *) p_payload, 
                                        &payload_lenght,
                                        p_nfc_ble_oob_pairing_data);
           
    return err_code;
}
