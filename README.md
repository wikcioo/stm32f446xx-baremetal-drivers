# stm32f446xx drivers and firmware examples

## Core drivers: found in drivers/core/
- [x] gpio with interrupt support
- [x] uart (TODO: interrupt mode)
- [x] rcc
- [ ] i2c
- [ ] spi
- [ ] timer
- [ ] pwm
- [ ] can

## Device drivers: found in drivers/bsp/
- [ ] adxl345 accelometer
- [ ] mpu6050 accelometer and gyroscope
- [ ] nrf24l01 radio transmitter and receiver
- [ ] ds1307 read time clock
- [ ] ssd1306 OLED display
- [ ] hc-06 Bluetooth module
- [ ] bmp280 barometer and pressure sensor

## Firmware: found in examples/

## How to build and flash?
**Note: this project has only been tested on Linux**

### Install st-link software
On Debian based distributions:
```sh
sudo apt install libusb-1.0-0-dev
```
On Arch based distributions:
```sh
sudo pacman -S stlink
```

### From the root directory first cross-compile the firmware you want to flash e.g.:
```sh
make -C path/to/firmware/directory
```

### Next flash the firmware using stlink
```sh
st-flash --reset write path/to/firmware/directory/<name>.bin 0x08000000
```
