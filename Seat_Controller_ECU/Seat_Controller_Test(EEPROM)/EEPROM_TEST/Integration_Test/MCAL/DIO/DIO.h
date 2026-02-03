/*
 * DIO.h
 *
 *  Created on: Sep 16, 2025
 *      Author: Moata
 */

#ifndef INTEGRATION_TEST_MCAL_DIO_DIO_H_
#define INTEGRATION_TEST_MCAL_DIO_DIO_H_



#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"


//PortA
#define DDRA  (*(volatile u8*)(0x3A))
#define PORTA (*(volatile u8*)(0x3B))
#define PINA  (*(volatile u8*)(0x39))

//PortB
#define DDRB  (*(volatile u8*)(0x37))
#define PORTB (*(volatile u8*)(0x38))
#define PINB  (*(volatile u8*)(0x36))

//PortC
#define DDRC  (*(volatile u8*)(0x34))
#define PORTC (*(volatile u8*)(0x35))
#define PINC  (*(volatile u8*)(0x33))

//PortD
#define DDRD  (*(volatile u8*)(0x31))
#define PORTD (*(volatile u8*)(0x32))
#define PIND  (*(volatile u8*)(0x30))


#define DIO_PORTA 1
#define DIO_PORTB 2
#define DIO_PORTC 3
#define DIO_PORTD 4


#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7



#define DIO_INPUT 0
#define DIO_OUTPUT 1


#define DIO_HIGH 1
#define DIO_LOW  0


void DIO_INIT(u8 PORT_NAME, u8 PIN_NUM, u8 Mode);
void DIO_SET_PIN_DIR(u8 PORT_NAME, u8 PIN_NUM, u8 Value);
void DIO_TOG_PIN(u8 PORT_NAME, u8 PIN_NUM);
u8 DIO_READ_PIN(u8 PORT_NAME, u8 PIN_NUM);


#endif /* INTEGRATION_TEST_MCAL_DIO_DIO_H_ */
