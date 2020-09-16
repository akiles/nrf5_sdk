/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
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
 
/**@file
 * @brief ANT bicycle power-only sensor application main entry. 
 * Configures and starts SoftDevice and all other needed modules.
 * @defgroup ant_bicycle_power_only_sensor ANT bicycle power-only sensor example
 * @{
 * @ingroup nrf_ant_bicycle_power
 *
 * @brief The bicycle power-only sensor implementation.
 *
 * The bicycle power-only sensor implementation implements all the features, 
 * which are required for the sensor to be compliant with the ANT+ Bike Power profile, 
 * as defined by the ANT+ Bicycle Power Profile specification:
 * - Transmit Power-Only main data page (0x10).
 * - Transmit Manufacturer Information (ANT Common Data Page).
 * - Transmit Product Information (ANT Common Data Page).
 * - Confirm to a manual zero-offset calibration procedure (0x01).
 * 
 * The general architecture of the power-only sensor is illustrated in the picture below.
 *
 *
 * @image html bicycle_power_only_tx_design.png "Architecture overview"
 *
 * @par User interface
 *
 * A simple user interface exists consisting of 2 keypad buttons, 
 * which allow the user to decrease or increase the instantaneous power value.
 *
 * @par Bicycle power-only sensor configuration options 
 *
 * The following compile time configuration options are available to suite various 
 * bicycle power-only sensor implementations:
 * - BP_NETWORK_KEY                      ANT PLUS network key.
 * - ANTPLUS_NETWORK_NUMBER              Network number associated with the channel.
 * - BP_TX_ANT_CHANNEL                   Channel number.
 * - BP_TX_DEVICE_NUMBER                 Device number.
 * - BP_DEVICE_TYPE                      Device type.
 * - BP_TX_TRANS_TYPE                    Transmission type.
 * - BP_RF_FREQ                          Channel radio frequency offset from 2400MHz.
 * - BP_MSG_PERIOD                       Channel period set to 32 kHz counts. 
 *
 * @par Development phase configuration options
 *
 * The bicycle power-only sensor will trace ASSERT macro specific information to UART depending on the 
 * selected compile time configuration options. 
 *
 * The following compile time configuration options are available, and enabled by default, to assist
 * in the development phase of the power-only sensor implementation:
 * - TRACE_UART           - Enable UART output.
 * 
 * @note The ANT+ Network Key is available for ANT+ Adopters. Please refer to http://thisisant.com 
 * to become an ANT+ Adopter and access the key. 
 */

#include <stdint.h>
#if defined(TRACE_UART)
    #include <stdio.h>  
    #include "app_uart.h"
#endif // defined(TRACE_UART) 
#include "ant_interface.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"
#include "boards.h"
#include "main_bicycle_power_only_tx.h"
#include "app_error.h"
#include "nordic_common.h"

#define UART_TX_BUF_SIZE 128u   /**< UART Tx buffer size. */
#define UART_RX_BUF_SIZE 1u     /**< UART Rx buffer size. */


/**@brief Function for handling SoftDevice asserts. Does not return.
 * 
 * Traces out the user supplied parameters and busy loops. 
 *
 * @param[in] pc             The value of the program counter.
 * @param[in] line_num       The line number where the assert occurred.
 * @param[in] p_file_name    File name where asserted.
 */
static void softdevice_assert_callback(uint32_t pc, uint16_t line_num, const uint8_t * p_file_name)
{
#if defined(TRACE_UART)    
    printf("ASSERT-softdevice_assert_callback\n");
    printf("PC: %#x\n", pc);
    printf("File name: %s\n", (const char*)p_file_name);
    printf("Line number: %d\n", line_num);
#endif // defined(TRACE_UART)     
    
    for (;;)
    {
        // No implementation needed.
    }
}


/**@brief Function for handling errors, which is called when an error has occurred. 
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name. 
 */
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
#if defined(TRACE_UART)    
    printf("ASSERT-app_error_handler\n");
    printf("Error code: %u\n", error_code);
    printf("File name:%s\n", (const char*)p_file_name);
    printf("Line number: %d\n", line_num);
#endif // defined(TRACE_UART)         
  
    for (;;)
    {
        // No implementation needed.
    }
}


#if defined(TRACE_UART)    
/**@brief Function for handling UART errors, which is called when an error has occurred. 
 *
 * @param[in] p_event Event supplied to the handler.
 */
void uart_error_handle(app_uart_evt_t * p_event)
{
  if ((p_event->evt_type == APP_UART_FIFO_ERROR) || 
      (p_event->evt_type == APP_UART_COMMUNICATION_ERROR))
  {
    // Copying parameters to static variables because parameters are not accessible in debugger.
    static volatile app_uart_evt_t uart_event;

    uart_event.evt_type = p_event->evt_type;
    uart_event.data     = p_event->data;
    UNUSED_VARIABLE(uart_event);  
    
    for (;;)
    {
        // No implementation needed.
    }
  }
}
#endif // defined(TRACE_UART)         


/**@brief Function for configuring and setting up the SoftDevice. 
 */
static __INLINE void softdevice_setup(void)
{    
    uint32_t err_code;
    
    err_code = sd_softdevice_enable(NRF_CLOCK_LFCLKSRC_XTAL_50_PPM, softdevice_assert_callback); 
    APP_ERROR_CHECK(err_code);

    // Configure application-specific interrupts.
    // Set application IRQ to lowest priority and
    // enable application IRQ (triggered from ANT protocol stack) 
    err_code = sd_nvic_SetPriority(PROTOCOL_EVENT_IRQn, NRF_APP_PRIORITY_LOW); 
    APP_ERROR_CHECK(err_code);
    
    err_code = sd_nvic_EnableIRQ(PROTOCOL_EVENT_IRQn);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for main application entry. Does not return.
 */
int main()
{    
#if defined(TRACE_UART)    
    // Configure and make UART ready for usage.    
    app_uart_comm_params_t comm_params =  
    {
        RX_PIN_NUMBER, 
        TX_PIN_NUMBER, 
        RTS_PIN_NUMBER, 
        CTS_PIN_NUMBER, 
        APP_UART_FLOW_CONTROL_DISABLED, 
        false, 
        UART_BAUDRATE_BAUDRATE_Baud38400
    }; 
        
    uint32_t err_code;
    APP_UART_FIFO_INIT(&comm_params, 
                       UART_RX_BUF_SIZE, 
                       UART_TX_BUF_SIZE, 
                       uart_error_handle, 
                       APP_IRQ_PRIORITY_LOW,
                       err_code);
    APP_ERROR_CHECK(err_code);
#endif // defined(TRACE_UART)     
        
    softdevice_setup();    
    
    // Run bicycle power-only TX main processing loop. Does not return.
    bp_only_tx_main_loop_run();  
    
    return 0;
}

/**
 *@}
 **/
