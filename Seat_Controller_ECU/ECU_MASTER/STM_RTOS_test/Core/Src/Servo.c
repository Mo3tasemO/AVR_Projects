#include "Servo.h"

#include "main.h"




// 50 Hz frame with 1 MHz tick: CCR = pulse (µs)
void Servo_SetAngle(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg)
{
  if (angle_deg < SERVO_INCLINE_MIN_DEG) angle_deg = SERVO_INCLINE_MIN_DEG;
  if (angle_deg > SERVO_INCLINE_MAX_DEG) angle_deg = SERVO_INCLINE_MAX_DEG;

  float span_deg = (SERVO_INCLINE_MAX_DEG - SERVO_INCLINE_MIN_DEG);
  float span_us  = (SERVO_INCLINE_MAX_US - SERVO_INCLINE_MIN_US);
  float pulse_us = SERVO_INCLINE_MIN_US + (angle_deg - SERVO_INCLINE_MIN_DEG) * (span_us / span_deg);

  uint16_t ccr = clamp_u16((int)(pulse_us + 0.5f), 0, 19999); // 20ms frame
  __HAL_TIM_SET_COMPARE(htim, channel, ccr);
}

void Servo_SetHeight(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg)
{
	if (angle_deg < SERVO_HEIGHT_MIN_DEG) angle_deg = SERVO_HEIGHT_MIN_DEG;
	if (angle_deg > SERVO_HEIGHT_MAX_DEG) angle_deg = SERVO_HEIGHT_MAX_DEG;

	  float span_deg = (SERVO_HEIGHT_MAX_DEG - SERVO_HEIGHT_MIN_DEG);
	  float span_us  = (SERVO_HEIGHT_MAX_US - SERVO_HEIGHT_MIN_US);
	  float pulse_us = SERVO_HEIGHT_MIN_US + (angle_deg - SERVO_HEIGHT_MIN_DEG) * (span_us / span_deg);

	  uint16_t ccr = clamp_u16((int)(pulse_us + 0.5f), 0, 19999); // 20ms frame
	  __HAL_TIM_SET_COMPARE(htim, channel, ccr);
}
void Servo_SetDistance(TIM_HandleTypeDef *htim, uint32_t channel, float angle_deg)
{
	if (angle_deg < SERVO_DISTANCE_MIN_DEG) angle_deg = SERVO_DISTANCE_MIN_DEG;
		if (angle_deg > SERVO_DISTANCE_MAX_DEG) angle_deg = SERVO_DISTANCE_MAX_DEG;

		  float span_deg = (SERVO_DISTANCE_MAX_DEG - SERVO_DISTANCE_MIN_DEG);
		  float span_us  = (SERVO_DISTANCE_MAX_US - SERVO_DISTANCE_MIN_US);
		  float pulse_us = SERVO_DISTANCE_MIN_US + (angle_deg - SERVO_DISTANCE_MIN_DEG) * (span_us / span_deg);

		  uint16_t ccr = clamp_u16((int)(pulse_us + 0.5f), 0, 19999); // 20ms frame
		  __HAL_TIM_SET_COMPARE(htim, channel, ccr);
}




float Height_AngleDeg_To_Cm(float angle_deg)
{
  /* clamp to your angle limits then map to cm range */
  if (angle_deg < SERVO_HEIGHT_MIN_DEG) angle_deg = SERVO_HEIGHT_MIN_DEG;
  if (angle_deg > SERVO_HEIGHT_MAX_DEG) angle_deg = SERVO_HEIGHT_MAX_DEG;
  return map_linear(angle_deg, SERVO_HEIGHT_MIN_DEG, SERVO_HEIGHT_MAX_DEG,
                    HEIGHT_MIN_CM, HEIGHT_MAX_CM);
}

float Slide_AngleDeg_To_Cm(float angle_deg)
{
  if (angle_deg < SERVO_DISTANCE_MIN_DEG) angle_deg = SERVO_DISTANCE_MIN_DEG;
  if (angle_deg > SERVO_DISTANCE_MAX_DEG) angle_deg = SERVO_DISTANCE_MAX_DEG;
  return map_linear(angle_deg, SERVO_DISTANCE_MIN_DEG, SERVO_DISTANCE_MAX_DEG,
                    SLIDE_MIN_CM, SLIDE_MAX_CM);
}




uint16_t clamp_u16(int v, int lo, int hi) {
  if (v < lo) return (uint16_t)lo;
  if (v > hi) return (uint16_t)hi;
  return (uint16_t)v;
}

float map_linear(float x, float in_min, float in_max,
                               float out_min, float out_max)
{
  if (x < in_min) x = in_min;
  if (x > in_max) x = in_max;
  const float span_in  = (in_max  - in_min);
  const float span_out = (out_max - out_min);
  return (span_in > 0.0f) ? (out_min + (x - in_min) * (span_out / span_in)) : out_min;
}


float Height_Cm_To_AngleDeg(float cm)
{
  if (cm < HEIGHT_MIN_CM) cm = HEIGHT_MIN_CM;
  if (cm > HEIGHT_MAX_CM) cm = HEIGHT_MAX_CM;
  return map_linear(cm, HEIGHT_MIN_CM, HEIGHT_MAX_CM,
                    SERVO_HEIGHT_MIN_DEG, SERVO_HEIGHT_MAX_DEG);
}

static inline float Slide_Cm_To_AngleDeg(float cm)
{
  if (cm < SLIDE_MIN_CM) cm = SLIDE_MIN_CM;
  if (cm > SLIDE_MAX_CM) cm = SLIDE_MAX_CM;
  return map_linear(cm, SLIDE_MIN_CM, SLIDE_MAX_CM,
                    SERVO_DISTANCE_MIN_DEG, SERVO_DISTANCE_MAX_DEG);
}



















