#ifndef _STM32F446XX_SPI_H_
#define _STM32F446XX_SPI_H_

#include "stm32f446xx.h"
#include "stm32f4xx_nvic.h"

/* SPI configuration structure */
typedef struct
{
    uint8_t mode;       /* @mode configuration */
    uint8_t comm;       /* @comm configuration */
    uint8_t clk_div;    /* @clk_div configuration */
    uint8_t cpol;       /* @cpol configuration */
    uint8_t cpha;       /* @cpha configuration */
    uint8_t ssm;        /* @ssm configuration */
    uint8_t dff;        /* @dff configuration */
    uint8_t ff;         /* @ff configuration */
} spi_config_t;

/* SPI handle structure */
typedef struct
{
    spi_regdef_t *spix;
    spi_config_t  config;
    uint8_t      *tx_buffer;
    uint8_t      *rx_buffer;
    uint32_t      tx_length;
    uint32_t      rx_length;
    uint8_t       tx_state;
    uint8_t       rx_state;
} spi_handle_t;

/* Serial peripheral interface driver public API */
void    spi_init               (spi_handle_t *spi_handle);

void    spi_transmit           (spi_handle_t *spi_handle, uint8_t *tx_buffer, uint32_t length);
void    spi_receive            (spi_handle_t *spi_handle, uint8_t *rx_buffer, uint32_t length);
uint8_t spi_transmit_it        (spi_handle_t *spi_handle, uint8_t *tx_buffer, uint32_t length);
uint8_t spi_receive_it         (spi_handle_t *spi_handle, uint8_t *rx_buffer, uint32_t length);

void    spi_irq_enable         (irq_nr number);
void    spi_irq_disable        (irq_nr number);
void    spi_irq_priority       (irq_nr number, irq_priority priority);
void    spi_irq_handler        (spi_handle_t *spi_handle);

uint8_t spi_get_flag_status    (spi_regdef_t *spix, uint8_t flag);
void    spi_peripheral_control (spi_regdef_t *spix, uint8_t state);
void    spi_clock_control      (spi_regdef_t *spix, uint8_t state);
void    spi_ssoe_control       (spi_regdef_t *spix, uint8_t state);
void    spi_ssi_control        (spi_regdef_t *spix, uint8_t state);

void    spi_interrupt_event_callback (spi_handle_t *spi_handle, uint8_t event);

/* SPI peripheral states */
#define SPI_STATE_READY      0
#define SPI_STATE_BUSY_IN_TX 1
#define SPI_STATE_BUSY_IN_RX 2

/* SPI interrupt events */
#define SPI_EVENT_TX_COMPLETE   0
#define SPI_EVENT_RX_COMPLETE   1
#define SPI_EVENT_OVERRUN_ERROR 2

/* @mode configuration */
#define SPI_MODE_SLAVE  0
#define SPI_MODE_MASTER 1

/* @comm configuration */
#define SPI_COMM_FULL_DUPLEX 0
#define SPI_COMM_HALF_DUPLEX 1
#define SPI_COMM_SIMPLEX_RX  2

/* @clk_div configuration */
#define SPI_CLK_DIV_2   0
#define SPI_CLK_DIV_4   1
#define SPI_CLK_DIV_8   2
#define SPI_CLK_DIV_16  3
#define SPI_CLK_DIV_32  4
#define SPI_CLK_DIV_64  5
#define SPI_CLK_DIV_128 6
#define SPI_CLK_DIV_256 7

/* @cpol configuration */
#define SPI_CPOL_IDLE_LOW  0
#define SPI_CPOL_IDLE_HIGH 1

/* @cpha configuration */
#define SPI_CPHA_FIRST_TRANSITION_CAPTURE  0
#define SPI_CPHA_SECOND_TRANSITION_CAPTURE 1

/* @ssm configuration */
#define SPI_SSM_DISABLE 0
#define SPI_SSM_ENABLE  1

/* @dff configuration */
#define SPI_DFF_8BITS  0
#define SPI_DFF_16BITS 1

/* @ff configuration */
#define SPI_FF_MSB_FIRST 0
#define SPI_FF_LSB_FIRST 1

/* SPI register bit positions */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7

#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8

/* SPI flags */
#define SPI_FLAG_TXE    (1 << SPI_SR_TXE)
#define SPI_FLAG_RXNE   (1 << SPI_SR_RXNE)
#define SPI_FLAG_BUSY   (1 << SPI_SR_BSY)

#endif
