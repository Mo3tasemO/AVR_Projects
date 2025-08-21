/*
 * LCD.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO.h"

#define LCD_PORT_INIT DIO_PORTD
#define LCD_PORT_RS DIO_PORTB
#define LCD_PORT_RW DIO_PORTB
#define LCD_PORT_E DIO_PORTB

#define LCD_PIN_RS DIO_PIN0
#define LCD_PIN_RW DIO_PIN1
#define LCD_PIN_E DIO_PIN2

#define ROW_0       0
#define ROW_1       1

#define COL_0       0
#define COL_1       1
#define COL_2       2
#define COL_3       3
#define COL_4       4
#define COL_5       5
#define COL_6       6
#define COL_7       7
#define COL_8       8
#define COL_9       9
#define COL_10      10
#define COL_11      11
#define COL_12      12
#define COL_13      13
#define COL_14      14
#define COL_15      15

#define BLOCK_0     0
#define BLOCK_1     1
#define BLOCK_2     2
#define BLOCK_3     3
#define BLOCK_4     4
#define BLOCK_5     5
#define BLOCK_6     6
#define BLOCK_7     7

void LCD_INIT(void);
void LCD_RS_CMD(u8 cmd);
void LCD_RW_DATA(u8 data);
void LCD_DIS_STR(u8 arr[]);
void LCD_DIS_CLR();
void LCD_MoveCursor (u8 row , u8 col) ;

#endif /* HAL_LCD_H_ */
