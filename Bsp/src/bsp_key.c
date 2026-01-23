#include "bsp_key.h"
#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"




key_fun_t gkey_t;




uint8_t set_timer_blink_counter;


//// 读取KEY_POWER引脚状态
//uint8_t Read_KEY_POWER(void)
//{
//    // 假设KEY_POWER连接到GPIOA的某个引脚
//    // 实际使用时需要根据具体连接修改
    
//    // 方法1：直接使用端口输入数据寄存器
//    return (KEY_POWER_GPIO_Port->IDR & KEY_POWER_Pin) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    
//    // 或者更简洁的写法：
//    // return (GPIOA->IDR & KEY_POWER_Pin) >> (KEY_POWER_Pin_Pos);
//}


/************************************************************************************
	*
	*Funtion Name:void key_handler(void)
	*Function:
	*Input Ref:
	*Return Ref:
	*
************************************************************************************/
void key_handler(void)
{
	if(KEY_POWER_VALUE() == KEY_DOWN ){
       key_power_long_handler();

	}	
	if(KEY_MODE_VALUE() == KEY_DOWN && gkey_t.key_power==power_on){

       key_mode_long_handler();
	}
	else if(KEY_DEC_VALUE()==KEY_DOWN && gkey_t.key_power==power_on){

          gkey_t.key_dec_flag =1;


    }
	else if(KEY_ADD_VALUE()==KEY_DOWN && gkey_t.key_power==power_on ){
		
           gkey_t.key_add_flag =1;



	}

	if(gkey_t.key_mode_flag== 1 && KEY_MODE_VALUE() == KEY_UP){

		key_mode_short_handler();
	}
	else if(gkey_t.key_add_flag == 1 && KEY_ADD_VALUE()== KEY_UP){
		gkey_t.key_add_flag++;
		Buzzer_KeySound();

		Add_Key_Fun(gkey_t.key_add_dec_mode);

	}
	else if(gkey_t.key_dec_flag == 1 && KEY_DEC_VALUE()== KEY_UP){
			gkey_t.key_dec_flag++;
			Buzzer_KeySound();
					  

			Dec_Key_Fun(gkey_t.key_add_dec_mode);

	}
	


}

/************************************************************************************
	*
	*Funtion Name:void key_power_long_handler(void)
	*Function:
	*Input Ref:
	*Return Ref:
	*
************************************************************************************/
void key_power_long_handler(void)
{

  //  static uint8_t power_onoff_flag;
    if(KEY_POWER_VALUE() == KEY_DOWN ){
		
		gkey_t.power_on_flag=1;

        if(gkey_t.power_key_long_counter < 180 && gkey_t.key_power==power_on &&  gctl_t.fan_warning==0 &&  gctl_t.ptc_warning==0){
			gkey_t.power_key_long_counter++;
        
        
        if(gkey_t.power_key_long_counter > 50 ){
             gkey_t.power_key_long_counter = 200;
             
            // gkey_t.power_on_flag++; 
         
          
             	//WIFI CONNCETOR process
			 gkey_t.wifi_led_fast_blink_flag=1;
             gpro_t.link_net_step=0;
			 //WIFI CONNCETOR process
			gpro_t.tencent_link_success =0;
			gpro_t.get_beijing_time_success =0;
			
		    wifi_t.gTimer_linking_tencent_duration=0; //120s
		    SendData_Set_Command(0X05,0X01);
             osDelay(50);

            Buzzer_KeySound();
			
            
         }

        }
    }

}
/************************************************************************************
	*
	*Funtion Name:void key_power_shot_handler(void)
	*Function:
	*Input Ref:
	*Return Ref:
	*
************************************************************************************/
void key_power_shot_handler(void)
{
	
    if(KEY_POWER_VALUE() == KEY_UP && gkey_t.power_on_flag==1 && gkey_t.power_key_long_counter !=200){ //short key of function

        gkey_t.power_key_long_counter=0;

      
           if(gkey_t.key_power==power_off){
              
             gkey_t.power_on_flag++; 
          
              gkey_t.key_power=power_on;
        
			   gpro_t.disp_power_on_flag =0xff;
			   gpro_t.wifi_power_on_normal_flag=0xff;
               
              gctl_t.step_process=0;
              gpro_t.power_off_flag =1;
			
			   Buzzer_KeySound();
               SendData_Set_Command(0X01,0X01);
               osDelay(100);
			   power_on_init_function();
         
               
            }
           else{
               Buzzer_KeySound();
              gkey_t.power_on_flag++;
            
              gkey_t.key_power=power_off;
			  gpro_t.disp_power_on_flag=0;
              gctl_t.step_process=0;
              
              power_off_init_function();
  
			 SendData_Set_Command(0X01,0X0);
              osDelay(100);

           }
         
       
      

        }
	    else if(KEY_POWER_VALUE() == KEY_UP && gkey_t.power_on_flag==1 && gkey_t.power_key_long_counter==200 ){
		   gkey_t.power_on_flag++; 

		   gkey_t.power_key_long_counter =0;


		}
//		else if(KEY_POWER_VALUE() == KEY_UP && gkey_t.power_key_long_counter < 60 &&  power_onoff_flag==1){
//
//
//		    gkey_t.power_on_flag++; 
//
//
//
//		}
			
}
/*********************************************************************************
*
*	�? �? �?:void smartphone_power_on_handler(uint8_t phone_on)
*	功能说明: 
*	�?    �?: 
*	�? �? �?: �?
*   
*********************************************************************************/
void smartphone_power_on_handler(void)
{

      
      gkey_t.power_key_long_counter=0;

      gkey_t.key_power=power_on;
      gkey_t.key_mode = disp_timer_timing;
       gctl_t.ai_flag = 1;
       gctl_t.ptc_warning =0;
       gctl_t.fan_warning =0;
      
        gctl_t.step_process=0;
        gpro_t.power_off_flag =1;
   


}
/*********************************************************************************
*
*	�? �? �?:static void mode_long_short_key_fun(void)
*	功能说明: 
*	�?    �?: 
*	�? �? �?: �?
*   
*********************************************************************************/
void key_mode_long_handler(void)
{

      gkey_t.key_mode_flag=1;
	if(KEY_MODE_VALUE() == KEY_DOWN && gkey_t.key_mode_long_counter < 100  &&  gctl_t.fan_warning==0 &&  gctl_t.ptc_warning==0){


        gkey_t.key_mode_long_counter++;
        if(gkey_t.key_mode_long_counter >  50 ){
            gkey_t.key_mode_long_counter = 150;
           
            gkey_t.key_mode_shot_flag = 0;
            gkey_t.key_mode = mode_set_timer;
           gkey_t.key_add_dec_mode = mode_set_timer;
           gctl_t.ai_flag = 0; //timer tiiming model
           gkey_t.gTimer_disp_set_timer = 0;       //counter exit timing this "mode_set_timer"
           
           Buzzer_KeySound();//buzzer_sound();
          
		 
          }

    }
}
/************************************************************************************
	*
	*Funtion Name:void key_power_shot_handler(void)
	*Function:
	*Input Ref:
	*Return Ref:
	*
************************************************************************************/
void key_mode_short_handler(void)
{
    

   if(KEY_MODE_VALUE() == KEY_UP && gkey_t.key_mode_flag==1 && gctl_t.fan_warning==0 &&  gctl_t.ptc_warning==0\
   	  && gkey_t.key_mode_long_counter != 150){ //short key of function

        gkey_t.key_mode_long_counter=0;
        gkey_t.key_mode_flag++;

		 if(gctl_t.ai_flag ==1){
                  gpro_t.receive_disp_mode = disp_timer_timing;//gkey_t.key_mode=disp_timer_timing;
				  gpro_t.gTimer_disp_short_time =0;
		         gctl_t.ai_flag = 0;
				 donot_disp_ai_symbol();

				 dispLCD_timerTime_fun();

				  gkey_t.key_mode = disp_timer_timing;

			  
		      }
			  else if(gctl_t.ai_flag==0){ //display don't AI MODE ,disp_works_item
			  	 
				  gpro_t.receive_disp_mode= disp_works_timing ;//gkey_t.key_mode=disp_works_timing;
				  gpro_t.gTimer_disp_short_time =0;

				   dispLCD_worksTime_fun();
				   gkey_t.key_mode = disp_works_timing;
				  }

			  
                  Buzzer_KeySound();
			   
		#if 0
     
         if(gkey_t.key_mode  == disp_works_timing){
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
            Buzzer_KeySound();
			SendData_Set_Command(0x07,0x02); //timer timing.
            osDelay(5);//HAL_Delay(10);

        }
        else{
			 gkey_t.key_mode_shot_flag = 1;
			 gctl_t.ai_flag = 1;
            gkey_t.key_mode_switch_flag = 1;
            gkey_t.key_mode  = disp_works_timing;
            gkey_t.key_add_dec_mode = disp_works_timing;

            //gkey_t.key_mode_be_pressed = 1;
			//g_tDisp.ai_mode_flag =1; //WT.EDIT 2025.06.07
            gpro_t.gTimer_disp_short_time=0;

			LCD_Disp_Works_Timing_Init();
            disp_ai_iocn();
            Buzzer_KeySound();
			SendData_Set_Command(0x07,0x01); 
            osDelay(5);//HAL_Delay(10);
         }

         #endif 
     }
     if(KEY_MODE_VALUE() == KEY_UP && gkey_t.key_mode_flag==1 && gctl_t.fan_warning==0 &&  gctl_t.ptc_warning==0\
	 	&& gkey_t.key_mode_long_counter == 150){

	     gkey_t.key_mode_long_counter=0;
		 gkey_t.key_mode_flag++;


     }


 }

void  key_mode_be_pressed_send_data_wifi(void)
{
   #if 0
   if(gkey_t.key_mode_be_pressed == 1){   // && gpro_t.tencent_link_success==1){

         gkey_t.key_mode_be_pressed= 0xff;

        SendData_Set_Command(0x27,0x01); 
        osDelay(5);//HAL_Delay(10);

             gctl_t.ai_flag = 1; // AI DISPLAY AI ICON

           
            LCD_Disp_Works_Timing_Init();
            disp_ai_iocn();
   
       
        if(gpro_t.tencent_link_success==1){
            MqttData_Publish_AiState(1); //timer model  = 2, works model = 1
            osDelay(20);

        }
     }
     else if(gkey_t.key_mode_be_pressed == 2 ){  // && gpro_t.tencent_link_success==1){
            gkey_t.key_mode_be_pressed= 0xff;

          SendData_Set_Command(0x27,0x02); //timer timing.
          osDelay(5);//HAL_Delay(10);

           gctl_t.ai_flag = 0; // NOT AI DISPLAY AI ICON    
           LCD_Disp_Timer_Timing_Init();
           disp_ai_iocn();
   
         if(gpro_t.tencent_link_success==1){

           MqttData_Publish_AiState(2); //timer model  = 2, works model = 1
           osDelay(20);
          }
       }
   #endif 

}


/***************************************************************************
    *
    *Function Name:void Dec_Key_Fun(uint8_t cmd)
    *Function : key down function 
    *Input Ref: run cmd
    *Return Ref : NO
    *
***************************************************************************/
void Dec_Key_Fun(uint8_t cmd)
{

  switch(cmd){

	     case disp_works_timing:

         case set_temp_value_item: //set temperature 

			gkey_t.set_temp_value_be_pressed =1;
			gpro_t.gTimer_set_temp_temp=0;

            gpro_t.gTimer_run_main_fun =0;
            gpro_t.gTimer_run_dht11=0; //不显示设置的温度
             
            gctl_t.gSet_temperature_value  --;
    		if( gctl_t.gSet_temperature_value  <20)gctl_t.gSet_temperature_value  =20;
    	    

    
    				
    	    glcd_t.number3_low =  gctl_t.gSet_temperature_value   / 10 ;
            glcd_t.number3_high = glcd_t.number3_low;// gctl_t.gSet_temperature_value   / 10 ;
    	    glcd_t.number4_low  = gctl_t.gSet_temperature_value   % 10; //
            glcd_t.number4_high = glcd_t.number4_low; //gctl_t.gSet_temperature_value   % 10; //

			 LCD_Number_ThreeFour_Temperature();

            
           
         break;

         case mode_set_timer: //set timer timing value 
             
            
              gkey_t.gTimer_disp_set_timer = 0; 

              gpro_t.set_timer_timing_minutes =0;

              gpro_t.set_timer_timing_hours -- ;//run_t.dispTime_minutes = run_t.dispTime_minutes - 1;
    		  if(gpro_t.set_timer_timing_hours < 0){//if(run_t.dispTime_minutes < 0){

    			 gpro_t.set_timer_timing_hours =24;//run_t.dispTime_hours --;
    				
    		  }
             //Set_Timer_Timing_Lcd_Blink();

			   glcd_t.number5_high = gpro_t.set_timer_timing_hours /10;
			   glcd_t.number5_low =  gpro_t.set_timer_timing_hours /10;

			   glcd_t.number6_high= gpro_t.set_timer_timing_hours %10;
                glcd_t.number6_low= gpro_t.set_timer_timing_hours %10;

                   //dispaly minutes 
			      glcd_t.number7_low =  0;
			      glcd_t.number7_high =  0;

			      glcd_t.number8_low = 0;
			      glcd_t.number8_high =   0;
			   
               gkey_t.add_dec_key_be_pressed=1;
                LCD_Number_FiveSix_Hours();

         break;
 
         }
}

/***************************************************************************
    *
    *Function Name:void Dec_Key_Fun(uint8_t cmd)
    *Function : key down function 
    *Input Ref: run cmd
    *Return Ref : NO
    *
***************************************************************************/
void Add_Key_Fun(uint8_t cmd)
{

 
   switch(cmd){
        
   case disp_works_timing:

	case set_temp_value_item:  //set temperature value 

         gkey_t.set_temp_value_be_pressed = 1;
        gpro_t.gTimer_set_temp_temp=0;
     
         gpro_t.gTimer_run_main_fun=0;
         gpro_t.gTimer_run_dht11=0;
        gctl_t.gSet_temperature_value   ++;
        if(gctl_t.gSet_temperature_value   < 20){
            gctl_t.gSet_temperature_value  =20;
        }

        if(gctl_t.gSet_temperature_value   > 40)gctl_t.gSet_temperature_value  = 40;

        glcd_t.number3_low = gctl_t.gSet_temperature_value   / 10 ;
        glcd_t.number3_high = gctl_t.gSet_temperature_value   / 10 ;
        glcd_t.number4_low  =gctl_t.gSet_temperature_value   % 10; //
        glcd_t.number4_high = gctl_t.gSet_temperature_value  % 10; //

         LCD_Number_ThreeFour_Temperature();
    
       gpro_t.gTimer_set_temp_temp=0;
      
    break;

    case mode_set_timer: //set timer timing value 

    
    
         gkey_t.gTimer_disp_set_timer = 0; 
         gpro_t.set_timer_timing_minutes=0;
         gpro_t.set_timer_timing_hours++ ;//run_t.dispTime_minutes = run_t.dispTime_minutes + 60;
		   if(gpro_t.set_timer_timing_hours > 24){ //if(run_t.dispTime_minutes > 59){

		          gpro_t.set_timer_timing_hours=0;//run_t.dispTime_hours =0;
		                
             }

		   glcd_t.number5_high = gpro_t.set_timer_timing_hours /10;
		   glcd_t.number5_low =  gpro_t.set_timer_timing_hours /10;

		   glcd_t.number6_high= gpro_t.set_timer_timing_hours %10;

		   glcd_t.number6_low= gpro_t.set_timer_timing_hours %10;
	
   

	      glcd_t.number7_low =  0;
	      glcd_t.number7_high =  0;

	      glcd_t.number8_low = 0;
	      glcd_t.number8_high =   0;
		  gkey_t.add_dec_key_be_pressed=1;

       LCD_Disp_Timer_Timing();
        
     break;
        
    }

}

/***************************************************************************
    *
    *Function Name:void key_add_dec_set_temp_value_fun(void)
    *Function :
    *Input Ref: 
    *Return Ref : NO
    *
***************************************************************************/
void key_add_dec_set_temp_value_fun(void)
{


    if((gkey_t.set_temp_value_be_pressed == 1 || g_tDisp.disp_set_temp_value_flag==1 || gpro_t.smart_phone_set_tmep_value_flag == 1) && gpro_t.gTimer_set_temp_temp > 2){

	   gpro_t.gTimer_run_dht11=0; 
       gpro_t.gTImer_send_disp_board =0;

      if(gkey_t.set_temp_value_be_pressed ==1 || gpro_t.smart_phone_set_tmep_value_flag == 1){

          if(gkey_t.set_temp_value_be_pressed ==1)gkey_t.set_temp_value_be_pressed++;
          if(gpro_t.smart_phone_set_tmep_value_flag == 1) gpro_t.smart_phone_set_tmep_value_flag ++;
          
           //lcd_donot_disp_number_34_temperature();
           // osDelay(400);
            Disp_SetTemp_Value(gctl_t.gSet_temperature_value );
            
            gpro_t.set_temperature_value_success =1;
            gctl_t.manual_turn_off_ptc_flag =0;
            
		
           
            sendData_setTemp_value(gctl_t.gSet_temperature_value ); //to send data the second display board
            osDelay(10);
            set_temp_value_compare_dht11_temp_value();
			 MqttData_Publis_SetTemp(gctl_t.gSet_temperature_value);
             osDelay(300);


      }
      else if(g_tDisp.disp_set_temp_value_flag == 1){ //this is the second display board  to the first display baord displa numbers.

          g_tDisp.disp_set_temp_value_flag++;

          // lcd_donot_disp_number_34_temperature();
           // osDelay(400);
            Disp_SetTemp_Value(gctl_t.gSet_temperature_value );
            gpro_t.set_temperature_value_success =1;

            //send_data_disp =0;//sendData_setTemp_value(gctl_t.gSet_temperature_value ); //to send data the second display board
            set_temp_value_compare_dht11_temp_value();

			

       }
      

   


    }

    
  
}
    
 
/********************************************************************
 * 
 * Function Name:void set_temp_value_compare_dht11_temp_value(void)
 * 
 * 
 * 
 ********************************************************************/
void set_temp_value_compare_dht11_temp_value(void)
{

   static uint8_t first_turn_off_flag;
   static uint8_t  send_1_off =0xff,send_1_on=0xff,send_2_on=0xff,send_2_off=0xff;
   static uint8_t send_2_on_flag,send_2_off_flag,send_1_on_flag,send_1_off_flag;
    switch(gpro_t.set_temperature_value_success){

    case 1:

        if(gctl_t.gSet_temperature_value > gctl_t.dht11_temp_value && gctl_t.interval_stop_run_flag  ==0){

            if(gctl_t.manual_turn_off_ptc_flag ==0 && gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
                gctl_t.ptc_flag = 1;

                Ptc_On();
                Disp_Dry_Icon();

                gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 

                sendDisplayCommand(0x02,0x1); // 关闭干燥功能
	            osDelay(5);
                  if(send_1_on !=send_1_on_flag){
                       send_1_on = send_1_on_flag;
                       send_1_off_flag ++;
                    if(gpro_t.tencent_link_success==1){
                       MqttData_Publish_SetPtc(0x01);
                       osDelay(100);
                     }
                  }
            }


        }
        else if(gctl_t.gSet_temperature_value <   gctl_t.dht11_temp_value || gctl_t.gSet_temperature_value ==   gctl_t.dht11_temp_value){

            gctl_t.ptc_flag = 0;
            Ptc_Off();
            Disp_Dry_Icon();
			sendDisplayCommand(0x02,0); // 关闭干燥功能
	        osDelay(5);
             if(send_1_off !=send_1_off_flag ){
                 send_1_off = send_1_off_flag;
                 send_1_on_flag ++;
                 if(gpro_t.tencent_link_success==1){
                     MqttData_Publish_SetPtc(0x0);
                     osDelay(100);
                   }
                  

              }
            gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 


        }
    break;


    case 0: //default of compare real temperature value 


    if(gctl_t.dht11_temp_value > 39){

          first_turn_off_flag=1;
          
          gctl_t.ptc_flag = 0;
          Ptc_Off();
          Disp_Dry_Icon();
          sendDisplayCommand(0x02,0); // 关闭干燥功能
	      osDelay(5);
          if(send_2_off !=send_2_off_flag ){
             send_2_off = send_2_off_flag;
             send_2_on_flag ++;
    	     if(gpro_t.tencent_link_success==1){
               MqttData_Publish_SetPtc(0x0);
               osDelay(10);

               }
          }


    }
    else if(gctl_t.dht11_temp_value < 38 && first_turn_off_flag==1 && gctl_t.interval_stop_run_flag ==0  ){

        if(gctl_t.manual_turn_off_ptc_flag ==0 &&  gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
         gctl_t.ptc_flag = 1;

         Ptc_On();
         Disp_Dry_Icon();
		 sendDisplayCommand(0x02,0x1); // 关闭干燥功能
	        osDelay(5);

         if(send_2_on !=send_2_on_flag ){
             send_2_on = send_2_on_flag;
             send_2_off_flag ++;
    	     if(gpro_t.tencent_link_success==1){
               MqttData_Publish_SetPtc(0x01);
               osDelay(10);
               }
          }

         gpro_t.gTimer_run_dht11=0;  //at once display sensor of temperature value 
        }


    }
    else if(gctl_t.dht11_temp_value < 40 && first_turn_off_flag==0  && gctl_t.interval_stop_run_flag ==0){

          if(gctl_t.manual_turn_off_ptc_flag ==0 &&  gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
             gctl_t.ptc_flag = 1;
    
             Ptc_On();
             Disp_Dry_Icon();
			 sendDisplayCommand(0x02,0x1); // 关闭干燥功能
	            osDelay(5);

            if(send_2_on !=send_2_on_flag ){
                 send_2_on = send_2_on_flag;
                 send_2_off_flag ++;
        	     if(gpro_t.tencent_link_success==1){
                   MqttData_Publish_SetPtc(0x01);
                   osDelay(100);
                  }
              }
    
             gpro_t.gTimer_run_dht11=0;  //at once display sensor of temperature value 
            }



    }


    break;

    }
}

uint8_t spot_flag;
void set_timer_value_handler(void)
{

	if(gkey_t.gTimer_disp_set_timer > 1 && gkey_t.key_add_dec_mode == mode_set_timer &&  gkey_t.key_mode_shot_flag ==0){

		if(gpro_t.set_timer_timing_hours == 0 && gpro_t.set_timer_timing_minutes==0){

		gkey_t.set_timer_timing_success = 0;

		gctl_t.ai_flag = 1;
		gkey_t.key_mode =disp_works_timing;

		gkey_t.key_add_dec_mode = set_temp_value_item;

		spot_flag++;
		if(gkey_t.set_timer_timing_success == 0 && gkey_t.add_dec_key_be_pressed == 1){
				gkey_t.add_dec_key_be_pressed =0;
				SendData_Data(0x2B, 0x0); //set up timer timing value .
				osDelay(100);
		}
		LCD_Disp_Works_Timing_Init();
    
		


		}
		else{
			gkey_t.set_timer_timing_success = 1;
			gpro_t.gTimer_timer_Counter =0; //start recoder timer timing is "0",from "0" start

			gctl_t.ai_flag = 0;

			gkey_t.key_mode = disp_timer_timing;
			gkey_t.key_add_dec_mode = set_temp_value_item;

			LCD_Disp_Timer_Timing_Init();

			if(gkey_t.set_timer_timing_success == 1 && gkey_t.add_dec_key_be_pressed == 1){
				gkey_t.add_dec_key_be_pressed =0;
				SendData_Data(0x2B, gpro_t.set_timer_timing_hours); //set up timer timing value .
				osDelay(100);
			}

			if(gpro_t.tencent_link_success==1){
			MqttData_Publish_AiState(2); //timer model  = 2, works model = 1
			osDelay(200);//HAL_Delay(200);
			}


		}
	}

}

