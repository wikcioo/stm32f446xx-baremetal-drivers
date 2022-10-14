#ifndef _STM32F446XX_RCC_H_
#define _STM32F446XX_RCC_H_

#include "stm32f446xx.h"

#define APB1_PERIPHERAL_CLOCK 0
#define APB2_PERIPHERAL_CLOCK 1

uint32_t rcc_get_pll_clock_freq(void);
uint32_t rcc_get_system_clock_freq(void);
uint32_t rcc_get_apbx_peripheral_clock_freq(uint8_t apbx);

#endif
