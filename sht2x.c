/*
 * sht2x.c
 *
 *  Created on: Mar 25, 2025
 *      Author: Celestial
 */

#include "sht2x.h"

I2C_HandleTypeDef *sht2x_i2c;

void SHT2X_Init(I2C_HandleTypeDef *hi2c) {
	sht2x_i2c = hi2c;
}

uint8_t SHT2X_Read_User_Reg(void) {
	uint8_t command = SHT2X_ADDR_READ_REG;
	uint8_t user_reg;

	HAL_I2C_Master_Transmit(sht2x_i2c, SHT2X_ADDR_DEV << 1, &command, 1, 1000);
	HAL_I2C_Master_Receive(sht2x_i2c, SHT2X_ADDR_DEV << 1, &user_reg, 1, 1000);

	return user_reg;
}
void SHT2X_Write_User_Reg(uint8_t data){
	uint8_t msg[2] = {SHT2X_ADDR_WRITE_REG, data};

	HAL_I2C_Master_Transmit(sht2x_i2c, SHT2X_ADDR_DEV << 1, msg, 2, 1000);
}

void SHT2X_Soft_Reset(void) {
	uint8_t command = SHT2X_ADDR_SOFT_RESET;

	HAL_I2C_Master_Transmit(sht2x_i2c, SHT2X_ADDR_DEV << 1, &command, 1, 1000);
}

void SHT2X_Set_Resolution(uint8_t res){
	uint8_t reg_user = SHT2X_Read_User_Reg();
	uint8_t value = (reg_user & 0x7E) | res; //0111 1110 = 0x7E
	uint8_t msg[2] = {SHT2X_ADDR_WRITE_REG, value};

	HAL_I2C_Master_Transmit(sht2x_i2c, SHT2X_ADDR_DEV << 1, msg, 2, 1000);
}

uint16_t Get_Measurment(uint8_t command) {
	uint8_t response_bytes[3] = {0};

	HAL_I2C_Master_Transmit(sht2x_i2c, SHT2X_ADDR_DEV << 1, &command, 1, 1000);
	HAL_I2C_Master_Receive(sht2x_i2c, SHT2X_ADDR_DEV << 1, response_bytes, 3, 1000);

	return (response_bytes[0] << 8) | response_bytes[1];
}

float SHT2X_Get_Relative_Humidity(uint8_t hold) { //Result in percentage
	uint8_t command = {hold ? SHT2X_ADDR_RH_HOLD : SHT2X_ADDR_RH};
	uint16_t rh_val_hex = Get_Measurment(command);

	return -6 + 125.00 * (rh_val_hex / 65536.0);
}
float SHT2X_Get_Temperature(uint8_t hold) { //Result in Celcius
	uint8_t command = {hold ? SHT2X_ADDR_TEMP_HOLD : SHT2X_ADDR_TEMP};
	uint16_t temperature_val_hex = Get_Measurment(command);

	return -6 + 125.00 * (temperature_val_hex / 65536.0);
}
