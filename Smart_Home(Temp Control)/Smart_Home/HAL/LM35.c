/*
 * LM35.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Moata
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/ADC.h"
#include "../MCAL/DIO.h"
#include "../HAL/LM35.h"
#include "../HAL/LCD.h"
#include <util/delay.h>


u16 Temp;

void Get_Temp (void)
{
	Temp = ADC_ReadDataUsingInterrupt()*0.25 ;
}
void Temp_Fun (void)
{
	u8 D0 , D1 , D2 ;
		LCD_INIT() ;
		LCD_DIS_STR(" Room Temp:") ;
		ADC_Init(ADC_PRESCALLER_64, INTERNAL_AREF) ;
		ADC_CallBack(Get_Temp) ;
		while (1)
		{
			ADC_StartConvrsion(ADC_CHANNEL1) ;
			D0 = Temp % 10  ;   Temp /=10 ;
			D1 = Temp % 10  ;   Temp /=10 ;
			D2 = Temp % 10  ;   Temp /=10 ;

			LCD_MoveCursor(ROW_0, COL_11) ;
//			LCD_RW_DATA(D2 + '0') ;
			LCD_RW_DATA(D1 + '0') ;
			LCD_RW_DATA(D0 + '0') ;
			_delay_ms(200) ;
		}
}

