#ifndef _STM32F446XX_CRC_H_
#define _STM32F446XX_CRC_H_

#include "stm32f446xx.h"

#define CRC_CR_RESET 0

uint32_t crc_accumulate(crc_regdef_t *hcrc, uint32_t *data, uint32_t length);
uint32_t crc_calculate(crc_regdef_t *hcrc, uint32_t *data, uint32_t length);

#endif
