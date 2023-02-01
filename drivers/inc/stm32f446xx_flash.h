#ifndef _STM32F446XX_FLASH_H_
#define _STM32F446XX_FLASH_H_

#include "stm32f446xx.h"

/* Generic flash macros */
#define FLASH_SUCCESS 1
#define FLASH_FAIL    0

/* Flash sector sizes */
#define FLASH_SECTOR_0_SIZE_KB (16  * 1024)
#define FLASH_SECTOR_1_SIZE_KB (16  * 1024)
#define FLASH_SECTOR_2_SIZE_KB (16  * 1024)
#define FLASH_SECTOR_3_SIZE_KB (16  * 1024)
#define FLASH_SECTOR_4_SIZE_KB (64  * 1024)
#define FLASH_SECTOR_5_SIZE_KB (128 * 1024)
#define FLASH_SECTOR_6_SIZE_KB (128 * 1024)
#define FLASH_SECTOR_7_SIZE_KB (128 * 1024)

/* Flash sector addresses */
#define FLASH_SECTOR_0_BASE_ADDR (FLASH_BASE_ADDR)
#define FLASH_SECTOR_1_BASE_ADDR (FLASH_SECTOR_0_BASE_ADDR + FLASH_SECTOR_0_SIZE_KB)
#define FLASH_SECTOR_2_BASE_ADDR (FLASH_SECTOR_1_BASE_ADDR + FLASH_SECTOR_1_SIZE_KB)
#define FLASH_SECTOR_3_BASE_ADDR (FLASH_SECTOR_2_BASE_ADDR + FLASH_SECTOR_2_SIZE_KB)
#define FLASH_SECTOR_4_BASE_ADDR (FLASH_SECTOR_3_BASE_ADDR + FLASH_SECTOR_3_SIZE_KB)
#define FLASH_SECTOR_5_BASE_ADDR (FLASH_SECTOR_4_BASE_ADDR + FLASH_SECTOR_4_SIZE_KB)
#define FLASH_SECTOR_6_BASE_ADDR (FLASH_SECTOR_5_BASE_ADDR + FLASH_SECTOR_5_SIZE_KB)
#define FLASH_SECTOR_7_BASE_ADDR (FLASH_SECTOR_6_BASE_ADDR + FLASH_SECTOR_6_SIZE_KB)
#define FLASH_END_ADDR           (FLASH_SECTOR_7_BASE_ADDR + FLASH_SECTOR_7_SIZE_KB)

void    flash_init(void);
uint8_t flash_read(uint32_t address, uint8_t *rx_buffer, uint32_t length);
uint8_t flash_is_status_bit_set(uint8_t bit_position);

/* Flash register bit positions */
#define FLASH_ACR_LATENCY   0

#define FLASH_SR_EOP        0
#define FLASH_SR_OPERR      1
#define FLASH_SR_WRPERR     4
#define FLASH_SR_PGAERR     5
#define FLASH_SR_PGPERR     6
#define FLASH_SR_PGSERR     7
#define FLASH_SR_RDERR      8
#define FLASH_SR_BSY        16

#define FLASH_CR_PG         0
#define FLASH_CR_SER        1
#define FLASH_CR_MER        2
#define FLASH_CR_SNB        3
#define FLASH_CR_PSIZE      8
#define FLASH_CR_STRT       16
#define FLASH_CR_EOPIE      24
#define FLASH_CR_ERRIE      25
#define FLASH_CR_LOCK       31

#endif