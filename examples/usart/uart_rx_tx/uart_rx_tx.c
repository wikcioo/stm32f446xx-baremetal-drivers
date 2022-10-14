/*
 * Description: Receiving and transmitting data over USART2 peripheral
 */
#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_usart.h"
#include <memory.h>

void init_gpio(void);
void init_usart2(void);

usart_handle_t usart2;

uint8_t data[32] = {0};
uint8_t data_index = 0;
uint8_t buffer = 0;

char msg[32] = "Received: ";
char greeting[32] = "Now Listening...\n";

int main()
{
    init_gpio();
    init_usart2();

    while (1)
    {
        memset(&data, 0, 32);
        data_index = 0;
        usart_transmit(&usart2, (uint8_t *)greeting, strlen(greeting));

        while (1)
        {
            usart_receive(&usart2, &buffer, 1);
            if (buffer == '\r') break;
            data[data_index++] = buffer;
        }

        data[data_index++] = '\n';
        usart_transmit(&usart2, (uint8_t *)msg, strlen(msg));
        usart_transmit(&usart2, data, data_index);
    }

    return 0;
}

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

    usart2_gpio.config.pin_number      = GPIO_PIN_3;
    gpio_init(&usart2_gpio);
}

void init_usart2(void)
{
    usart2.usartx                 = USART2;
    usart2.config.mode            = USART_MODE_TX_RX;
    usart2.config.baudrate        = USART_BAUDRATE_115200;
    usart2.config.word_length     = USART_WORD_LENGTH_8BITS;
    usart2.config.parity          = USART_PARITY_NONE;
    usart2.config.stop_bits       = USART_STOP_BITS_1;
    usart2.config.hw_flow_control = USART_HW_FLOW_CONTROL_NONE;

    usart_init(&usart2);
}
