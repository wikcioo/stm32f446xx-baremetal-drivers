#include "stm32f446xx_crc.h"

uint32_t crc_accumulate(crc_regdef_t *hcrc, uint32_t *data, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++) {
        hcrc->DR = data[i];
    }

    return hcrc->DR;
}

uint32_t crc_calculate(crc_regdef_t *hcrc, uint32_t *data, uint32_t length)
{
    /* Reset CRC first */
    hcrc->CR |= 1 << CRC_CR_RESET;
    return crc_accumulate(hcrc, data, length);
}
