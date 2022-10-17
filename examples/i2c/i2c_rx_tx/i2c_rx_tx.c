/*
 * Description: Send and receive data over I2C on button press.
 */
#include <string.h>
#include <stdlib.h>

#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_i2c.h"
#include "stm32f4xx_systick.h"

#define SLAVE_ADDR 0x68

i2c_handle_t hi2c1;

void init_i2c(void)
{
    gpio_handle_t i2c_gpio = {0};
    i2c_gpio.gpiox                  = GPIOB;
    i2c_gpio.config.pin_mode        = GPIO_MODE_ALT_FUNC;
    i2c_gpio.config.pin_output_type = GPIO_OUTPUT_OPEN_DRAIN;
    i2c_gpio.config.pin_alt_func    = GPIO_ALT_FUNC_4;
    i2c_gpio.config.pin_pupd        = GPIO_PULL_UP;
    i2c_gpio.config.pin_speed       = GPIO_SPEED_HIGH;

    /* PB8 -> I2C1_SCL */
    i2c_gpio.config.pin_number      = GPIO_PIN_8;
    gpio_init(&i2c_gpio);

    /* PB9 -> I2C1_SDA */
    i2c_gpio.config.pin_number      = GPIO_PIN_9;
    gpio_init(&i2c_gpio);

    hi2c1.i2cx                 = I2C1;
    hi2c1.config.ack_control   = I2C_ACK_ENABLE;
    hi2c1.config.clk_speed     = I2C_CLK_SPEED_SM;
    hi2c1.config.fm_duty_cycle = I2C_DUTY_CYCLE_2;
    i2c_init(&hi2c1);
}

void init_button(void)
{
    gpio_handle_t btn = {0};
    btn.gpiox             = GPIOC;
    btn.config.pin_number = GPIO_PIN_13;
    btn.config.pin_mode   = GPIO_MODE_INPUT;
    btn.config.pin_speed  = GPIO_SPEED_MEDIUM;
    btn.config.pin_pupd   = GPIO_NO_PUPD;
    gpio_init(&btn);
}

int main()
{
    init_i2c();
    init_button();

    while (1)
    {
        uint8_t command = 0;
        uint8_t length = 0;
        uint8_t buffer[32] = {0};

        if (gpio_read_pin(GPIOC, GPIO_PIN_13) == GPIO_PIN_LOW)
        {
            delay_ms(200);

            command = 0x51;
            i2c_master_transmit(&hi2c1, &command, 1, SLAVE_ADDR, I2C_STOP_BIT_ENABLE);
            i2c_master_receive(&hi2c1, &length, 1, SLAVE_ADDR, I2C_STOP_BIT_ENABLE);

            command = 0x52;
            i2c_master_transmit(&hi2c1, &command, 1, SLAVE_ADDR, I2C_STOP_BIT_DISABLE);
            i2c_master_receive(&hi2c1, buffer, length, SLAVE_ADDR, I2C_STOP_BIT_ENABLE);

            buffer[length++] = '\0';
        }
    }

    return 0;
}
