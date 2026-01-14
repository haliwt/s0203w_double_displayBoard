#include "bsp_adc.h"
#include "bsp.h"
#include "adc.h"


static void Detected_Fan_Error(void);
static void Detected_Ptc_Error(void);


static uint16_t Get_Adc_Channel(uint32_t ch) ;

static uint16_t Get_Adc_Average(uint32_t ch,uint8_t times);

uint16_t fan_detect_voltage,ptc_temp_voltage;

//uint8_t times_flag;
/*****************************************************************
*
	*Function Name: static uint16_t Get_Adc(uint32_t ch)  
	*Function ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?
	*Return Ref: No
	*
	*
*****************************************************************/
static uint16_t Get_Adc_Channel(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;

	ADC1_ChanConf.Channel=ch;                                   //Í¨µÀ
    ADC1_ChanConf.Rank= ADC_REGULAR_RANK_1;                                    //第一个序列
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_1CYCLE_5;//ADC_SAMPLETIME_239CYCLES_5;      //²ÉÑùÊ±¼ä               


	HAL_ADC_ConfigChannel(&hadc1,&ADC1_ChanConf);        //Í¨µÀÅäÖÃ
	
    HAL_ADC_Start(&hadc1);                               //start ADC transmit
	
    HAL_ADC_PollForConversion(&hadc1,10);                //轮询转换
 
	return (uint16_t)HAL_ADC_GetValue(&hadc1);	        	//·µ»Ø×î½üÒ»´ÎADC1¹æÔò×éµÄ×ª»»½á¹û
}
/*****************************************************************
*
	*Function Name: static uint16_t Get_Adc(uint32_t ch)  
	*Function ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?
	*Return Ref: No
	*
	*
*****************************************************************/
static uint16_t Get_Adc_Average(uint32_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc_Channel(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 



void Get_PTC_Temperature_Voltage(uint32_t channel,uint8_t times)
{
    uint16_t adcx;

 

    #if 1
	
	adcx = Get_Adc_Average(channel,times);

    ptc_temp_voltage  =(uint16_t)((adcx * 3300)/4096); //amplification 100 ,3.11V -> 311


	#ifdef DEBUG
      printf("ptc= %d",run_t.ptc_temp_voltage);
	#endif 

 

    #endif 

	if(ptc_temp_voltage < 373 || ptc_temp_voltage ==373){ //87 degree
  
	    gctl_t.ptc_flag = 0; //turn off
	    Ptc_Off(); //turn off

        gctl_t.ptc_warning = 1;
        gkey_t.key_mode = disp_ptc_error_number; //disp_error_number;
        
        Buzzer_Ptc_Error_Sound();

        if(gpro_t.tencent_link_success==1){

        Publish_Data_Warning(ptc_temp_warning,warning);
	     HAL_Delay(200);//osDelay(300);//HAL_Delay(350);
 
 
        MqttData_Publish_SetPtc(0);
		 HAL_Delay(100);//osDelay(300);//HAL_Delay(350);  

        }

	     SendData_Set_Command(0x08,0x01); //ptc error codes
   	      
   }
}


/*****************************************************************
	*
	*Function Name: void Get_Fan_Adc_Fun(uint8_t channel,uint8_t times)
	*Function ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?, hexadecimal of average
	*Return Ref: No
	*
	*
*****************************************************************/
void Get_Fan_Adc_Fun(uint32_t channel,uint8_t times)
{
	uint16_t adc_fan_hex;//,fan_detect_voltage;
	
	static uint8_t detect_error_times;
	
	adc_fan_hex = Get_Adc_Average(channel,times);

    fan_detect_voltage  =(uint16_t)((adc_fan_hex * 3300)/4096); //amplification 1000 ,3.111V -> 3111
	
   
   
   if(fan_detect_voltage < 320 ){
         detect_error_times ++;
	          
		if(detect_error_times >2){
			detect_error_times = 3;
		  gctl_t.fan_warning = 1;
          gkey_t.key_mode = disp_fan_error_number; //disp_error_number;
		  Buzzer_Fan_Error_Sound();

           wifi_t.set_wind_speed_value = 2;
          
       
          if(gpro_t.tencent_link_success ==1){
           Publish_Data_Warning(fan_warning,warning);
	       HAL_Delay(100);//osDelay(350);//HAL_Delay(350);

           MqttData_Publis_SetFan(0);
	       HAL_Delay(200);//osDelay(350);//HAL_Delay(350);

            MqttData_Publish_SetPtc(0);
            HAL_Delay(200);//osDelay(350);//HAL_Delay(350);

             

            }

			SendData_Set_Command(0x09,0x01); //fan error codes

          }
		
		

        
   }
   else{
      detect_error_times=0;


   }
}

/***************************************************************************
    *
    *Function Name:vvoid detected_error_handler(void)
    *Function : 
    *Input Ref: NO
    *Return Ref : NO
    *
***************************************************************************/
static void Detected_Fan_Error(void)
{
     //2 minute 180s
		
        if(wifi_t.set_wind_speed_value ==0){ //max fan speed be detected if not defalut .
        if( gctl_t.interval_stop_run_flag  ==0){
		   Get_Fan_Adc_Fun(ADC_CHANNEL_0,10);
        }
        }
				
	
}

static void Detected_Ptc_Error(void)
{
   
	  Get_PTC_Temperature_Voltage(ADC_CHANNEL_1,10);
    

}


/***************************************************************************
    *
    *Function Name:vvoid detected_error_handler(void)
    *Function : 
    *Input Ref: NO
    *Return Ref : NO
    *
***************************************************************************/
void detected_ptc_fan_error_handler(void)
{
    static uint8_t adc_switch_flag;
	if(gpro_t.gTimer_ptc_detected > 5 && gctl_t.interval_stop_run_flag==0){ //3 minutes 120s

	    gpro_t.gTimer_ptc_detected=0;

	    adc_switch_flag = adc_switch_flag ^ 0x01;

		if(adc_switch_flag==1){
		   Detected_Fan_Error();

		}
		else{
		    Detected_Ptc_Error();

		}

	   if(gctl_t.fan_warning ==1){

	       Buzzer_Fan_Error_Sound();


	   }
    
       
      }
}



