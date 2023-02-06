#include "stm32f446xx_flash.h"
#include <string.h>

int main(void)
{
    flash_init();

    /* First write some dummy data to the sector we erase later */
    uint8_t data[] = "FooBarBar";
    flash_write(FLASH_SECTOR_4_BASE_ADDR, data, strlen((char *)data));

    flash_sector_erase(FLASH_SECTOR_4_NUMBER);

    return 0;
}
