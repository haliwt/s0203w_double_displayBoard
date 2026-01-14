/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    iwdg.c
  * @brief   This file provides code for the configuration
  *          of the IWDG instances.
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
#include "iwdg.h"

/* USER CODE BEGIN 0 */
#include "bsp.h"

/* USER CODE END 0 */
 uint8_t iwdg_error;
IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128; //  128* 4095 /32KHz = 16380ms = 16.38s
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  if(HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    //Error_Handler();
     iwdg_error = 0xff;
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/* USER CODE BEGIN 1 */
#if 0
void iwdg_feed(void)
{
   if(gctl_t.gTimer_feed_dog_times > 6){
      gctl_t.gTimer_feed_dog_times =0;

    HAL_IWDG_Refresh(&hiwdg);  /* ��װ�ؼ����� */

    }
}

#endif 

/* USER CODE END 1 */
