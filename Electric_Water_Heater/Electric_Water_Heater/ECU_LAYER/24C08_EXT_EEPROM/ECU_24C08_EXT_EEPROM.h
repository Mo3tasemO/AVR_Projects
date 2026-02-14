/*
 * 24C08_EXT_EEPROM.h
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#ifndef ECU_LAYER_24C08_EXT_EEPROM_ECU_24C08_EXT_EEPROM_H_
#define ECU_LAYER_24C08_EXT_EEPROM_ECU_24C08_EXT_EEPROM_H_
/* Section : Includes */
#include "ECU_24C08_EXT_EEPROM_CFG.h"
#include "../../MCAL_LAYER/I2C/HAL_I2C.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"


/* Section: Macro Declarations */
/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

/*I2C EEPROM_INTERFACE*/

Std_ReturnType EXT_EEPROM_INIT(uint32 SCL);
Std_ReturnType EXT_EEPROM_WRITE_BYTE(uint16 Address, uint8 Data[]);
Std_ReturnType EXT_EEPROM_WRITE_PAGE(uint8 Address, uint32 Data);
uint8 EXT_EEPROM_READ_BYTE(uint16 Address, uint8 *Data, uint8 length);

#endif /* ECU_LAYER_24C08_EXT_EEPROM_ECU_24C08_EXT_EEPROM_H_ */

