#include "bsp.h"
#include "queue.h"

uint8_t usart2_dataBuf[1];


uint8_t recieve_flag;
uint8_t receive_key_message;
uint8_t receive_task_start;
uint8_t key_long_counter;
uint16_t power_key_long_counter ;
uint8_t  dc_power_on;
uint8_t check_code;


/*
**********************************************************************************************************
											宏定�?
**********************************************************************************************************
*/
#define POWER_KEY_0	        (1 << 0)
#define MODE_KEY_1	        (1 << 1)
#define DEC_KEY_2           (1 << 2)
#define ADD_KEY_3           (1 << 3)

#define RUN_POWER_4         (1 << 4)
#define RUN_MODE_5          (1 << 5)
#define RUN_DEC_6           (1 << 6)
#define DECODER_BIT_7           (1 << 7)

#define PHONE_POWER_ON_RX_8       (1<<8)
#define PHONE_POWER_ON_9         (1<<9)
#define DECODER_BIT_10            (1<<10)



//typedef struct Msg
//{
//	uint8_t  ucMessageID;
//    uint8_t  uid;
//    uint8_t  bcc_check_code;
//	uint8_t usData[12];
//	
//}MSG_T;
//
//MSG_T   gl_tMsg; /* 定义丢�个结构体用于消息队列 */


uint8_t rx_data_counter,rx_end_flag;
uint8_t add_flag,dec_flag;



/***********************************************************************************************************
											函数声明
***********************************************************************************************************/
static void vTaskUsartPro(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);


/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskUsartPro = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

/**********************************************************************************************************
*	�? �? �?: main
*	功能说明: 标准c程序入口�?
*	�?    参：�?
*	�? �? �?: �?
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
	/* 创建任务 */
	AppTaskCreate();

	/* �����*/
//	AppObjCreate();
	
    /* 启动调度，开始执行任�? */
    vTaskStartScheduler();
}


/**********************************************************************************************************
	*
	*Funtion Name:static void vTaskUsartPro(void *pvParameters)
	*Funtion:送的事件标志位设�?
	*Input Ref:的形�?
	*	�? �? 
	*   �? �?  
	*
**********************************************************************************************************/
#if 1
static void vTaskUsartPro(void *pvParameters)//static void vTaskMsgPro(void *pvParameters)
{

    BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(20000); /* 设置�?大等待时间为100ms */
	uint32_t ulValue;
	
	while(1)
	{

    
    
		xResult = xTaskNotifyWait(0x00000000,	   
							   		0xFFFFFFFF,	  
							    	&ulValue,		  /* 保存ulNotifiedValue到变量ulValue�? */
									xMaxBlockTime );  /* �?大允许延迟时�? */
		   
		if( xResult == pdPASS )
		{
            if((ulValue & DECODER_BIT_7) != 0){

	        gpro_t.disp_rx_cmd_done_flag = 0;


           check_code =  bcc_check(mess_t.mesData,mess_t.mesLength);

           if(check_code == mess_t.bcc_check_code ){
           
              receive_data_fromm_display(mess_t.mesData);
			

           }

		}

   


		}
		
	}
}
#endif 
/**********************************************************************************************************
*	�? �? �?: vTaskStart
*	功能说明: 启动任务，也就是�?高优先级任务，这里用作按键扫描�??
*	�?    �?: pvParameters 是在创建该任务时传�?�的形参
*	�? �? �?: �?
*   �? �? �?: 4  
**********************************************************************************************************/
static void vTaskMsgPro(void *pvParameters)//static void vTaskStart(void *pvParameters)
{
   //BaseType_t xResult;
  // const TickType_t xMaxBlockTime = pdMS_TO_TICKS(100); /* 设置�?大等待时间为30ms */
 
  // uint32_t ulValue;
   static uint8_t dc_power_on_flag;
  
    while(1)
    {


       //DC the first power on run prcess once times.    //
        if(dc_power_on_flag==0){
         dc_power_on_flag++;
          
          LED_Mode_Off();
          Backlight_Off();
          
          buzzer_sound();
          gpro_t.shut_Off_backlight_flag = turn_on;
        }
		
    
		if(gkey_t.power_on_flag ==1 && KEY_POWER_VALUE() == KEY_UP){
             key_power_shot_handler();//power_long_short_key_fun();

         }
         else if(wifi_t.smartphone_app_power_on_flag == 1){
           wifi_t.smartphone_app_power_on_flag++;
           SendData_Set_Command(0X21,0X01);
           osDelay(20);
          }
         
         
           if(gkey_t.key_power==power_on){
            
         
          power_on_run_handler();

		  
	   
          record_time_or_timer_handler();
		  
          key_add_dec_set_temp_value_fun();

		  set_timer_value_handler();

		  dispLCD_timeColon_handler();

		  
         
          LCD_Fan_Run_Icon(wifi_t.set_wind_speed_value);
		  
          link_wifi_net_handler(gkey_t.wifi_led_fast_blink_flag);
		  
          Disip_Wifi_Icon_State();

		 

          
         
        }
        else{
            
          power_off_run_handler();

       }

		
         if(gkey_t.wifi_led_fast_blink_flag==0 ){
                 wifi_get_beijing_time_handler();
                 wifi_auto_detected_link_state();

         }
		 
        
      // receive_message_displaybord_handler();
       vTaskDelay(10);
      }

    }
/**********************************************************************************************************
*	�? �? �?: vTaskMsgPro
*	功能说明: 使用函数xTaskNotifyWait接收任务vTaskTaskUserIF发�?�的事件标志位设�?
*	�?    �?: pvParameters 是在创建该任务时传�?�的形参
*	�? �? �?: �?
*   �? �? �?: 3  
**********************************************************************************************************/
static void vTaskStart(void *pvParameters)//static void vTaskMsgPro(void *pvParameters)
{
   // MSG_T *ptMsg;
   // BaseType_t xResult;
	//const TickType_t xMaxBlockTime = pdMS_TO_TICKS(50); /* 设置�?大等待时间为100ms */
	//uint32_t ulValue;
   
   
	
    while(1)
    {
	  
	    key_handler();
   
             
        vTaskDelay(20);
    }
}
/**********************************************************************************************************
*	�? �? �?: AppTaskCreate
*	功能说明: 创建应用任务
*	�?    参：�?
*	�? �? �?: �?
**********************************************************************************************************/
static void AppTaskCreate (void)
{


    xTaskCreate( vTaskUsartPro,     		/* 任务函数  */
                 "vTaskUsartPro",   		/* 任务�?    */
                 128,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,               		/* 任务优先�?*/
                 &xHandleTaskUsartPro );  /* 任务句柄  */

	
	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务�?    */
                 256,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 1,               		/* 任务优先�?*/
                 &xHandleTaskMsgPro );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务�?    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,              		/* 任务优先�?*/
                 &xHandleTaskStart );   /* 任务句柄  */
}
/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
     static uint8_t state;
     BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(huart->Instance==USART1)//if(huart==&huart1) // Motor Board receive data (filter)
	{
      // DISABLE_INT();
		switch(state)
		{
		case 0:  //#0
			if(disp_inputBuf[0] == 0xA5){  // 0xA5 --didplay command head
               rx_data_counter=0;
			     mess_t.mesLength=0;
               mess_t.mesData[rx_data_counter] = disp_inputBuf[0];
			   state=1; //=1

             }
            else
                state=0;
		break;

       
		case 1: //#1

            if(gpro_t.disp_rx_cmd_done_flag ==0){
              /* 初始化结构体指针 */
               rx_data_counter++;
		     
	          mess_t.mesData[rx_data_counter] = disp_inputBuf[0];
              

              if(rx_end_flag == 1){

                state = 0;
            
                mess_t.mesLength = rx_data_counter;
                rx_end_flag=0;

                rx_data_counter =0;

                gpro_t.disp_rx_cmd_done_flag = 1 ;

          

                 mess_t.bcc_check_code=disp_inputBuf[0];

          
                #if 1

                 xTaskNotifyFromISR(xHandleTaskUsartPro,  /* 目标任务 */
                                    DECODER_BIT_7,     /* 设置目标任务事件标志位bit0  */
                                    eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                                    &xHigherPriorityTaskWoken);

                /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                #endif 
                  
              }

              }

              if(mess_t.mesData[rx_data_counter] ==0xFE && rx_end_flag == 0 &&  rx_data_counter > 4){
                     
                       rx_end_flag = 1 ;
               }

        break;


			
		}

      //  ENABLE_INT();
	    __HAL_UART_CLEAR_OREFLAG(&huart1);
		HAL_UART_Receive_IT(&huart1,disp_inputBuf,1);//UART receive data interrupt 1 byte
		
	}
    else if(huart->Instance==USART2)  //wifi usart1 --wifi 
    {
      // DISABLE_INT();    
	  if(gpro_t.linking_tencent_cloud_doing  ==1){ //link tencent netware of URL

			wifi_t.wifi_data[wifi_t.wifi_uart_rx_counter] = usart2_dataBuf[0];
			wifi_t.wifi_uart_rx_counter++;

			if(*usart2_dataBuf==0X0A) // 0x0A = "\n"
			{
				//wifi_t.usart2_rx_flag = 1;
				Wifi_Rx_Link_Net_InputInfo_Handler();
				wifi_t.wifi_uart_rx_counter=0;
			}

	      } 
		  else{

		         if(wifi_t.get_rx_beijing_time_enable==1){
					wifi_t.wifi_data[wifi_t.wifi_uart_rx_counter] =usart2_dataBuf[0];
					wifi_t.wifi_uart_rx_counter++;
				}
			    else{
					
                   // wifi_t.wifi_data_rx[wifi_t.wifi_uart_rx_counter] =usart2_dataBuf[0];
					///wifi_t.wifi_uart_rx_counter++;
                    Subscribe_Rx_Interrupt_Handler();

				}
	      }
	 
	//  ENABLE_INT();

	__HAL_UART_CLEAR_OREFLAG(&huart2);
	
	 HAL_UART_Receive_IT(&huart2,usart2_dataBuf,1);
     
	}


 }

  
 

//	__HAL_UART_CLEAR_NEFLAG(&huart2);
//	__HAL_UART_CLEAR_FEFLAG(&huart2);
//	__HAL_UART_CLEAR_OREFLAG(&huart2);
//	__HAL_UART_CLEAR_TXFECF(&huart2);


/*********************************************************************
*
*Function Name: 
*Function :
*Input Ref:
*Return Ref:
*
*********************************************************************/
void smartphone_turn_on_handler(void)
{
   
    xTaskNotify(xHandleTaskMsgPro,  /* 目标任务 */
    PHONE_POWER_ON_RX_8,      /* 设置目标任务事件标志位bit0  */
    eSetBits);  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */

}


void display_board_commnunication_handler(void)
{

        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
         DECODER_BIT_10,     /* 设置目标任务事件标志位bit0  */
         eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
            &xHigherPriorityTaskWoken);

                /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
           portYIELD_FROM_ISR(xHigherPriorityTaskWoken);



}




