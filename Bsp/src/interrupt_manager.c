#include "interrupt_manager.h"
#include "bsp.h"

uint8_t disp_inputBuf[1];


//typedef struct Msg
//{
//	uint8_t  ucMessageID;
//	uint8_t usData[12];
//	//uint8_t ulData[1];
//}MSG_T;
//
//MSG_T   gl_tMsg; /* 定义丢�个结构体用于消息队列 */







/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function call back function
	*timer 1ms 
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm1,tm2,tm3;
  static uint16_t tm0;

 
    
   if(htim->Instance==TIM17){
    
    tm0++;  //1ms
	tm1++;
    tm3++;

    if(tm1>9){ //10ms
        tm1=0;
        
    gctl_t.gTimer_wifi_fast_blink++;
  
    
	glcd_t.gTimer_fan_blink++;
	gpro_t.gTimer_set_timer_value++;

   
       
    	
    }
	
    if(tm3>99){ //1*100 = 100ms 
       tm3=0;
     
            //key timer
       gkey_t.gTimer_set_temp_blink++;

       //lcd timer 
      
       
       glcd_t.gTimer_error_times++;
       
      
    }

    if(tm0>999){ //100 *10ms = 1000ms = 1s
		tm0=0;
		tm2++;

		glcd_t.gTimer_colon_blink++ ;
      
          //control timer
        gctl_t.gTimer_wifi_blink++;
    
         //key timer
	 
         gkey_t.gTimer_power_off_run_times++;
        
        gkey_t.gTimer_disp_set_timer++;
    
        //process gtimer
        gpro_t.gTimer_ptc_detected++;
        gpro_t.gTimer_works_counter_sencods ++;
        gpro_t.gTimer_timer_Counter++;
	
		gpro_t.gTimer_run_dht11++;
        
        gpro_t.gTimer_run_one_mintue ++;
     
        gpro_t.gTimer_run_main_fun++;
        
       
    
        gpro_t.gTimer_get_data_from_tencent_data++;
        gpro_t.gTimer_set_temp_temp ++;
        gpro_t.gTimer_disp_short_time++ ;

        gpro_t.gTimer_login_tencent_times ++;
        gpro_t.gTImer_send_disp_board++;
        gpro_t.gTimer_update_data_to_tencent ++ ;
        gpro_t.gTimer_disp_works_time++;
		gpro_t.gTimer_disp_smg_4bit++;
   
        
        //wifi

        wifi_t.gTimer_linking_tencent_duration++;

      
		wifi_t.gTimer_get_beijing_time++;
        wifi_t.gTimer_auto_detected_net_state_times++;
        wifi_t.gTimer_auto_link_net_time++;
        wifi_t.gTimer_power_first_link_tencent++;
        

        

       if(tm2 > 59){ //60s = 1 minutes
			tm2 =0;
			gpro_t.gTimer_run_total++;
		
            gpro_t.gTimer_shut_off_backlight++;
			

		}
	}
	
   }


}







