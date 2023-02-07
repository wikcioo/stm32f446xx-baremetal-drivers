FIRMWARE = mass_erase
ELF = $(FIRMWARE).elf
CC = arm-none-eabi-gcc
MACH = cortex-m4
PROJECT_ROOT = ../../..
CORE_DRIVERS_DIR = ../../../drivers
CFLAGS = -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -g -Wall -Wformat -Wpedantic -Wshadow -O0 -I$(CORE_DRIVERS_DIR)/inc
LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T$(PROJECT_ROOT)/stm32f446xx_flash_ram.ld -Wl,-Map=$(FIRMWARE).map

.PHONY = all clean

all:
	@if [ ! -d "$(PROJECT_ROOT)/build" ]; then\
		echo "Cross-Compiling core drivers";\
		$(MAKE) --no-print-directory -C $(PROJECT_ROOT)/;\
	fi
	@make --no-print-directory $(ELF)
	@arm-none-eabi-objcopy -O binary $(ELF) $(FIRMWARE).bin

$(ELF): $(FIRMWARE).o
	$(CC) $(LDFLAGS) $(wildcard $(PROJECT_ROOT)/build/*.o) $< -o $@

$(FIRMWARE).o: $(FIRMWARE).c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.elf *.bin *.o *.map
