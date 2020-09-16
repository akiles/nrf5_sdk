/*
This software is subject to the license described in the license.txt file included with this software distribution.
You may not use this file except in compliance with this license.
Copyright © Dynastream Innovations Inc. 2014
All rights reserved.
*/

#ifndef ANTFS_OTA_H__
#define ANTFS_OTA_H__

#include <stdint.h>

/*
 * OTA Update Information File
 */
#define OTA_INFO_FILE_STRUCTURE_VERSION_BYTES           1
#define OTA_INFO_HARDWARE_VERSION_BYTES                 1
#define OTA_INFO_REGION_PRODUCT_ID_BYTES                1
#define OTA_INFO_MAXIMUM_SWAP_SPACE_BYTES               4
#define OTA_INFO_WIRELESS_STACK_VERSION_ID_BYTES        4
#define OTA_INFO_WIRELESS_STACK_VERSION_LENGTH_BYTES    1
#define OTA_INFO_WIRELESS_STACK_VERSION_STRING_BYTES    16
#define OTA_INFO_BOOTLOADER_VERSION_ID_BYTES            4
#define OTA_INFO_BOOTLOADER_VERSION_LENGTH_BYTES        1
#define OTA_INFO_BOOTLOADER_VERSION_STRING_BYTES        16
#define OTA_INFO_APPLICATION_VERSION_ID_BYTES           4
#define OTA_INFO_APPLICATION_VERSION_LENGTH_BYTES       1
#define OTA_INFO_APPLICATION_VERSION_STRING_BYTES       16

#define OTA_INFO_FILE_STRUCTURE_VERSION_OFFSET          0
#define OTA_INFO_HARDWARE_VERSION_OFFSET                OTA_INFO_FILE_STRUCTURE_VERSION_OFFSET          + OTA_INFO_FILE_STRUCTURE_VERSION_BYTES
#define OTA_INFO_REGION_PRODUCT_ID_OFFSET               OTA_INFO_HARDWARE_VERSION_OFFSET                + OTA_INFO_HARDWARE_VERSION_BYTES
#define OTA_INFO_MAXIMUM_SWAP_SPACE_OFFSET              OTA_INFO_REGION_PRODUCT_ID_OFFSET               + OTA_INFO_REGION_PRODUCT_ID_BYTES
#define OTA_INFO_WIRELESS_STACK_VERSION_ID_OFFSET       OTA_INFO_MAXIMUM_SWAP_SPACE_OFFSET              + OTA_INFO_MAXIMUM_SWAP_SPACE_BYTES
#define OTA_INFO_WIRELESS_STACK_VERSION_LENGTH_OFFSET   OTA_INFO_WIRELESS_STACK_VERSION_ID_OFFSET       + OTA_INFO_WIRELESS_STACK_VERSION_ID_BYTES
#define OTA_INFO_WIRELESS_STACK_VERSION_STRING_OFFSET   OTA_INFO_WIRELESS_STACK_VERSION_LENGTH_OFFSET   + OTA_INFO_WIRELESS_STACK_VERSION_LENGTH_BYTES
#define OTA_INFO_BOOTLOADER_VERSION_ID_OFFSET           OTA_INFO_WIRELESS_STACK_VERSION_STRING_OFFSET   + OTA_INFO_WIRELESS_STACK_VERSION_STRING_BYTES
#define OTA_INFO_BOOTLOADER_VERSION_LENGTH_OFFSET       OTA_INFO_BOOTLOADER_VERSION_ID_OFFSET           + OTA_INFO_BOOTLOADER_VERSION_ID_BYTES
#define OTA_INFO_BOOTLOADER_VERSION_STRING_OFFSET       OTA_INFO_BOOTLOADER_VERSION_LENGTH_OFFSET       + OTA_INFO_BOOTLOADER_VERSION_LENGTH_BYTES
#define OTA_INFO_APPLICATION_VERSION_ID_OFFSET          OTA_INFO_BOOTLOADER_VERSION_STRING_OFFSET       + OTA_INFO_BOOTLOADER_VERSION_STRING_BYTES
#define OTA_INFO_APPLICATION_VERSION_LENGTH_OFFSET      OTA_INFO_APPLICATION_VERSION_ID_OFFSET          + OTA_INFO_APPLICATION_VERSION_ID_BYTES
#define OTA_INFO_APPLICATION_VERSION_STRING_OFFSET      OTA_INFO_APPLICATION_VERSION_LENGTH_OFFSET      + OTA_INFO_APPLICATION_VERSION_LENGTH_BYTES
#define OTA_INFO_FILE_END_OFFSET                        OTA_INFO_APPLICATION_VERSION_STRING_OFFSET      + OTA_INFO_APPLICATION_VERSION_STRING_BYTES

#define OTA_UPDATE_INFO_FILE_DATA_TYPE                  ((uint8_t)0x0E)
#define OTA_UPDATE_INFO_FILE_SIZE                       ((uint32_t)OTA_INFO_FILE_END_OFFSET)

#define OTA_INFO_FILE_STRUCTURE_VERSION                 ((uint8_t)0x10) //The most significant 4 bits indicate major revision, while the least significant 4 bits indicate a minor revision.
#define OTA_INFO_HARDWARE_VERSION                       ((uint8_t)0x00) //TODO TBD
#define OTA_INFO_REGION_PRODUCT_ID                      ((uint8_t)0x00) //TODO TBD

#define OTA_INFO_WIRELESS_STACK_VERSION_ID              ((uint32_t)0x00000000)
#define OTA_INFO_BOOTLOADER_VERSION_ID                  ((uint32_t)0x00000000)
#define OTA_INFO_APPLICATION_VERSION_ID                 ((uint32_t)0x00000000)

/*
 * OTA Update Image File
 */
#define OTA_IMAGE_HEADER_SIZE_OFFSET                                    0
#define OTA_IMAGE_HEADER_FILE_STRUCT_VER_OFFSET                         1
#define OTA_IMAGE_HEADER_ARCH_ID_OFFSET                                 2
#define OTA_IMAGE_HEADER_ID_STRING_OFFSET                               4
#define OTA_IMAGE_HEADER_IMAGE_FORMAT_OFFSET                            8
#define OTA_IMAGE_HEADER_RESERVED                                       9
#define OTA_IMAGE_HEADER_IMAGE_STACK_SIZE_OFFSET                        10
#define OTA_IMAGE_HEADER_IMAGE_BOOTLOADER_SIZE_OFFSET                   14
#define OTA_IMAGE_HEADER_IMAGE_APPLICATION_SIZE_OFFSET                  18
#define OTA_IMAGE_HEADER_VERSION_INFO_SIZE_OFFSET                       22

#define OTA_IMAGE_HEADER_SIZE_MAX                                       256
#define OTA_IMAGE_HEADER_ID_STRING_SIZE_MAX                             4

#define OTA_IMAGE_VERSION_INFO_SIZE_MIN                                 15
#define OTA_IMAGE_VERSION_INFO_SIZE_MAX                                 780
#define OTA_IMAGE_VERSION_INFO_MAX                                      OTA_IMAGE_VERSION_INFO_SIZE_MIN

#define OTA_IMAGE_CRC_SIZE_MAX                                          2

typedef struct
{
    uint8_t     header_size;
    uint8_t     file_struct_version;
    uint16_t    architecture_identifier;
    uint8_t     identifier_string[4];
    uint8_t     image_format;
    uint8_t     reserved;
    uint32_t    wireless_stack_size;
    uint32_t    bootloader_size;
    uint32_t    application_size;
    uint16_t    version_info_size;
}ota_image_header_t;

void antfs_ota_update_information_file (uint8_t * p_data, uint32_t * p_length);
ota_image_header_t * antfs_ota_image_header_parsing (uint8_t * p_data, uint32_t length);

bool antfs_ota_version_info_parsing (uint8_t ** p_data, uint32_t * p_length);
uint8_t * antfs_ota_version_info_get(uint16_t * p_info_len);

bool antfs_ota_crc_parsing(uint8_t ** p_data, uint32_t * p_length);
uint16_t antfs_ota_crc_get (void);

#endif // ANTFS_OTA_H__
