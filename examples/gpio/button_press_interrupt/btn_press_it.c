#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"

void init_led_gpio(void);
void init_btn_gpio(void);

int main()
{
    init_led_gpio();
    init_btn_gpio();

    while (1);
}

void EXTI15_10_IRQHandler(void)
{
    gpio_irq_handler(GPIO_PIN_13);
    gpio_toggle_pin(GPIOA, GPIO_PIN_5);
}

void init_led_gpio(void)
{
    gpio_handle_t led = {0};

    led.gpiox                  = GPIOA;
    led.config.pin_number      = GPIO_PIN_5;
    led.config.pin_mode        = GPIO_MODE_OUTPUT;
    led.config.pin_output_type = GPIO_OUTPUT_PUSH_PULL;
    led.config.pin_speed       = GPIO_SPEED_FAST;
    led.config.pin_pupd        = GPIO_NO_PUPD;

    gpio_init(&led);
}

void init_btn_gpio(void)
{
    gpio_handle_t btn = {0};

    btn.gpiox             = GPIOC;
    btn.config.pin_number = GPIO_PIN_13;
    btn.config.pin_mode   = GPIO_MODE_IT_FE;
    btn.config.pin_pupd   = GPIO_NO_PUPD;
    btn.config.pin_speed  = GPIO_SPEED_FAST;

    gpio_init(&btn);

    gpio_irq_priority(IRQ_NR_EXTI15_10, IRQ_PRI_15);
    gpio_irq_enable(IRQ_NR_EXTI15_10);
}
