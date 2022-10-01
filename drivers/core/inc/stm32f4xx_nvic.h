#ifndef _STM32F4XX_NVIC_H_
#define _STM32F4XX_NVIC_H_

#include <stdint.h>

#define NVIC_IMPL_PRIORITY_BITS_NR 4

#define NVIC_ISER_BASE_PTR  ((volatile uint32_t *) 0xE000E100)
#define NVIC_ICER_BASE_PTR  ((volatile uint32_t *) 0xE000E180)
#define NVIC_ISPR_BASE_PTR  ((volatile uint32_t *) 0xE000E200)
#define NVIC_ICPR_BASE_PTR  ((volatile uint32_t *) 0xE000E280)
#define NVIC_IABR_BASE_PTR  ((volatile uint32_t *) 0xE000E300)
#define NVIC_IPR_BASE_PTR   ((volatile uint32_t *) 0xE000E400)

typedef enum
{
    IRQ_NR_EXTI0     = 6,
    IRQ_NR_EXTI1     = 7,
    IRQ_NR_EXTI2     = 8,
    IRQ_NR_EXTI3     = 9,
    IRQ_NR_EXTI4     = 10,
    IRQ_NR_EXTI9_5   = 23,
    IRQ_NR_EXTI15_10 = 40,
} irq_nr;

typedef enum
{
    IRQ_PRI_0  = 0,
    IRQ_PRI_1  = 1,
    IRQ_PRI_2  = 2,
    IRQ_PRI_3  = 3,
    IRQ_PRI_4  = 4,
    IRQ_PRI_5  = 5,
    IRQ_PRI_6  = 6,
    IRQ_PRI_7  = 7,
    IRQ_PRI_8  = 8,
    IRQ_PRI_9  = 9,
    IRQ_PRI_10 = 10,
    IRQ_PRI_11 = 11,
    IRQ_PRI_12 = 12,
    IRQ_PRI_13 = 13,
    IRQ_PRI_14 = 14,
    IRQ_PRI_15 = 15,
} irq_priority;

void nvic_enable_irq(irq_nr number);
void nvic_disable_irq(irq_nr number);
void nvic_set_priority(irq_nr number, irq_priority priority);

#endif
