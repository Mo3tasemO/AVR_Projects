/*
 * LCD.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/LCD.h"

#include <util/delay.h>


void LCD_INIT(void)
{
	_delay_ms(50);
	DIO_PORT_INIT(LCD_PORT_INIT, 0xff);
	DIO_INIT(LCD_PORT_RS, LCD_PIN_RS, DIO_OUTPUT);
	DIO_INIT(LCD_PORT_RW, LCD_PIN_RW, DIO_OUTPUT);
	DIO_INIT(LCD_PORT_E, LCD_PIN_E, DIO_OUTPUT);
	LCD_RS_CMD(0x38);
	_delay_ms(1);
	LCD_RS_CMD(0x0D);
	_delay_ms(1);
	LCD_RS_CMD(0x01);
	_delay_ms(1);
	LCD_RS_CMD(0x06);



}
void LCD_RS_CMD(u8 cmd)
{
	DIO_SET_Pin_Val(LCD_PORT_RW, LCD_PIN_RW, DIO_LOW);
	DIO_SET_Pin_Val(LCD_PORT_RS, LCD_PIN_RS, DIO_LOW);
	DIO_SET_PORT(LCD_PORT_INIT, cmd);
	DIO_SET_Pin_Val(LCD_PORT_E, LCD_PIN_E, DIO_HIGH);
	_delay_ms(1);
	DIO_SET_Pin_Val(LCD_PORT_E, LCD_PIN_E, DIO_LOW);
	_delay_ms(1);
}
void LCD_RW_DATA(u8 data)
{

	DIO_SET_Pin_Val(LCD_PORT_RW, LCD_PIN_RW, DIO_LOW);
	DIO_SET_Pin_Val(LCD_PORT_RS, LCD_PIN_RS, DIO_HIGH);
	DIO_SET_PORT(LCD_PORT_INIT, data);
	DIO_SET_Pin_Val(LCD_PORT_E, LCD_PIN_E, DIO_HIGH);
	_delay_ms(1);
	DIO_SET_Pin_Val(LCD_PORT_E, LCD_PIN_E, DIO_LOW);
	_delay_ms(1);
}
void LCD_DIS_STR(u8 arr[])
{
	u8 i = 0;
	while(arr[i] != '\0')
	{
		LCD_RW_DATA(arr[i]);
		i++;
	}
}
void LCD_DIS_CLR()
{
	LCD_RS_CMD(0x01);
}
void LCD_MoveCursor (u8 row , u8 col)
{
	u8 AC = 0 ;
	if (row == 0)
	{
		AC = col ;
	}
	else if (row == 1)
	{
		AC = col+0x40 ;
	}
	LCD_RS_CMD(AC+0x80) ;
}

