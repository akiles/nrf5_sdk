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

#ifndef BUTTONS_H__
#define BUTTONS_H__

#include <stdbool.h>

/**@brief Configures device buttons.
 *
 * @details Buttons are configured to generate key press events 
 *          handled by bsp_event_handler() function.
 */
void buttons_init(void);

#endif // BUTTONS_H__
