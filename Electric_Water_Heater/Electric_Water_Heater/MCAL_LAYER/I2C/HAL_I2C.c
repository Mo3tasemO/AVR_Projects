/*
 * HAL_I2C.c
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#include "HAL_I2C.h"

pin_config_t SCL_PIN ={
		.port = PORTC_INDEX,
		.pin = GPIO_PIN0,
		.direction = GPIO_DIRECTION_INPUT,
		.logic = GPIO_LOW
};
pin_config_t SDA_PIN ={
		.port = PORTC_INDEX,
		.pin = GPIO_PIN1,
		.direction = GPIO_DIRECTION_INPUT,
		.logic = GPIO_LOW
};


Std_ReturnType I2C_INIT(uint32 SCL){
	Std_ReturnType ret = E_OK;
	TWBR = ((16000000/SCL)-16)/(2*PRESCALER);
	switch(PRESCALER){
	case 1:
		TWSR = 0;
		break;
	case 4:
		TWSR = 1;
		break;
	case 16:
		TWSR = 2;
		break;
	case 64:
		TWSR = 3;
		break;
	}
	return ret;
}
Std_ReturnType I2C_START_CON(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWSTA);	//START_CONDITION
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	while(READ_BIT(TWCR, TWINT) == 0);
	while((TWSR & 0xF8) != 0x08); // Address 0x08 is the status address for START_CONDITION transmitted
	return ret;
}
Std_ReturnType I2C_REPEAT_START_CON(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWSTA);	//START_CONDITION
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	while(READ_BIT(TWCR, TWINT) == 0);
	while((TWSR & 0xF8) != 0x10); // Address 0x10 is the status address for REPEAT_START_CONDITION transmitted
	return ret;
}
Std_ReturnType I2C_STOP_CON(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWSTO);	//STOP_CONDITION
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	return ret;
}
Std_ReturnType I2C_SEND_ADDRESS(uint8 Address){
	Std_ReturnType ret = E_OK;
	TWDR = Address;	// Shift left to sent the MSB First
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);
	while(READ_BIT(TWCR, TWINT) == 0);
	if (((TWSR & 0xF8) != 0x18) && ((TWSR & 0xF8) != 0x40))
	{
		return E_NOT_OK;
	}
	return ret;
}
Std_ReturnType I2C_SEND_DATA(uint8 Data){
	Std_ReturnType ret = E_OK;
	TWDR = Data;
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);
	while(READ_BIT(TWCR, TWINT) == 0);
	if ((TWSR & 0xF8) != 0x28){
		return E_NOT_OK; // Address 0x28 is the status address for data transmitted and ack received
	}
	return ret;
}


uint8 I2C_READ_DATA(void){
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWEA);	//Acknowledgment
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	while(READ_BIT(TWCR, TWINT) == 0);
	while((TWSR & 0xF8) != 0x50); // Address 0x60 is the status address for Receive address
	return TWDR;
}

uint8 I2C_READ_ACK(void)
{
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWEA);	//Acknowledgment
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	while(READ_BIT(TWCR, TWINT) == 0);
	/* Check status: 0x50 = Data received, ACK returned */
	if ((TWSR & 0xF8) != 0x50){
		return 0;
	}
	return TWDR;
}
uint8 I2C_READ_NACK(void)
{
	SET_BIT(TWCR, TWEN);	//Enable
	SET_BIT(TWCR, TWINT);	//CLEAR_FLAG
	while(READ_BIT(TWCR, TWINT) == 0);
	/* Check status: 0x58 = Data received, NACK returned */
	if ((TWSR & 0xF8) != 0x58){
		return 0;
	}
	return TWDR;
}
