# STM32F446xx baremetal drivers

## Currently supports:
- [x] gpio with interrupt support
- [x] uart (TODO: interrupt mode)
- [x] spi with interrupt support
- [x] i2c (TODO: interrupt mode)
- [x] rcc
- [x] nvic
- [x] systick
- [x] crc
- [ ] timer
- [ ] pwm

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
