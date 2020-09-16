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
 
/** @file
 *
 * @defgroup nfc_ac_rec_parser Alternative Carrier records parser
 * @{
 * @ingroup nfc_ble_pair_msg
 * @brief Functions for parsing and decoding Alternative Carrier records.
 */

#ifndef __NFC_AC_REC_PARSER_H__
#define __NFC_AC_REC_PARSER_H__

#include "nfc_ndef_record.h"
#include "nfc_ac_rec.h"

/**
 * @brief Function for parsing general record description as Alternative Carrier record.
 *
 * This function checks if record description matches the Alternative Carrier record and extracts
 * its payload structure. It is required for the record description to use binary payload
 * descriptor.
 *
 * @param[in]     p_rec_desc             Pointer to the record descriptor.
 * @param[in,out] p_ac_rec_payload_data  Pointer to the structure that will be used to hold
 *                                       parsed data.
 * 
 * @retval NRF_SUCCESS                 If the function completed successfully.
 * @retval NRF_ERROR_INVALID_DATA      If the NDEF record type or TNF is incorrect.
 * @retval NRF_ERROR_NOT_SUPPORTED     If the payload descriptor is not binary.
 * @retval NRF_ERROR_NULL              If any provided arguments or any needed buffers stored in 
 *                                     \p p_ac_rec_payload_data are nulls.
 * @retval NRF_ERROR_NO_MEM            If any from provided buffers does not have enough space
 *                                     to store its data.
 * @retval NRF_ERROR_INVALID_LENGTH    If any length field exceeds record payload.
 * @retval NRF_ERROR_INVALID_PARAM     If Carrier Power State field has incorrect value.
 */
ret_code_t nfc_ac_rec_parse(nfc_ndef_record_desc_t    const * const p_rec_desc, 
                            nfc_ac_rec_payload_desc_t       * const p_ac_rec_payload_data);

#endif // __NFC_AC_REC_PARSER_H__

/** @} */
