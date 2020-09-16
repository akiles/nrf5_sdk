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
 * @defgroup nfc_le_oob_rec_parser LE OOB records parser
 * @{
 * @ingroup nfc_ble_pair_msg
 * @brief Functions for parsing and decoding LE OOB records.
 */

#ifndef __NFC_LE_OOB_REC_PARSER_H__
#define __NFC_LE_OOB_REC_PARSER_H__

#include "nfc_ndef_record.h"
#include "nfc_ble_oob_advdata_parser.h"
#include "nfc_ble_pair_common.h"

/**
 * @brief Function for parsing general record description as LE OOB record.
 *
 * This function checks if record description matches the LE OOB record pattern and extracts BLE
 * OOB Advertising data structure. It is required for the record description to use binary payload
 * descriptor.
 *
 * @param[in]     p_rec_desc                   Pointer to the record descriptor.
 * @param[in,out] p_nfc_ble_oob_pairing_data   Pointer to the structure that will be used to hold
 *                                             parsed data.
 * 
 * @retval NRF_SUCCESS              If the function completed successfully.
 * @retval NRF_ERROR_INVALID_DATA   If the NDEF record type or TNF is incorrect.
 * @retval NRF_ERROR_NOT_SUPPORTED  If the payload descriptor is not binary.
 * @retval Other                    An error code that might have been returned by
 *                                  @ref nfc_ble_oob_advdata_parse function.
 */
ret_code_t nfc_le_oob_rec_parse(nfc_ndef_record_desc_t     const * const p_rec_desc, 
                                nfc_ble_oob_pairing_data_t       * const p_nfc_ble_oob_pairing_data);

#endif // __NFC_LE_OOB_REC_PARSER_H__

/** @} */
