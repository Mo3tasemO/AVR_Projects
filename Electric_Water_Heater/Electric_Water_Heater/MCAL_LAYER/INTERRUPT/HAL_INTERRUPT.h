/*
 * HAL_INTERRUPT.h
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#ifndef MCAL_LAYER_INTERRUPT_HAL_INTERRUPT_H_
#define MCAL_LAYER_INTERRUPT_HAL_INTERRUPT_H_

/* Section : Includes */

#include "HAL_INTERRUPT_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "../MCAL_STD_LIB.h"

/* Section: Macro Declarations */


#define I_BIT	7	/* SET I_BIT-> Global Interrupt*/
#define SREG	(*(volatile uint8*)(0x5F))
#define MCUCR	(*(volatile uint8*)(0x55))
#define MCUCSR	(*(volatile uint8*)(0x54))
#define GICR	(*(volatile uint8*)(0x5B))
#define GIFR	(*(volatile uint8*)(0x5A))


#define ISC00	0
#define ISC01	1
#define ISC10	2
#define ISC11	3
#define ISC2	6

/*INTERRUPT_REQUEST_BITS*/
#define INT0	6
#define INT1	7
#define INT2	5

/*FLAG_BITS*/
#define INTF0	6
#define INTF1	7
#define INTF2	5

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */


/*Interrupt Sense Control*/

typedef enum {
	LOW_LEVEL_INTERRUPT = 1,
	ON_CHANGE_INTERRUPT = 2,
	FALLING_EDGE_INTERRUPT = 3,
	RISING_EDGE_INTERRUPT = 4
}interrupt_sense_control_t;


typedef struct {
	pin_config_t interrupt_pin;
}interrupt_pin_config_t;



/* Section: Function Declarations */

Std_ReturnType INT0_INIT(const interrupt_pin_config_t *INT0_CFG, interrupt_sense_control_t INT0_SENSE);
Std_ReturnType INT1_INIT(const interrupt_pin_config_t *INT1_CFG, interrupt_sense_control_t INT1_SENSE);
Std_ReturnType INT2_INIT(const interrupt_pin_config_t *INT2_CFG, interrupt_sense_control_t INT2_SENSE);



#endif /* MCAL_LAYER_INTERRUPT_HAL_INTERRUPT_H_ */
