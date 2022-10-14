#include "stm32f446xx_rcc.h"

#define HSI_FREQ 16000000U
#define HSE_FREQ 8000000U

uint16_t ahb_prescaler[8]  = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t  apbx_prescaler[4] = {2, 4, 8, 16};

uint32_t rcc_get_pll_clock_freq(void)
{
    uint16_t plln = (RCC->PLLCFGR >> 6) & 0x1FF;
    uint8_t pllp = (((RCC->PLLCFGR >> 16) & 0x3) + 1) * 2;
    uint8_t pllm = RCC->PLLCFGR & 0x3F;
    uint32_t vco = HSE_FREQ * (plln / pllm);
    uint32_t pll_clock_freq = vco / pllp;

    return pll_clock_freq;
}

uint32_t rcc_get_system_clock_freq(void)
{
    uint32_t system_clock_freq;
    uint8_t clock_source = (RCC->CFGR >> 2) & 0x3;

    if (clock_source == 0)
        system_clock_freq = HSI_FREQ;
    else if (clock_source == 1)
        system_clock_freq = HSE_FREQ;
    else if (clock_source == 2)
        system_clock_freq = rcc_get_pll_clock_freq();

    return system_clock_freq;
}

uint32_t rcc_get_apbx_peripheral_clock_freq(uint8_t apbx)
{
    uint32_t apbx_peripheral_clock_freq;
    uint8_t ahb_presc, apbx_presc;
    uint32_t system_clock = rcc_get_system_clock_freq();

    int presc = ((RCC->CFGR >> 4) & 0xF);
    if (presc < 8)
        ahb_presc = 1;
    else
        ahb_presc  = ahb_prescaler[presc - 8];

    if (apbx == APB1_PERIPHERAL_CLOCK) 
    {
        presc = ((RCC->CFGR >> 10) & 0x7);
        if (presc < 4)
            apbx_presc = 1;
        else
            apbx_presc = apbx_prescaler[presc - 4];
    }
    else if (apbx == APB2_PERIPHERAL_CLOCK)
    {
        presc = ((RCC->CFGR >> 13) & 0x7);
        if (presc < 4)
            apbx_presc = 1;
        else
            apbx_presc = apbx_prescaler[presc - 4];
    }

    apbx_peripheral_clock_freq = system_clock / ahb_presc / apbx_presc;
    return apbx_peripheral_clock_freq;
}
