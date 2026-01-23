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

   //if(pdata[1] == 0x02||){

    switch(pdata[2]){

     case 0:


     break;

     case 0x01: //表示�?机指�?
        //wake_up_backlight_on();
        gpro_t.gTimer_shut_off_backlight =0;

        if(pdata[3] == 0x01){ //open
      
             Buzzer_KeySound();// buzzer_sound();
			gctl_t.step_process=0;
            gpro_t.disp_power_on_flag = 1;
			gkey_t.key_power=power_on;
           SendWifiData_Answer_Cmd(0x01,0x01); //WT.EDIT 2025.01.07 
           osDelay(50);


        }
        else if(pdata[3] == 0x0){
           Buzzer_KeySound();//buzzer_sound();
		   gpro_t.disp_power_on_flag = 2;
		   gkey_t.key_power=power_off;
         

         SendWifiData_Answer_Cmd(0x01,0x0); //WT.EDIT 2025.01.07
		 osDelay(50);
        }
    	

     break;

     case 0x02: //PTC打开关闭指令

     if(pdata[3] == 0x01){

        buzzer_sound();

         gpro_t.gTimer_shut_off_backlight =0;
       
          gctl_t.manual_turn_off_ptc_flag = 0;
          gctl_t.ptc_flag = 1;
          Disp_Dry_Icon();
          if(gctl_t.interval_stop_run_flag  ==0){

               Ptc_On();

           }
          
          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPtc(0x01);
	  	      osDelay(200);//HAL_Delay(350);
           }
       }
       else if(pdata[3] == 0x0){
        
    
          Buzzer_KeySound();
          gctl_t.manual_turn_off_ptc_flag = 1;
       
          gctl_t.ptc_flag = 0;
          Ptc_Off();
          Disp_Dry_Icon();
          
         if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPtc(0x0);
	  	      osDelay(200);//HAL_Delay(350);
          }
        }
     
      
     break;

    

     case 0x03: //PLASMA 打开关闭指令

         buzzer_sound();
      

        gpro_t.gTimer_shut_off_backlight =0;
         

        if(pdata[3] == 0x01){
            
           gctl_t.plasma_flag  = 1;
          
           Disp_Kill_Icon();
           if(gctl_t.interval_stop_run_flag  ==0){
                Plasma_On();

           }
           

          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPlasma(0x01);
	  	      osDelay(200);//HAL_Delay(350);
          }
          
         

           
        }
        else if(pdata[3] == 0x0){
       
           gctl_t.plasma_flag  = 0;
           Plasma_Off();
           Disp_Kill_Icon();

          if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetPlasma(0x0);
	  	      osDelay(200);//HAL_Delay(350);
          }
         

        }


     break;


      case 0x04: //ultrasonic  打开关闭指令
	   Buzzer_KeySound();

       if(pdata[3] == 0x01){  //open 
          
         if(gctl_t.interval_stop_run_flag ==0){
          
            gctl_t.ultrasonic_flag =1;
            
            Disp_Ultrsonic_Icon();

            if(gctl_t.interval_stop_run_flag  ==0){
                Ultrasonic_Pwm_Output();

             }

             if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetUltrasonic(0x01);
	  	      osDelay(200);//HAL_Delay(350);
             }

          }
       	}
        else if(pdata[3] == 0x0){ //close 
			

                gctl_t.ultrasonic_flag =0;
            	Ultrasonic_Pwm_Stop();
             	Disp_Ultrsonic_Icon();

              if(gpro_t.tencent_link_success==1){
              MqttData_Publish_SetUltrasonic(0x0);
	  	      osDelay(300);//HAL_Delay(350);
             }

        }


     break;

      case 0x05: // link wifi command
          buzzer_sound();
		

         gpro_t.tencent_link_success=0;
         gkey_t.wifi_led_fast_blink_flag=1;
         wifi_t.gTimer_linking_tencent_duration=0;
          SendWifiData_Answer_Cmd(0x05,0x01); //WT.EDIT 2025.01.07 
		  vTaskDelay(100);


     break;

     case 0x06: //buzzer sound done

          Buzzer_KeySound()  ;
	       

     break;

	 case 0x16:
	     Buzzer_KeySound();
		 SendWifiData_Answer_Cmd(0x16,0x01); //WT.EDIT 2025.01.07 
		 vTaskDelay(100);

	 break;
	 

	 case 0x17: //switch display by has been set up timer value or works timing value

           if(pdata[3]==0x01){
	           if(gpro_t.tencent_link_success==1){
			    MqttData_Publish_AiState(1);
	            vTaskDelay(200);
	           	}
           	}
		    else if(pdata[3]==0){

			
	           if(gpro_t.tencent_link_success==1){
	              MqttData_Publish_AiState(2); //timer model  = 2, works model = 1
	             vTaskDelay(200);

	           }

            }
  
	    

	 break;



      case 0x1A: //read DHT11 of sensor temperature and humidity value 读取传感的温度数�?
         
      
      break;

	  case 0x1B:

      case 0x2A:   //set up temperature value 按键设置的温度�??

        if(pdata[4] == 0x01){ 
          
		  gctl_t.gSet_temperature_value  = pdata[5] ; 
		  
		
      
		  gctl_t.manual_turn_off_ptc_flag = 0;
          gpro_t.set_temperature_value_success=1;
	

	       gpro_t.gTimer_set_temp_value=20;
	       
		   Disp_SetTemp_Value(gctl_t.gSet_temperature_value);
		   
           if(gpro_t.tencent_link_success==1){
		    MqttData_Publis_SetTemp(gctl_t.gSet_temperature_value);
            osDelay(300);
           	}
            
       
         }
        

      break;

   

      case 0x1C: //表示时间：小时，分，�?

        if(pdata[4] == 0x03){ //数据

          


        }
      break;

        case 0x1D: //表示日期�? 年，月，�?

        if(pdata[3] == 0x0F){ //数据

             
            

        }
      break;


     

     case 0x27: //AI mode 
     

        
     break;


     case 0x2B: //  timer timing .
       
         if(pdata[3]==0x0F){
	         if(pdata[4]==0x01){
			 	if(pdata[5]>0){
                gpro_t.set_timer_timing_hours = pdata[5];
	            gkey_t.key_mode = disp_timer_timing;
	           gpro_t.gTimer_timer_Counter=0;
	            gkey_t.set_timer_timing_success = 1;
	            gkey_t.gTimer_disp_set_timer = 0; 
	            gpro_t.set_timer_timing_minutes =0;
	          
	          
				dispLCD_timerTime_fun();
			 	}
				else{
				 gpro_t.set_timer_timing_hours=0;
			     gkey_t.key_mode = disp_works_timing;
			     gpro_t.gTimer_timer_Counter=0;
			     gkey_t.set_timer_timing_success = 0;
			     gkey_t.gTimer_disp_set_timer = 0; 
			     gpro_t.set_timer_timing_minutes =0;
				 dispLCD_rx_worksTime_fun();
                
}

				}
	            
	         }
         

     break;

	 case 0x6C: //works timing 
		  if(pdata[3]==0x0F){
			if(pdata[4]==0x03){
             gpro_t.disp_works_hours_value=pdata[5];
    
            gpro_t.disp_works_minutes_value = pdata[6];
		    gpro_t.gTimer_works_counter_sencods = pdata[7];
	 
			}
	      }
	 break;

	 case 0x6B://timer timing 
	    if(pdata[3]==0x0F){
	         if(pdata[4]==0x03){
			 	
                gpro_t.set_timer_timing_hours = pdata[5];
	            gpro_t.set_timer_timing_minutes =pdata[6];
	            gpro_t.gTimer_timer_Counter=pdata[7];
	    
	          }
	    	}

	 break; 

	 case 0xFF: //copy order or notice .

	 break;
        
     
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


