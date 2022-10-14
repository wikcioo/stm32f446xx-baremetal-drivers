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
} i2c_handle_t;

/* Inter-integrated circuit driver public API */

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

#endif