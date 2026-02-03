/*
 * EEPROM.h
 *
 *  Created on: Sep 16, 2025
 *      Author: Moata
 */

#ifndef INTEGRATION_TEST_MCAL_EEPROM_EEPROM_H_
#define INTEGRATION_TEST_MCAL_EEPROM_EEPROM_H_


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#define EEAR (*(volatile u16*)(0x3E))
#define EEDR (*(volatile u8*)(0x3D))
#define EECR (*(volatile u8*)(0x3C))

#define EERIE 3
#define EEMWE 2
#define EEWE 1
#define EERE 0

void EEPROM_WRITE(u16 Address, u16 Data);
u8 EEPROM_READ(u16 Address);


#endif /* INTEGRATION_TEST_MCAL_EEPROM_EEPROM_H_ */
