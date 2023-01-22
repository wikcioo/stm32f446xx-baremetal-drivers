#include "stm32f446xx_flash.h"
#include "stm32f446xx_rcc.h"

void flash_init(void)
{
    uint32_t system_clock = rcc_get_system_clock_freq();

    // Reset the last 4 bits so that WS = 0 (default behaviour)
    FLASH->ACR &= ~(0xF << FLASH_ACR_LATENCY);

    // The following calculates the WS value based on the system clock frequency
    // For now it is assumed that the internal voltage reference is 3.3V,
    // which makes the step value between frequencies to be 30
    // TODO: Implement this function for other voltage values

    uint8_t step = 30; // hardcoded for now
    uint8_t ws_value = ((system_clock / MEGA) - 1) / step;

    // Set the last 4 bits to the ws_value
    FLASH->ACR |= (ws_value & 0xF) << FLASH_ACR_LATENCY;
}
