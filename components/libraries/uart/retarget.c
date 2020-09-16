/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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
 
#include <stdio.h>
#include <stdint.h>
#include "app_uart.h"
#include "nordic_common.h"
#include "nrf_error.h"

struct __FILE 
{
    int handle;
};
FILE __stdout;
FILE __stdin;

static const uint8_t overflow_message[] = "\r\nERROR: BUFFOR OVERFLOW\r\n";

#if defined(__CC_ARM)
int fgetc(FILE *p_file)
{
  uint8_t input;
  while (NRF_ERROR_NOT_FOUND == app_uart_get(&input))
  {
      // No implementation needed.
  }
  return input;
}

int fputc(int ch, FILE * p_file)
{
  uint32_t err_code = app_uart_put((uint8_t)ch);
  if (err_code == NRF_ERROR_NO_MEM)
  {
    UNUSED_PARAMETER(app_uart_flush());
    for (uint32_t i = 0; i < sizeof(overflow_message); i++)
    {
      UNUSED_VARIABLE(app_uart_put(overflow_message[i]));
    }
  }
  return ch;
}

#elif defined(__GNUC__)

int _write(int file, const char *ptr, int len)
{
    int i;
    uint32_t err_code;

    UNUSED_PARAMETER(file);

    for (i = 0; i < len; i++)
    {
      err_code = app_uart_put(*ptr++);
      if (err_code == NRF_ERROR_NO_MEM)
      {
          UNUSED_PARAMETER(app_uart_flush());
          for (uint32_t i = 0; i < sizeof(overflow_message); i++)
          {
              UNUSED_VARIABLE(app_uart_put(overflow_message[i]));
          }
      }
    }

    return len;
}

int _read(int file, char *ptr, int len)
{
  int ret_len = len;
  uint8_t input;
  UNUSED_PARAMETER(file);

  while (len--)
  {
    UNUSED_VARIABLE(app_uart_get(&input));
    *ptr++ = input;
  }

  return ret_len;
}
#endif

