/*
 * Description: Blinking an led located at GPIO port A pin 5
 */

#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f4xx_systick.h"

int main()
{
    gpio_handle_t led = {0};

    led.gpiox                  = GPIOA;
    led.config.pin_number      = GPIO_PIN_5;
    led.config.pin_mode        = GPIO_MODE_OUTPUT;
    led.config.pin_output_type = GPIO_OUTPUT_PUSH_PULL;
    led.config.pin_speed       = GPIO_SPEED_MEDIUM;
    led.config.pin_pupd        = GPIO_NO_PUPD;

    gpio_init(&led);

    while (1)
    {
        gpio_toggle_pin(GPIOA, GPIO_PIN_5);
        delay_ms(1000);
    }

    return 0;
}
