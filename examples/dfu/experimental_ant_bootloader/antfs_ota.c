/*
This software is subject to the license described in the license.txt file included with this software distribution.
You may not use this file except in compliance with this license.
Copyright © Dynastream Innovations Inc. 2014
All rights reserved.
*/
#include <stdint.h>
#include <string.h>

#include "ant_interface.h"                      // ant stack softdevice access
#include "ant_boot_settings.h"
#include "antfs.h"
#include "antfs_ota.h"

#include "dfu_types.h"                          //
#include "app_error.h"

#include "version.c"
static const uint8_t        identifier_string[4] = {".SUF"};
static uint8_t              m_version_info[OTA_IMAGE_VERSION_INFO_MAX];
static uint8_t              m_crc[OTA_IMAGE_CRC_SIZE_MAX];

static ota_image_header_t   ota_image_header;
static uint16_t             m_version_info_count = 0;
static uint8_t              m_crc_count = 0;

/**/

void antfs_ota_update_information_file (uint8_t * p_data, uint32_t * p_length)
{
    uint32_t u32_temp, err_code;

    p_data[OTA_INFO_FILE_STRUCTURE_VERSION_OFFSET]  = OTA_INFO_FILE_STRUCTURE_VERSION;                          /* File Structure Version */
    p_data[OTA_INFO_HARDWARE_VERSION_OFFSET]        = OTA_INFO_HARDWARE_VERSION;                                /* Hardware Version */
    p_data[OTA_INFO_REGION_PRODUCT_ID_OFFSET]       = OTA_INFO_REGION_PRODUCT_ID;                               /* Region/Product Identifier*/

    u32_temp = DFU_IMAGE_MAX_SIZE_FULL;                                                                         /* Maximum swap space */
    (void)uint32_encode(u32_temp, &p_data[OTA_INFO_MAXIMUM_SWAP_SPACE_OFFSET]);

    u32_temp = OTA_INFO_WIRELESS_STACK_VERSION_ID;
    (void)uint32_encode(u32_temp, &p_data[OTA_INFO_WIRELESS_STACK_VERSION_ID_OFFSET]);                          /* Wireless Protocol Stack Version Identifier*/

    p_data[OTA_INFO_WIRELESS_STACK_VERSION_LENGTH_OFFSET]   = OTA_INFO_WIRELESS_STACK_VERSION_STRING_BYTES;     /* Wireless Protocol Stack Version String Length*/

    err_code = sd_ant_version_get(&p_data[OTA_INFO_WIRELESS_STACK_VERSION_STRING_OFFSET]);                      /* Wireless Protocol Stack Version String*/
    APP_ERROR_CHECK(err_code);

    u32_temp = OTA_INFO_BOOTLOADER_VERSION_ID;
    (void)uint32_encode(u32_temp, &p_data[OTA_INFO_BOOTLOADER_VERSION_ID_OFFSET]);                              /* Bootloader Version Identifier*/

    p_data[OTA_INFO_BOOTLOADER_VERSION_LENGTH_OFFSET]   = OTA_INFO_BOOTLOADER_VERSION_STRING_BYTES;             /* Bootloader Version String Length*/

    memcpy(&p_data[OTA_INFO_BOOTLOADER_VERSION_STRING_OFFSET],                                                  /* Bootloader Version String*/
            ac_bootloader_version,
            sizeof(ac_bootloader_version));

    u32_temp = OTA_INFO_APPLICATION_VERSION_ID;
    (void)uint32_encode(u32_temp, &p_data[OTA_INFO_APPLICATION_VERSION_ID_OFFSET]);                             /* Application Version Identifier*/

    p_data[OTA_INFO_APPLICATION_VERSION_LENGTH_OFFSET]  = OTA_INFO_APPLICATION_VERSION_STRING_BYTES;            /* Application Version String Length*/

    memcpy(&p_data[OTA_INFO_APPLICATION_VERSION_STRING_OFFSET],                                                 /* Application Version String*/
            ANT_BOOT_APP_VERSION,
            OTA_INFO_APPLICATION_VERSION_STRING_BYTES);

    *p_length = OTA_UPDATE_INFO_FILE_SIZE;
}


ota_image_header_t * antfs_ota_image_header_parsing(uint8_t * p_data, uint32_t length)
{
    ota_image_header.header_size                     = p_data[OTA_IMAGE_HEADER_SIZE_OFFSET];
    ota_image_header.file_struct_version             = p_data[OTA_IMAGE_HEADER_FILE_STRUCT_VER_OFFSET];
    ota_image_header.architecture_identifier         = uint16_decode((uint8_t*)(&p_data[OTA_IMAGE_HEADER_ARCH_ID_OFFSET]));
    for (uint8_t ndx=0; ndx < OTA_IMAGE_HEADER_ID_STRING_SIZE_MAX; ndx++)
    {
        ota_image_header.identifier_string[ndx]      = p_data[OTA_IMAGE_HEADER_ID_STRING_OFFSET + ndx];
    }
    ota_image_header.image_format                    = p_data[OTA_IMAGE_HEADER_IMAGE_FORMAT_OFFSET];
    ota_image_header.wireless_stack_size             = uint32_decode((uint8_t*)(&p_data[OTA_IMAGE_HEADER_IMAGE_STACK_SIZE_OFFSET]));
    ota_image_header.bootloader_size                 = uint32_decode((uint8_t*)(&p_data[OTA_IMAGE_HEADER_IMAGE_BOOTLOADER_SIZE_OFFSET]));
    ota_image_header.application_size                = uint32_decode((uint8_t*)(&p_data[OTA_IMAGE_HEADER_IMAGE_APPLICATION_SIZE_OFFSET]));
    ota_image_header.version_info_size               = uint32_decode((uint8_t*)(&p_data[OTA_IMAGE_HEADER_VERSION_INFO_SIZE_OFFSET]));

    // Sanity Checks
    // Header size should not be bigger than the current parsed buffer or else its insufficient data.
    if (ota_image_header.header_size > length)
    {
        return NULL;
    }

    // verify .SUF file
    for (uint8_t ndx = 0; ndx < OTA_IMAGE_HEADER_ID_STRING_SIZE_MAX; ndx++)
    {
        if (ota_image_header.identifier_string[ndx] != identifier_string[ndx])
        {
            return NULL;
        }
    }

    // check version info size is within the range.
    if ((ota_image_header.version_info_size < OTA_IMAGE_VERSION_INFO_SIZE_MIN && ota_image_header.version_info_size != 0) ||
            (ota_image_header.version_info_size > OTA_IMAGE_VERSION_INFO_SIZE_MAX))
    {
        return NULL;
    }

    m_version_info_count = 0;
    m_crc_count = 0;

    return &ota_image_header;
}

// This parse the version_info
bool antfs_ota_version_info_parsing(uint8_t ** pp_data, uint32_t * p_length)
{
    while (*p_length)
    {
        if( m_version_info_count < ota_image_header.version_info_size)
        {
            m_version_info[m_version_info_count] = *(*pp_data);
            // advance the pointer, currently just throwing away the data.
            (*pp_data)++;
            // decrease the length
            (*p_length)--;
            // increase the version info count
            m_version_info_count++;
        }

        if( m_version_info_count == ota_image_header.version_info_size)
        {
            return  true;
        }
    }
    return false;
}

uint8_t * antfs_ota_version_info_get( uint16_t * p_info_len )
{
    *p_info_len = OTA_IMAGE_VERSION_INFO_MAX;
    return &m_version_info[0];
}

// This parse the crc
bool antfs_ota_crc_parsing(uint8_t ** pp_data, uint32_t * p_length)
{
    while (*p_length)
    {
        if( m_crc_count < OTA_IMAGE_CRC_SIZE_MAX)
        {
            m_crc[m_crc_count] = *(*pp_data);
            // advance the pointer, currently just throwing away the data.
            (*pp_data)++;
            // decrease the length
            (*p_length)--;
            // increase the version info count
            m_crc_count++;
        }

        if (m_crc_count == OTA_IMAGE_CRC_SIZE_MAX)
        {
            return true;
        }
    }
    return false;
}

uint16_t antfs_ota_crc_get (void)
{
    uint16_t ota_image_crc = 0;

    ota_image_crc = (uint16_t) m_crc[1] << 8;
    ota_image_crc |= (uint16_t) m_crc[0];

    return ota_image_crc;
}

