#ifndef RTE_SEATCONTROLLER_H
#define RTE_SEATCONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

/* ===========================================================
 * Data Types
 * =========================================================== */

/* ===========================================================
 * Sender/Receiver Ports
 * =========================================================== */

typedef int Std_ReturnType;

/* Sensor values */
extern Std_ReturnTyp Rte_Write_ppSensor_Height(uint8_t h);
extern Std_ReturnType Rte_Read_rpSensor_Height(uint8_t* h);

extern Std_ReturnType Rte_Write_ppSensor_Incline(uint8_t inc);
extern Std_ReturnType Rte_Read_rpSensor_Incline(uint8_t* inc);

extern Std_ReturnType Rte_Read_ppSensor_Slide(uint8_t s);
extern Std_ReturnType Rte_Read_rpSensor_Slide(uint8_t* s);


/* ===========================================================
 * Client/Server Ports
 * =========================================================== */
/* EEPROM read/write */
extern uint8_t Rte_Call_Eeprom_Read(uint16_t address);
extern void Rte_Call_Eeprom_Write(uint16_t address, uint8_t data);


#endif /* RTE_SEATCONTROLLER_H */
