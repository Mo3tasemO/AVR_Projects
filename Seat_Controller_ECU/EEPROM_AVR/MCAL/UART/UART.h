/*
 * UART.h
 *
 *  Created on: Sep 9, 2025
 *      Author: Moata
 */

#ifndef MCAL_UART_H_
#define MCAL_UART_H_


#define UDR     (*(volatile u8*)(0x2C))
#define UCSRA   (*(volatile u8*)(0x2B))
#define UCSRB   (*(volatile u8*)(0x2A))
#define UCSRC   (*(volatile u8*)(0x40))
#define UBRRH   (*(volatile u8*)(0x40))
#define UBRRL   (*(volatile u8*)(0x29))

#define RXC  7
#define TXC  6
#define UDRE 5
#define FE   4
#define DOR  3
#define PE   2
#define U2X  1
#define MPCM 0

#define RXCIE  7
#define TXCIE  6
#define UDRIE  5
#define RXEN   4
#define TXEN   3
#define UCSZ2  2
#define RXB8   1
#define TXB8   0

#define URSEL  7
#define UMSEL  6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

void UART_Init (u32 BuadRate , u32 DataSize) ;
void UART_Tx   (u8 Data) ;
void UART_TxStr (u8 str []) ;
u8 UART_RX   (void) ;


#endif /* MCAL_UART_H_ */
