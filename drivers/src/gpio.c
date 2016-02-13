/*
 * gpio.c
 *
 *  Created on: 11.11.2015
 *      Author: b_ene_000
 */

#include "gpio.h"

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if (GPIO_Pin == KEY_BUTTON_PIN)
  {
    ubKeyPressed = SET;

    /* Display LCD messages */
    BSP_LCD_DisplayStringAt(0, 70, (uint8_t*)"Enebish", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 95, (uint8_t*)"Mira", CENTER_MODE);
  }

  if (GPIO_Pin == GPIO_PIN_2)
  {
    BSP_LCD_DisplayStringAt(0, 70, (uint8_t*)"        ", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 95, (uint8_t*)"        ", CENTER_MODE);
  }

  if (GPIO_Pin == GPIO_PIN_5)
  {
    /* Display LCD messages */
    BSP_LCD_DisplayStringAt(0, 70, (uint8_t*)"Enebish", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 95, (uint8_t*)"Mira", CENTER_MODE);

  }
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine2_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOD clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Configure PD2 pin as input floating */
  GPIO_InitStructure.Pin = GPIO_PIN_2;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine5_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Pin = GPIO_PIN_5;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void GPIO_Init2 (void)
{
  __HAL_RCC_GPIOG_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_Init_Type;
  GPIO_Init_Type.Pin = GPIO_PIN_13 | GPIO_PIN_14;
  GPIO_Init_Type.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init_Type.Pull = GPIO_NOPULL;
  GPIO_Init_Type.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Type);

  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
}


