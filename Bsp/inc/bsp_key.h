#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_
#include "main.h"

#define KEY_POWER_VALUE()    HAL_GPIO_ReadPin(KEY_POWER_GPIO_Port, KEY_POWER_Pin)

#define KEY_MODE_VALUE()     HAL_GPIO_ReadPin(KEY_MODE_GPIO_Port, KEY_MODE_Pin)

#define KEY_DEC_VALUE()    HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin)

#define KEY_ADD_VALUE()    HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)


typedef enum{

    KEY_UP,
    KEY_DOWN,
    

}key_pressed_t;



typedef enum{

   power_off,
   power_on,

}power_state;


typedef enum mode_key_t{
    
   disp_works_timing,
   disp_timer_timing,

   set_temp_value_item,
   
   mode_set_timer,
   mode_confirm,
   mode_set_temp,
   set_timer_confirm,
   counter_up,
   counter_down,
   key_sound,
   disp_fan_error_number,
   disp_ptc_error_number,
   disp_error_number
   
}mode_state;

 typedef struct _key_fun{
   
   uint8_t  key_power;
   uint8_t  key_mode;
   uint8_t  key_sound_flag;
   uint8_t  key_mode_be_pressed;
   uint8_t  power_on_flag;
  
   uint8_t  key_mode_flag;
   uint8_t  key_add_flag;
   uint8_t  key_dec_flag;

 
   uint8_t  key_add_dec_mode;
   uint8_t  set_timer_timing_success;
   uint8_t  power_key_long_counter;
   uint8_t  key_mode_long_counter;

   uint8_t set_temp_value_be_pressed;

  
   uint8_t  key_mode_shot_flag ;

   uint8_t   key_mode_times;
   uint8_t   set_temp_value;
   uint8_t   key_mode_switch_flag;

   uint8_t  wifi_led_fast_blink_flag;
 
   uint8_t  gTimer_disp_set_timer_blink;
   uint8_t  gTimer_power_off;
   uint8_t  gTimer_disp_set_timer;
   uint8_t  gTimer_set_temp_blink;

  
   uint8_t gTimer_key_temp_timing;

   uint8_t gTimer_power_key_counter;
   uint8_t gTimer_power_off_run_times;
	

}key_fun_t;


 extern key_fun_t gkey_t;
 
 void key_handler(void);

void key_power_long_handler(void);

void key_mode_long_handler(void);

void key_mode_short_handler(void);


void Dec_Key_Fun(uint8_t cmd);

void Add_Key_Fun(uint8_t cmd);


void key_add_dec_set_temp_value_fun(void);



void smartphone_power_on_handler(void);

void set_temp_value_compare_dht11_temp_value(void);


void  key_mode_be_pressed_send_data_wifi(void);


void key_power_shot_handler(void);

void set_timer_value_handler(void);



#endif 

