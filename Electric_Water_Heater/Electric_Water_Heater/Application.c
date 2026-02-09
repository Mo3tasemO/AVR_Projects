/*
 * Application.c
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#include "Application.h"
void application_init(void);

pin_config_t led1 = {
		.port = PORTC_INDEX,
		.pin = GPIO_PIN7,
		.direction = GPIO_DIRECTION_OUTPUT,
		.logic = GPIO_LOW
};

interrupt_pin_config_t int1_pin = {
		.interrupt_pin.port = PORTD_INDEX,
		.interrupt_pin.pin = GPIO_PIN3,
		.interrupt_pin.direction = GPIO_DIRECTION_INPUT,
		.interrupt_pin.logic = GPIO_LOW,
};

int main(){
//	Std_ReturnType ret = E_OK;

	application_init();




	while(1){

	}













	return 0;
}


void application_init(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(SREG, I_BIT);	//SET I_BIT -> 1, Global Interrupt
	GPIO_PIN_INIT(&led1);
	ECU_LAYER_INIT();
	ret = INT1_INIT(&int1_pin, FALLING_EDGE_INTERRUPT);

}

void __vector_2 (void)__attribute__((signal)) ;	// Vector2(address) -> ISR of interrupt 1 in vector table
void __vector_2 (void)
{
	GPIO_PIN_WRITE_LOGIC(&led1, GPIO_HIGH);
	_delay_ms(2000);
	GPIO_PIN_WRITE_LOGIC(&led1, GPIO_LOW);
}
