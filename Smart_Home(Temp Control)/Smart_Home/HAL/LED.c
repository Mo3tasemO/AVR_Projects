/*
 * LED.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#include "LED.h"

void LED_INIT(u8 PORT_NAME, u8 PIN_NUM)
{
	DIO_INIT(PORT_NAME, PIN_NUM, DIO_OUTPUT);
}
void LED_ON(u8 PORT_NAME, u8 PIN_NUM){
	DIO_SET_Pin_Val(PORT_NAME, PIN_NUM, DIO_HIGH);
}
void LED_OFF(u8 PORT_NAME, u8 PIN_NUM){
	DIO_SET_Pin_Val(PORT_NAME, PIN_NUM, DIO_LOW);
}
void LED_TOG(u8 PORT_NAME, u8 PIN_NUM){
	DIO_TOG_Pin(PORT_NAME, PIN_NUM);
}
