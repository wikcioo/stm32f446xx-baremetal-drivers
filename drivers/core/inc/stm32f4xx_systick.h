#ifndef _STM32F4XX_SYSTICK_H_
#define _STM32F4XX_SYSTICK_H_

#include <stdint.h>

#define __IO volatile

typedef struct
{
    __IO uint32_t CSR;
    __IO uint32_t RVR;
    __IO uint32_t CVR;
    __IO uint32_t CALIB;
} systick_regdef_t;

#define SYSTICK_BASE_ADDR   0xE000E010
#define SYSTICK             ((systick_regdef_t *) SYSTICK_BASE_ADDR)

void delay_ms(int millis);

#endif
