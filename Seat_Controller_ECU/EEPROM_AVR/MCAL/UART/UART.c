/*
 * UART.c
 *
 *  Created on: Sep 9, 2025
 *      Author: Moata
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "UART.h"

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
