#include "stm32f4xx_systick.h"
#include "stm32f446xx_rcc.h"

#define SYSTICK_CSR_ENABLE      (1 << 0)
#define SYSTICK_CSR_CLKSOURCE   (1 << 2)
#define SYSTICK_CSR_COUNTFLAG   (1 << 16)

void delay_ms(int millis)
{
    SYSTICK->RVR |= (rcc_get_system_clock_freq() / 1000) & 0xFFFFFF;
    SYSTICK->CVR &= ~0xFFFFFF;
    SYSTICK->CSR |= (SYSTICK_CSR_CLKSOURCE | SYSTICK_CSR_ENABLE);

    while (millis--)
        while (!(SYSTICK->CSR & SYSTICK_CSR_COUNTFLAG));

    SYSTICK->CSR &= ~SYSTICK_CSR_ENABLE;
}
