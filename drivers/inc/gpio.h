/*
 * gpio.h
 *
 *  Created on: 11.11.2015
 *      Author: b_ene_000
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

__IO uint8_t ubKeyPressed;

void EXTILine2_Config(void);
void EXTILine5_Config(void);
void GPIO_Init2 (void);

#endif /* INC_GPIO_H_ */
