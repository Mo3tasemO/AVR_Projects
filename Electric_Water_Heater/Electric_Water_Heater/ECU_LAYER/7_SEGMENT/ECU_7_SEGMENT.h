/*
 * 7_SEGMENT.h
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#ifndef ECU_LAYER_7_SEGMENT_ECU_7_SEGMENT_H_
#define ECU_LAYER_7_SEGMENT_ECU_7_SEGMENT_H_
/* Section : Includes */
#include "ECU_7_SEGMENT_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

/* Section: Macro Declarations */
/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef enum {
	COMMON_ANODE,
	COMMON_CATHODE
}segment_type_t;

typedef struct {
	pin_config_t segment_pins[4];
	segment_type_t segment_type;
}seven_segment_pins_t;

extern seven_segment_pins_t seg1;
extern uint8 *Data_Seven_Seg;
/* Section: Function Declarations */


Std_ReturnType SEVEN_SEGMENT_INIT(const seven_segment_pins_t *segment);
Std_ReturnType SEVEN_SEGMENT_WRITE_NUMBER(const seven_segment_pins_t *segment, uint8 Number);
Std_ReturnType SEVEN_SEGMENT_2_DIGIT_WRITE(const seven_segment_pins_t *segment, uint8 Number);


#endif /* ECU_LAYER_7_SEGMENT_ECU_7_SEGMENT_H_ */
