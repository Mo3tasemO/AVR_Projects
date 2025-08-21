/*
 * LED.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO.h"


void LED_INIT(u8 PORT_NAME, u8 PIN_NUM);
void LED_ON(u8 PORT_NAME, u8 PIN_NUM);
void LED_OFF(u8 PORT_NAME, u8 PIN_NUM);
void LED_TOG(u8 PORT_NAME, u8 PIN_NUM);

#endif /* HAL_LED_H_ */
