/*
 * HAL_I2C.h
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#ifndef MCAL_LAYER_I2C_HAL_I2C_H_
#define MCAL_LAYER_I2C_HAL_I2C_H_

/* Section : Includes */

#include "HAL_I2C_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/HAL_INTERRUPT.h"
/* Section: Macro Declarations */

#define PRESCALER	1
/* I2C Registers*/
#define	TWCR	(*(volatile uint8*)(0x56))
#define	TWDR	(*(volatile uint8*)(0x23))
#define	TWAR	(*(volatile uint8*)(0x22))
#define	TWSR	(*(volatile uint8*)(0x21))
#define	TWBR	(*(volatile uint8*)(0x20))


/*Register_Bits*/
typedef enum {
	TWBR0,
	TWBR1,
	TWBR2,
	TWBR3,
	TWBR4,
	TWBR5,
	TWBR6,
	TWBR7
}TWBR_BITS;
typedef enum {
	TWIE,
	TWEN = 2,
	TWWC,
	TWSTO,
	TWSTA,
	TWEA,
	TWINT
}TWCR_BITS;
typedef enum {
	TWPS0,
	TWPS1,
	TWS3 = 3,
	TWS4,
	TWS5,
	TWS6,
	TWS7
}TWSR_BITS;
typedef enum {
	TWGCE,
	TWA0,
	TWA1,
	TWA2,
	TWA3,
	TWA4,
	TWA5
}TWAR_BITS;



/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

extern pin_config_t SCL_PIN;
extern pin_config_t SDA_PIN;


/* Section: Function Declarations */
Std_ReturnType I2C_INIT(uint32 SCL);
Std_ReturnType I2C_START_CON(void);
Std_ReturnType I2C_REPEAT_START_CON(void);
Std_ReturnType I2C_STOP_CON(void);
Std_ReturnType I2C_SEND_ADDRESS(uint8 Address);
Std_ReturnType I2C_SEND_DATA(uint8 Data);
uint8 I2C_READ_DATA(void);
uint8 I2C_READ_ACK(void);
uint8 I2C_READ_NACK(void);
#endif /* MCAL_LAYER_I2C_HAL_I2C_H_ */
