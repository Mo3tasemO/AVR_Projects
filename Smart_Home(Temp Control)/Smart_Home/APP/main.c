/*
 * main.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */
#include "../HAL/KEYPAD.h"
#include "../HAL/LCD.h"
#include "../HAL/LED.h"
#include "../MCAL/DIO.h"
#include "../MCAL/EEPROM.h"
#include "../MCAL/ADC.h"
#include "../HAL/LM35.h"
#include <util/delay.h>

void Get_Temp (void);

void Temp_Fun (void);

void main(void)
{
	u8 KEYPAD_IN, DATA, OLD_PASS, i = 0;
	u16 NEW_PASS[3];

	KEYBAD_INIT(DIO_PORTC);
	LCD_INIT();
	LCD_DIS_STR(" 1_Login/2_New: ");
	while(1)
	{
		KEYPAD_IN = KEYBAD_GET_VAL(DIO_PORTC);
		if(KEYPAD_IN == '1')
		{
			LCD_DIS_CLR();
			LCD_DIS_STR(" Enter Pass:");
			i = 0;
			while(i < 3)
			{
				DATA = KEYBAD_GET_VAL(DIO_PORTC);
				if((DATA >= '0') && (DATA <= '9'))
				{
					LCD_RW_DATA('*');
					NEW_PASS[i] = DATA;
					i++;
				}
			}
			_delay_ms(2000);
			i = 0;
			if((EEPROM_READ(0x70 + i) == NEW_PASS[i]) && (EEPROM_READ(0x70 + i+1) == NEW_PASS[i+1]) && (EEPROM_READ(0x70 + i+2) == NEW_PASS[i+2]))
			{
				LCD_DIS_CLR();
				LCD_DIS_STR(" Correct Pass");
				_delay_ms(5000);
				Get_Temp();
				Temp_Fun();
			}
			else
			{
				LCD_DIS_CLR();
				LCD_DIS_STR(" Wrong Pass");
				_delay_ms(5000);
			}
			LCD_DIS_CLR();
			LCD_DIS_STR(" 1_Login/2_New: ");
		}
		else if(KEYPAD_IN == '2')
		{
			LCD_DIS_CLR();
			LCD_DIS_STR(" Enter Pass:");
			i = 0;

			while(i < 3)
			{
				DATA = KEYBAD_GET_VAL(DIO_PORTC);

				if((DATA >= '0') && (DATA <= '9'))
				{
					LCD_RW_DATA('*');
					EEPROM_WRITE(0x70 + i, DATA);
					i++;
				}
			}
			_delay_ms(2000);
			LCD_DIS_CLR();
			LCD_DIS_STR(" Password Saved");
			_delay_ms(5000);
			LCD_DIS_CLR();
			LCD_DIS_STR(" 1_Login/2_New: ");
		}
	}
}
