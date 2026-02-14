/*
 * 24C08_EXT_EEPROM.c
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#include "ECU_24C08_EXT_EEPROM.h"

Std_ReturnType EXT_EEPROM_INIT(uint32 SCL){
	Std_ReturnType ret = E_OK;
	ret = I2C_INIT(SCL);
	return ret;
}
Std_ReturnType EXT_EEPROM_WRITE_BYTE(uint16 Address, uint8 Data[]){
	Std_ReturnType ret = E_OK;
	uint8 Control_Byte = 0xA0, i = 0;
	if((Address >= 0x00) && (Address <= 0x0FF)){
		Control_Byte = 0xA0;// 0xA0 means that the device code is 1010(0)for enable (00)for A9&A8 (0)for Write (10100000)
	}
	else if((Address >= 0x100) && (Address <= 0x1FF)){
		Control_Byte = 0xA2;// 0xA2 means that the device code is 1010(0)for enable (01)for A9&A8 (0)for Write (10100010)
	}
	else if((Address >= 0x200) && (Address <= 0x2FF)){
		Control_Byte = 0xA4;// 0xA4 means that the device code is 1010(0)for enable (10)for A9&A8 (0)for Write (10100100)
	}
	else if((Address >= 0x300) && (Address <= 0x3FF)){
		Control_Byte = 0xA6;// 0xA6 means that the device code is 1010(0)for enable (11)for A9&A8 (0)for Write (10100110)
	}
	else{
		ret = E_NOT_OK;
	}
	ret = I2C_START_CON();
	ret = I2C_SEND_ADDRESS(Control_Byte);
	ret = I2C_SEND_ADDRESS((uint8)Address);
	while(Data[i] != '\0'){
		ret = I2C_SEND_DATA(Data[i]);
		i++;
	}
	ret = I2C_STOP_CON();
	_delay_ms(100);
	return ret;
}
Std_ReturnType EXT_EEPROM_WRITE_PAGE(uint8 Address, uint32 Data){
	Std_ReturnType ret = E_OK;


	return ret;
}
Std_ReturnType EXT_EEPROM_READ_BYTE(uint16 Address, uint8 *Data, uint8 length){
	Std_ReturnType ret = E_OK;
	uint8 Control_Byte = 0xA0, i = 0;
	if((Address >= 0x00) && (Address <= 0x0FF)){
		Control_Byte = 0xA0;// 0xA0 means that the device code is 1010(0)for enable (00)for A9&A8 (0)for Write (10100000)
	}
	else if((Address >= 0x100) && (Address <= 0x1FF)){
		Control_Byte = 0xA2;// 0xA2 means that the device code is 1010(0)for enable (01)for A9&A8 (0)for Write (10100010)
	}
	else if((Address >= 0x200) && (Address <= 0x2FF)){
		Control_Byte = 0xA4;// 0xA4 means that the device code is 1010(0)for enable (10)for A9&A8 (0)for Write (10100100)
	}
	else if((Address >= 0x300) && (Address <= 0x3FF)){
		Control_Byte = 0xA6;// 0xA6 means that the device code is 1010(0)for enable (11)for A9&A8 (0)for Write (10100110)
	}
	else{
		ret = E_NOT_OK;
	}
	ret = I2C_START_CON();
	ret = I2C_SEND_ADDRESS(Control_Byte);
	ret = I2C_SEND_DATA((uint8)Address);
	ret = I2C_REPEAT_START_CON();
	ret = I2C_SEND_ADDRESS(Control_Byte | 0x01);
	for(i = 0; i < length; i++){
		if(i == length - 1){
			Data[i] = I2C_READ_NACK();
		}
		else{
			Data[i] = I2C_READ_ACK();
		}
	}
	ret = I2C_STOP_CON();
	return ret;
}
