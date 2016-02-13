/*
 * samsung.h
 *
 *  Created on: 31.01.2016
 *      Author: b_ene_000
 */

#ifndef INC_IR_SAMSUNG_H_
#define INC_IR_SAMSUNG_H_

/* Define to prevent recursive inclusion -------------------------------------*/
#include "main.h"
#include "ir_decode.h"

/** @defgroup Samsung SIRC_Exported_Constants
  * @{
  */
#ifdef SAMSUNG_SIRC

#define IR_MESSAGE               " SIRC Samsung "
#define IR_BITS_COUNT            32

#define IR_HEADER_LOW_MIN_US     (4550 - 100)
#define IR_HEADER_LOW_MAX_US     (4550 + 100)
#define IR_HEADER_WHOLE_MIN_US   (4450 - 100)
#define IR_HEADER_WHOLE_MAX_US   (4450 + 100)

#define IR_ONTIME_MIN_US         (630 - 50)
#define IR_ONTIME_MAX_US         (630 + 50)

#define IR_VALUE_STEP_US         1115
#define IR_VALUE_MARGIN_US       100
#define IR_VALUE_00_US           485

/**
  * @brief  SIRC frame structure
  */
typedef struct IR_Frame_TypeDef
{
  __IO uint16_t Command;   /*!< Command field */
  __IO uint16_t Address;   /*!< Address field */
};

uint16_t DecDeviceID;
uint16_t DecCommandID;

uint8_t comL;
uint8_t comH;
uint8_t devL;
uint8_t devH;

char hex[10];
char Buffer[10];
char Buffer2[20];
char DeviceID[17];
char CommandID[17];

char DeviceIDL[9];
char DeviceIDH[9];
char CommandIDL[9];
char CommandIDH[9];
uint16_t Cnt;

void ConvertSamsung(void);

#endif
#endif /* INC_IR_SAMSUNG_H_ */
