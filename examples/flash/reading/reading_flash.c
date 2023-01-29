#include "stm32f446xx.h"
#include "stm32f446xx_flash.h"

int main(void)
{
    uint8_t flash_data[100];

    flash_init();
    flash_read(FLASH_SECTOR_0_BASE_ADDR, flash_data, 100);

    return 0;
}
