#include "bsp.h"

second_disp_ref  g_tDisp;

uint8_t step_disp;


static void second_disp_ref_data(void);

/**********************************************************************
    *
    *Function Name:
    *Function: receive usart touchkey of command 
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
void second_disp_power_on_fun(void)
{
    gkey_t.key_power=power_on;
    gkey_t.key_mode = disp_timer_timing;
    gctl_t.ai_flag = 1;
    gctl_t.ptc_warning =0;
    gctl_t.fan_warning =0;

    gctl_t.step_process=0;
    gpro_t.power_off_flag =1;
    g_tDisp.second_disp_power_on =1;
	gctl_t.step_process=0;

}
/**********************************************************************
    *
    *Function Name:
    *Function: receive usart touchkey of command 
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
void second_disp_power_off_fun(void)
{
     gkey_t.key_power=power_off;
     gctl_t.step_process=0;
}

/**********************************************************************
    *
    *Function Name:
    *Function: receive usart touchkey of command 
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
void second_disp_set_link_wifi_fun(void)
{

   

    //WIFI CONNCETOR process
    gkey_t.wifi_led_fast_blink_flag=1;
     //WIFI CONNCETOR process
    gpro_t.tencent_link_success =0;
    gpro_t.get_beijing_time_success =0;

    gpro_t.link_net_step =0;
    wifi_t.gTimer_linking_tencent_duration=0; //120s
         
}
/**********************************************************************
    *
    *Function Name:
    *Function: receive usart touchkey of command 
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
void second_disp_ai_time_fun(void)
{
     
    gkey_t.key_mode_switch_flag = 1;
    gkey_t.key_mode  = disp_works_timing;
    gkey_t.key_add_dec_mode = set_temp_value_item;
    gctl_t.ai_flag = 1; // AI DISPLAY AI ICON

   
             
}

/**************************************************************************
*
*Function Name :
*
*
*
*
**************************************************************************/
void second_disp_not_ai_timer_fun(void)
{

    
    gkey_t.key_mode  = disp_timer_timing;

    gctl_t.ai_flag = 0; // DON'T DISP AI ICON
    //counter exit timing this "mode_set_timer"
    gkey_t.key_mode_switch_flag = 1;
    gkey_t.key_add_dec_mode = set_temp_value_item;

    LCD_Disp_Timer_Timing_Init();
    disp_ai_iocn();
  


   // gkey_t.key_mode_be_pressed = 2;
    
              
}


void link_second_disp_board_handler(void)
{

 

    if( g_tDisp.second_disp_power_on ==1){

        //g_tDisp.second_disp_power_on ++ ;

      switch(step_disp){

       case 0:
        if(gpro_t.tencent_link_success==1){
              
             SendWifiData_To_Data(0x1F,0x01); //0x1F: 0x1=wifi link net is succes ,0x0 = wifi link net is fail
             osDelay(5);
         }
         else{

              SendWifiData_To_Data(0x1F,0x0); //0x1F: 0x1=wifi link net is succes ,0x0 = wifi link net is fail
             osDelay(5);


         }
         step_disp = 1;
         break;

         case 1:
         SendWifiData_To_PanelTime(gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value, gpro_t.gTimer_works_counter_sencods);
         osDelay(5);

     
         g_tDisp.second_disp_power_on ++ ;
         step_disp = 0;

         break;


         
        }

    }

}


/**********************************************************************************************************
*
*	函 数 名: void Process_Dynamical_Action(void)
*	功能说明: 主板工作：功能动作输出			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
#if 0
static void second_disp_ref_data(void)
{

    SendWifiData_Ref_three(gctl_t.ptc_flag,gctl_t.plasma_flag,gctl_t.ultrasonic_flag);
    osDelay(5);//HAL_Delay(10);

   SendWifiData_To_PanelTime(gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value, gpro_t.gTimer_works_counter_sencods);
    osDelay(5);//HAL_Delay(10);	
    if(gpro_t.set_temperature_value_success ==1){

        sendData_setTemp_value(gctl_t.gSet_temperature_value ); //to send data the second display board
        osDelay(5);//HAL_Delay(10);

    }

  

    
    if(gctl_t.ai_flag == 1){

          SendData_Set_Command(0x27,0x01); // works timing.
          osDelay(5);//HAL_Delay(10);

     }
     else{
         SendData_Set_Command(0x27,0x02); //timer timing.
          osDelay(5);//HAL_Delay(10);
     }


    
}
#endif 
