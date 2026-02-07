/*
 * ECU_INIT.h
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#ifndef ECU_INIT_H_
#define ECU_INIT_H_

/* Section : Includes */

#include "24C08_EXT_EEPROM/ECU_24C08_EXT_EEPROM.h"
#include "7_SEGMENT/ECU_7_SEGMENT.h"
#include "CERAMIC_HEATER/ECU_CERAMIC_HEATER.h"
#include "COOLER_PELTIER/ECU_COOLER_PELTIER.h"
#include "FAN_CONTROL/ECU_FAN_CONTROL.h"
#include "PUSH_BUTTONS/ECU_PUSH_BUTTONS.h"
#include "RELAY/ECU_RELAY.h"
#include "TEMP_SENSOR/ECU_TEMP_SENSOR.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

void ECU_LAYER_INIT(void);

#endif /* ECU_INIT_H_ */

