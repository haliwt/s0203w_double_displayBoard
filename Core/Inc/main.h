/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_FAN_Pin 						GPIO_PIN_0
#define ADC_FAN_GPIO_Port 					GPIOA

#define ADC_NTC_Pin 						GPIO_PIN_1
#define ADC_NTC_GPIO_Port 					GPIOA

//
#define PLASMA_Pin 							GPIO_PIN_5
#define PLASMA_GPIO_Port 					GPIOA

#define FAN_OUT_Pin 						GPIO_PIN_6
#define FAN_OUT_GPIO_Port 					GPIOA

#define FAN_COMM_Pin 						GPIO_PIN_7
#define FAN_COMM_GPIO_Port 					GPIOA

#define RELAY_Pin 							GPIO_PIN_0
#define RELAY_GPIO_Port 					GPIOB

#define BEEP_PWM_Pin 						GPIO_PIN_1
#define BEEP_PWM_GPIO_Port 					GPIOB

//sensor temperature detected GPIO
#define TEMP_Pin 							        GPIO_PIN_13
#define TEMP_GPIO_Port 						        GPIOB

#define ULTRA_PWM_Pin 						GPIO_PIN_8
#define ULTRA_PWM_GPIO_Port 				GPIOA

//display panel GPIO

#define KEY_POWER_Pin 						GPIO_PIN_15
#define KEY_POWER_GPIO_Port 				GPIOA
#define KEY_POWER_EXTI_IRQn 				EXTI4_15_IRQn

#define KEY_MODE_Pin 						GPIO_PIN_0
#define KEY_MODE_GPIO_Port 					GPIOD
#define KEY_MODE_EXTI_IRQn 					EXTI0_1_IRQn

#define KEY_UP_Pin 							GPIO_PIN_1
#define KEY_UP_GPIO_Port 					GPIOD
#define KEY_UP_EXTI_IRQn 					EXTI0_1_IRQn

#define KEY_DOWN_Pin 						GPIO_PIN_2
#define KEY_DOWN_GPIO_Port 					GPIOD
#define KEY_DOWN_EXTI_IRQn 					EXTI2_3_IRQn


//end key input GPIO
//display board of key of led 
#define POWER_LED_Pin           GPIO_PIN_3
#define POWER_LED_GPIO_Port     GPIOD

#define LED_CTL_Pin GPIO_PIN_3
#define LED_CTL_GPIO_Port GPIOB

#define LCD_LIGHT_Pin GPIO_PIN_4
#define LCD_LIGHT_GPIO_Port GPIOB

#define TM1723_DIO_Pin GPIO_PIN_5
#define TM1723_DIO_GPIO_Port GPIOB

#define TM1723_SCLK_Pin GPIO_PIN_6
#define TM1723_SCLK_GPIO_Port GPIOB

#define TM1723_STB_Pin GPIO_PIN_7
#define TM1723_STB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define  WIFI_EN_Pin           GPIO_PIN_12  
#define  WIFI_EN_GPIO_Port      GPIOA

//USART1 DISPLAY BOARD COMMNUNICATION
#define DISP_TX_Pin             GPIO_PIN_9
#define DISP_TX_GPIO_Port       GPIOA

#define DISP_RX_Pin             GPIO_PIN_10
#define DISP_RX_GPIO_Port       GPIOA


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
