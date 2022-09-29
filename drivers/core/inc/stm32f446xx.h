#ifndef _STM32F446XX_H_
#define _STM32F446XX_H_

#include <stdint.h>

#define __IO volatile

/* Generic macros */
#define ENABLE      1
#define DISABLE     0
#define SET         ENABLE
#define RESET       DISABLE

/* Base addresses of Flash, SRAM and ROM memories */
#define FLASH_BASE_ADDR         0x08000000U
#define SRAM1_BASE_ADDR         0x20000000U
#define SRAM2_BASE_ADDR         0x2001C000U
#define ROM_BASE_ADDR           0x1FFF0000U

/* Base addresses of AHBx and APBx bus peripherals */
#define APB1PERIPH_BASE_ADDR    0x40000000U
#define APB2PERIPH_BASE_ADDR    0x40010000U
#define AHB1PERIPH_BASE_ADDR    0x40020000U
#define AHB2PERIPH_BASE_ADDR    0x50000000U
#define AHB3PERIPH_BASE_ADDR    0x60000000U

/* Base addresses of peripherals hanging on AHB1 bus */
#define GPIOA_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x0000U)
#define GPIOB_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x0400U)
#define GPIOC_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x0800U)
#define GPIOD_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x0C00U)
#define GPIOE_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x1000U)
#define GPIOF_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x1400U)
#define GPIOG_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x1800U)
#define GPIOH_BASE_ADDR         (AHB1PERIPH_BASE_ADDR + 0x1C00U)
#define RCC_BASE_ADDR           (AHB1PERIPH_BASE_ADDR + 0x3800U)

/* Base addresses of peripherals hanging on APB1 bus */
#define USART2_BASE_ADDR        (APB1PERIPH_BASE_ADDR + 0x4400U)
#define USART3_BASE_ADDR        (APB1PERIPH_BASE_ADDR + 0x4800U)
#define UART4_BASE_ADDR         (APB1PERIPH_BASE_ADDR + 0x4C00U)
#define UART5_BASE_ADDR         (APB1PERIPH_BASE_ADDR + 0x5000U)

/* Base addresses of peripherals hanging on APB2 bus */
#define USART1_BASE_ADDR        (APB2PERIPH_BASE_ADDR + 0x1000U)
#define USART6_BASE_ADDR        (APB2PERIPH_BASE_ADDR + 0x1400U)

/* Peripheral register definition structures */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t PLLCFGR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	__IO uint32_t AHB3RSTR;
		 uint32_t RESERVED0;
	__IO uint32_t APB1RSTR;
	__IO uint32_t APB2RSTR;
		 uint32_t RESERVED1[2];
	__IO uint32_t AHB1ENR;
	__IO uint32_t AHB2ENR;
	__IO uint32_t AHB3ENR;
		 uint32_t RESERVED2;
	__IO uint32_t APB1ENR;
	__IO uint32_t APB2ENR;
		 uint32_t RESERVED3[2];
	__IO uint32_t AHB1LPENR;
	__IO uint32_t AHB2LPENR;
	__IO uint32_t AHB3LPENR;
		 uint32_t RESERVED4;
	__IO uint32_t APB1LPENR;
	__IO uint32_t APB2LPENR;
		 uint32_t RESERVED5[2];
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
		 uint32_t RESERVED6[2];
	__IO uint32_t SSCGR;
	__IO uint32_t PLLI2SCFGR;
	__IO uint32_t PLLSAICFGR;
	__IO uint32_t DCKCFGR;
	__IO uint32_t CKGATENR;
	__IO uint32_t DCKCFGR2;
} rcc_regdef_t;

typedef struct
{
    __IO uint32_t MODER;
    __IO uint32_t OTYPER;
    __IO uint32_t OSPEEDR;
    __IO uint32_t PUPDR;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t LCKR;
    __IO uint32_t AFR[2];
} gpio_regdef_t;

typedef struct
{
	__IO uint32_t SR;
	__IO uint32_t DR;
	__IO uint32_t BRR;
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t GTPR;
} usart_regdef_t;

/* Peripheral definitions (base addresses type-casted to xxx_regdef_t) */
#define RCC     ((rcc_regdef_t *) RCC_BASE_ADDR)

#define GPIOA   ((gpio_regdef_t *) GPIOA_BASE_ADDR)
#define GPIOB   ((gpio_regdef_t *) GPIOB_BASE_ADDR)
#define GPIOC   ((gpio_regdef_t *) GPIOC_BASE_ADDR)
#define GPIOD   ((gpio_regdef_t *) GPIOD_BASE_ADDR)
#define GPIOE   ((gpio_regdef_t *) GPIOE_BASE_ADDR)
#define GPIOF   ((gpio_regdef_t *) GPIOF_BASE_ADDR)
#define GPIOG   ((gpio_regdef_t *) GPIOG_BASE_ADDR)
#define GPIOH   ((gpio_regdef_t *) GPIOH_BASE_ADDR)

#define USART1  ((usart_regdef_t *) USART1_BASE_ADDR)
#define USART2  ((usart_regdef_t *) USART2_BASE_ADDR)
#define USART3  ((usart_regdef_t *) USART3_BASE_ADDR)
#define UART4   ((usart_regdef_t *) UART4_BASE_ADDR)
#define UART5   ((usart_regdef_t *) UART5_BASE_ADDR)
#define USART6  ((usart_regdef_t *) USART6_BASE_ADDR)

/* Clock enable macros for GPIOx */
#define GPIOA_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_CLK_ENABLE()  (RCC->AHB1ENR |= (1 << 7))

/* Clock disable macros for GPIOx */
#define GPIOA_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_DISABLE()  (RCC->AHB1ENR &= ~(1 << 7))

/* Clock enable macros for USARTx */
#define USART1_CLK_ENABLE()  (RCC->APB2ENR |= (1 << 4))
#define USART2_CLK_ENABLE()  (RCC->APB1ENR |= (1 << 17))
#define USART3_CLK_ENABLE()  (RCC->APB1ENR |= (1 << 18))
#define UART4_CLK_ENABLE()   (RCC->APB1ENR |= (1 << 19))
#define UART5_CLK_ENABLE()   (RCC->APB1ENR |= (1 << 20))
#define USART6_CLK_ENABLE()  (RCC->APB2ENR |= (1 << 5))

/* Clock disable macros for USARTx */
#define USART1_CLK_DISABLE()  (RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLK_DISABLE()  (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DISABLE()  (RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DISABLE()   (RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DISABLE()   (RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLK_DISABLE()  (RCC->APB2ENR &= ~(1 << 5))

#endif
