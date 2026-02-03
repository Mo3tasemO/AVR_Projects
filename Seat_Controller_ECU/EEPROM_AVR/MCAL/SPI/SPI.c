/*
 * SPI.c
 *
 *  Created on: Sep 11, 2025
 *      Author: Moata
 */


#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO.h"
#include "SPI.h"



void SPI_MasterInit (u8 Prescaller)
{
	DIO_INIT(DIO_PORTB, DIO_PIN7, DIO_OUTPUT) ; //clk
	DIO_INIT(DIO_PORTB, DIO_PIN5, DIO_OUTPUT) ; //MOSI
	DIO_INIT(DIO_PORTB, DIO_PIN4, DIO_OUTPUT) ; //SS
	SET_BIT(SPCR , MSTR) ;
	switch (Prescaller)
	{
	case 4 :
		CLR_BIT(SPSR , SPI2X) ;
		CLR_BIT(SPCR , SPR1) ;
		CLR_BIT(SPCR , SPR0) ;
		break ;
	case 16 :
		CLR_BIT(SPSR , SPI2X) ;
		CLR_BIT(SPCR , SPR1) ;
		SET_BIT(SPCR , SPR0) ;
		break ;
	case 64 :
		CLR_BIT(SPSR , SPI2X) ;
		SET_BIT(SPCR , SPR1) ;
		CLR_BIT(SPCR , SPR0) ;
		break ;
	case 128 :
		CLR_BIT(SPSR , SPI2X) ;
		SET_BIT(SPCR , SPR1) ;
		SET_BIT(SPCR , SPR0) ;
		break ;
	case 2 :
		SET_BIT(SPSR , SPI2X) ;
		CLR_BIT(SPCR , SPR1) ;
		CLR_BIT(SPCR , SPR0) ;
		break ;
	case 8 :
		SET_BIT(SPSR , SPI2X) ;
		CLR_BIT(SPCR , SPR1) ;
		SET_BIT(SPCR , SPR0) ;
		break ;
	case 32 :
		SET_BIT(SPSR , SPI2X) ;
		SET_BIT(SPCR , SPR1) ;
		CLR_BIT(SPCR , SPR0) ;
		break ;
	}
	SET_BIT(SPCR , SPE) ;
}
void SPI_SlaveInit1 (void)
{
	DIO_INIT(DIO_PORTB, DIO_PIN6, DIO_OUTPUT) ; //MISO
	SET_BIT(SPCR , SPE) ;
}
void SPI_Send  (u8 Data)
{
	DIO_SET_PIN_DIR(DIO_PORTB, DIO_PIN4, DIO_LOW) ;
	SPDR = Data ;
	while (READ_BIT(SPSR , SPIF) == 0) ;
}
u8 SPI_Recive (void)
{
	while (READ_BIT(SPSR , SPIF) == 0) ;
	return SPDR ;
}

