/*
 * 7_SEGMENT.c
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */
#include "ECU_7_SEGMENT.h"

pin_config_t segment_enable1 ={
		.port = PORTD_INDEX,
		.pin = GPIO_PIN6,
		.direction = GPIO_DIRECTION_OUTPUT,
		.logic = GPIO_LOW
};
pin_config_t segment_enable2 ={
		.port = PORTD_INDEX,
		.pin = GPIO_PIN7,
		.direction = GPIO_DIRECTION_OUTPUT,
		.logic = GPIO_LOW
};
seven_segment_pins_t seg1 = {
		.segment_pins[0].port = PORTB_INDEX,
		.segment_pins[0].pin = GPIO_PIN4,
		.segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
		.segment_pins[0].logic = GPIO_LOW,
		.segment_pins[1].port = PORTB_INDEX,
		.segment_pins[1].pin = GPIO_PIN5,
		.segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
		.segment_pins[1].logic = GPIO_LOW,
		.segment_pins[2].port = PORTB_INDEX,
		.segment_pins[2].pin = GPIO_PIN6,
		.segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
		.segment_pins[2].logic = GPIO_LOW,
		.segment_pins[3].port = PORTB_INDEX,
		.segment_pins[3].pin = GPIO_PIN7,
		.segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
		.segment_pins[3].logic = GPIO_LOW,
		.segment_type = COMMON_ANODE
};
uint8 *Data_Seven_Seg;
Std_ReturnType SEVEN_SEGMENT_INIT(const seven_segment_pins_t *segment){
	Std_ReturnType ret = E_OK;
	if(NULL == segment){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(segment->segment_pins[0]));
		ret = GPIO_PIN_INIT(&(segment->segment_pins[1]));
		ret = GPIO_PIN_INIT(&(segment->segment_pins[2]));
		ret = GPIO_PIN_INIT(&(segment->segment_pins[3]));
	}
	return ret;
}
Std_ReturnType SEVEN_SEGMENT_WRITE_NUMBER(const seven_segment_pins_t *segment, uint8 Number){
	Std_ReturnType ret = E_OK;
	if((NULL == segment) && (Number > 9)){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_WRITE_LOGIC(&(segment->segment_pins[0]), (Number & 0x01));
		ret = GPIO_PIN_WRITE_LOGIC(&(segment->segment_pins[1]), ((Number >> 1) & 0x01));
		ret = GPIO_PIN_WRITE_LOGIC(&(segment->segment_pins[2]), ((Number >> 2) & 0x01));
		ret = GPIO_PIN_WRITE_LOGIC(&(segment->segment_pins[3]), ((Number >> 3) & 0x01));
	}
	return ret;
}
Std_ReturnType SEVEN_SEGMENT_2_DIGIT_WRITE(const seven_segment_pins_t *segment, uint8 Number){
	Std_ReturnType ret = E_OK;
	if((NULL == segment)){
		ret = E_NOT_OK;
	}
	else{
		ret = SEVEN_SEGMENT_WRITE_NUMBER(segment, (uint8)Number/10);
		ret = GPIO_PIN_WRITE_LOGIC(&segment_enable2, GPIO_HIGH);
		_delay_ms(5);
		ret = GPIO_PIN_WRITE_LOGIC(&segment_enable1, GPIO_LOW);
		ret = SEVEN_SEGMENT_WRITE_NUMBER(segment, Number%10);
		ret = GPIO_PIN_WRITE_LOGIC(&segment_enable1, GPIO_HIGH);
		_delay_ms(5);
		ret = GPIO_PIN_WRITE_LOGIC(&segment_enable2, GPIO_LOW);
	}
	return ret;
}
