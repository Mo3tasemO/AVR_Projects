/*
 * SPI.h
 *
 *  Created on: Sep 11, 2025
 *      Author: Moata
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define SPCR  (*(volatile u8*)(0x2D))
#define SPSR  (*(volatile u8*)(0x2E))
#define SPDR  (*(volatile u8*)(0x2F))

#define SPIE  7
#define SPE   6
#define DORD  5
#define MSTR  4
#define CPOL  3
#define CPHA  2
#define SPR1  1
#define SPR0  0

#define SPIF  7
#define WCOL  6
#define SPI2X 0

void SPI_MasterInit (u8 Prescaller) ;
void SPI_SlaveInit1 (void) ;
void SPI_Send  (u8 Data) ;
u8 SPI_Recive (void) ;

#endif /* MCAL_SPI_SPI_H_ */
