#include "stm32f446xx_flash.h"
#include <string.h>

int main(void)
{
    uint8_t data[] = "Hello, World\n";

    flash_init();
    flash_write(FLASH_SECTOR_4_BASE_ADDR, data, strlen((char *)data));

    return 0;
}
