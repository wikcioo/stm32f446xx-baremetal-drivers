#include "stm32f446xx_spi.h"

static uint8_t spi_get_flag_status(spi_regdef_t *spix, uint8_t flag);
static void spi_peripheral_control(spi_regdef_t *spix, uint8_t state);
static void spi_clock_control(spi_regdef_t *spix, uint8_t state);
static void spi_ssi_control(spi_regdef_t *spix, uint8_t state);

void spi_init(spi_handle_t *spi_handle)
{
    spi_clock_control(spi_handle->spix, ENABLE);

    uint16_t temp_reg = 0;

    /* Configure SPI_CR1 */
    temp_reg |= spi_handle->config.mode << SPI_CR1_MSTR;
    
    if (spi_handle->config.comm == SPI_COMM_HALF_DUPLEX)
        temp_reg |= 1 << SPI_CR1_BIDIMODE;
    else if (spi_handle->config.comm == SPI_COMM_SIMPLEX_RX)
        temp_reg |= 1 << SPI_CR1_RXONLY;

    temp_reg |= spi_handle->config.clk_div << SPI_CR1_BR;
    temp_reg |= spi_handle->config.cpol    << SPI_CR1_CPOL;
    temp_reg |= spi_handle->config.cpha    << SPI_CR1_CPHA;
    temp_reg |= spi_handle->config.ssm     << SPI_CR1_SSM;
    temp_reg |= spi_handle->config.dff     << SPI_CR1_DFF;
    temp_reg |= spi_handle->config.ff      << SPI_CR1_LSBFIRST;

    spi_handle->spix->CR1 = temp_reg;

    if (spi_handle->config.ssm == SPI_SSM_ENABLE)
        spi_ssi_control(spi_handle->spix, ENABLE);
}

void spi_transmit(spi_handle_t *spi_handle, uint8_t *tx_buffer, uint32_t length)
{
    spi_peripheral_control(spi_handle->spix, ENABLE);

    while (length--)
    {
        while (!spi_get_flag_status(spi_handle->spix, SPI_FLAG_TXE));

        if (spi_handle->config.dff == SPI_DFF_8BITS)
        {
            spi_handle->spix->DR = *tx_buffer++;
        }
        else
        {
            spi_handle->spix->DR = *(uint16_t *)tx_buffer++;
            length--; /* Because we just sent 2 bytes of data */
        }
    }
}

void spi_receive(spi_handle_t *spi_handle, uint8_t *rx_buffer, uint32_t length)
{
}

static uint8_t spi_get_flag_status(spi_regdef_t *spix, uint8_t flag)
{
    return (spix->SR & flag) ? SET : RESET;
}

static void spi_peripheral_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
        spix->CR1 |= 1 << SPI_CR1_SPE;
    else
        spix->CR1 &= ~(1 << SPI_CR1_SPE);
}

static void spi_clock_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
    {
        if      (spix == SPI1) SPI1_CLK_ENABLE();
        else if (spix == SPI2) SPI2_CLK_ENABLE();
        else if (spix == SPI3) SPI3_CLK_ENABLE();
        else if (spix == SPI4) SPI4_CLK_ENABLE();
    }
    else
    {
        if      (spix == SPI1) SPI1_CLK_DISABLE();
        else if (spix == SPI2) SPI2_CLK_DISABLE();
        else if (spix == SPI3) SPI3_CLK_DISABLE();
        else if (spix == SPI4) SPI4_CLK_DISABLE();
    }

}

static void spi_ssi_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
        spix->CR1 |= 1 << SPI_CR1_SSI;
    else
        spix->CR1 &= ~(1 << SPI_CR1_SSI);
}
