/*
 * HAL_INTERRUPT.c
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */
#include "HAL_INTERRUPT.h"





/*
 *
 * */
Std_ReturnType INT0_INIT(const interrupt_pin_config_t *INT0_CFG, interrupt_sense_control_t INT0_SENSE){
	Std_ReturnType ret = E_OK;
	SET_BIT(SREG, I_BIT);	//SET I_BIT -> 1, Global Interrupt
	if(NULL == INT0_CFG){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(INT0_CFG->interrupt_pin));
		switch(INT0_SENSE){
		case LOW_LEVEL_INTERRUPT :
			CLEAR_BIT(MCUCR, ISC00);	//Sense Control To Low Level
			CLEAR_BIT(MCUCR, ISC01);
			break;
		case ON_CHANGE_INTERRUPT :
			SET_BIT(MCUCR, ISC00);	//Sense Control To Low Level
			CLEAR_BIT(MCUCR, ISC01);
			break;
		case FALLING_EDGE_INTERRUPT :
			CLEAR_BIT(MCUCR, ISC00);	//Sense Control To Low Level
			SET_BIT(MCUCR, ISC01);
			break;
		case RISING_EDGE_INTERRUPT :
			SET_BIT(MCUCR, ISC00);	//Sense Control To Low Level
			SET_BIT(MCUCR, ISC01);
			break;
		default :
			ret = E_NOT_OK;
		}
		SET_BIT(GIFR, INTF0);	//You Must Clear The Flag -> Set it to 1
		SET_BIT(GICR, INT0);	//External Interrupt Request Enable
	}
	return ret;
}

/*
 *
 * */
Std_ReturnType INT1_INIT(const interrupt_pin_config_t *INT1_CFG, interrupt_sense_control_t INT1_SENSE){
	Std_ReturnType ret = E_OK;
	if(NULL == INT1_CFG){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(INT1_CFG->interrupt_pin));
		switch(INT1_SENSE){
		case LOW_LEVEL_INTERRUPT :
			CLEAR_BIT(MCUCR, ISC10);	//Sense Control To Low Level
			CLEAR_BIT(MCUCR, ISC11);
			break;
		case ON_CHANGE_INTERRUPT :
			SET_BIT(MCUCR, ISC10);	//Sense Control To Low Level
			CLEAR_BIT(MCUCR, ISC11);
			break;
		case FALLING_EDGE_INTERRUPT :
			CLEAR_BIT(MCUCR, ISC10);	//Sense Control To Low Level
			SET_BIT(MCUCR, ISC11);
			break;
		case RISING_EDGE_INTERRUPT :
			SET_BIT(MCUCR, ISC10);	//Sense Control To Low Level
			SET_BIT(MCUCR, ISC11);
			break;
		default :
			ret = E_NOT_OK;
		}
		SET_BIT(GIFR, INTF1);	//You Must Clear The Flag -> Set it to 1
		SET_BIT(GICR, INT1);	//External Interrupt Request Enable
	}
	return ret;
}

/*
 *
 * */
Std_ReturnType INT2_INIT(const interrupt_pin_config_t *INT2_CFG, interrupt_sense_control_t INT2_SENSE){
	Std_ReturnType ret = E_OK;
	SET_BIT(SREG, I_BIT);	//SET I_BIT -> 1, Global Interrupt
	if(NULL == INT2_CFG){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(INT2_CFG->interrupt_pin));
		switch(INT2_SENSE){
		case FALLING_EDGE_INTERRUPT :
			CLEAR_BIT(MCUCSR, ISC2);	//Sense Control To Low Level
			break;
		case RISING_EDGE_INTERRUPT :
			SET_BIT(MCUCSR, ISC2);	//Sense Control To Low Level
			break;
		default :
			ret = E_NOT_OK;
		}
		SET_BIT(GIFR, INTF2);	//You Must Clear The Flag -> Set it to 1
		SET_BIT(GICR, INT2);	//External Interrupt Request Enable
	}
	return ret;
}
