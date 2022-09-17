#ifndef _STM32F446XX_GPIO_H_
#define _STM32F446XX_GPIO_H_

#include "stm32f446xx.h"

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
#define GPIO_MODE_INPUT     0b00
#define GPIO_MODE_OUTPUT    0b01
#define GPIO_MODE_ALT_FUNC  0b10
#define GPIO_MODE_ANALOG    0b11

/* @pin_output_type configuration */
#define GPIO_OUTPUT_PUSH_PULL   0b0
#define GPIO_OUTPUT_OPEN_DRAIN  0b1

/* @pin_speed configuration */
#define GPIO_SPEED_LOW      0b00
#define GPIO_SPEED_MEDIUM   0b01
#define GPIO_SPEED_FAST     0b10
#define GPIO_SPEED_HIGH     0b11

/* @pin_pupd configuration */
#define GPIO_NO_PUPD    0b00
#define GPIO_PULL_UP    0b01
#define GPIO_PULL_DOWN  0b10

/* @pin_alt_func configuration */
#define GPIO_ALT_FUNC_0     0b0000
#define GPIO_ALT_FUNC_1     0b0001
#define GPIO_ALT_FUNC_2     0b0010
#define GPIO_ALT_FUNC_3     0b0011
#define GPIO_ALT_FUNC_4     0b0100
#define GPIO_ALT_FUNC_5     0b0101
#define GPIO_ALT_FUNC_6     0b0110
#define GPIO_ALT_FUNC_7     0b0111
#define GPIO_ALT_FUNC_8     0b1000
#define GPIO_ALT_FUNC_9     0b1001
#define GPIO_ALT_FUNC_10    0b1010
#define GPIO_ALT_FUNC_11    0b1011
#define GPIO_ALT_FUNC_12    0b1100
#define GPIO_ALT_FUNC_13    0b1101
#define GPIO_ALT_FUNC_14    0b1110
#define GPIO_ALT_FUNC_15    0b1111

#endif
