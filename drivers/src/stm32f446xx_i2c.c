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

void i2c_master_transmit(i2c_handle_t *i2c_handle, uint8_t *tx_buffer, uint32_t length, uint8_t slave_addr)
{
}

void i2c_master_receive(i2c_handle_t *i2c_handle, uint8_t *rx_buffer, uint32_t length, uint8_t slave_addr)
{
}

uint8_t i2c_get_flag_status(i2c_regdef_t *i2cx, uint32_t flag)
{
    return (i2cx->SR1 & flag) ? SET : RESET;
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
