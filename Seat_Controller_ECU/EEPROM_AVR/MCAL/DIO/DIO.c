/*
 * DIO.c
 *
 *  Created on: Sep 7, 2025
 *      Author: Moata
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO.h"




void DIO_INIT(u8 PORT_NAME, u8 PIN_NUM, u8 Mode)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		if(Mode == DIO_INPUT)
		{
			CLR_BIT(DDRA, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRA, PIN_NUM);
		}
		break;
	case DIO_PORTB:
		if( Mode == DIO_INPUT)
		{
			CLR_BIT(DDRA, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRA, PIN_NUM);
		}
		break;
	case DIO_PORTC:
		if( Mode == DIO_INPUT)
		{
			CLR_BIT(DDRA, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRA, PIN_NUM);
		}
		break;
	case DIO_PORTD:
		if( Mode == DIO_INPUT)
		{
			CLR_BIT(DDRA, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRA, PIN_NUM);
		}
		break;
	}
}
void DIO_SET_PIN_DIR(u8 PORT_NAME, u8 PIN_NUM, u8 Value)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		if(Value == DIO_LOW)
		{
			CLR_BIT(PORTA, PIN_NUM);
		}
		else if(Value == DIO_HIGH)
		{
			SET_BIT(PORTA, PIN_NUM);
		}
		break;
	case DIO_PORTB:
		if(Value == DIO_LOW)
		{
			CLR_BIT(PORTB, PIN_NUM);
		}
		else if(Value == DIO_HIGH)
		{
			SET_BIT(PORTB, PIN_NUM);
		}
		break;
	case DIO_PORTC:
		if(Value == DIO_LOW)
		{
			CLR_BIT(PORTC, PIN_NUM);
		}
		else if(Value == DIO_HIGH)
		{
			SET_BIT(PORTC, PIN_NUM);
		}
		break;
	case DIO_PORTD:
		if(Value == DIO_LOW)
		{
			CLR_BIT(PORTD, PIN_NUM);
		}
		else if(Value == DIO_HIGH)
		{
			SET_BIT(PORTD, PIN_NUM);
		}
		break;
	}
}
void DIO_TOG_PIN(u8 PORT_NAME, u8 PIN_NUM)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		TOG_BIT(PORTA, PIN_NUM);
		break;
	case DIO_PORTB:
		TOG_BIT(PORTB, PIN_NUM);
		break;
	case DIO_PORTC:
		TOG_BIT(PORTC, PIN_NUM);
		break;
	case DIO_PORTD:
		TOG_BIT(PORTD, PIN_NUM);
		break;
	}
}
u8 DIO_READ_PIN(u8 PORT_NAME, u8 PIN_NUM)
{
	u8 RET_VAL = 0;
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		RET_VAL = READ_BIT(PINA, PIN_NUM);
		break;
	case DIO_PORTB:
		RET_VAL = READ_BIT(PINB, PIN_NUM);
		break;
	case DIO_PORTC:
		RET_VAL = READ_BIT(PINC, PIN_NUM);
		break;
	case DIO_PORTD:
		RET_VAL = READ_BIT(PIND, PIN_NUM);
		break;
	}
	return RET_VAL;
}
