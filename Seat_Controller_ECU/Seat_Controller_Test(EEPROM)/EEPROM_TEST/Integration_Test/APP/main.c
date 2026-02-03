/*
 * main.c
 *
 *  Created on: Sep 16, 2025
 *      Author: Moata
 */



#include "../MCAL/DIO/DIO.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/EEPROM/EEPROM.h"
#include "../MCAL/UART/UART.h"
#include <avr/interrupt.h>
#include <util/delay.h>


void main()
{
	UART_Init(9600, 8) ;
	char buffer[20];
	u8 index = 0;

	//	u16 Address = 0x08;
	//	_delay_ms(500) ;

	while (1)
	{
		//		u8 Received_Data = UART_RX();
		//		EEPROM_WRITE(Address, Received_Data);
		//		Address++;
		if(UCSRA & (1 << RXC))
		{
			char c = UART_ReceiveChar();

			if (c == '\r' || c == '\n') {
				buffer[index] = '\0';   // terminate string
				if (index > 0) {
					ProcessCommand(buffer);
					index = 0;          // reset for next command
				}
			} else {
				if (index < sizeof(buffer) - 1) {
					buffer[index++] = c;
				}

			}
		}
	}
}
