#ifndef _STM32F446XX_GPIO_H_
#define _STM32F446XX_GPIO_H_

#include "stm32f446xx.h"
#include "stm32f4xx_nvic.h"

/* GPIO pin configuration structure */
typedef struct
{
    uint8_t pin_number;         /* See @pin_number configuration */
    uint8_t pin_mode;           /* See @pin_mode configuration */
    uint8_t pin_output_type;    /* See @pin_output_type configuration */
    uint8_t pin_speed;          /* See @pin_speed configuration */
    uint8_t pin_pupd;           /* See @pin_pupd configuration */
    uint8_t pin_alt_func;       /* See @pin_alt_func configuration */
} gpio_pinconfig_t;

/* GPIO handle structure */
typedef struct
{
    gpio_regdef_t *gpiox;
    gpio_pinconfig_t config;
} gpio_handle_t;

/* General-purpose I/O driver public API */
void gpio_init(gpio_handle_t *gpio_handle);

uint8_t gpio_read_pin(gpio_regdef_t *gpiox, uint8_t pin_number);
uint16_t gpio_read_port(gpio_regdef_t *gpiox);
void gpio_write_pin(gpio_regdef_t *gpiox, uint8_t pin_number, uint8_t value);
void gpio_write_port(gpio_regdef_t *gpiox, uint16_t value);
void gpio_toggle_pin(gpio_regdef_t *gpiox, uint8_t pin_number);

void gpio_irq_enable(irq_nr number);
void gpio_irq_disable(irq_nr number);
void gpio_irq_priority(irq_nr number, irq_priority priority);
void gpio_irq_handler(uint8_t pin_number);

/* General GPIO macros */
#define GPIO_PIN_LOW    0
#define GPIO_PIN_HIGH   1

/* @pin_number configuration */
#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15

/* @pin_mode configuration */
#define GPIO_MODE_INPUT     0
#define GPIO_MODE_OUTPUT    1
#define GPIO_MODE_ALT_FUNC  2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_RE     4
#define GPIO_MODE_IT_FE     5
#define GPIO_MODE_IT_RFE    6

/* @pin_output_type configuration */
#define GPIO_OUTPUT_PUSH_PULL   0
#define GPIO_OUTPUT_OPEN_DRAIN  1

/* @pin_speed configuration */
#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3

/* @pin_pupd configuration */
#define GPIO_NO_PUPD    0
#define GPIO_PULL_UP    1
#define GPIO_PULL_DOWN  2

/* @pin_alt_func configuration */
#define GPIO_ALT_FUNC_0     0
#define GPIO_ALT_FUNC_1     1
#define GPIO_ALT_FUNC_2     2
#define GPIO_ALT_FUNC_3     3
#define GPIO_ALT_FUNC_4     4
#define GPIO_ALT_FUNC_5     5
#define GPIO_ALT_FUNC_6     6
#define GPIO_ALT_FUNC_7     7
#define GPIO_ALT_FUNC_8     8
#define GPIO_ALT_FUNC_9     9
#define GPIO_ALT_FUNC_10    10
#define GPIO_ALT_FUNC_11    11
#define GPIO_ALT_FUNC_12    12
#define GPIO_ALT_FUNC_13    13
#define GPIO_ALT_FUNC_14    14
#define GPIO_ALT_FUNC_15    15

#define GPIO_CODE(x)    (x == GPIOA ? 0 :\
                         x == GPIOB ? 1 :\
                         x == GPIOC ? 2 :\
                         x == GPIOD ? 3 :\
                         x == GPIOE ? 4 :\
                         x == GPIOF ? 5 :\
                         x == GPIOG ? 6 :\
                         x == GPIOH ? 7 : 0)

#endif
