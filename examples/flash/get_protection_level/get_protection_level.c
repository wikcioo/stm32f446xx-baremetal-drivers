/*
 * USART2 code used for debugging only
 */

#include <string.h>
#include <stdio.h>
#include <memory.h>

#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_usart.h"
#include "stm32f446xx_flash.h"

usart_handle_t usart2;

void init_gpio(void)
{
    gpio_handle_t usart2_gpio;

    usart2_gpio.gpiox                  = GPIOA;
    usart2_gpio.config.pin_mode        = GPIO_MODE_ALT_FUNC;
    usart2_gpio.config.pin_alt_func    = GPIO_ALT_FUNC_7;
    usart2_gpio.config.pin_output_type = GPIO_OUTPUT_PUSH_PULL;
    usart2_gpio.config.pin_pupd        = GPIO_PULL_UP;
    usart2_gpio.config.pin_speed       = GPIO_SPEED_HIGH;
    usart2_gpio.config.pin_number      = GPIO_PIN_2;

    gpio_init(&usart2_gpio);
}

void init_usart2(void)
{
    usart2.usartx                 = USART2;
    usart2.config.mode            = USART_MODE_TX_ONLY;
    usart2.config.baudrate        = USART_BAUDRATE_115200;
    usart2.config.word_length     = USART_WORD_LENGTH_8BITS;
    usart2.config.parity          = USART_PARITY_NONE;
    usart2.config.stop_bits       = USART_STOP_BITS_1;
    usart2.config.hw_flow_control = USART_HW_FLOW_CONTROL_NONE;

    usart_init(&usart2);
}

int main(void)
{
    init_gpio();
    init_usart2();
    flash_init();

    uint8_t levels[8];
    memset(levels, 0, 8);
    flash_get_protection_level(levels);

    char data[32];
    uint32_t len = snprintf(data, sizeof(data), "Data: %d %d %d %d %d %d %d %d",
            levels[0], levels[1], levels[2], levels[3], levels[4], levels[5], levels[6], levels[7]);

    usart_transmit(&usart2, (uint8_t *)data, len);

    while (1);

    return 0;
}
