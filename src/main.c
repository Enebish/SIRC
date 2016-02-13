//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "ir_decode.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wmissing-declarations"
//#pragma GCC diagnostic ignored "-Wreturn-type"

char buffer1[10];

int main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("SIRC Protocol");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

	HAL_Init();
	// At this stage the system clock should have already been configured
	// at high speed.
	SystemClock_Config();

	/*##-1- Initialize the LCD #################################################*/
	/* Initialize the LCD */
	BSP_LCD_Init();

	/* Initialize the LCD Layers */
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);

	/* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

#if defined USE_LCD_IR_REMOTE
	/* Display LCD messages */
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(5, 10, (uint8_t*)"Infra-Red Receiver", CENTER_MODE);
	BSP_LCD_DisplayStringAt(5, 30, (uint8_t*)"SIRC protocol Samsung", CENTER_MODE);
#endif

	IR_Init();

	/* Configure LED3 and LED4 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* Configure USER Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	//EXTILine2_Config();
	//EXTILine5_Config();
	//TIM3_Init();

	// Infinite loop
	while (1)
	{
	  HAL_Delay(100);
	  if (IRFrameReceived)
	  {
      snprintf(buffer1, 7, "%*d", 4, comL);
      BSP_LCD_DisplayStringAt(0, 290, (uint8_t*) "          ", CENTER_MODE);
      BSP_LCD_DisplayStringAt(0, 290, (uint8_t*) buffer1, CENTER_MODE);
      IRFrameReceived = NO;
	  }

//		BSP_LED_On(LED3);
//		BSP_LED_Off(LED4);
//		HAL_Delay(100);
//		BSP_LED_Off(LED3);
//		BSP_LED_On(LED4);
	}
}

//#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
