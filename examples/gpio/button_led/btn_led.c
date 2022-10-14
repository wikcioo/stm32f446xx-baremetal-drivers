#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"

static void delay(void)
{
    for (uint32_t i = 0; i < 200000; i++);
}

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

    gpio_handle_t btn = {0};
    btn.gpiox             = GPIOC;
    btn.config.pin_number = GPIO_PIN_13;
    btn.config.pin_mode   = GPIO_MODE_INPUT;
    btn.config.pin_speed  = GPIO_SPEED_MEDIUM;
    btn.config.pin_pupd   = GPIO_NO_PUPD;
    gpio_init(&btn);

    while (1)
    {
        if (gpio_read_pin(GPIOC, GPIO_PIN_13) == GPIO_PIN_LOW)
        {
            gpio_toggle_pin(GPIOA, GPIO_PIN_5);
            delay();
        }
    }

    return 0;
}
