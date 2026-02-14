/*
 * Application.c
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#include "Application.h"
void application_init(void);



int main(){
	Std_ReturnType ret = E_OK;

	application_init();
	for(int i = 0; i < 2; i++){
		ret = EXT_EEPROM_READ_BYTE(0x10 + i, &Data_Seven_Seg[i], 2);
		Data_Seven_Seg[i] -= '0';
		_delay_ms(100);
	}

	while(1){

		ret = SEVEN_SEGMENT_2_DIGIT_WRITE(&seg1, Data_Seven_Seg);


	}



	return 0;
}


void application_init(void){
	Std_ReturnType ret = E_OK;
//	SET_BIT(SREG, I_BIT);	//SET I_BIT -> 1, Global Interrupt
	ECU_LAYER_INIT();


	ret = SEVEN_SEGMENT_INIT(&seg1);
	ret = EXT_EEPROM_INIT(100000);
	ret = EXT_EEPROM_WRITE_BYTE(0x10, "35");
	_delay_ms(100);

}

//void __vector_2 (void)__attribute__((signal)) ;	// Vector2(address) -> ISR of interrupt 1 in vector table
//void __vector_2 (void)
//{
//	GPIO_PIN_WRITE_LOGIC(&led1, GPIO_HIGH);
//	_delay_ms(2000);
//	GPIO_PIN_WRITE_LOGIC(&led1, GPIO_LOW);
//}
