#include "bsp.h"

message_disp mess_t;

void receive_message_displaybord_handler(void)
{
    uint8_t check_code;
	if(gpro_t.disp_rx_cmd_done_flag ==1){
            gpro_t.disp_rx_cmd_done_flag = 0;


		   check_code =  bcc_check(mess_t.mesData,mess_t.mesLength);

		  if(check_code == mess_t.bcc_check_code ){
		  
			 receive_data_fromm_display(mess_t.mesData);
			 if(gpro_t.buzzer_sound_flag == 1){
				 gpro_t.buzzer_sound_flag++ ;
				 buzzer_sound();


			 }
		  }

      }
}

/**********************************************************************
    *
    *Function Name:void receive_data_fromm_display(uint8_t *pdata,uint8_t len)
    *Function: receive usart touchkey of command 
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
void receive_data_fromm_display(uint8_t *pdata)
{

   if(pdata[1] == 0x02){

    switch(pdata[2]){

     case 0:


     break;

     case 0x01: //表示�?机指�?
        //wake_up_backlight_on();
        gpro_t.gTimer_shut_off_backlight =0;

        if(pdata[3] == 0x00 ){ //open
            if(pdata[4]==0x01){
             Buzzer_KeySound();// buzzer_sound();
			gctl_t.step_process=0;
            gpro_t.disp_power_on_flag = 1;
			gkey_t.key_power=power_on;
           SendWifiData_Answer_Cmd(0x01,0x01); //WT.EDIT 2025.01.07 
           osDelay(5);


        }
        else if(pdata[4] == 0x0){
           Buzzer_KeySound();//buzzer_sound();
		   gpro_t.disp_power_on_flag = 2;
		   gkey_t.key_power=power_off;
         

         SendWifiData_Answer_Cmd(0x01,0x0); //WT.EDIT 2025.01.07
		 osDelay(5);
        }
    	}

     break;

     case 0x02: //PTC打开关闭指令

     if(pdata[4] == 0x01){

        buzzer_sound();
        wake_up_backlight_on();
         gpro_t.gTimer_shut_off_backlight =0;
       
          gctl_t.manual_turn_off_ptc_flag = 0;
          gctl_t.ptc_flag = 1;
          Disp_Dry_Icon();
          if(gctl_t.interval_stop_run_flag  ==0){

               Ptc_On();

           }
          
          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPtc(0x01);
	  	      osDelay(50);//HAL_Delay(350);
           }
       }
       else if(pdata[3] == 0x0){
        
          //buzzer_sound();
          //wake_up_backlight_on();
          //gpro_t.gTimer_shut_off_backlight =0;
          Buzzer_KeySound();
          gctl_t.manual_turn_off_ptc_flag = 1;
       
          gctl_t.ptc_flag = 0;
          Ptc_Off();
          Disp_Dry_Icon();
          
         if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPtc(0x0);
	  	      osDelay(50);//HAL_Delay(350);
          }
        }
     
      
     break;

     case 0x22: //notification :ccompare set temp value ->PTC打开关闭指令,没有蜂鸣器声音�??
     // wake_up_backlight_on();
     // gpro_t.gTimer_shut_off_backlight =0;

      if(pdata[4] == 0x01){

         
         
        if(gctl_t.interval_stop_run_flag  ==0 && gctl_t.manual_turn_off_ptc_flag ==0){
		  	     gctl_t.ptc_flag = 1;
         
                  Disp_Dry_Icon();

                 Ptc_On();
          }
         if(gpro_t.tencent_link_success==1 && gctl_t.manual_turn_off_ptc_flag==0){
              MqttData_Publish_SetPtc(0x01);
	  	      osDelay(50);//HAL_Delay(350);
           }
          
         
         
       }
       else if(pdata[4] == 0x0){

       
         
          gctl_t.ptc_flag = 0;
          Ptc_Off();
          Disp_Dry_Icon();
          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPtc(0x0);
	  	      osDelay(50);//HAL_Delay(350);
           }

       }

     break;

     case 0x03: //PLASMA 打开关闭指令

         buzzer_sound();
         wake_up_backlight_on();

        gpro_t.gTimer_shut_off_backlight =0;
         

        if(pdata[4] == 0x01){
            
           gctl_t.plasma_flag  = 1;
          
           Disp_Kill_Icon();
           if(gctl_t.interval_stop_run_flag  ==0){
                Plasma_On();

           }
           

          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPlasma(0x01);
	  	      osDelay(50);//HAL_Delay(350);
          }
          
         

           
        }
        else if(pdata[4] == 0x0){
       
           gctl_t.plasma_flag  = 0;
           Plasma_Off();
           Disp_Kill_Icon();

          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPlasma(0x0);
	  	      osDelay(50);//HAL_Delay(350);
          }
         

        }


     break;


      case 0x04: //ultrasonic  打开关闭指令

         //buzzer_sound();

        //wake_up_backlight_on();
        //gpro_t.gTimer_shut_off_backlight =0;
            
       if(pdata[4] == 0x01){  //open 
           Buzzer_KeySound();
         //if(gctl_t.interval_stop_run_flag ==0){
          
            gctl_t.ultrasonic_flag =1;
            
            Disp_Ultrsonic_Icon();

            if(gctl_t.interval_stop_run_flag  ==0){
                Ultrasonic_Pwm_Output();

             }

             if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetUltrasonic(0x01);
	  	      osDelay(50);//HAL_Delay(350);
             }



        //}

        }
        else if(pdata[4] == 0x0){ //close 
			 Buzzer_KeySound();

             gctl_t.ultrasonic_flag =0;
            	Ultrasonic_Pwm_Stop();
             	Disp_Ultrsonic_Icon();

              if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetUltrasonic(0x0);
	  	      osDelay(50);//HAL_Delay(350);
             }

        }


     break;

      case 0x05: // link wifi command
          buzzer_sound();

          wake_up_backlight_on();
         gpro_t.gTimer_shut_off_backlight =0;
         

       if(pdata[4] == 0x01){  // link wifi 
        

        second_disp_set_link_wifi_fun();

           
            

        }
        else if(pdata[4] == 0x0){ //don't link wifi 

        }


     break;

     case 0x06: //buzzer sound done
        // wake_up_backlight_on();
        if(pdata[3]==0){
	        if(pdata[4] == 0x01){  //
	           
	             Buzzer_KeySound()  ;
	             gkey_t.key_mode_shot_flag = 1;
				 gctl_t.ai_flag = 1;
				gkey_t.key_mode_switch_flag = 1;
				gkey_t.key_mode  = disp_works_timing;


				gpro_t.gTimer_disp_short_time=0;

				LCD_Disp_Works_Timing_Init();
				disp_ai_iocn();

	        }
	        else if(pdata[4] == 0x02){

			 gkey_t.key_mode  = disp_timer_timing;

			 gkey_t.key_mode_shot_flag = 1;

			   gctl_t.ai_flag = 0; // DON'T DISP AI ICON


			// g_tDisp.ai_mode_flag =2; //WT.EDIT 2025.06.07

			gkey_t.key_mode_switch_flag = 1;
			gkey_t.key_add_dec_mode = set_temp_value_item;
            gkey_t.key_mode_be_pressed = 2;
			gpro_t.gTimer_disp_short_time=0;
			LCD_Disp_Timer_Timing_Init();
			disp_ai_iocn();
	        }

        }


     break;

	 case 0x07: //switch display by has been set up timer value or works timing value

	      if(pdata[3]==0){
	        if(pdata[4] == 0x02 || pdata[4] ==0x01){  //display AI =2,disp_timer_item.
	           Buzzer_KeySound();

			  if(gctl_t.ai_flag ==1){
                  gpro_t.receive_disp_mode = disp_timer_timing;//gkey_t.key_mode=disp_timer_timing;
				  gpro_t.gTimer_disp_short_time =0;
			     // dispLCD_worksTime_fun();
			     if(gkey_t.set_timer_timing_success ==1){
                       dispLCD_timerTime_fun();

				  }
				  else{
				     gctl_t.ai_flag = 0; // DISPLAY AI ICON
					  donot_disp_ai_symbol();
                      display_timer_times_handler(); 
				  }
				  gkey_t.key_mode = disp_timer_timing;

			  
		      }
			  else if(gctl_t.ai_flag==0){ //display don't AI MODE ,disp_works_item
			  	 
				  gpro_t.receive_disp_mode= disp_works_timing ;//gkey_t.key_mode=disp_works_timing;
				  gpro_t.gTimer_disp_short_time =0;

				   dispLCD_worksTime_fun();
				  gkey_t.key_mode = disp_works_timing;
				  }

			  }
           
	      } 
	  

	 break;

     case 0x0A: //the second display board link state. dc power on the first link state

        wake_up_backlight_on();
        gpro_t.gTimer_shut_off_backlight =0;
        if(pdata[4] == 0x01){  //
          if(gkey_t.key_power==power_on){
            g_tDisp.disp_second_link_state_flag =1;

          }
          else{
              g_tDisp.disp_second_link_state_flag =0;


          }
           

        }
       

     break;


      case 0x1A: //read DHT11 of sensor temperature and humidity value 读取传感的温度数�?
          //wake_up_backlight_on();
          //gpro_t.gTimer_shut_off_backlight =0;
        if(pdata[4] == 0x0F){ //
          if(gkey_t.set_temp_value_be_pressed !=1){
          gpro_t.set_temperature_value_success=1;
          gkey_t.set_temp_value_be_pressed = 1;     //send data to tencent flag.
          
          //gctl_t.gSet_temperature_value  = pdata[5] ;
          //  gclt_t.read_dht11_temperature_value = pdata[5];

          }

        }
      break;

      case 0x2A:   //set up temperature value 按键设置的温度�??

       //  wake_up_backlight_on();
        if(pdata[4] == 0x01){ 
          Buzzer_KeySound();
		 
		  gpro_t.gTimer_set_temp_temp=0;
          g_tDisp.disp_set_temp_value_flag =1;
		  gctl_t.manual_turn_off_ptc_flag = 0;
          gpro_t.set_temperature_value_success=1;
		   gpro_t.gTImer_send_disp_board =10;
          gctl_t.gSet_temperature_value  = pdata[5] ;  
          if(gctl_t.interval_stop_run_flag==0){
           temperatureValue_compareHandler();

          }
       
         }
        

      break;

      case 0x1B: //湿度数据

        if(pdata[3] == 0x0F){ //数据
            

        }
      break;

      case 0x1C: //表示时间：小时，分，�?

        if(pdata[3] == 0x0F){ //数据

          


        }
      break;

        case 0x1D: //表示日期�? 年，月，�?

        if(pdata[3] == 0x0F){ //数据

             
            

        }
      break;


     

     case 0x27: //AI mode 
      wake_up_backlight_on();
      gpro_t.gTimer_shut_off_backlight =0;

      if(pdata[4] == 0x01){ //AI mode ,don't buzzer sound .
        
        g_tDisp.ai_mode_flag =1;
        gkey_t.key_mode = disp_works_timing;
      //   second_disp_ai_time_fun();
      }
       else{
      
        gkey_t.key_mode = disp_timer_timing;
        g_tDisp.ai_mode_flag =2 ;
        gpro_t.gTimer_disp_short_time =0;
       // second_disp_not_ai_timer_fun();
       
            

        }
        
     break;


     case 0x2B: //display #1 or display #2  timer timing .
         //wake_up_backlight_on();
         ///gpro_t.gTimer_shut_off_backlight =0;
         if(pdata[3]==0x0F){
	         if(pdata[4]==0x01){
                gpro_t.set_timer_timing_hours = pdata[5];
	            gkey_t.key_mode = disp_timer_timing;
	           gpro_t.gTimer_timer_Counter=0;
	            gkey_t.set_timer_timing_success = 1;
	            gkey_t.gTimer_disp_set_timer = 0; 
	            gpro_t.set_timer_timing_minutes =0;
	          
	          
				dispLCD_timerTime_fun();
	            
	         }
         }

     break;
        
     
     }

   }

}

/**********************************************************************
    *
    *Function Name:uint8_t bcc_check(const unsigned char *data, int len) 
    *Function: BCC校验函数
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
uint8_t bcc_check(const unsigned char *data, int len) 
{
    unsigned char bcc = 0;
    for (int i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}


