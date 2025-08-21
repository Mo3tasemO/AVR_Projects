/*
 * DIO.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO.h"

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
		if(Mode == DIO_INPUT)
		{
			CLR_BIT(DDRB, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRB, PIN_NUM);
		}
		break;
	case DIO_PORTC:
		if(Mode == DIO_INPUT)
		{
			CLR_BIT(DDRC, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRC, PIN_NUM);
		}
		break;
	case DIO_PORTD:
		if(Mode == DIO_INPUT)
		{
			CLR_BIT(DDRD, PIN_NUM);
		}
		else if(Mode == DIO_OUTPUT)
		{
			SET_BIT(DDRD, PIN_NUM);
		}
		break;
	}
}
void DIO_SET_Pin_Val(u8 PORT_NAME, u8 PIN_NUM, u8 value)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		if(value == DIO_HIGH)
		{
			SET_BIT(PORTA, PIN_NUM);
		}
		else if(value == DIO_LOW)
		{
			CLR_BIT(PORTA, PIN_NUM);
		}
		break;
	case DIO_PORTB:
		if(value == DIO_HIGH)
		{
			SET_BIT(PORTB, PIN_NUM);
		}
		else if(value == DIO_LOW)
		{
			CLR_BIT(PORTB, PIN_NUM);
		}
		break;
	case DIO_PORTC:
		if(value == DIO_HIGH)
		{
			SET_BIT(PORTC, PIN_NUM);
		}
		else if(value == DIO_LOW)
		{
			CLR_BIT(PORTC, PIN_NUM);
		}
		break;
	case DIO_PORTD:
		if(value == DIO_HIGH)
		{
			SET_BIT(PORTD, PIN_NUM);
		}
		else if(value == DIO_LOW)
		{
			CLR_BIT(PORTD, PIN_NUM);
		}
		break;
	}
}
void DIO_TOG_Pin(u8 PORT_NAME, u8 PIN_NUM)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		TOG(PORTA, PIN_NUM);

		break;
	case DIO_PORTB:
		TOG(PORTB, PIN_NUM);

		break;
	case DIO_PORTC:
		TOG(PORTC, PIN_NUM);

		break;
	case DIO_PORTD:
		TOG(PORTD, PIN_NUM);

		break;
	}
}
u8 DIO_READ_Pin(u8 PORT_NAME, u8 PIN_NUM)
{
	u8 ret_val ;
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		ret_val = READ_BIT(PINA, PIN_NUM);

		break;
	case DIO_PORTB:
		ret_val = READ_BIT(PINB, PIN_NUM);

		break;
	case DIO_PORTC:
		ret_val = READ_BIT(PINC, PIN_NUM);

		break;
	case DIO_PORTD:
		ret_val = READ_BIT(PIND, PIN_NUM);

		break;
	}
	return ret_val;
}
void DIO_PORT_INIT(u8 PORT_NAME, u8 Mode)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		DDRA = Mode;
		break;
	case DIO_PORTB:
		DDRB = Mode;
		break;
	case DIO_PORTC:
		DDRC = Mode;
		break;
	case DIO_PORTD:
		DDRD = Mode;
		break;
	}
}
void DIO_SET_PORT(u8 PORT_NAME, u8 Value)
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		PORTA = Value;
		break;
	case DIO_PORTB:
		PORTB = Value;
		break;
	case DIO_PORTC:
		PORTC = Value;
		break;
	case DIO_PORTD:
		PORTD = Value;
		break;
	}
}
void DIO_TogPortValue  (u8  PORT_NAME          )
{
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		PORTA = ~PORTA;
		break;
	case DIO_PORTB:
		PORTB = ~PORTB;
		break;
	case DIO_PORTC:
		PORTC = ~PORTC;
		break;
	case DIO_PORTD:
		PORTD = ~PORTD;
		break;
	}
}
u8    DIO_ReadPortValue (u8  PORT_NAME       )
{
	u8 ret_value = 0;
	switch(PORT_NAME)
	{
	case DIO_PORTA:
		ret_value = PINA;
		break;
	case DIO_PORTB:
		ret_value = PINB;
		break;
	case DIO_PORTC:
		ret_value = PINC;
		break;
	case DIO_PORTD:
		ret_value = PIND;
		break;
	}
	return ret_value;
}
