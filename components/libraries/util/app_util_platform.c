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

#include "app_util_platform.h"

#ifdef SOFTDEVICE_PRESENT
/* Global nvic state instance, required by nrf_nvic.h */
nrf_nvic_state_t nrf_nvic_state;
#endif

static uint32_t m_in_critical_region = 0;

void app_util_disable_irq(void)
{
    __disable_irq();
    m_in_critical_region++;
}

void app_util_enable_irq(void)
{
    m_in_critical_region--;
    if (m_in_critical_region == 0)
    {
        __enable_irq();
    }
}

void app_util_critical_region_enter(uint8_t *p_nested)
{
#if __CORTEX_M == (0x04U)
    ASSERT(APP_LEVEL_PRIVILEGED == privilege_level_get())
#endif

#if defined(SOFTDEVICE_PRESENT)
    /* return value can be safely ignored */
    (void) sd_nvic_critical_region_enter(p_nested);
#else
    app_util_disable_irq();
#endif
}

void app_util_critical_region_exit(uint8_t nested)
{
#if __CORTEX_M == (0x04U)
    ASSERT(APP_LEVEL_PRIVILEGED == privilege_level_get())
#endif

#if defined(SOFTDEVICE_PRESENT)
    /* return value can be safely ignored */
    (void) sd_nvic_critical_region_exit(nested);
#else
    app_util_enable_irq();
#endif
}


uint8_t privilege_level_get(void)
{
#if __CORTEX_M == (0x00U) || defined(_WIN32) || defined(__unix) || defined(__APPLE__)
    /* the Cortex-M0 has no concept of privilege */
    return APP_LEVEL_PRIVILEGED;
#elif __CORTEX_M == (0x04U)
    uint32_t isr_vector_num = __get_IPSR() & IPSR_ISR_Msk ;
    if (0 == isr_vector_num)
    {
        /* Thread Mode, check nPRIV */
        int32_t control = __get_CONTROL();
        return control & CONTROL_nPRIV_Msk ? APP_LEVEL_UNPRIVILEGED : APP_LEVEL_PRIVILEGED;
    }
    else
    {
        /* Handler Mode, always privileged */
        return APP_LEVEL_PRIVILEGED;
    }
#endif
}


uint8_t current_int_priority_get(void)
{
    uint32_t isr_vector_num = __get_IPSR() & IPSR_ISR_Msk ;
    if (isr_vector_num > 0)
    {
        int32_t irq_type = ((int32_t)isr_vector_num - EXTERNAL_INT_VECTOR_OFFSET);
        return (NVIC_GetPriority((IRQn_Type)irq_type) & 0xFF);
    }
    else
    {
        return APP_IRQ_PRIORITY_THREAD;
    }
}
