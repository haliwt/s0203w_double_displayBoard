#include "bsp_fan.h"
#include "bsp.h"

uint8_t fan_full_speed,fan_stop_flag;
void FAN_GPIO_Iint(void)
{

   GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = FAN_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void Fan_Run(void)
{
   static uint8_t fan_full_init =0xff;
   if(fan_full_init !=fan_full_speed){
     fan_full_init =fan_full_speed;
      gpro_t.fan_lower_speed++;
      gpro_t.fan_middle_speed++;
      fan_stop_flag++;

      MX_TIM16_Init(10); //100KHZ,duty =50%


    }

   HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);//ultrasnoic On
   FAN_COM_SetLow(); //PA6
	 

}

void fan_max_run(void)
{
   
   MX_TIM16_Init(10); //100KHZ,duty =50%
   HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);//ultrasnoic On
   FAN_COM_SetLow(); //PA6
}




void Fan_Run_Middle(void)
{

  static uint8_t run_mid_init= 0xff;

   if(run_mid_init != gpro_t.fan_middle_speed){
     run_mid_init = gpro_t.fan_middle_speed;
     fan_full_speed++;
     gpro_t.fan_lower_speed++;
     fan_stop_flag++;
 
        MX_TIM16_Init(9); //100KHZ,duty =50%



   }
   
 
   HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);//ultrasnoic On
   FAN_COM_SetLow(); //PA6


}

void Fan_Run_Lower(void)
{
   uint8_t run_low_init=0xff;

   if(run_low_init != gpro_t.fan_lower_speed){
     run_low_init = gpro_t.fan_lower_speed;
     fan_full_speed++;
     gpro_t.fan_middle_speed++;
     fan_stop_flag++;
      MX_TIM16_Init(8); //100KHZ,duty =50%



    }
   
   
   HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);//ultrasnoic On
   FAN_COM_SetLow(); //PA6


}

 
void Fan_Stop(void)
{
   static uint8_t fan_stop_init = 0xff;

   if(fan_stop_init != fan_stop_flag){
       fan_stop_init = fan_stop_flag;

        fan_full_speed++;
        gpro_t.fan_middle_speed++;
        gpro_t.fan_lower_speed++;


   }

    HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);//ultrasnoic On

    FAN_COM_SetLow(); //PA6
  
}


