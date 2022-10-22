#ifndef _STM32F446XX_I2C_H_
#define _STM32F446XX_I2C_H_

#include "stm32f446xx.h"
#include "stm32f4xx_nvic.h"

/* I2C configuration structure */
typedef struct
{
    uint8_t  slave_addr;
    uint8_t  ack_control;       /* @ack_control configuration */
    uint32_t clk_speed;         /* @clk_speed configuration */
    uint16_t fm_duty_cycle;     /* @fm_duty_cycle configuration */
} i2c_config_t;

/* I2C handle structure */
typedef struct
{
    i2c_regdef_t *i2cx;
    i2c_config_t  config;
    uint8_t      *tx_buffer;
    uint8_t      *rx_buffer;
    uint32_t      tx_length;
    uint32_t      rx_length;
    uint8_t       tx_rx_state;
    uint8_t       slave_addr;
    uint32_t      rx_size;
    uint8_t       gen_stop;
} i2c_handle_t;

/* Inter-integrated circuit driver public API */
void    i2c_init                (i2c_handle_t *i2c_handle);

void    i2c_master_transmit     (i2c_handle_t *i2c_handle, uint8_t *tx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop);
void    i2c_master_receive      (i2c_handle_t *i2c_handle, uint8_t *rx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop);
uint8_t i2c_master_transmit_it  (i2c_handle_t *i2c_handle, uint8_t *tx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop);
uint8_t i2c_master_receive_it   (i2c_handle_t *i2c_handle, uint8_t *rx_buffer, uint32_t length, uint8_t slave_addr, uint8_t gen_stop);

void    i2c_close_transmisstion (i2c_handle_t *i2c_handle);
void    i2c_close_reception     (i2c_handle_t *i2c_handle);

void    i2c_irq_enable          (irq_nr number);
void    i2c_irq_disable         (irq_nr number);
void    i2c_irq_priority        (irq_nr number, irq_priority priority);
void    i2c_irq_event_handler   (i2c_handle_t *i2c_handle);
void    i2c_irq_error_handler   (i2c_handle_t *i2c_handle);

uint8_t i2c_is_status_flag1_set (i2c_regdef_t *i2cx, uint32_t flag);
uint8_t i2c_is_status_flag2_set (i2c_regdef_t *i2cx, uint32_t flag);
void    i2c_peripheral_control  (i2c_regdef_t *i2cx, uint8_t state);
void    i2c_clock_control       (i2c_regdef_t *i2cx, uint8_t state);
void    i2c_ack_control         (i2c_regdef_t *i2cx, uint8_t state);

void    i2c_application_callback (i2c_handle_t *i2c_handle, uint8_t event_or_error);

/* I2C peripheral states */
#define I2C_STATE_READY      0
#define I2C_STATE_BUSY_IN_TX 1
#define I2C_STATE_BUSY_IN_RX 2

/* I2C interrupt events */
#define I2C_EVENT_TX_COMPLETE 0
#define I2C_EVENT_RX_COMPLETE 1
#define I2C_EVENT_STOP        2
#define I2C_EVENT_DATA_REQ    3
#define I2C_EVENT_DATA_RCV    4

/* I2C interrupt errors */
#define I2C_ERROR_BUS       0
#define I2C_ERROR_ARB_LOSS  1
#define I2C_ERROR_ACK_FAIL  2
#define I2C_ERROR_OVR       3
#define I2C_ERROR_TIMEOUT   4

/* @ack_control configuration */
#define I2C_ACK_DISABLE     0
#define I2C_ACK_ENABLE      1

/* @clk_speed configuration */
#define I2C_CLK_SPEED_SM    100000
#define I2C_CLK_SPEED_FM2K  200000
#define I2C_CLK_SPEED_FM4K  400000

/* @fm_duty_cycle configuration */
#define I2C_DUTY_CYCLE_2    0
#define I2C_DUTY_CYCLE_16_9 1

/* Other i2c macros */
#define I2C_WRITE_DATA 0
#define I2C_READ_DATA  1

#define I2C_STOP_BIT_DISABLE 0
#define I2C_STOP_BIT_ENABLE  1

/* I2C register bit positions */
#define I2C_CR1_PE			0
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_SWRST		15

#define I2C_CR2_FREQ		0
#define I2C_CR2_ITERREN		8
#define I2C_CR2_ITEVTEN		9
#define I2C_CR2_ITBUFEN		10

#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_TIMEOUT		14

#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_DUALF		7

#define I2C_CCR_CCR			0
#define I2C_CCR_DUTY		14
#define I2C_CCR_FS			15

/* I2C flags */
#define I2C_FLAG_TXE		(1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE		(1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB			(1 << I2C_SR1_SB)
#define I2C_FLAG_OVR		(1 << I2C_SR1_OVR)
#define I2C_FLAG_AF			(1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO		(1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR		(1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF		(1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10		(1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF		(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR		(1 << I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT    (1 << I2C_SR1_TIMEOUT)

#define I2C_FLAG_MSL        (1 << I2C_SR2_MSL)
#define I2C_FLAG_TRA        (1 << I2C_SR2_TRA)
#define I2C_FLAG_BUSY       (1 << I2C_SR2_BUSY)
#define I2C_FLAG_DUALF      (1 << I2C_SR2_DUALF)
#define I2C_FLAG_GENCALL    (1 << I2C_SR2_GENCALL)

#endif
