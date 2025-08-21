/*
 * BIT_MATH.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Moata
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_


#define SET_BIT(reg,bit)   ((reg)|=(1<<(bit)))
#define TOG(reg,bit)   ((reg)^=(1<<(bit)))
#define CLR_BIT(reg,bit)   ((reg)&=(~(1<<(bit))))
#define READ_BIT(reg,bit)  (((reg)&(1<<(bit)))>>(bit))


#endif /* LIB_BIT_MATH_H_ */
