/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PLASMA_Pin|FAN_COMM_Pin|FAN_OUT_Pin|WIFI_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RELAY_Pin|LED_CTL_Pin|LCD_LIGHT_Pin|TEMP_Pin
                          |TM1723_DIO_Pin|TM1723_SCLK_Pin|TM1723_STB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(POWER_LED_GPIO_Port, POWER_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = PLASMA_Pin|FAN_COMM_Pin|FAN_OUT_Pin|WIFI_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = RELAY_Pin|LED_CTL_Pin|LCD_LIGHT_Pin
                          |TM1723_DIO_Pin|TM1723_SCLK_Pin|TM1723_STB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    GPIO_InitStruct.Pin = TEMP_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;            /* 开漏输出 */
    GPIO_InitStruct.Pull= GPIO_PULLUP;                    /* 上拉 */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(GPIOB,  &GPIO_InitStruct);   /* 初始化DHT11_DQ引脚 */


  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = POWER_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POWER_LED_GPIO_Port, &GPIO_InitStruct);


  /*Configure GPIO pin : PtPin  interrupt GPIO*/
  GPIO_InitStruct.Pin = KEY_POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  HAL_GPIO_Init(KEY_POWER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = KEY_MODE_Pin|KEY_UP_Pin|KEY_DOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);


   /* EXTI interrupt init*/
//  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
//  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
//
//  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 3, 0);
//  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
//
//  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
//  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
