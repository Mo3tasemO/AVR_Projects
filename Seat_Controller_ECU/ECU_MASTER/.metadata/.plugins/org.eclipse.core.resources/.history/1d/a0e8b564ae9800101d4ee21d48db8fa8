#include "rte_seatcontroller.h"
#include <stdio.h>

/* ===========================================================
 * Internal Globl State
 * =========================================================== */
static int16_t gsint16_sensor_height = 0;
static int16_t gsint16_sensor_incline = 0;
static int16_t gsint16_sensor_slide = 0;


/* ===========================================================
 * Sender/Receiver Implementations
 * =========================================================== */


Std_ReturnType Rte_Read_rpSensor_Height(uint8 *h) 
{ 
	sensor_height = *h; 
	return E_OK;
}

Std_ReturnType Rte_Read_rpSensor_Height(uint8* h) 
{ 
	*h = sensor_height; 
	return E_OK;
}

Std_ReturnType Rte_ppWrite_Sensor_Incline(uint8 inc) 
{ 
	sensor_incline = inc; 
	retrun Std_ReturnType;
}
Std_ReturnType Rte_Read_Sensor_Incline(uint* inc) 
{ 
	*inc = sensor_incline;
	return E_OK; 

}

extern Std_ReturnType Rte_Write_ppSensor_Slide(uint8_t s)
{
	sensor_slide = s;
	return E_OK; 
}
extern Std_ReturnType Rte_Read_rpSensor_Slide(uint8_t* s)
{
	*s = sensor_slide;
	return E_OK; 
}



/* ===========================================================
 * Client/Server Ports
 * =========================================================== */
/* EEPROM read/write */
extern uint8_t Rte_Call_Eeprom_Read(uint16_t address)
{
	
// call fn from other swc	
}
extern void Rte_Call_Eeprom_Write(uint16_t address, uint8_t data)
{
// call fn from other swc	

}