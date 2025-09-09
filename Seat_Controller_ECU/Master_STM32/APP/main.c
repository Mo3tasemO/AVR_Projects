/*
 * main.c
 *
 *  Created on: Sep 7, 2025
 *      Author: Moata
 */
#include "../MCAL/DIO/DIO.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include <util/delay.h>
void main()
{
	DIO_INIT(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	while(1)
	{
		DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN0, DIO_HIGH);
		_delay_ms(2000);
		DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN0, DIO_LOW);
		_delay_ms(2000);
	}

}

