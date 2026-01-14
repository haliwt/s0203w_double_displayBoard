#ifndef __BSP_FAN_H_
#define __BSP_FAN_H_
#include "main.h"



void FAN_GPIO_Iint(void);




#define FAN_CCW_SetHigh()            HAL_GPIO_WritePin(FAN_OUT_GPIO_Port,FAN_OUT_Pin,GPIO_PIN_SET)    // output high level
#define FAN_CCW_SetLow()             HAL_GPIO_WritePin(FAN_OUT_GPIO_Port,FAN_OUT_Pin,GPIO_PIN_RESET)    // output low level

#define FAN_COM_SetHigh()            HAL_GPIO_WritePin(FAN_COMM_GPIO_Port,FAN_COMM_Pin,GPIO_PIN_SET)    // output high level
#define FAN_COM_SetLow()             HAL_GPIO_WritePin(FAN_COMM_GPIO_Port,FAN_COMM_Pin,GPIO_PIN_RESET)    // output low level


void Fan_Run(void);

 
void Fan_Stop(void);

void Fan_Run_Middle(void);

void Fan_Run_Lower(void);

void fan_max_run(void);


#endif


