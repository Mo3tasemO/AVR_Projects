/*
 * TASKS.h
 *
 *  Created on: Sep 15, 2025
 *      Author: ahmed
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_



void StartDefaultTask(void *argument);
void StartI2CTask(void *argument);
void StartADC_ReadTask(void *argument);
void StartSpiReadTask(void *argument);
void StartManual_ModeTask(void *argument);
void StartAuto_ModeTask(void *argument);
void StartSwitchModeTask(void *argument);
void StartSendAlifeMessageTask(void *argument);



#endif /* INC_TASKS_H_ */
