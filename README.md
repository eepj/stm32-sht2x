# SHT2x_for_STM32_HAL
An STM32 HAL library for the SHT2x temperature/humidity sensor series. Tested on an SHT20.

## To test
* Minimal setup:
```
                                             _________
                                    N/C 4 --| |_____| |-- 3 N/C
                                    VDD 5 --|         |-- 2 GND
                                   SDA1 6 --|_________|-- 1 SCL1
                                   
 ```
* In STM32CubeIDE, include [`sht2x_for_stm32_hal.h`](./sht2x_for_stm32_hal.h) and [`sht2x_for_stm32_hal.c`](./sht2x_for_stm32_hal.c).
* Complie and flash [`main.c`](./examples/main.c) in [`./examples`](./examples) to microcontroller.
* Read the results from a UART monitor.
* Refer to [datasheets](https://www.sensirion.com/en/environmental-sensors/humidity-sensors/humidity-temperature-sensor-sht2x-digital-i2c-accurate/) for further information.

## Known issues
* Replaced binary values with hexadecimal for compatibility with Keil.
* Moved user I2C handle definition from .h header to .c file to prevent multiple definition error. Made definition in .h header  `extern`.
