/*
 * Description: Send data over SPI on button click.
 */
#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_spi.h"
#include "stm32f4xx_systick.h"
#include <string.h>

spi_handle_t hspi1;

void init_spi1_peripherals(void)
{
    gpio_handle_t spi_gpio = {0};
    spi_gpio.gpiox               = GPIOB;
    spi_gpio.config.pin_mode     = GPIO_MODE_ALT_FUNC;
    spi_gpio.config.pin_alt_func = GPIO_ALT_FUNC_5;
    spi_gpio.config.pin_pupd     = GPIO_NO_PUPD;
    spi_gpio.config.pin_speed    = GPIO_SPEED_HIGH;

    /* PB3 -> SPI1_SCK */
    spi_gpio.config.pin_number   = GPIO_PIN_3;
    gpio_init(&spi_gpio);

    /* PB5 -> SPI1_MOSI */
    spi_gpio.config.pin_number   = GPIO_PIN_5;
    gpio_init(&spi_gpio);

    gpio_write_pin(GPIOB, GPIO_PIN_3, GPIO_PIN_LOW);
    gpio_write_pin(GPIOB, GPIO_PIN_5, GPIO_PIN_LOW);

    hspi1.spix           = SPI1;
    hspi1.config.mode    = SPI_MODE_MASTER;
    hspi1.config.comm    = SPI_COMM_FULL_DUPLEX;
    hspi1.config.clk_div = SPI_CLK_DIV_2;
    hspi1.config.cpol    = SPI_CPOL_IDLE_LOW;
    hspi1.config.cpha    = SPI_CPHA_FIRST_TRANSITION_CAPTURE;
    hspi1.config.ssm     = SPI_SSM_ENABLE;
    hspi1.config.dff     = SPI_DFF_8BITS;
    hspi1.config.ff      = SPI_FF_MSB_FIRST;
    spi_init(&hspi1);
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
    const char *data = "Hello SPI\n";

    init_spi1_peripherals();
    init_button();

    while (1)
    {
        if (gpio_read_pin(GPIOC, GPIO_PIN_13) == GPIO_PIN_LOW)
        {
            spi_transmit(&hspi1, (uint8_t *)data, strlen(data));
            delay_ms(300);
        }
    }

    return 0;
}
