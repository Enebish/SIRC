/*
 * sony.h
 *
 *  Created on: 01.02.2016
 *      Author: b_ene_000
 */

#ifndef INC_IR_SONY_H_
#define INC_IR_SONY_H_

/* Define to prevent recursive inclusion -------------------------------------*/
#include "main.h"
#include "ir_decode.h"

/** @defgroup Sony SIRC_Exported_Constants
  * @{
  */
#ifdef SONY_SIRC

#define IR_MESSAGE               " SIRC Sony "
#define IR_BITS_COUNT            12

#define IR_HEADER_LOW_MIN_US     (2400 - 150)
#define IR_HEADER_LOW_MAX_US     (2400 + 150)
#define IR_HEADER_WHOLE_MIN_US   (600 - 150)
#define IR_HEADER_WHOLE_MAX_US   (600 + 150)

#define IR_ONTIME_MIN_US         (600 - 50)
#define IR_ONTIME_MAX_US         (600 + 50)

#define IR_VALUE_STEP_US         600
#define IR_VALUE_MARGIN_US       150
#define IR_VALUE_00_US           600

/**
  * @brief  SIRC frame structure
  */
typedef struct
{
  __IO uint16_t Command;   /*!< Command field */
  __IO uint16_t Address;   /*!< Address field */
}IR_Frame_TypeDef;
#endif

uint16_t DecDeviceID;
uint16_t DecCommandID;

uint8_t comL;
uint8_t devL;

void ConvertSony(void);

#endif /* INC_IR_SONY_H_ */
