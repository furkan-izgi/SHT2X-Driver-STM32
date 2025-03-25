/*
 * sht2x.h
 *
 *  Created on: Mar 25, 2025
 *      Author: Celestial
 */

#ifndef INC_SHT2X_H_
#define INC_SHT2X_H_

#include "stm32f4xx_hal.h"
extern I2C_HandleTypeDef *sht2x_i2c;

/* REGISTERS (p. 8) */
#define SHT2X_ADDR_DEV 				0x40

#define SHT2X_ADDR_TEMP_HOLD 		0xE3
#define SHT2X_ADDR_RH_HOLD 			0xE5
#define SHT2X_ADDR_TEMP 			0xF3
#define SHT2X_ADDR_RH 				0xF5

#define SHT2X_ADDR_WRITE_REG 		0xE6
#define SHT2X_ADDR_READ_REG 		0xE7
#define SHT2X_ADDR_SOFT_RESET 		0xFE

#define SHT2X_HOLD 					1

/* USER REGISTER SECTION (p. 9) */
#define SHT2X_EoB_ABOVE				0 /* VDD > 2.25V */
#define SHT2X_EoB_BELOW				1 /* VDD < 2.25V */
#define SHT2X_OTP_RELOAD_DISABLE	1
#define SHT2X_OTP_RELOAD_ENABLE		0

/* RESOLUTION RH - TEMPERATURE (p. 9) */
#define	SHT2X_RES_12_14				0x00
#define	SHT2X_RES_08_12				0x01
#define	SHT2X_RES_10_13				0x80
#define	SHT2X_RES_11_11				0x81

/* FUNCTIONS */

void SHT2X_Init(I2C_HandleTypeDef *hi2c);

uint8_t SHT2X_Read_User_Reg(void);
void SHT2X_Write_User_Reg(uint8_t data);

void SHT2X_Soft_Reset(void);
void SHT2X_Set_Resolution(uint8_t res);

uint16_t Get_Measurment(uint8_t command);

float SHT2X_Get_Relative_Humidity(uint8_t hold); //Result in percentage
float SHT2X_Get_Temperature(uint8_t hold); //Result in Celcius






#endif /* INC_SHT2X_H_ */
