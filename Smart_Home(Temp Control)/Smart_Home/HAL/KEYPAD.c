/*
 * KEYPAD.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/KEYPAD.h"
u8 KEY_ARR[4][4] = {
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'N', '0', '=', '+'}
};

#define KEY_PRESSED 0
#define KEY_NOT_PRESSED 255

void KEYBAD_INIT(u8 PORT_NAME)
{
	DIO_PORT_INIT(PORT_NAME, 0x0f);
	DIO_SET_PORT(PORT_NAME, 0xff);
}
u8 KEYBAD_GET_VAL(u8 PORT_NAME)
{
	u8 rows, col, ret_val = KEY_NOT_PRESSED, state = 0;
	for(rows = 0; rows < 4; rows++)
	{
		DIO_SET_Pin_Val(PORT_NAME, rows, DIO_LOW);
		for(col = 0; col < 4; col++)
		{
			state = DIO_READ_Pin(PORT_NAME, col+4);
			if(state == KEY_PRESSED)
			{
				ret_val = KEY_ARR[rows][col];
				while(DIO_READ_Pin(PORT_NAME, col+4) == KEY_PRESSED);
			}
		}
		DIO_SET_Pin_Val(PORT_NAME, rows, DIO_HIGH);
	}
	return ret_val;
}

