#include "stm32f446xx_i2c.h"
#include "stm32f446xx_rcc.h"

static void i2c_generate_start(i2c_regdef_t *i2cx)
{
    i2cx->CR1 |= 1 << I2C_CR1_START;
}

static void i2c_generate_stop(i2c_regdef_t *i2cx)
{
    i2cx->CR1 |= 1 << I2C_CR1_STOP;
}

static void i2c_generate_address(i2c_regdef_t *i2cx, uint8_t slave_addr, uint8_t operation)
{
    slave_addr <<= 1;
    slave_addr |= operation & 1;
    i2cx->DR = slave_addr;
}

static void i2c_clear_addr_flag(i2c_regdef_t *i2cx)
{
    /* Cleared by reading peripheral registers SR1 and SR2 */
    uint32_t dummy;
    dummy = i2cx->SR1;
    dummy = i2cx->SR2;
    (void)dummy; /* Prevent unused variable compiler warning */
}

void i2c_init(i2c_handle_t *i2c_handle)
{
    i2c_clock_control(i2c_handle->i2cx, ENABLE);
    uint32_t apb1_freq = rcc_get_apbx_peripheral_clock_freq(APB1_PERIPHERAL_CLOCK);

    /* Configure I2C_CR1 */
    uint32_t temp_reg = 0;
    temp_reg |= i2c_handle->config.ack_control << I2C_CR1_ACK;
    i2c_handle->i2cx->CR1 |= temp_reg;

    /* Configure I2C_CR2 */
    temp_reg = 0;
    temp_reg |= (apb1_freq / 1000000U) & 0x3F;
    i2c_handle->i2cx->CR2 |= temp_reg;

    /* Configure I2C_CCR */
    temp_reg = 0;
    if (i2c_handle->config.clk_speed == I2C_CLK_SPEED_SM)
    {
        /* Standard mode */
        temp_reg |= apb1_freq / (2 * i2c_handle->config.clk_speed);
    }
    else
    {
        /* Fast mode */
        temp_reg |= 1 << I2C_CCR_FS;
        temp_reg |= i2c_handle->config.fm_duty_cycle << I2C_CCR_DUTY;

        if (i2c_handle->config.fm_duty_cycle == I2C_DUTY_CYCLE_2)
            temp_reg |= apb1_freq / (3 * i2c_handle->config.clk_speed);
        else
            temp_reg |= apb1_freq / (25 * i2c_handle->config.clk_speed);
    }

    temp_reg = temp_reg & 0xFFF;
    i2c_handle->i2cx->CCR |= temp_reg;

    /* Configure I2C_TRISE */
    temp_reg = 0;
    if (i2c_handle->config.clk_speed == I2C_CLK_SPEED_SM)
        temp_reg |= (apb1_freq / 1000000U) + 1;
    else
        temp_reg |= ((apb1_freq * 300) / 1000000000U) + 1;

    i2c_handle->i2cx->TRISE |= temp_reg;
}

void i2c_master_transmit(i2c_handle_t *i2c_handle, uint8_t *tx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop)
{
    i2c_peripheral_control(i2c_handle->i2cx, ENABLE);

    i2c_generate_start(i2c_handle->i2cx);
    /* Confirm that the start generation completed before continuing */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_SB));

    i2c_generate_address(i2c_handle->i2cx, slave_addr, I2C_WRITE_DATA);
    /* Confirm that address generation completed before continuing */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_ADDR));

    i2c_clear_addr_flag(i2c_handle->i2cx);

    while (length--)
    {
        /* Wait until data register is empty */
        while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_TXE));
        i2c_handle->i2cx->DR = *tx_buffer++;
    }

    /* Wait until data register is empty */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_TXE));
    /* Wait until byte transfer is finished */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_BTF));

    if (gen_stop == I2C_STOP_BIT_ENABLE)
        i2c_generate_stop(i2c_handle->i2cx);
}

void i2c_master_receive(i2c_handle_t *i2c_handle, uint8_t *rx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop)
{
    i2c_peripheral_control(i2c_handle->i2cx, ENABLE);

    i2c_generate_start(i2c_handle->i2cx);
    /* Confirm that the start generation completed before continuing */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_SB));

    i2c_generate_address(i2c_handle->i2cx, slave_addr, I2C_READ_DATA);
    /* Confirm that address generation completed before continuing */
    while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_ADDR));

    if (length == 1)
    {
        i2c_ack_control(i2c_handle->i2cx, DISABLE);
        i2c_clear_addr_flag(i2c_handle->i2cx);

        /* Wait until receive buffer is not empty */
        while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_RXNE));

        if (gen_stop == I2C_STOP_BIT_ENABLE)
            i2c_generate_stop(i2c_handle->i2cx);

        *rx_buffer = i2c_handle->i2cx->DR;
    }
    else
    {
        i2c_clear_addr_flag(i2c_handle->i2cx);

        for (uint32_t i = length; i > 0; i--)
        {
            if (length == 2)
            {
                i2c_ack_control(i2c_handle->i2cx, DISABLE);
                if (gen_stop == I2C_STOP_BIT_ENABLE)
                    i2c_generate_stop(i2c_handle->i2cx);
            }

            /* Wait until receive buffer is not empty */
            while (!i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_RXNE));

            *rx_buffer++ = i2c_handle->i2cx->DR;
        }
    }

    if (i2c_handle->config.ack_control == I2C_ACK_ENABLE)
        i2c_ack_control(i2c_handle->i2cx, ENABLE);
}

uint8_t i2c_master_transmit_it(i2c_handle_t *i2c_handle, uint8_t *tx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop)
{
    uint8_t state = i2c_handle->tx_rx_state;;

    if (state != I2C_STATE_BUSY_IN_TX && state != I2C_STATE_BUSY_IN_RX)
    {
        /* Save data and update state */
        i2c_handle->tx_buffer   = tx_buffer;
        i2c_handle->tx_length   = length;
        i2c_handle->tx_rx_state = I2C_STATE_BUSY_IN_TX;
        i2c_handle->slave_addr  = slave_addr;
        i2c_handle->gen_stop    = gen_stop;
    }

    /* Enable buffer, event and error interrupts */
    i2c_handle->i2cx->CR2 |= (1 << I2C_CR2_ITBUFEN) | (1 << I2C_CR2_ITEVTEN) | (1 << I2C_CR2_ITERREN);

    i2c_generate_start(i2c_handle->i2cx);

    return state;
}

uint8_t i2c_master_receive_it(i2c_handle_t *i2c_handle, uint8_t *rx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop)
{
    uint8_t state = i2c_handle->tx_rx_state;

    if (state != I2C_STATE_BUSY_IN_TX && state != I2C_STATE_BUSY_IN_RX)
    {
        /* Save data and update state */
        i2c_handle->rx_buffer   = rx_buffer;
        i2c_handle->rx_length   = length;
        i2c_handle->rx_size     = length;
        i2c_handle->tx_rx_state = I2C_STATE_BUSY_IN_RX;
        i2c_handle->slave_addr  = slave_addr;
        i2c_handle->gen_stop    = gen_stop;
    }

    /* Enable buffer, event and error interrupts */
    i2c_handle->i2cx->CR2 |= (1 << I2C_CR2_ITBUFEN) | (1 << I2C_CR2_ITEVTEN) | (1 << I2C_CR2_ITERREN);

    i2c_generate_start(i2c_handle->i2cx);

    return state;
}

void i2c_close_transmisstion(i2c_handle_t *i2c_handle)
{
    /* Disable buffer and event interrupts */
    i2c_handle->i2cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
    i2c_handle->i2cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

    /* Reset tx elements in I2C handle */
    i2c_handle->tx_buffer   = (void *)0;
    i2c_handle->tx_length   = 0;
    i2c_handle->tx_rx_state = I2C_STATE_READY;
}

void i2c_close_reception(i2c_handle_t *i2c_handle)
{
    /* Disable buffer and event interrupts */
    i2c_handle->i2cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
    i2c_handle->i2cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

    /* Reset rx elements in I2C handle */
    i2c_handle->rx_buffer   = (void *)0;
    i2c_handle->rx_length   = 0;
    i2c_handle->rx_size     = 0;
    i2c_handle->tx_rx_state = I2C_STATE_READY;

    if (i2c_handle->config.ack_control == I2C_ACK_ENABLE)
        i2c_ack_control(i2c_handle->i2cx, ENABLE);
}

void i2c_irq_enable(irq_nr number)
{
    nvic_enable_irq(number);
}

void i2c_irq_disable(irq_nr number)
{
    nvic_disable_irq(number);
}

void i2c_irq_priority(irq_nr number, irq_priority priority)
{
    nvic_set_priority(number, priority);
}

void i2c_irq_error_handler(i2c_handle_t *i2c_handle)
{
    uint8_t is_error_interrupt_set;

    is_error_interrupt_set = i2c_handle->i2cx->CR2 & (1 << I2C_CR2_ITERREN);

    if (i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_BERR) && is_error_interrupt_set)
    {
        /* Handle 'bus error' interrupt */
        i2c_handle->i2cx->SR1 &= ~(1 << I2C_SR1_BERR);
        i2c_application_callback(i2c_handle, I2C_ERROR_BUS);
    }

    if (i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_ARLO) && is_error_interrupt_set)
    {
        /* Handle 'arbitration loss' interrupt */
        i2c_handle->i2cx->SR1 &= ~(1 << I2C_SR1_ARLO);
        i2c_application_callback(i2c_handle, I2C_ERROR_ARB_LOSS);
    }

    if (i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_AF) && is_error_interrupt_set)
    {
        /* Handle 'acknowledge failure' interrupt */
        i2c_handle->i2cx->SR1 &= ~(1 << I2C_SR1_AF);
        i2c_application_callback(i2c_handle, I2C_ERROR_ACK_FAIL);
    }

    if (i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_OVR) && is_error_interrupt_set)
    {
        /* Handle 'overrun/underrun' interrupt */
        i2c_handle->i2cx->SR1 &= ~(1 << I2C_SR1_OVR);
        i2c_application_callback(i2c_handle, I2C_ERROR_OVR);
    }

    if (i2c_is_status_flag1_set(i2c_handle->i2cx, I2C_FLAG_TIMEOUT) && is_error_interrupt_set)
    {
        /* Handle 'timeout' interrupt */
        i2c_handle->i2cx->SR1 &= ~(1 << I2C_SR1_TIMEOUT);
        i2c_application_callback(i2c_handle, I2C_ERROR_TIMEOUT);
    }
}

uint8_t i2c_is_status_flag1_set(i2c_regdef_t *i2cx, uint32_t flag)
{
    return (i2cx->SR1 & flag) ? SET : RESET;
}

uint8_t i2c_is_status_flag2_set (i2c_regdef_t *i2cx, uint32_t flag)
{
    return (i2cx->SR2 & flag) ? SET : RESET;
}

void i2c_peripheral_control(i2c_regdef_t *i2cx, uint8_t state)
{
    if (state == ENABLE)
        i2cx->CR1 |= 1 << I2C_CR1_PE;
    else
        i2cx->CR1 &= ~(1 << I2C_CR1_PE);
}

void i2c_clock_control(i2c_regdef_t *i2cx, uint8_t state)
{
    if (state == ENABLE)
    {
        if      (i2cx == I2C1) I2C1_CLK_ENABLE();
        else if (i2cx == I2C2) I2C2_CLK_ENABLE();
        else if (i2cx == I2C3) I2C3_CLK_ENABLE();
    }
    else
    {
        if      (i2cx == I2C1) I2C1_CLK_DISABLE();
        else if (i2cx == I2C2) I2C2_CLK_DISABLE();
        else if (i2cx == I2C3) I2C3_CLK_DISABLE();
    }
}

void i2c_ack_control(i2c_regdef_t *i2cx, uint8_t state)
{
    if (state == ENABLE)
        i2cx->CR1 |= 1 << I2C_CR1_ACK;
    else
        i2cx->CR1 &= ~(1 << I2C_CR1_ACK);
}

__attribute__((weak)) void i2c_application_callback(i2c_handle_t *i2c_handle, uint8_t event_or_error)
{
    /* Needs to be overriden if the application wants to handle interrupt events and errors */
}
