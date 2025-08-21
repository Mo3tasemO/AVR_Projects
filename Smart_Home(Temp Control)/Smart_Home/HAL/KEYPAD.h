/*
 * KEYPAD.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO.h"

#define KEY_PRESSED 0
#define NOT_KEY_PRESSED 255


void KEYBAD_INIT(u8 PORT_NAME);
u8 KEYBAD_GET_VAL(u8 PORT_NAME);

#endif /* HAL_KEYPAD_H_ */
