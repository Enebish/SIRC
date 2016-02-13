#ifndef __STM32F4xx_DECODE_H
#define __STM32F4xx_DECODE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//#define SAMSUNG_SIRC
//#define LIVARNOLUX_SIRC
//#define SONY_SIRC

#if !defined (IR_RC5_PROTOCOL) && !defined (IR_SIRC_PROTOCOL)
//#define IR_RC5_PROTOCOL
#define IR_SIRC_PROTOCOL
#endif

#if defined SAMSUNG_SIRC
  #include "ir_samsung.h"
#elif defined SONY_SIRC
  #include "ir_sony.h"
#elif defined LIVARNOLUX_SIRC
  #include "ir_livarnolux.h"
#endif

#define IR_TIM            TIM4                       /*!< Timer used for IR decoding */
#define TIM_PRESCALER     83                         /* !< TIM prescaler  168000000/84=2000000 ( 1/2MHz=500 nS )*/
#define IR_TIM_CLK        __HAL_RCC_TIM4_CLK_ENABLE  /*!< Clock of the used timer */
#define IR_TIM_IRQn       TIM4_IRQn                  /*!< IR TIM IRQ */
#define IR_TIM_Channel    TIM_CHANNEL_1              /*!< IR TIM Channel */

#define IR_GPIO_PORT      GPIOB                      /*!< Port which IR output is connected */
#define IR_GPIO_PORT_CLK  __HAL_RCC_GPIOB_CLK_ENABLE /*!< IR pin GPIO Clock Port */
#define IR_GPIO_PIN       GPIO_PIN_7                 /*!< Pin which IR is connected */

GPIO_InitTypeDef          GPIO_InitStructure;
TIM_HandleTypeDef         TIM_ICInitStructure;

/* Timer Input Capture Configuration Structure declaration */
TIM_IC_InitTypeDef        sConfig;
TIM_SlaveConfigTypeDef    Slave_Config;

/** @defgroup SIRC_Exported_Constants
  * @{
  */
//#define USE_LCD_IR_REMOTE
#define IR_STATUS_HEADER         0
#define IR_STATUS_RX             1

#define IR_BIT_ERROR             0xFF
#define IR_HEADER_ERROR          0xFF
#define IR_HEADER_OK             0x00

typedef enum
{
  NO = 0,
  YES = !NO
} StatusYesOrNo;

__IO StatusYesOrNo IRFrameReceived;   /*!< IR frame status */

typedef struct
{
  uint8_t count;  /*!< Bit count */
  uint8_t status; /*!< Status */
  uint32_t data;  /*!< Data */
} tIR_packet;

tIR_packet IRTmpPacket; /*!< IR packet*/

/* IR bit definitions*/
uint16_t IROnTimeMin;
uint16_t IROnTimeMax;
uint16_t IRValueStep;
uint16_t IRValueMargin;
uint32_t IRValue00;

/* Header time definitions*/
uint16_t IRHeaderLowMin;
uint16_t IRHeaderLowMax;
uint16_t IRHeaderWholeMin;
uint16_t IRHeaderWholeMax;

void IR_ResetPacket(void);
void IR_Init(void);

#endif /* __STM32F4xx_SIRC_H */
