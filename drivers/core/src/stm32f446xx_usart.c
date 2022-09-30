#include "stm32f446xx_usart.h"
#include "stm32f446xx_rcc.h"

static uint8_t usart_get_flag_status(usart_regdef_t *usartx, uint32_t flag);
static void usart_peripheral_enable(usart_regdef_t *usartx, uint8_t state);
static void usart_clock_control(usart_regdef_t *usartx, uint8_t state);
static void usart_set_baudrate(usart_regdef_t *usartx, uint32_t baudrate);

void usart_init(usart_handle_t *usart_handle)
{
    usart_clock_control(usart_handle->usartx, ENABLE);

    /* Configure USART_CR1 */
    uint32_t temp_reg = 0;

    if (usart_handle->config.mode == USART_MODE_TX_ONLY)
        temp_reg |= 1 << USART_CR1_TE;
    else if (usart_handle->config.mode == USART_MODE_RX_ONLY)
        temp_reg |= 1 << USART_CR1_RE;
    else if (usart_handle->config.mode == USART_MODE_TX_RX)
        temp_reg |= (1 << USART_CR1_TE) | (1 << USART_CR1_RE);

    if (usart_handle->config.parity == USART_PARITY_EVEN)
    {
        temp_reg |= 1 << USART_CR1_PCE;
    }
    else if (usart_handle->config.parity == USART_PARITY_ODD)
    {
        temp_reg |= 1 << USART_CR1_PCE;
        temp_reg |= 1 << USART_CR1_PS;
    }

    temp_reg |= (usart_handle->config.word_length << USART_CR1_M);

    usart_handle->usartx->CR1 |= temp_reg;

    /* Configure USART_CR2 */
    temp_reg = 0;
    temp_reg |= usart_handle->config.stop_bits << USART_CR2_STOP;
    usart_handle->usartx->CR2 |= temp_reg;

    /* Configure USART_CR3 */
    temp_reg = 0;

    if (usart_handle->config.hw_flow_control == USART_HW_FLOW_CONTROL_CTS)
        temp_reg |= 1 << USART_CR3_CTSE;
    else if (usart_handle->config.hw_flow_control == USART_HW_FLOW_CONTROL_RTS)
        temp_reg |= 1 << USART_CR3_RTSE;
    else if (usart_handle->config.hw_flow_control == USART_HW_FLOW_CONTROL_CTS_RTS)
        temp_reg |= (1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE);

    usart_handle->usartx->CR3 |= temp_reg;

    /* Configure USART_BRR */
    usart_set_baudrate(usart_handle->usartx, usart_handle->config.baudrate);
}

void usart_transmit(usart_handle_t *usart_handle, uint8_t *tx_buffer, uint32_t length)
{
    usart_peripheral_enable(usart_handle->usartx, ENABLE);

    while (length--)
    {
        while (!usart_get_flag_status(usart_handle->usartx, USART_FLAG_TXE));

        if (usart_handle->config.word_length == USART_WORD_LENGTH_9BITS)
        {
            uint16_t *data = (uint16_t *)tx_buffer;
            usart_handle->usartx->DR = (*data & (uint16_t)0x1FF);
            tx_buffer++;
            if (usart_handle->config.parity == USART_PARITY_NONE) tx_buffer++;
        }
        else
        {
            usart_handle->usartx->DR = (*tx_buffer & (uint8_t)0xFF);
            tx_buffer++;
        }
    }

    while (!usart_get_flag_status(usart_handle->usartx, USART_FLAG_TC));
}

void usart_receive(usart_handle_t *usart_handle, uint8_t *rx_buffer, uint32_t length)
{

}

static uint8_t usart_get_flag_status(usart_regdef_t *usartx, uint32_t flag)
{
    return (usartx->SR & flag) ? SET : RESET;
}

static void usart_peripheral_enable(usart_regdef_t *usartx, uint8_t state)
{
    if (state == ENABLE)
        usartx->CR1 |= 1 << USART_CR1_UE;
    else
        usartx->CR1 &= ~(1 << USART_CR1_UE);
}

static void usart_clock_control(usart_regdef_t *usartx, uint8_t state)
{
    if (state == ENABLE)
    {
        if      (usartx == USART1) USART1_CLK_ENABLE();
        else if (usartx == USART2) USART2_CLK_ENABLE();
        else if (usartx == USART3) USART3_CLK_ENABLE();
        else if (usartx == UART4)  UART4_CLK_ENABLE();
        else if (usartx == UART5)  UART5_CLK_ENABLE();
        else if (usartx == USART6) USART6_CLK_ENABLE();
    }
    else
    {
        if      (usartx == USART1) USART1_CLK_DISABLE();
        else if (usartx == USART2) USART2_CLK_DISABLE();
        else if (usartx == USART3) USART3_CLK_DISABLE();
        else if (usartx == UART4)  UART4_CLK_DISABLE();
        else if (usartx == UART5)  UART5_CLK_DISABLE();
        else if (usartx == USART6) USART6_CLK_DISABLE();
    }
}

static void usart_set_baudrate(usart_regdef_t *usartx, uint32_t baudrate)
{
    uint32_t apbx_clock;
    uint32_t usartdiv;

    if (usartx == USART1 || usartx == USART6)
        apbx_clock = rcc_get_apbx_peripheral_clock_freq(APB2_PERIPHERAL_CLOCK);
    else
        apbx_clock = rcc_get_apbx_peripheral_clock_freq(APB1_PERIPHERAL_CLOCK);

    uint8_t oversampling8 = usartx->CR1 & (1 << USART_CR1_OVER8);
    if (oversampling8)
        usartdiv = (25 * apbx_clock / (2 * baudrate));
    else
        usartdiv = (25 * apbx_clock / (4 * baudrate));

    uint16_t mantissa = (usartdiv / 100) & 0xFFF;
    uint8_t  fraction = usartdiv - (mantissa * 100);

    if (oversampling8)
        fraction = (((fraction * 8) + 50) / 100) & 0xF;
    else
        fraction = (((fraction * 16) + 50) / 100) & 0xF;

    usartx->BRR |= (mantissa << 4) | fraction; 
}
