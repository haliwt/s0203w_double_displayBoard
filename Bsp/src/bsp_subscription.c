#include "bsp_subscription.h"
#include <string.h>
#include <stdlib.h>
#include "bsp.h"

//uint8_t  rx_tencent_num_buffer[40];
uint8_t wind_total_value;

static void smartphone_app_timer_power_on_handler(void);

uint8_t rx_data_state;


/*******************************************************************************
**
*Function Name:void Publish_Data_ToCloud(void)
*Function: dy
*Input Ref: 
*Return Ref:NO
*
********************************************************************************/
void Subscriber_Data_FromCloud_Handler(void)
{
        
	     //uint8_t *device_massage;
	     uint8_t device_massage[150];

        // device_massage = (uint8_t *)malloc(128);
         wifi_t.randomName[0]=HAL_GetUIDw0();
      
         sprintf((char *)device_massage,"AT+TCMQTTSUB=\"$thing/down/property/%s/UYIJIA01-%d\",0\r\n", PRODUCT_ID, wifi_t.randomName[0]);
         HAL_UART_Transmit(&huart2, device_massage, strlen((const char *)device_massage), 0xffff); 
        /// free(device_massage);
   }
/*******************************************************************************
**
*Function Name:void Subscribe_Rx_IntHandler(void)
*Function: interrupt USART2 receive data fun
*Input Ref: 
*Return Ref:NO
*
********************************************************************************/
void Subscribe_Rx_Interrupt_Handler(void)
{
   
     switch(rx_data_state)
      {
      case 0: //#0

	  	if((usart2_dataBuf[0] == 'p') ||usart2_dataBuf[0]=='E' || usart2_dataBuf[0] =='T'){ //hex :54 - "T" -fixed
           rx_data_state=1; //=1
           wifi_t.wifi_rx_counter=0;
          }
          else{
               wifi_t.wifi_rx_counter=0;
               rx_data_state=0; 
            }
        break;

      case 1:
      
         if((usart2_dataBuf[0] == 'a')  ||usart2_dataBuf[0]=='R' || usart2_dataBuf[0] =='C'){//hex :54 - "T" -fixed
           rx_data_state=2; //=1
           wifi_t.wifi_rx_counter=0;
            }
          else{
               wifi_t.wifi_rx_counter=0;
               rx_data_state=0;
            }
            
         break;
      case 2: //#1
             if((usart2_dataBuf[0] == 'r')||usart2_dataBuf[0]=='R'||usart2_dataBuf[0] =='M')  {//hex :4B - "K" -fixed
                rx_data_state=3; //=1
                wifi_t.wifi_rx_counter=0;
             }
             else{
                rx_data_state =0;
                 wifi_t.wifi_rx_counter=0;
             }
         break;
            
        case 3:
            if((usart2_dataBuf[0] == 'a')||usart2_dataBuf[0]=='o'|| usart2_dataBuf[0] =='Q'){    //hex :4B - "K" -fixed
           rx_data_state=4; //=1
           wifi_t.wifi_rx_counter=0;
          }
         else{
          rx_data_state =0;
             wifi_t.wifi_rx_counter=0;
         }
        
        break;
        
        case 4:
            if((usart2_dataBuf[0] == 'm')  ||usart2_dataBuf[0]=='R'|| usart2_dataBuf[0] =='T'){  //hex :4B - "K" -fixed
           rx_data_state=5; //=1
            wifi_t.wifi_rx_counter=0;
            }
         else{
           rx_data_state =0;
             wifi_t.wifi_rx_counter=0;
         }
        
        break;

      case 5:
       if((usart2_dataBuf[0] == 's') ||usart2_dataBuf[0]==':'|| usart2_dataBuf[0] =='T'){   //hex :4B - "K" -fixed
           rx_data_state=6; //=1
           wifi_t.wifi_rx_counter=0;
        }
         else{
          rx_data_state=0;
            wifi_t.wifi_rx_counter=0;
         }
            
      break;

      
      case 6:
       if((usart2_dataBuf[0] == '"')||usart2_dataBuf[0]=='2' || usart2_dataBuf[0] =='S'){    //hex :4B - "K" -fixed
            rx_data_state=7; //=1
           wifi_t.wifi_rx_counter=0;
        }
         else{
          rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
         }
            
      break;

      case 7:
       if((usart2_dataBuf[0] == ':')||usart2_dataBuf[0]=='0' ||usart2_dataBuf[0]=='T' ){  //hex :4B - "K" -fixed
        rx_data_state=8; //=1
         wifi_t.wifi_rx_counter=0;
    	}
		else{
          rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
         }
           
      break;

       case 8:
       if((usart2_dataBuf[0] == '{') ||usart2_dataBuf[0]=='8' ||usart2_dataBuf[0]=='A' ){ //hex :4B - "K" -fixed
         if(usart2_dataBuf[0]=='8') {
            rx_data_state =11;
             wifi_t.wifi_rx_counter=0;
         }
         else if(usart2_dataBuf[0]=='A'){
            rx_data_state =12;
             wifi_t.wifi_rx_counter=0;

          }
         else{
            rx_data_state =9; //=1
            wifi_t.wifi_rx_counter=0;

            }

        }
         else{
          rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
         }

	  break;


      case 9:

       if(wifi_t.rx_data_success ==0){

            //wifi_t.wifi_data[wifi_t.wifi_rx_counter] = usart2_dataBuf[0];
            wifi_t.wifi_data_rx[wifi_t.wifi_rx_counter]= usart2_dataBuf[0];
            wifi_t.wifi_rx_counter++ ;

            if(usart2_dataBuf[0]=='}' || usart2_dataBuf[0]==0x0A) //0x7D='}', 0x0A = line feed // end
            {
                wifi_t.rx_data_success=1;
                rx_data_state=0;
                wifi_t.received_data_from_tencent_cloud = wifi_t.wifi_rx_counter;
               
             }


       }
       else{
            wifi_t.rx_data_success=0;
           rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
            wifi_t.received_data_from_tencent_cloud =0;


       }

     break;

     
      case 11:
		 gpro_t.tencent_link_success =0; 
         gpro_t.get_beijing_time_success = 0;
        rx_data_state =0;
         wifi_t.wifi_rx_counter=0;
          wifi_t.wifi_uart_rx_counter=0;

      break;

      case 12:
		if(usart2_dataBuf[0]== 'T'){   //hex :4B - "K" -fixed
        rx_data_state=13; //=1
        }
        else{
           rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
         }

      break;

	  case 13:

       if(usart2_dataBuf[0]== 'E'){   //hex :4B - "K" -fixed
         rx_data_state=14; //=1
        }
        else{
            rx_data_state =0;
             wifi_t.wifi_rx_counter=0;
         }

      break;

	  case 14:
		if(usart2_dataBuf[0]== ':'){   //hex :4B - "K" -fixed
         rx_data_state=15; //=1
         }
         else{
            rx_data_state =0;
             wifi_t.wifi_rx_counter=0;
         }

      break;

	  case 15:
		if(usart2_dataBuf[0]== '0'){   //hex :4B - "K" -fixed
            gpro_t.tencent_link_success = 0;//wifi_t.esp8266_login_cloud_success =0;
            gpro_t.get_beijing_time_success = 0;
           rx_data_state =0;
            wifi_t.wifi_rx_counter=0;
            wifi_t.wifi_uart_rx_counter=0;
        }
        else if(usart2_dataBuf[0]== '1'){

            gpro_t.tencent_link_success = 1;//net_t.esp8266_login_cloud_success =1;
       
            rx_data_state =0;
             wifi_t.wifi_rx_counter=0;
             wifi_t.wifi_uart_rx_counter=0;
        }
        else{

          rx_data_state =0;
           wifi_t.wifi_rx_counter=0;


        }

      break;

	

	  default:
      break;
      }
    
    
  
}
	
   

  
/*******************************************************************************
    **
    *Function Name:void Tencent_Cloud_Rx_Handler(void)
    *Function: 
    *Input Ref: +TCMQTTCONN:OK
    *Return Ref:NO
    *
********************************************************************************/


/*******************************************************************************
    **
    *Function Name:void Tencent_Cloud_Rx_Handler(void)
    *Function: 
    *Input Ref: +TCMQTTCONN:OK
    *Return Ref:NO
    *
********************************************************************************/
void Tencent_Cloud_Rx_Handler(void)
{
    if(wifi_t.rx_data_success==1){
        
       wifi_t.rx_data_success=0;
       wifi_t.wifi_rx_counter=0;
 
       wifi_t.gTimer_auto_detected_net_state_times=0;
	
     if(wifi_t.received_data_from_tencent_cloud > 22){ //36
	    wifi_t.received_data_from_tencent_cloud=0;
		
		wifi_t.get_rx_beijing_time_enable=0; //enable beijing times
		wifi_t.response_wifi_signal_label = APP_TIMER_POWER_ON_REF;
	    __HAL_UART_CLEAR_OREFLAG(&huart2);
		//strcpy((char*)TCMQTTRCVPUB,(char *)wifi_t.data,40);
   
     }
     else{

   
       if(strstr((char *)wifi_t.wifi_data_rx,"open\":0")){
    		  wifi_t.response_wifi_signal_label = OPEN_OFF_ITEM;
            
    		 
    	}
    	else if(strstr((char *)wifi_t.wifi_data_rx,"open\":1")){
    	   
    	   wifi_t.response_wifi_signal_label = OPEN_ON_ITEM;
             
    	}

 
 
    	
       if(strstr((char *) wifi_t.wifi_data_rx,"ptc\":0")){
                if(power_on_state() ==power_on){
    			   
    	           wifi_t.response_wifi_signal_label = PTC_OFF_ITEM;
    	         
                 }
             
    			
        }
        else if(strstr((char *) wifi_t.wifi_data_rx,"ptc\":1")){
                if(power_on_state() ==power_on){
    	     
    			  wifi_t.response_wifi_signal_label = PTC_ON_ITEM;
    				
                }
             
        }

 

    if(strstr((char *)wifi_t.wifi_data_rx,"Anion\":0")){
          if(power_on_state() ==power_on){
	      //   gctl_t.plasma_flag=0;
			wifi_t.response_wifi_signal_label = ANION_OFF_ITEM;
		    
             }
        
		 
    }
    else if(strstr((char *)wifi_t.wifi_data_rx,"Anion\":1")){
            if(power_on_state() ==power_on){
         //   gctl_t.plasma_flag=1;
			wifi_t.response_wifi_signal_label = ANION_ON_ITEM;
		
            }
      }
    
	
    if(strstr((char *)wifi_t.wifi_data_rx,"sonic\":0")){
            if(power_on_state() ==power_on){
           // gctl_t.ultrasonic_flag=0;
			wifi_t.response_wifi_signal_label = SONIC_OFF_ITEM;
        
                
            }
    }
    else if(strstr((char *)wifi_t.wifi_data_rx,"sonic\":1")){
            if(power_on_state() ==power_on){
          //  gctl_t.ultrasonic_flag=1;
			wifi_t.response_wifi_signal_label = SONIC_ON_ITEM;
       
           }
    }

    
     if(strstr((char *)wifi_t.wifi_data_rx,"state\":1")){
           if(power_on_state() ==power_on){
           
            
			wifi_t.response_wifi_signal_label = STATE_AI_MODEL_ITEM;
        	}

         
		  
    }
    else if(strstr((char *)wifi_t.wifi_data_rx,"state\":2")){
            if(power_on_state() ==power_on){
        
			wifi_t.response_wifi_signal_label = STATE_TIMER_MODEL_ITEM;
            }


        
			
    }

       if(strstr((char *)wifi_t.wifi_data_rx,"find")){

		 if(power_on_state()==power_on){
         
			wifi_t.response_wifi_signal_label= FAN_ITEM;
		}

        }


   

       
      if(strstr((char *)wifi_t.wifi_data_rx,"find")){

		 if(power_on_state()==power_on){
            
			wifi_t.response_wifi_signal_label= FAN_ITEM;
		}

        }


  
	
   
   if(strstr((char *)wifi_t.wifi_data_rx,"temperature")){

	        if(power_on_state() ==power_on){

			wifi_t.response_wifi_signal_label = TEMPERATURE_ITEM;
            
	        }
      

      
    }
  
   
  
     }
  
 
    }
 }

/****************************************************************************
**
   *Function Name:void JsonParse_Tencent_Cmd_Handler(void)
   *Function: parse setment of wifi receive data from tencent 
   *Input Ref: NO
   *Return Ref:NO
   *

*****************************************************************************/
void JsonParse_Tencent_Cmd_Handler(void)
{

 //   uint8_t i;
    static uint8_t wind_hundred, wind_decade,wind_unit,temp_decade,temp_unit;
	
  while(wifi_t.response_wifi_signal_label != 0xff && wifi_t.response_wifi_signal_label !=0 && wifi_t.response_wifi_signal_label !=0xf0){

   switch(wifi_t.response_wifi_signal_label){
       
	case OPEN_OFF_ITEM:

       gpro_t.wifi_power_on_normal_flag=2;
       gkey_t.key_power = power_off; //WT.EDIT 2024.02.20
        MqttData_Publish_SetOpen(0);  
        HAL_Delay(350);//350

        gpro_t.tencent_link_success=1;
      
        gkey_t.power_key_long_counter=0;
        wifi_t.smartphone_app_power_on_flag=0;
        buzzer_sound();
         gpro_t.power_off_flag =1;
         SendData_Set_Command(0x01, 0x00); //power off command
        wifi_t.gTimer_auto_detected_net_state_times=0; //don't need check wifi if has or not
        wifi_t.response_wifi_signal_label = 0xff;
        
	  break;

	  case OPEN_ON_ITEM:
       gpro_t.wifi_power_on_normal_flag=1;
	   gkey_t.key_power = power_on; 
	 
	   //  gkey_t.power_key_long_counter=1;
		gpro_t.tencent_link_success=1;
		MqttData_Publish_SetOpen(1);  
		HAL_Delay(200);//300
        buzzer_sound();
        // gkey_t.key_power = power_on;
        SendData_Set_Command(0x01, 0x01); //power on comman
        osDelay(5);
        //smartphone_turn_on_handler();
      

		gctl_t.ptc_warning =0;
		gctl_t.fan_warning =0;
		
		wifi_t.gTimer_auto_detected_net_state_times=0;//don't need check wifi if has or not
		wifi_t.response_wifi_signal_label = 0xff;

	  break;

	  case PTC_ON_ITEM:
	  if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){

         //gpro_t.gTimer_shut_off_backlight =0;
         //wake_up_backlight_on();
         
	    if(ptc_error_state() ==0){
			 gctl_t.manual_turn_off_ptc_flag= 0;
	         Ptc_On();
             gctl_t.ptc_flag=1;
             Disp_Dry_Icon();
             MqttData_Publish_SetPtc(0x01);
             osDelay(100);//HAL_Delay(350);//350ms
            
             SendData_Set_Command(0x02, 0x01); //ptc turn on command
             osDelay(5);
			 Buzzer_KeySound();//buzzer_sound()	;
        }
		
          
		 wifi_t.gTimer_auto_detected_net_state_times=0;//don't need check wifi if has or not
         wifi_t.response_wifi_signal_label=0xff;
         gpro_t.linking_tencent_cloud_doing =0;
	  	}
	    
	   break;

	  case PTC_OFF_ITEM:
	  	if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
		
		 gpro_t.gTimer_shut_off_backlight =0;
         //wake_up_backlight_on();
         MqttData_Publish_SetPtc(0);
		 osDelay(100);//HAL_Delay(350);

		
		 Ptc_Off();
		 gctl_t.ptc_flag=0;
         Disp_Dry_Icon();
         
         gctl_t.manual_turn_off_ptc_flag= 1;
         
        SendData_Set_Command(0x02, 0x0); //ptc turn off command
	    osDelay(5);
	    Buzzer_KeySound();//buzzer_sound()	;
	    
		

		wifi_t.response_wifi_signal_label = 0xff;
		wifi_t.gTimer_auto_detected_net_state_times=0;
		gpro_t.linking_tencent_cloud_doing =0;


	  	}
	  	break;

	  case ANION_OFF_ITEM: //"杀菌" //5
	  	if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
		     gpro_t.gTimer_shut_off_backlight =0;
             wake_up_backlight_on();
		    Plasma_Off();
	    
			
            MqttData_Publish_SetPlasma(0);
			osDelay(100);//HAL_Delay(200);
           gctl_t.plasma_flag=0;
           Disp_Kill_Icon();

           
            SendData_Set_Command(0x03, 0x00); //plasma turn off command
            osDelay(5);
            Buzzer_KeySound();
           
		  
		}
        wifi_t.gTimer_auto_detected_net_state_times=0;
		gpro_t.linking_tencent_cloud_doing =0;
       wifi_t.response_wifi_signal_label = 0xff;
		
	   break;
		
	  case ANION_ON_ITEM: //plasma 
	  	if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
			gpro_t.gTimer_shut_off_backlight =0;
            wake_up_backlight_on();
			Plasma_On();
	  
            MqttData_Publish_SetPlasma(1);
		    osDelay(50);//HAL_Delay(200);
           gctl_t.plasma_flag=1;
            Disp_Kill_Icon();

            SendData_Set_Command(0x03, 0x01); //plasma turn on command
            osDelay(5);
            Buzzer_KeySound();
		   
			}
        wifi_t.gTimer_auto_detected_net_state_times=0;
       gpro_t.linking_tencent_cloud_doing =0;
	   wifi_t.response_wifi_signal_label=0xff;
	    break;

	  case SONIC_OFF_ITEM://ultransonic off
        if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
            gpro_t.gTimer_shut_off_backlight =0;
            wake_up_backlight_on();
			Ultrasonic_Pwm_Stop();
	    
            MqttData_Publish_SetUltrasonic(0);
			osDelay(50);//HAL_Delay(200);
            gctl_t.ultrasonic_flag=0;
             Disp_Ultrsonic_Icon();

            SendData_Set_Command(0x04, 0x0); //ultrasonic turn off command
            osDelay(5);
             Buzzer_KeySound();
            
		}
        wifi_t.gTimer_auto_detected_net_state_times=0;
	     wifi_t.response_wifi_signal_label=0xff;
		
		 gpro_t.linking_tencent_cloud_doing =0;
	  	break;

	  case SONIC_ON_ITEM://ultransonic on
	    if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
			
			gpro_t.gTimer_shut_off_backlight =0;
            wake_up_backlight_on();
			Ultrasonic_Pwm_Output();
            MqttData_Publish_SetUltrasonic(1);
			HAL_Delay(200);
          
            gctl_t.ultrasonic_flag=1;
            Disp_Ultrsonic_Icon();

           SendData_Set_Command(0x04, 0x01); //ultrasonic turn on  command
             buzzer_sound();
            //send data to the second display board
           
		}
       wifi_t.gTimer_auto_detected_net_state_times=0;
	   wifi_t.response_wifi_signal_label=0xff;
	  
        gpro_t.linking_tencent_cloud_doing =0;
	  	break;

	  case STATE_TIMER_MODEL_ITEM: //display timer timing of value  
	  if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
	  	    buzzer_sound();
            gpro_t.gTimer_shut_off_backlight =0;
             wake_up_backlight_on();
	       
	        gkey_t.key_mode=disp_timer_timing;
            gctl_t.ai_flag = 0 ; //timer model


            LCD_Disp_Timer_Timing_Init();

           MqttData_Publish_SetState(2); //timer model  = 2, works model = 1
			HAL_Delay(200);
            //do someting disp timer timing value 
            SendData_Set_Command(0x27, 0x02); //AI turn off command
           
            
		
			
        }
       wifi_t.gTimer_auto_detected_net_state_times=0;
	   wifi_t.response_wifi_signal_label = 0xff;
	
	   
	  break;
		
	  case STATE_AI_MODEL_ITEM: //display works timing 
	  	 if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){

            gpro_t.gTimer_shut_off_backlight =0;
             wake_up_backlight_on();
		    buzzer_sound();
		    gkey_t.key_mode=disp_works_timing;
            gctl_t.ai_flag = 1;//AI mode

         
            LCD_Disp_Works_Timing_Init();

           

           
            MqttData_Publish_SetState(1); //beijing timing = 1
			HAL_Delay(200);

            SendData_Set_Command(0x27, 0x01); //AI turn on command

           
			
          
        }
       wifi_t.gTimer_auto_detected_net_state_times=0;

	   wifi_t.response_wifi_signal_label = 0xff;
		
		  
			 gpro_t.linking_tencent_cloud_doing =0;
	  	break;

	  case TEMPERATURE_ITEM:
	   if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){

             gpro_t.gTimer_shut_off_backlight =0;
             wake_up_backlight_on();

             gctl_t.manual_turn_off_ptc_flag= 0; //only  manual turn on flag is zero can be changed .
			 gpro_t.gTimer_run_dht11=0;  // don't display sensor of temperature value 
             gpro_t.gTImer_send_disp_board =0;

             temp_decade=wifi_t.wifi_data_rx[14]-0x30; //
             temp_unit=wifi_t.wifi_data_rx[15]-0x30;
             
            gctl_t.gSet_temperature_value = temp_decade*10 +  temp_unit;
            
            if(gctl_t.gSet_temperature_value > 40)   gctl_t.gSet_temperature_value=40;
            if(gctl_t.gSet_temperature_value <20 )   gctl_t.gSet_temperature_value=20;
            
            
            MqttData_Publis_SetTemp(gctl_t.gSet_temperature_value);
			osDelay(20);//HAL_Delay(200);//350
		

           
         //   gkey_t.key_add_dec_mode = set_temp_value_item; //set_temp_value_item;
           
            gpro_t.smart_phone_set_tmep_value_flag = 1;//gpro_t.set_temperature_value_success =1;
        
           gpro_t.gTimer_run_dht11=0; 
           wifi_t.gTimer_auto_detected_net_state_times=0;
           gpro_t.gTimer_set_temp_temp = 5;
          
         
            Disp_SetTemp_Value(gctl_t.gSet_temperature_value);
            //send data to the second display board
          //  gkey_t.set_temp_value_be_pressed = 1 ;

           sendData_setTemp_value(gctl_t.gSet_temperature_value); //smart phone set temperature value .
           gpro_t.gTimer_run_dht11=0; 
	
         
		    buzzer_sound();
		}
      wifi_t.response_wifi_signal_label = 0xff;
	 
	  wifi_t.gTimer_auto_detected_net_state_times=0;	
	  gpro_t.linking_tencent_cloud_doing =0;
	  break;

	  case FAN_ITEM:
	    if(power_on_state() ==power_on && ptc_error_state()==0 && fan_error_state()==0){
			buzzer_sound();
            gpro_t.gTimer_shut_off_backlight =0;
             wake_up_backlight_on();

		     if(gctl_t.fan_warning ==0){
                 
           		     wind_hundred =wifi_t.wifi_data_rx[7]-0x30;
                 
                     wind_decade=wifi_t.wifi_data_rx[8]-0x30;
                     wind_unit = wifi_t.wifi_data_rx[9]-0x30;
                     
                   
                   if(wind_hundred ==1 && wind_decade==0 && wind_unit==0) wind_total_value=100;
                   else
                      wind_total_value = wind_hundred*10 + wind_decade;

                  MqttData_Publis_SetFan(wind_total_value);
                   osDelay(100);//HAL_Delay(50);//

                    if(wind_total_value < 34 ){

                         wifi_t.set_wind_speed_value=2;
                        

                     }
                     else if(wind_total_value> 33 && wind_total_value < 67){
                         wifi_t.set_wind_speed_value=1;
                         

                     }
                     else{

                        wifi_t.set_wind_speed_value=0;
                        

                     }
                }
                else{

                  wifi_t.set_wind_speed_value=0;
   
                  MqttData_Publis_SetFan(wifi_t.set_wind_speed_value);
                  osDelay(100);//HAL_Delay(50);
                  //do seomthing 
                   
                }
              
               
           }
   
        
	      wifi_t.gTimer_auto_detected_net_state_times=0;
	      wifi_t.response_wifi_signal_label = 0xff;
         gpro_t.linking_tencent_cloud_doing =0;
	  	break;

	  case APP_TIMER_POWER_ON_REF :

	
		 //gpro_t.gTimer_shut_off_backlight =0;
          //wake_up_backlight_on();
		
		   wifi_t.get_rx_beijing_time_enable=0; //enable beijing times
          
		   smartphone_app_timer_power_on_handler();

	      wifi_t.response_wifi_signal_label=0xff;
	
		 wifi_t.gTimer_auto_detected_net_state_times=0;
		  gpro_t.linking_tencent_cloud_doing =0;

	  break;


   }


   if(wifi_t.response_wifi_signal_label==0xff){
        
        wifi_t.response_wifi_signal_label=0xf0;
        

//		for(i=0;i<15;i++){
//		   rx_tencent_num_buffer[i]=0;
//		}
   //     memset(wifi_t.wifi_data_rx,'\0',40);
        wifi_t.wifi_data_rx[0] =0;
        wifi_t.wifi_data_rx[1] =0;
//        wifi_t.wifi_data_rx[2] =0;
//        wifi_t.wifi_data_rx[3] =0;
//        wifi_t.wifi_data_rx[4] =0;
    }
}
}


/*****************************************************************************
	*
	*Function Name:static void smartphone_app_timer_power_on_handler(void)
	*Function:
	*Inpur Ref:
	*Retern Ref:
	*
*****************************************************************************/
static void smartphone_app_timer_power_on_handler(void)
{

   static uint8_t app_step;


    if(app_step==0 ){

		app_step=1;
		if(strstr((char *)wifi_t.wifi_data_rx,"open\":1")){
		    wifi_t.smartphone_app_power_on_flag=1;
		    gkey_t.key_power=power_on;
		     wifi_t.set_wind_speed_value=0;
            
		}
        if(strstr((char *)wifi_t.wifi_data_rx,"ptc\":1")){

            gctl_t.ptc_flag=1;
		}
		else{ //if(strstr((char *)TCMQTTRCVPUB,"ptc\":0")){
         gctl_t.manual_turn_off_ptc_flag= 1;
		 gctl_t.ptc_flag=0;


		}

		if(strstr((char *)wifi_t.wifi_data_rx,"sonic\":1")){

		gctl_t.ultrasonic_flag=1;

		}
		else{// if(strstr((char *)TCMQTTRCVPUB,"sonic\":0")){

		gctl_t.ultrasonic_flag=0;

		}

		if(strstr((char *)wifi_t.wifi_data_rx,"Anion\":1")){
		gctl_t.plasma_flag=1;
		}
		else{ // if(strstr((char *)TCMQTTRCVPUB,"Anion\":0")){
		gctl_t.plasma_flag=0;
		}



		
    }
   

   

	if(app_step==1){
	  	app_step=0;
		Buzzer_KeySound();//buzzer_sound();
        #if 0
       
       MqttData_Publis_App_PowerOn_Ref();
  
		
		osDelay(200);//HAL_Delay(50);//

        SendWifiData_Ref_three(gctl_t.ptc_flag,gctl_t.plasma_flag,gctl_t.ultrasonic_flag);
		osDelay(100);//HAL_Delay(50);//
		#endif 
		//smartphone_turn_on_handler();
        
   
	

	  memset(wifi_t.wifi_data_rx,'\0',40);

	}


    
}
      
/*******************************************************************************
**
*Function Name:void Subscribe_Rx_IntHandler(void)
*Function: interrupt USART2 receive data fun
*Input Ref: +TCMQTTCONN:OK
*Return Ref:NO
*
********************************************************************************/
void Wifi_Rx_Link_Net_InputInfo_Handler(void)
{

    if(strstr((const char*)wifi_t.wifi_data,"+TCSAP:WIFI_CONNECT_SUCCESS")){
        wifi_t.soft_ap_config_success=1;

    }
    
    if(strstr((const char*)wifi_t.wifi_data,"+TCMQTTCONN:OK")){
        gpro_t.tencent_link_success =1;
        gpro_t.linking_tencent_cloud_doing=0;
        gkey_t.wifi_led_fast_blink_flag =0;

        wifi_t.gTimer_auto_detected_net_state_times=0;
        wifi_t.soft_ap_config_flag=0;
    }
    else if(strstr((char*)wifi_t.wifi_data,"+CME ERROR:208")){

        gpro_t.linking_tencent_cloud_doing=0; //release this flag. usart
        //wifi_t.esp8266_login_cloud_success =0;
        gpro_t.tencent_link_success=0;



        wifi_t.get_rx_beijing_time_enable=0;
        gkey_t.wifi_led_fast_blink_flag =0;
    }
    else if(strstr((char*)wifi_t.wifi_data,"+TCPRDINFOSET:1,\"EHQB1P53IH\"")){ //WT.EDIT 2024.07.22

    // wifi_t.serch_for_wifi_flag=1;
    //  wifi_t.gTime_link_time_start =0;

    }
    else  if(strstr((char*)wifi_t.wifi_data,"+TCMQTTCONN:FAIL,202")){

        //  wifi_t.esp8266_login_cloud_success =0;
        gpro_t.tencent_link_success=0;
   

        //gpro_t.linking_tencent_cloud_doing=1; //release this flag. usart
        gpro_t.linking_tencent_cloud_doing=0;
        wifi_t.get_rx_beijing_time_enable=0;
        gkey_t.wifi_led_fast_blink_flag =0;
    }
    else if(strstr((const char*)wifi_t.wifi_data,"+TCMQTTCONN:OK")){
            gpro_t.tencent_link_success=1;
            gpro_t.linking_tencent_cloud_doing=0;
            wifi_t.gTimer_auto_detected_net_state_times=0;
            gkey_t.wifi_led_fast_blink_flag =0;
			wifi_t.get_rx_beijing_time_enable=0;//WT.EDIT 2025.06.12

            wifi_t.soft_ap_config_flag=0;
    }
    else if(strstr((char*)wifi_t.wifi_data,"+CME ERROR:208")){


        gpro_t.tencent_link_success=0;//wifi_t.esp8266_login_cloud_success =0;
        gpro_t.linking_tencent_cloud_doing=1;//gpro_t.linking_tencent_cloud_doing=1; //release this flag. usart
        wifi_t.get_rx_beijing_time_enable=0;
        gkey_t.wifi_led_fast_blink_flag =0;

    }
    else if(strstr((char*)wifi_t.wifi_data,"+TCMQTTCONN:FAIL,202")){

        gpro_t.tencent_link_success=0; //wifi_t.esp8266_login_cloud_success =0;


        gpro_t.linking_tencent_cloud_doing=1;//gpro_t.linking_tencent_cloud_doing=1; //release this flag. usart

        wifi_t.get_rx_beijing_time_enable=0;
        gkey_t.wifi_led_fast_blink_flag =0;
    }
    else if(strstr((char*)wifi_t.wifi_data,"+TCMQTTDISCON")){

        gpro_t.tencent_link_success=0;//wifi_t.esp8266_login_cloud_success =0;
        wifi_t.get_rx_beijing_time_enable=0;
        gpro_t.linking_tencent_cloud_doing=1;//gpro_t.linking_tencent_cloud_doing=1; //release this flag. usart
        gkey_t.wifi_led_fast_blink_flag =0;
    }
    else if(strstr((char*)wifi_t.wifi_data,"+TCSAP:WIFI_CONNECT_FAILED")){

            gpro_t.tencent_link_success=0;//wifi_t.esp8266_login_cloud_success =0;
            wifi_t.get_rx_beijing_time_enable=0;
            gpro_t.linking_tencent_cloud_doing=1;//gpro_t.linking_tencent_cloud_doing=1; //release this flag. usart
            gkey_t.wifi_led_fast_blink_flag =0;


    }
  
    wifi_t.wifi_uart_rx_counter=0;
    wifi_t.once_rx_data_done = 1;    
}



void clear_rx_copy_data(void)
{
   //uint8_t i;
   #if 0
   if( wifi_t.once_rx_data_done == 1 && wifi_link_net_state() == 0){

      wifi_t.once_rx_data_done ++;

      for(i=0;i<150;i++){
        
       wifi_t.wifi_data[i]=0;
      // wifi_t.auto_det_data[i]=0;
      }
    }
   #endif 
   if( wifi_t.once_rx_data_done == 1){
      wifi_t.once_rx_data_done ++; //WT.EDIT 2024.08.17
      memset(wifi_t.wifi_data,'\0',150);
    }
}


