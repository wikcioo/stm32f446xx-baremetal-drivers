#include "stm32f446xx_spi.h"

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
    else
        spi_ssoe_control(spi_handle->spix, ENABLE);
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
    spi_peripheral_control(spi_handle->spix, ENABLE);

    while (length--)
    {
        if (spi_handle->config.dff == SPI_DFF_8BITS)
        {
            *rx_buffer++ = spi_handle->spix->DR & 0xFF;
        }
        else
        {
            *(uint16_t *)rx_buffer++ = spi_handle->spix->DR;
            length--; /* Because we just sent 2 bytes of data */
        }
    }
}

uint8_t spi_transmit_it(spi_handle_t *spi_handle, uint8_t *tx_buffer, uint32_t length)
{
    uint8_t state = spi_handle->tx_state;

    if (state != SPI_STATE_BUSY_IN_TX)
    {
        /* Save data and update state */
        spi_handle->tx_buffer = tx_buffer;
        spi_handle->tx_length = length;
        spi_handle->tx_state  = SPI_STATE_BUSY_IN_TX;

        /* Enable TXE interrupt */
        spi_handle->spix->CR2 |= 1 << SPI_CR2_TXEIE;
    }

    return state;
}

uint8_t spi_receive_it(spi_handle_t *spi_handle, uint8_t *rx_buffer, uint32_t length)
{
    uint8_t state = spi_handle->rx_state;

    if (state != SPI_STATE_BUSY_IN_RX)
    {
        /* Save data and update state */
        spi_handle->rx_buffer = rx_buffer;
        spi_handle->rx_length = length;
        spi_handle->rx_state  = SPI_STATE_BUSY_IN_RX;

        /* Enable RXNE interrupt */
        spi_handle->spix->CR2 |= 1 << SPI_CR2_RXNEIE;
    }

    return state;
}

void spi_irq_enable(irq_nr number)
{
    nvic_enable_irq(number);
}

void spi_irq_disable(irq_nr number)
{
    nvic_disable_irq(number);
}

void spi_irq_priority(irq_nr number, irq_priority priority)
{
    nvic_set_priority(number, priority);
}

void spi_irq_handler(spi_handle_t *spi_handle)
{
    uint8_t is_flag_set;
    uint8_t is_interrupt_set;

    is_flag_set      = spi_handle->spix->SR & (1 << SPI_SR_TXE);
    is_interrupt_set = spi_handle->spix->CR2 & (1 << SPI_CR2_TXEIE);
    if (is_flag_set && is_interrupt_set)
    {
        /* Handle TXE interrupt */
        if (spi_handle->config.dff == SPI_DFF_16BITS)
        {
            spi_handle->spix->DR = *(uint16_t *)spi_handle->tx_buffer++;
            spi_handle->tx_length -= 2;
        }
        else
        {
            spi_handle->spix->DR = *spi_handle->tx_buffer++;
            spi_handle->tx_buffer--;
        }

        if (spi_handle->tx_length <= 0)
        {
            /* Disable the interrupt */
            spi_handle->spix->CR2 &= ~(1 << SPI_CR2_TXEIE);

            /* Reset data and state */
            spi_handle->tx_buffer = (void *)0;
            spi_handle->tx_length = 0;
            spi_handle->tx_state  = SPI_STATE_READY;

            spi_interrupt_event_callback(spi_handle, SPI_EVENT_TX_COMPLETE);
        }
    }

    is_flag_set      = spi_handle->spix->SR & (1 << SPI_SR_RXNE);
    is_interrupt_set = spi_handle->spix->CR2 & (1 << SPI_CR2_RXNEIE);
    if (is_flag_set && is_interrupt_set)
    {
        /* Handle RXNE interrupt */
        if (spi_handle->config.dff == SPI_DFF_16BITS)
        {
            *(uint16_t *)spi_handle->rx_buffer++ = (uint16_t)spi_handle->spix->DR;
            spi_handle->rx_length -= 2;
        }
        else
        {
            *spi_handle->rx_buffer++ = (uint8_t)spi_handle->spix->DR;
            spi_handle->rx_length--;
        }

        if (spi_handle->rx_length <= 0)
        {
            /* Disable the interrupt */
            spi_handle->spix->CR2 &= ~(1 << SPI_CR2_RXNEIE);

            /* Reset data and state */
            spi_handle->rx_buffer = (void *)0;
            spi_handle->rx_length = 0;
            spi_handle->rx_state  = SPI_STATE_READY;

            spi_interrupt_event_callback(spi_handle, SPI_EVENT_RX_COMPLETE);
        }
    }

    is_flag_set      = spi_handle->spix->SR & (1 << SPI_SR_OVR);
    is_interrupt_set = spi_handle->spix->CR2 & (1 << SPI_CR2_ERRIE);
    if (is_flag_set && is_interrupt_set)
    {
        /* Handle overrun error interrupt */
        if (spi_handle->tx_state != SPI_STATE_BUSY_IN_TX)
        {
            /* Clear overrun error by reading DR and SR */
            uint8_t temp_reg;
            temp_reg = spi_handle->spix->DR;
            temp_reg = spi_handle->spix->SR;
            (void)temp_reg; /* Prevents compiler warning: unused variable */
        }

        spi_interrupt_event_callback(spi_handle, SPI_EVENT_OVERRUN_ERROR);
    }
}

uint8_t spi_get_flag_status(spi_regdef_t *spix, uint8_t flag)
{
    return (spix->SR & flag) ? SET : RESET;
}

void spi_peripheral_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
        spix->CR1 |= 1 << SPI_CR1_SPE;
    else
        spix->CR1 &= ~(1 << SPI_CR1_SPE);
}

void spi_clock_control(spi_regdef_t *spix, uint8_t state)
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

void spi_ssoe_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
        spix->CR2 |= 1 << SPI_CR2_SSOE;
    else
        spix->CR2 &= ~(1 << SPI_CR2_SSOE);
}

void spi_ssi_control(spi_regdef_t *spix, uint8_t state)
{
    if (state == ENABLE)
        spix->CR1 |= 1 << SPI_CR1_SSI;
    else
        spix->CR1 &= ~(1 << SPI_CR1_SSI);
}

__attribute__((weak)) void spi_interrupt_event_callback(spi_handle_t *spi_handle, uint8_t event)
{
    /* Needs to be overriden if application wants to handle interrupt events. */
}
