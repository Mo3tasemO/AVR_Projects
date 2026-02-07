/*
 * Servo.h
 *
 *  Created on: Sep 13, 2025
 *      Author: ahmed
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"






#define SERVO_INCLINE_MIN_US   500.0f   // safe start for SG90
#define SERVO_INCLINE_MAX_US   2500.0f   // safe start for SG90
#define SERVO_INCLINE_MIN_DEG  0.0f
#define SERVO_INCLINE_MAX_DEG  180.0f

#define SERVO_HEIGHT_MIN_US     500.0f   // safe start for SG90
#define SERVO_HEIGHT_MAX_US     2500.0f   // safe start for SG90
#define SERVO_HEIGHT_MIN_DEG    0.0f
#define SERVO_HEIGHT_MAX_DEG    360.0f


#define SERVO_DISTANCE_MIN_US   500.0f   // safe start for SG90
#define SERVO_DISTANCE_MAX_US   2500.0f   // safe start for SG90
#define SERVO_DISTANCE_MIN_DEG  0.0f
#define SERVO_DISTANCE_MAX_DEG  360.0f


#define HEIGHT_MIN_CM   2.0f
#define HEIGHT_MAX_CM   5.3f
#define SLIDE_MIN_CM    3.0f
#define SLIDE_MAX_CM    7.5f





void Servo_SetAngle(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg);
void Servo_SetHeight(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg);
void Servo_SetDistance(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg);
float map_linear(float x, float in_min, float in_max, float out_min, float out_max);
uint16_t clamp_u16(int v, int lo, int hi);








#endif /* INC_SERVO_H_ */
