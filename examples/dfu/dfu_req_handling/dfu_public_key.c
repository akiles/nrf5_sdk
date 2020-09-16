
/* This file was automatically generated by nrfutil on 2017-06-30 (YY-MM-DD) at 16:51:49 */

#include "stdint.h"
#include "compiler_abstraction.h"

/* This file was generated with a throwaway private key, that is only inteded for a debug version of the DFU project.
  Please see https://github.com/NordicSemiconductor/pc-nrfutil/blob/master/README.md to generate a valid public key. */

#ifdef NRF_DFU_DEBUG_VERSION 

/** @brief Public key used to verify DFU images */
__ALIGN(4) const uint8_t pk[64] =
{
    0x9d, 0xa7, 0x84, 0xd0, 0xf3, 0x56, 0xa0, 0x11, 0xf7, 0xdf, 0xb6, 0xfb, 0x73, 0xfa, 0xea, 0x4d, 0x1a, 0xbe, 0x9f, 0x23, 0x11, 0x19, 0x46, 0x24, 0x23, 0x09, 0x0c, 0xba, 0xb2, 0xd2, 0x2a, 0x33, 
    0x2c, 0x2d, 0xed, 0x55, 0x3f, 0x89, 0xa6, 0x54, 0x36, 0x3e, 0x4f, 0xc2, 0x1a, 0x2d, 0xac, 0xd9, 0x88, 0x46, 0x69, 0xbf, 0x65, 0x9a, 0xf8, 0xf6, 0x22, 0xb3, 0x5b, 0x39, 0x3d, 0x6b, 0xce, 0x70
};

#else
#error "Debug public key not valid for production. Please see https://github.com/NordicSemiconductor/pc-nrfutil/blob/master/README.md to generate it"
#endif
