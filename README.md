# SHT2x_for_STM32_HAL
An STM32 HAL library written for the SHT2x temperature/humidity sensor series. Tested on an SHT20.

## To test
* Minimal setup:
```
                                             _________
                                            |  _____  |
                                    N/C 4 --| |_____| |-- 3 N/C
                                    VDD 5 --|         |-- 2 GND
                                   SDA1 6 --|         |-- 1 SCL1
                                            |_________|
 
 ```
* In STM32CubeIDE, include [`sht2x_for_stm32_hal.h`](./sht2x_for_stm32_hal.h) and [`sht2x_for_stm32_hal.c`](./sht2x_for_stm32_hal.c).
* Complie and flash [`main.c`](./examples/main.c) in [`./examples`](./examples) to microcontroller.
* Read the results from a UART monitor.
* Refer to datasheets for further information.

## Known issues
* Line 63 of [`sht2x_for_stm32_hal.c`](./sht2x_for_stm32_hal.c) may throw an error.
