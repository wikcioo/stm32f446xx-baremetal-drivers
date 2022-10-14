#ifndef _STM32F446XX_USART_H_
#define _STM32F446XX_USART_H_

#include "stm32f446xx.h"

/* USART configuration structure */
typedef struct
{
    uint8_t  mode;              /* See @mode configuration */
    uint8_t  word_length;       /* See @word_length configuration */
    uint8_t  stop_bits;         /* See @stop_bits configuration */
    uint32_t baudrate;          /* See @baudrate configuration */
    uint8_t  parity;            /* See @parity configuration */
    uint8_t  hw_flow_control;   /* See @hw_flow_control configuration */
} usart_config_t;

/* USART handle structure */
typedef struct
{
    usart_regdef_t *usartx;
    usart_config_t config;
} usart_handle_t;

/* Universal synchronous asynchronous receiver transmitter driver public API */
void usart_init     (usart_handle_t *usart_handle);
void usart_transmit (usart_handle_t *usart_handle, uint8_t *tx_buffer, uint32_t length);
void usart_receive  (usart_handle_t *usart_handle, uint8_t *rx_buffer, uint32_t length);

/* @mode configuration */
#define USART_MODE_TX_ONLY      0
#define USART_MODE_RX_ONLY      1
#define USART_MODE_TX_RX        2

/* See @word_length configuration */
#define USART_WORD_LENGTH_8BITS 0
#define USART_WORD_LENGTH_9BITS 1

/* See @stop_bits configuration */
#define USART_STOP_BITS_1       0
#define USART_STOP_BITS_0_5     1
#define USART_STOP_BITS_2       2
#define USART_STOP_BITS_1_5     3

/* See @baudrate configuration */
#define USART_BAUDRATE_1200		1200
#define USART_BAUDRATE_2400		2400
#define USART_BAUDRATE_9600		9600
#define USART_BAUDRATE_19200 	19200
#define USART_BAUDRATE_38400 	38400
#define USART_BAUDRATE_57600 	57600
#define USART_BAUDRATE_115200 	115200
#define USART_BAUDRATE_230400 	230400
#define USART_BAUDRATE_460800 	460800
#define USART_BAUDRATE_921600 	921600
#define USART_BAUDRATE_2M 		2000000
#define SUART_BAUDRATE_3M 		3000000

/* See @parity configuration */
#define USART_PARITY_NONE       0
#define USART_PARITY_EVEN       1
#define USART_PARITY_ODD        2

/* See @hw_flow_control configuration */
#define USART_HW_FLOW_CONTROL_NONE      0
#define USART_HW_FLOW_CONTROL_CTS       1
#define USART_HW_FLOW_CONTROL_RTS       2
#define USART_HW_FLOW_CONTROL_CTS_RTS   3

/* USART register bit positions */
#define USART_SR_PE			0
#define USART_SR_FE			1
#define USART_SR_NF			2
#define USART_SR_ORE		3
#define USART_SR_IDLE		4
#define USART_SR_RXNE		5
#define USART_SR_TC			6
#define USART_SR_TXE		7
#define USART_SR_LBD		8
#define USART_SR_CTS		9

#define USART_BRR_DIV_FRAC	0
#define USART_BRR_DIV_MANT	4

#define USART_CR1_SBK		0
#define USART_CR1_RWU		1
#define USART_CR1_RE		2
#define USART_CR1_TE		3
#define USART_CR1_IDLEIE	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE		7
#define USART_CR1_PEIE		8
#define USART_CR1_PS		9
#define USART_CR1_PCE		10
#define USART_CR1_WAKE		11
#define USART_CR1_M			12
#define USART_CR1_UE		13
#define USART_CR1_OVER8		15

#define USART_CR2_ADD		0
#define USART_CR2_LBDL		5
#define USART_CR2_LBDIE 	6
#define USART_CR2_LBCL		8
#define USART_CR2_CPHA 		9
#define USART_CR2_CPOL 		10
#define USART_CR2_CLKEN 	11
#define USART_CR2_STOP		12
#define USART_CR2_LINEN 	14

#define USART_CR3_EIE		0
#define USART_CR3_IREN 		1
#define USART_CR3_IRLP 		2
#define USART_CR3_HDSEL 	3
#define USART_CR3_NACK 		4
#define USART_CR3_SCEN 		5
#define USART_CR3_DMAR 		6
#define USART_CR3_DMAT 		7
#define USART_CR3_RTSE 		8
#define USART_CR3_CTSE 		9
#define USART_CR3_CTSIE		10
#define USART_CR3_ONEBIT 	11

#define USART_GTPR_PSC		0
#define USART_GTPR_GT		8

/* USART flags */
#define USART_FLAG_TXE      (1 << USART_SR_TXE)
#define USART_FLAG_RXNE     (1 << USART_SR_RXNE)
#define USART_FLAG_TC       (1 << USART_SR_TC)

#endif
