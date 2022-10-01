#include "stm32f4xx_nvic.h"

void nvic_enable_irq(irq_nr number)
{
    *(NVIC_ISER_BASE_PTR + (number / 32)) |= 1 << (number % 32);
}

void nvic_disable_irq(irq_nr number)
{
    *(NVIC_ICER_BASE_PTR + (number / 32)) |= 1 << (number % 32);
}

void nvic_set_priority(irq_nr number, irq_priority priority)
{
    uint8_t offset  = number / 4;
    uint8_t section = number % 4;
    uint8_t shift   = (8 * section) + (8 - NVIC_IMPL_PRIORITY_BITS_NR);
    *(NVIC_IPR_BASE_PTR + offset) |= (priority << shift);
}
