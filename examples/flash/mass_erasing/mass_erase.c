#include "stm32f446xx_flash.h"
#include <string.h>

int main(void)
{
    uint8_t data[] = "MassEraseMassEraseMassErase";

    flash_init();
    flash_write(FLASH_SECTOR_4_BASE_ADDR, data, strlen((char *)data));
    flash_write(FLASH_SECTOR_5_BASE_ADDR, data, strlen((char *)data));
    flash_write(FLASH_SECTOR_6_BASE_ADDR, data, strlen((char *)data));
    flash_write(FLASH_SECTOR_7_BASE_ADDR, data, strlen((char *)data));

    flash_mass_erase();

    while (1);

    return 0;
}
