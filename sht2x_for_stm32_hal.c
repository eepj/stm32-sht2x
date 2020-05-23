/* An STM32 HAL library written for the SHT2x temperature/humidity sensor series. */
/* Libraries by @eepj www.github.com/eepj */
#include "sht2x_for_stm32_hal.h"
#include "main.h"
#ifdef __cplusplus
extern "C"{
#endif

I2C_HandleTypeDef *_sht2x_ui2c;
	
/**
 * @brief Initializes the SHT2x temperature/humidity sensor.
 * @param hi2c User I2C handle pointer.
 */
void SHT2x_Init(I2C_HandleTypeDef *hi2c) {
	_sht2x_ui2c = hi2c;
}

/**
 *  @brief Performs a soft reset.
 */
void SHT2x_SoftReset(void){
	uint8_t cmd = SHT2x_SOFT_RESET;
	HAL_I2C_Master_Transmit(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, &cmd, 1, SHT2x_TIMEOUT);
}

/**
 * @brief Gets the value stored in user register.
 * @return 8-bit value stored in user register, 0 to 255.
 */
uint8_t SHT2x_ReadUserReg(void) {
	uint8_t val;
	uint8_t cmd = SHT2x_READ_REG;
	HAL_I2C_Master_Transmit(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, &cmd, 1, SHT2x_TIMEOUT);
	HAL_I2C_Master_Receive(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, &val, 1, SHT2x_TIMEOUT);
	return val;
}

/**
 * @brief Sends the designated command to sensor and read a 16-bit raw value.
 * @param cmd Command to send to sensor.
 * @return 16-bit raw value, 0 to 65535.
 */
uint16_t SHT2x_GetRaw(uint8_t cmd) {
	uint8_t val[3] = { 0 };
	HAL_I2C_Master_Transmit(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, &cmd, 1, SHT2x_TIMEOUT);
	HAL_I2C_Master_Receive(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, val, 3, SHT2x_TIMEOUT);
	return val[0] << 8 | val[1];
}

/**
 * @brief Measures and gets the current temperature.
 * @param hold Holding mode, 0 for no hold master, 1 for hold master.
 * @return Floating point temperature value.
 */
float SHT2x_GetTemperature(uint8_t hold) {
	uint8_t cmd = (hold ? SHT2x_READ_TEMP_HOLD : SHT2x_READ_TEMP_NOHOLD);
	return -46.85 + 175.72 * (SHT2x_GetRaw(cmd) / 65536.0);
}

/**
 * @brief Measures and gets the current relative humidity.
 * @param hold Holding mode, 0 for no hold master, 1 for hold master.
 * @return Floating point relative humidity value.
 */
float SHT2x_GetRelativeHumidity(uint8_t hold) {
	uint8_t cmd = (hold ? SHT2x_READ_RH_HOLD : SHT2x_READ_RH_NOHOLD);
	return -6 + 125.00 * (SHT2x_GetRaw(cmd) / 65536.0);
}

/**
 * @brief Sets the measurement resolution.
 * @param res Enum resolution.
 * @note Available resolutions: RES_14_12, RES_12_8, RES_13_10, RES_11_11.
 * @note RES_14_12 = 14-bit temperature and 12-bit RH resolution, etc.
 */
void SHT2x_SetResolution(SHT2x_Resolution res) {
	uint8_t val = SHT2x_ReadUserReg();
	val = (val & 0x7e) | res;
	uint8_t temp[2] = { SHT2x_WRITE_REG, val };
	HAL_I2C_Master_Transmit(_sht2x_ui2c, SHT2x_I2C_ADDR << 1, temp, 2, SHT2x_TIMEOUT);
}

/**
 * @brief Converts degrees Celsius to degrees Fahrenheit.
 * @param celsius Floating point temperature in degrees Celsius.
 * @return Floating point temperature in degrees Fahrenheit.
 */
float SHT2x_CelsiusToFahrenheit(float celsius) {
	return (9.0 / 5.0) * celsius + 32;
}

/**
 * @brief Converts degrees Celsius to Kelvin.
 * @param celsius Floating point temperature in degrees Celsius.
 * @return Floating point temperature in Kelvin.
 */
float SHT2x_CelsiusToKelvin(float celsius) {
	return celsius + 273;
}

/**
 * @brief Gets the integer part of a floating point number.
 * @note Avoids the use of sprinf floating point formatting.
 * @param num Floating point number.
 * @return Integer part of floating point number.
 */
int32_t SHT2x_GetInteger(float num) {
	return num / 1;
}

/**
 * @brief Gets the decimal part of a floating point number.
 * @note Avoids the use of sprinf floating point formatting.
 * @param num Floating point number.
 * @return Decimal part of floating point number.
 */
uint32_t SHT2x_GetDecimal(float num, int digits) {
	float postDec = num - SHT2x_GetInteger(num);
	return postDec * SHT2x_Ipow(10, digits);
}

/**
 * @brief Integer equivalent of pow() in math.h.
 * @param base Base.
 * @param power Power.
 * @return
 */
uint32_t SHT2x_Ipow(uint32_t base, uint32_t power) {
	uint32_t temp = base;
	for (uint32_t i = 1; i < power; i++)
		temp *= base;
	return temp;
}

#ifdef __cplusplus
}
#endif
