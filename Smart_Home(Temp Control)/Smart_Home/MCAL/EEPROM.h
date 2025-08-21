/*
 * EEPROM.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#ifndef MCAL_EEPROM_H_
#define MCAL_EEPROM_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO.h"

#define EEAR (*(volatile u16*)(0x3E))
#define EEDR (*(volatile u8*)(0x3D))
#define EECR (*(volatile u8*)(0x3C))

#define EERIE 3
#define EEMWE 2
#define EEWE 1
#define EERE 0

void EEPROM_WRITE(u16 Address, u16 Data);
u8 EEPROM_READ(u16 Address);


#endif /* MCAL_EEPROM_H_ */
