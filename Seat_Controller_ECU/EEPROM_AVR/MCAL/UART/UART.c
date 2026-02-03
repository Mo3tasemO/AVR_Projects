/*
 * UART.c
 *
 *  Created on: Sep 9, 2025
 *      Author: Moata
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "UART.h"
#include "../DIO/DIO.h"
#include "../EEPROM/EEPROM.h"
#include <util/delay.h>

void UART_Init (u32 BuadRate , u32 DataSize)
{
	u16 UBRR = (8000000/(16*BuadRate))-1 ;
	UBRRL = (u8)UBRR ;
	UBRRH = (u8)(UBRR>>8) ;

	SET_BIT(UCSRB , TXEN) ;
	SET_BIT(UCSRB , RXEN) ;

	switch (DataSize)
	{
	case 5 :
		SET_BIT(UCSRC , URSEL) ;
		CLR_BIT(UCSRB , UCSZ2) ;
		CLR_BIT(UCSRC , UCSZ1) ;
		CLR_BIT(UCSRC , UCSZ0) ;
		break ;
	case 6 :
		SET_BIT(UCSRC , URSEL) ;
		CLR_BIT(UCSRB , UCSZ2) ;
		CLR_BIT(UCSRC , UCSZ1) ;
		SET_BIT(UCSRC , UCSZ0) ;
		break ;
	case 7 :
		SET_BIT(UCSRC , URSEL) ;
		CLR_BIT(UCSRB , UCSZ2) ;
		SET_BIT(UCSRC , UCSZ1) ;
		CLR_BIT(UCSRC , UCSZ0) ;
		break ;
	case 8 :
		SET_BIT(UCSRC , URSEL) ;
		CLR_BIT(UCSRB , UCSZ2) ;
		SET_BIT(UCSRC , UCSZ1) ;
		SET_BIT(UCSRC , UCSZ0) ;
		break ;
	case 9 :
		SET_BIT(UCSRC , URSEL) ;
		SET_BIT(UCSRB , UCSZ2) ;
		SET_BIT(UCSRC , UCSZ1) ;
		SET_BIT(UCSRC , UCSZ0) ;
		break ;
	}
}
void UART_Tx   (u8 Data)
{
	while (READ_BIT(UCSRA , UDRE) == 0) ;
	UDR = Data ;
}
void UART_TxStr (u8 str [])
{
	u8 i = 0 ;
	while (str [i] != '\0')
	{
		UART_Tx (str [i]) ;
		i ++ ;
	}
	UART_Tx ('\0') ;
}
u8 UART_RX   (void)
{
	while (READ_BIT(UCSRA , RXC) == 0) ;
	return UDR ;
}

void UART_SendByte(u8 data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

void UART_SendFrame(u8 cmd_id, u32 param1, u8 param2) {
	// Response Frame = Header | Length | Cmd_ID | Param1 | Param2 | Tail
	UART_SendByte(CMD_HEADER);
	UART_SendByte(6); UART_SendByte(0); UART_SendByte(0); UART_SendByte(0); // length = 6 bytes
	UART_SendByte(cmd_id);
	UART_SendByte((u8)(param1 & 0xFF));
	UART_SendByte(param2);
	UART_SendByte(RES_TAIL);
}

char UART_ReceiveChar(void) {
	while (!(UCSRA & (1 << RXC))); // wait until data received
	return UDR;
}
void ProcessCommand(char *cmd) {
	u16 addr;
	char out[32];

	if (cmd[0] == 'W') {
		// Format: W-0x10-123
		unsigned int a;
		unsigned int v;
		if (sscanf(cmd, "W-%x-%u", &a, &v) == 2) {   // parse hex address + decimal value
			addr = (u16)a;

			// convert number to string before storing
			char strVal[10];
			sprintf(strVal, "%u", v);

			// write each character to EEPROM
			for (u8 i = 0; strVal[i] != '\0'; i++) {
				EEPROM_WRITE(addr + i, strVal[i]);
			}
			EEPROM_WRITE(addr + strlen(strVal), '\0');  // null terminator
			DIO_SET_PIN_DIR(DIO_PORTD,DIO_PIN2, DIO_HIGH);
			_delay_ms(200);
			DIO_SET_PIN_DIR(DIO_PORTD,DIO_PIN2, DIO_LOW);

			sprintf(out, "WRITE[0x%X]=\"%s\" OK\r\n", addr, strVal);

			UART_TxStr(out);
		} else {
			UART_TxStr("INVALID WRITE\r\n");
		}

	}
	else if (cmd[0] == 'R') {
		// Format: R-0x10
		unsigned int a;
		if (sscanf(cmd, "R-%x", &a) == 1) {
			addr = (u16)a;

			// read back string
			char strVal[10];
			u8 i = 0;
			char c;
			do {
				c = EEPROM_READ(addr + i);
				strVal[i] = c;
			} while (c != '\0' && ++i < sizeof(strVal)-1);
			strVal[i] = '\0';

			sprintf(out, "READ[0x%X]=\"%s\"\r\n", addr, strVal);
			UART_TxStr(out);
		} else {
			UART_TxStr("INVALID READ\r\n");
		}
	}
	else {
		UART_TxStr("UNKNOWN CMD\r\n");
	}
}
