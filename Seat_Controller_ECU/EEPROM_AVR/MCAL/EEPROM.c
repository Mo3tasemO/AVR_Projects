/*
 * EEPROM.c
 *
 *  Created on: Sep 9, 2025
 *      Author: Moata
 */

#include "EEPROM.h"

void EEPROM_WRITE(u16 Address, u16 Data)
{
	EEAR = Address;
	EEDR = Data;
	SET_BIT(EECR, EEMWE);
	SET_BIT(EECR, EEWE);


	while (READ_BIT(EECR , EEWE) == 1) ;
}
u8 EEPROM_READ(u16 Address)
{
	EEAR = Address;
	SET_BIT(EECR, EERE);
	return EEDR;
}
