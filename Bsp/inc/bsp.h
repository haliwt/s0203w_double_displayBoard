#ifndef  	__BSP_H_
#define 	__BSP_H_
#include "main.h"


#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"






#include "interrupt_manager.h"
#include "adc.h"

#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "iwdg.h"



//maiboard
#include "bsp_adc.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_buzzer.h"
#include "bsp_key.h"


#include "bsp_power.h"
#include "bsp_tm1723.h"

#include "bsp_ultrasonic.h"
#include "bsp_delay.h"
#include "bsp_ctl.h"
#include "bsp_fan.h"
#include "bsp_plasma.h"
#include "bsp_ptc.h"
#include "bsp_message.h"
#include "bsp_usart.h"
#include "bsp_time.h"
#include "bsp_lcd_app.h"
#include "bsp_sensor.h"//#include "bsp_dht11.h"
#include "bsp_dht11_app.h"

#include "bsp_freertos_app.h"


//double display board

#include "bsp_cmd_link.h"
#include "bsp_decoder.h"
#include "bsp_second_disp.h"

//wifi
#include "bsp_wifi.h"
#include "bsp_wifi_fun.h"

#include "bsp_publish.h"
#include "bsp_subscription.h"
#include "bsp_mqtt_iot.h"



#define  USE_FreeRTOS      1

#if USE_FreeRTOS == 1
	#include "FreeRTOS.h"
	#include "task.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ¿ª¹ØÈ«¾ÖÖÐ¶ÏµÄºê */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* enable global interrupter */
	#define DISABLE_INT()	__set_PRIMASK(1)	/*  */
#endif




typedef struct {


   uint8_t gPower_On ;

   uint8_t power_off_flag;
   uint8_t shut_Off_backlight_flag;
   uint8_t disp_power_on_flag ;

   uint8_t tencent_link_success;
   uint8_t linking_tencent_cloud_doing ;


   uint8_t wind_speed_init_flag ;

   uint8_t fan_lower_speed;
   uint8_t fan_middle_speed;


   uint8_t wifi_power_on_normal_flag;
   


  
 
   //WIFI


  
   uint8_t set_temperature_value_success;
 
   uint8_t disp_timer_switch_time_flag;


   //display board
   uint8_t disp_rx_cmd_done_flag;
   uint8_t buzzer_sound_flag;
 
   uint8_t get_beijing_step ;
   uint8_t link_net_step;
   uint8_t first_link_tencent_cloud_flag;
   uint8_t get_beijing_time_success;


   uint8_t disp_works_minutes_value;
   uint8_t  disp_works_hours_value;
   uint8_t receive_disp_mode;

   //the second display ref 


   uint8_t smart_phone_set_tmep_value_flag;


     

   int8_t set_timer_timing_hours;
   int8_t set_timer_timing_minutes;

 //TIMER OF TIMES 

   uint8_t gTimer_run_dht11;

   uint8_t gTimer_run_one_mintue ;
   
   uint8_t gTimer_run_total;
 

   uint8_t gTimer_works_counter_sencods;
  
   uint8_t gTimer_timer_Counter;
  
   uint8_t gTimer_disp_set_timer_blink ;

   uint8_t gTimer_ptc_detected;
   uint8_t gTimer_shut_off_backlight;
   uint8_t gTimer_get_data_from_tencent_data;
   uint8_t gTimer_run_main_fun;
   uint8_t gTimer_set_temp_temp ;
   uint8_t gTimer_disp_short_time;
   uint8_t gTimer_login_tencent_times;
   uint8_t gTImer_send_disp_board;
   uint8_t gTimer_power_off_run_times;
   uint8_t gTimer_update_data_to_tencent ;
   uint8_t gTimer_disp_works_time;
   uint8_t gTimer_set_timer_value;
   uint8_t gTimer_disp_smg_4bit;
  
}BSP_process_t;

extern BSP_process_t gpro_t;


extern uint8_t disp_inputBuf[1];





void mainboard_active_handler(void);



void disp_works_or_timer_timing_fun(void);



void link_wifi_net_handler(uint8_t link);

void read_senson_dht11_data(void);

void  record_time_or_timer_handler(void);

void power_off_init_function(void);



#endif 

