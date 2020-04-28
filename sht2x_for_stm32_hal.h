/* An STM32 HAL library written for the SHT2x temperature/humidity sensor series. */
/* Library by @eepj www.github.com/eepj */
#ifndef SHT2X_FOR_STM32_HAL_H
#define SHT2X_FOR_STM32_HAL_H
#include "main.h"
/*----------------------------------------------------------------------------*/
#define SHT2x_I2C_ADDR			0x40
#define SHT2x_HOLD_MASTER		1
#define SHT2x_READ_TEMP_HOLD	0b11100011
#define	SHT2x_READ_RH_HOLD		0b11100101
#define SHT2x_READ_TEMP_NOHOLD	0b11110011
#define SHT2x_READ_RH_NOHOLD	0b11110101
#define	SHT2x_WRITE_REG			0b11100110
#define SHT2x_READ_REG			0b11100111
#define SHT2x_SOFT_RESET		0b11111110
#define SHT2x_TIMEOUT			1000
/*----------------------------------------------------------------------------*/
typedef enum Resolution {
	RES_14_12 = 0b00000000,
	RES_12_8 = 0b00000001,
	RES_13_10 = 0b10000000,
	RES_11_11 = 0b10000001,
} Resolution;
/*----------------------------------------------------------------------------*/
I2C_HandleTypeDef *_sht2x_ui2c;

void SHT2x_Init(I2C_HandleTypeDef *hi2c);
void SHT2x_SetResolution(Resolution res);

uint8_t SHT2x_ReadUserReg(void);

uint16_t SHT2x_GetRaw(uint8_t cmd);

float SHT2x_GetTemperature(uint8_t hold);
float SHT2x_GetRelativeHumidity(uint8_t hold);

float SHT2x_CelsiusToFahrenheit(float celsius);
float SHT2x_CelsiusToKelvin(float celsius);

int32_t SHT2x_Pre(float f);
uint32_t SHT2x_Post(float f, int digits);
uint32_t SHT2x_Ipow(uint32_t x, uint32_t y);

#endif
