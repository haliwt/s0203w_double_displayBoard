#include "bsp.h"


uint8_t power_off_flag,fan_run_one_flag;
/***********************************************************************
*
*Function Name:static void power_off_function(void)
*Function: by key be pressed power off run process
*Input Ref:NO
*Return Ref:NO
*
************************************************************************/
void power_off_init_function(void)
{

  if(gpro_t.power_off_flag == 1){
    		gpro_t.power_off_flag ++;
    	    
           //key set ref 

           gkey_t.gTimer_power_off_run_times=0;
           gkey_t.wifi_led_fast_blink_flag=0;
            gctl_t.ptc_flag =0;
            gctl_t.plasma_flag =0;
            
            gctl_t.fan_warning = 0;
            gctl_t.ptc_warning = 0;
            gkey_t.set_timer_timing_success =0;
    	   
    	  
    	    //control set ref
    	    wifi_t.link_net_tencent_data_flag =1;

             gctl_t.step_process=0;
             //cotrol displ dht11 value 
            

            //wifi set ref
    	
   
  
            wifi_t.gTimer_linking_tencent_duration=0; //120s

         
    	     gpro_t.wifi_power_on_normal_flag=0;
			 gpro_t.disp_power_on_flag =0;
			 gpro_t.wifi_power_on_normal_flag=0;
		
		      wifi_t.smartphone_app_power_on_flag=0;

            gpro_t.gTimer_run_dht11=20;
            gpro_t.set_temperature_value_success=0;

              gkey_t.key_add_dec_mode = disp_works_timing;
			
	          gpro_t.set_timer_timing_hours =0 ;
	          gpro_t.set_timer_timing_minutes =0;

		
		      if(gkey_t.set_timer_timing_success==1){
			      disp_time_4bit_init();
				   gkey_t.set_timer_timing_success = 0;

		      }
			  else if(gpro_t.get_beijing_time_success==0){

				   disp_time_4bit_init();


                 }


			 
			  
			  
           
    	    //stop main board function ref.
    	    PowerOff_Off_Led();
            SendData_Set_Command(0X01,0X00);
            osDelay(5);
    	  
		
	  }

     if(gpro_t.tencent_link_success ==1 && power_off_flag==0 ){
	
		power_off_flag++;
		MqttData_Publish_PowerOff_Ref();
	   osDelay(300);
	     
		 
		  
	}
	
   
	
}

/*******************************************************************************************************
*Function Name: void mainboard_process_handler(void)
*Function:
*			 本函数缺省为空操作�?�用户可以添加喂狗�?�设置CPU进入休眠模式的功能�??
*	�?    �?: �?
*	�? �? �?: �?
**********************************************************************************************************/
//void mainboard_process_handler(void)
void power_off_run_handler(void)
{
 static uint8_t  send_data_to_cloud;

  gkey_t.power_key_long_counter=0;
  if( gkey_t.key_sound_flag == key_sound){
		gkey_t.key_sound_flag =0;
		Buzzer_KeySound();

    }

  
  
   if(gpro_t.disp_power_on_flag ==2 || gpro_t.wifi_power_on_normal_flag==2){
      power_off_init_function();
	  if(gpro_t.disp_power_on_flag ==2)gpro_t.disp_power_on_flag++;
      if(gpro_t.wifi_power_on_normal_flag==2)gpro_t.wifi_power_on_normal_flag++;

   }

   
   
   if(fan_run_one_flag==1){
		  if(gkey_t.gTimer_power_off_run_times < 61){
			   Fan_Run();
			   OnlyDisp_Wind_Icon_Handler();
		  
		
			   
   
  }
  else{
	fan_run_one_flag++;
	gpro_t.power_off_flag++;
	Fan_Stop();
	Backlight_Off();
	Lcd_Display_Off();


	}
   
   }
		
   Breath_Led();
   if(gpro_t.tencent_link_success ==1 && send_data_to_cloud > 200){
		send_data_to_cloud=0;
		
        Subscriber_Data_FromCloud_Handler();
	    osDelay(100);
	
    }

}



/***********************************************************************
	*
	*Function Name:void power_on_run_handler(void)
	*Function: 
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************************************/
void power_on_run_handler(void)
{

    
     switch(gctl_t.step_process){


		  case 0:
		   
           if(gpro_t.disp_power_on_flag == 1 || gpro_t.wifi_power_on_normal_flag==1||wifi_t.smartphone_app_power_on_flag==1||wifi_t.smartphone_app_power_on_flag==2){
                power_on_init_function();

           }

             power_off_flag=0;
             fan_run_one_flag=1;

            gctl_t.step_process = 1;


		  break;


       
          case 1:   //run dht11 display 

            read_senson_dht11_data();
			//LCD_Fan_Run_Icon(wifi_t.set_wind_speed_value);

          gctl_t.step_process=2;
		  
          break;

        

	  case 2: //7

       
         
        if(gctl_t.ptc_warning == 0 && gctl_t.fan_warning ==0){
        if(g_tDisp.ai_mode_flag ==1 ){
            g_tDisp.ai_mode_flag=3;

             LCD_Disp_Works_Timing_Init();
             disp_ai_iocn();

             second_disp_ai_time_fun();

         if(gpro_t.tencent_link_success==1 ){
             MqttData_Publish_SetState(1);
	         osDelay(300);//HAL_Delay(350);
           }
        }
        else if(g_tDisp.ai_mode_flag ==2 ){
            g_tDisp.ai_mode_flag =3;

            LCD_Disp_Timer_Timing_Init();
            disp_ai_iocn();
            second_disp_not_ai_timer_fun();
  

        if(gpro_t.tencent_link_success==1 &&  g_tDisp.ai_mode_flag ==3){
			g_tDisp.ai_mode_flag++;
         MqttData_Publish_SetState(2);
	     osDelay(300);//HAL_Delay(350);

         }
        }

       }
         gctl_t.step_process=3;
	   
      case 3: 
	   
	   if(gpro_t.tencent_link_success==1 && wifi_t.smartphone_app_power_on_flag==0 && wifi_t.link_net_tencent_data_flag ==1){ //after send publish datat to tencent .){
             wifi_t.link_net_tencent_data_flag ++;
		  
		      MqttData_Publish_Update_Data();//MqttData_Publish_SetOpen(0x01);
		     osDelay(300);//HAL_Delay(20);
          
            

		}
		else if(gpro_t.tencent_link_success==1 && wifi_t.smartphone_app_power_on_flag==0 && wifi_t.link_net_tencent_data_flag ==2 ){
             wifi_t.link_net_tencent_data_flag ++;

           
		    //MqttData_Publish_Update_Data();
		    /// osDelay(20);//HAL_Delay(20);
		    Subscriber_Data_FromCloud_Handler();
            osDelay(200);
		     

		}
        else if(gpro_t.tencent_link_success==1 && wifi_t.link_net_tencent_data_flag ==3 ){
             
         
            wifi_t.link_net_tencent_data_flag ++;
            Update_Dht11_Totencent_Value();
            osDelay(100);
       }
       else if(gpro_t.tencent_link_success==1 && wifi_t.link_net_tencent_data_flag ==4 ){
                 wifi_t.link_net_tencent_data_flag++ ;
                   Publish_Data_Warning(fan_warning,no_warning);
                      osDelay(300);
                
                      Publish_Data_Warning(ptc_temp_warning,no_warning);
                      osDelay(200);
                
       }
		gctl_t.step_process=4;

	 break;

      case 4:

    	mainboard_active_handler();
	  
    	gctl_t.step_process=5;
     break;

      case 5:

    	 detected_ptc_fan_error_handler();
    	 gctl_t.step_process=6;
       break;

      case 6:
		   if(gpro_t.receive_disp_mode == disp_timer_timing || gpro_t.receive_disp_mode == disp_works_timing){
	        Display_modeKey_switchTime_Handler();
		   }
	  	   else if(gpro_t.receive_disp_mode != disp_timer_timing && gpro_t.receive_disp_mode != disp_works_timing){	
              if(gpro_t.gTimer_disp_smg_4bit > 2){
			  	gpro_t.gTimer_disp_smg_4bit =0;
			  Display_WorksTimingr_Handler(gkey_t.key_mode);
              }
	  	   }
	  	  
    	  gctl_t.step_process=7;
      break;



	case 7: //check works times

	       works_two_hours_handler();
		  // LCD_Fan_Run_Icon(wifi_t.set_wind_speed_value);
		   gctl_t.step_process=1;
    break;

	default:

	break;

	
   }

 }      

/***********************************************************************
	*
	*Function Name:static void power_off_function(void)
	*Function: by key be pressed power off run process
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************************************/
void power_on_init_function(void)
{
     

	if(gpro_t.get_beijing_time_success==0 ){

		gpro_t.disp_works_minutes_value=0;
		gpro_t.disp_works_hours_value =0;
		gpro_t.gTimer_works_counter_sencods =0;

	}


	if(wifi_t.smartphone_app_power_on_flag==0){
	  main_fun_init();

	}
	else{
		MqttData_Publis_App_PowerOn_Ref();
	    osDelay(300);//HAL_Delay(50);//

		SendWifiData_Ref_three(gctl_t.ptc_flag,gctl_t.plasma_flag,gctl_t.ultrasonic_flag);
		osDelay(100);//HAL_Delay(50);//
    }



	LED_Mode_On();
	LED_POWER_ON();
	Backlight_On();


	//LCD_Numbers1234_Init();
	//Display_Wind_Icon_Inint();

	Update_DHT11_Value();


	sendData_Real_TimeHum(gctl_t.dht11_humidity_value,gctl_t.dht11_temp_value);
	osDelay(5);
    LCD_Numbers1234_Init();
	LCD_Fan_Run_Icon(0);
	Disp_HumidityTemp_Init();


	if(gpro_t.tencent_link_success==1){
		MqttData_Publish_SetOpen(1);  
		osDelay(300);//300

		Subscriber_Data_FromCloud_Handler();
		osDelay(200);//HAL_Delay(30);

	}

    gpro_t.power_off_flag=1;


	//temperature value inti
	gpro_t.set_temperature_value_success=0;

	wifi_t.set_wind_speed_value=0; //init 
	gctl_t.ptc_warning = 0;
	gctl_t.fan_warning = 0;

	//timig init
	gpro_t.gTimer_run_total=0;

    gkey_t.set_timer_timing_success = 0;
	gpro_t.set_timer_timing_hours =0 ;
	gpro_t.set_timer_timing_minutes =0;

	gpro_t.gTimer_timer_Counter =0;

	gpro_t.gTimer_run_dht11=100;
	wifi_t.link_net_tencent_data_flag=1;


	gkey_t.key_add_dec_mode = disp_works_timing;
	gctl_t.ai_flag = 1; // AI DISPLAY AI ICON
	gkey_t.key_mode = disp_works_timing;
	gctl_t.gSet_temperature_value =40;
    gpro_t.receive_disp_mode = 0xff;
	
	

	if(gpro_t.tencent_link_success==1){

		Publish_Data_Warning(fan_warning,no_warning);
		osDelay(300);

		Publish_Data_Warning(ptc_temp_warning,no_warning);
		osDelay(200);

	}
	//TM1723_All_Off();
	TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);

}

