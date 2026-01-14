#include "bsp.h"


BSP_process_t gpro_t;

static void Mainboard_Action_Fun(void);

static void Process_Dynamical_Action(void);
//static void power_off_function(void);
/**********************************************************************************************************
*
*	函 数 名: void mainboard_active_handler(void)
*	功能说明: 
*			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
void mainboard_active_handler(void)
{
   if(gpro_t.gTimer_run_main_fun > 1 && gpro_t.receive_disp_mode != disp_timer_timing){
        gpro_t.gTimer_run_main_fun =0;
        if(gctl_t.interval_stop_run_flag  ==0){
            Process_Dynamical_Action();
        }


        link_second_disp_board_handler();
    }

//    if(gpro_t.gTimer_disp_works_time > 24 && gpro_t.receive_disp_mode != disp_timer_timing){
//       gpro_t.gTimer_disp_works_time=0;
//
//        display_works_times_handler();
//
//
//    }



}




/**********************************************************************************************************
*
*	函 数 名: void Process_Dynamical_Action(void)
*	功能说明: 主板工作：功能动作输出			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
static void Process_Dynamical_Action(void)
{


    if(gctl_t.ai_flag == 1){

            disp_ai_symbol();

     }
     else{
       donot_disp_ai_symbol();

     }

   if(ptc_state() ==1 && gctl_t.manual_turn_off_ptc_flag == 0 &&  gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){


       Ptc_On();
       Disp_Dry_Icon();


     }
    else{

           
     Ptc_Off();
     Disp_Dry_Icon();
    }
            

    if(plasma_state() ==1){
		
       Plasma_On();
       Disp_Kill_Icon();

    }
	else{

	   Plasma_Off();
       Disp_Kill_Icon();

	}

    if(ultrasonic_state() ==1){

         Ultrasonic_Pwm_Output();
         Disp_Ultrsonic_Icon();

    }
    else{

    Ultrasonic_Pwm_Stop();
    Disp_Ultrsonic_Icon();


    }

  
    switch(wifi_t.set_wind_speed_value){
    
         case 0: //full speed
    
    
           Fan_Run();
    
         break;
    
         case 1 : //middle speed
          Fan_Run_Middle();
    
         break;
    
         case 2: //lower speed
         
          
          if(gpro_t.wind_speed_init_flag ==1){
               gpro_t.wind_speed_init_flag++;
                  Fan_Run();
                  osDelay(1000);
          
          }
          else
             Fan_Run_Lower();
         break;
    
    
       }


    if(g_tDisp.second_disp_power_on ==2){
        
        g_tDisp.second_disp_power_on++;

    if(gpro_t.tencent_link_success==1){
              
             SendWifiData_To_Data(0x1F,0x01); //0x1F: 0x1=wifi link net is succes ,0x0 = wifi link net is fail
             osDelay(10);
         }
         else{

              SendWifiData_To_Data(0x1F,0x0); //0x1F: 0x1=wifi link net is succes ,0x0 = wifi link net is fail
             osDelay(10);


         }

    }


}






/***************************************************************************
    *
    *Function Name:void link_wifi_net_handler(uint8_t link)
    *Function : 
    *Input Ref: link wifi flag :1 -> link wifi ,0-> don't link wifi
    *Return Ref : NO
    *
***************************************************************************/
void link_wifi_net_handler(uint8_t link)
{

   static uint8_t send_second_disp_flag;
    if(link == 1){

         if(wifi_t.gTimer_linking_tencent_duration > 119){

            gkey_t.wifi_led_fast_blink_flag =0;//gpro_t.wifi_led_fast_blink_flag =0;
           if(gpro_t.tencent_link_success==0){

             gpro_t.get_beijing_step = 10;
             wifi_t.gTimer_auto_detected_net_state_times = 120;
             gpro_t.linking_tencent_cloud_doing =1;
             wifi_t.soft_ap_config_flag =1; 
           }
   
        // link_net_flag = 1;
         send_second_disp_flag=0;
     
         gpro_t.link_net_step=0;
         
        }
        else{ //link wifi this is led fast blinking . 
          link_wifi_net_state_handler();

           if( gkey_t.wifi_led_fast_blink_flag== 1 && send_second_disp_flag==0){
               send_second_disp_flag++;

               SendData_Set_Command(0x05,0x01);// link wifi net .
               osDelay(10);

         }

        }

       

    }
}

#if 0
    else{

       switch(link_net_flag ){


       case 0:

          // Detected_Fan_Error();
           //Detected_Ptc_Error();

      // break;

        case 1:
      
        if(gpro_t.tencent_link_success==1){

              link_net_flag = 2 ; 
              send_second_disp_flag=0;

                gpro_t.link_net_step=0;
			 
				// MqttData_Publish_SetOpen(0x01);
		        // osDelay(200);//HAL_Delay(200);
               //  SendData_Set_Command(0x1F,0x01);//has been link net OK
                // osDelay(5);
                  
           }
           else{

                link_net_flag = 4 ;
                send_second_disp_flag=0;
           }
        break;

        case 2:

           if(gpro_t.tencent_link_success==1){
                  link_net_flag = 3 ;     
        
              //  Subscriber_Data_FromCloud_Handler();
              //  osDelay(50);//HAL_Delay(200);
                
               
           }
           else{

                link_net_flag = 4 ;
           }
         break;


        case 3:
        if(gpro_t.tencent_link_success==1){
               link_net_flag = 0;
		       //  Publish_Data_ToTencent_Initial_Data();
				// HAL_Delay(200);
                //  osDelay(200);
               
         }
          else{

                link_net_flag = 4 ;
           }

        break;


        case 4:
        
         if(gpro_t.tencent_link_success==0){

             link_net_flag = 0;
             send_second_disp_flag=0;
            
              gpro_t.link_net_step=0;
             gpro_t.get_beijing_step = 11;
              SendData_Set_Command(0x1F,0x0);
              osDelay(5);

           }
		  link_net_flag = 0xff ;

        break;
       

        }

        
        
             

     }
 }

#endif 

/********************************************************
 * 
 * Function Name:void read_senson_dht11_data(void)
 * 
 * 
 *******************************************************/
void read_senson_dht11_data(void)
{

  static uint8_t power_on_run_dht11_times ;
  if(gkey_t.set_temp_value_be_pressed !=1){
	  if(gpro_t.gTimer_run_dht11 > 5  ||  power_on_run_dht11_times < 20){
	        gpro_t.gTimer_run_dht11=0;
	        power_on_run_dht11_times ++;

	        Update_DHT11_Value();

	        Disp_HumidityTemp_Value();

	        
       }
  }

  if(gpro_t.gTImer_send_disp_board > 7 ){

       gpro_t.gTImer_send_disp_board=0;
        if(gctl_t.interval_stop_run_flag==0){
            set_temp_value_compare_dht11_temp_value();//SetTemp_Compare_SensoTemp();

        }
        sendData_Real_TimeHum(gctl_t.dht11_humidity_value,gctl_t.dht11_temp_value);
        osDelay(10);

  }

  if(gpro_t.gTimer_update_data_to_tencent > 20 && gpro_t.tencent_link_success == 1){

      gpro_t.gTimer_update_data_to_tencent =0;

      Update_Dht11_Totencent_Value();
  }

}

void record_time_or_timer_handler(void)
{
    if(gkey_t.key_mode == disp_timer_timing ){
    if(gpro_t.gTimer_works_counter_sencods > 59 ){
    
          gpro_t.gTimer_works_counter_sencods=0;
    
          gpro_t.disp_works_minutes_value++;
    
        if( gpro_t.disp_works_minutes_value > 59){ //1 hours
            gpro_t.disp_works_minutes_value=0;
    
             gpro_t.disp_works_hours_value++;
    
    
            if(gpro_t.disp_works_hours_value > 99){
                gpro_t.disp_works_hours_value=0;
    
    
            }
            
        }
        }
        
     }
     else if(gkey_t.key_mode == disp_works_timing){

     if( gkey_t.set_timer_timing_success == 1){
     if(gpro_t.gTimer_timer_Counter > 59){
	    gpro_t.gTimer_timer_Counter =0;
		
		gpro_t.set_timer_timing_minutes -- ;
    
	
	    if(gpro_t.set_timer_timing_minutes <  0 ){
			 
		   gpro_t.set_timer_timing_hours -- ;
		   gpro_t.set_timer_timing_minutes =59;
         }

		
		
		 if(gpro_t.set_timer_timing_hours < 0 ){
		 
			
			gpro_t.set_timer_timing_hours=0;
    		gpro_t.set_timer_timing_minutes=0;
    		gkey_t.key_power = power_off;
            gpro_t.power_off_flag = 1;
    			//gkey_t.gTimer_power_off_run_times=0;
           
            
			
	      }

        }
        }

    }

}


