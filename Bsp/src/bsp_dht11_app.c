#include "bsp.h"


/********************************************************************
 * 
 * Function Name:void temperatureValue_compareHandler(void)
 * 
 * 
 * 
 ********************************************************************/
void temperatureValue_compareHandler(void)
{

  
    if(gpro_t.set_temperature_value_success==1){

  

        if(gctl_t.gSet_temperature_value > gctl_t.dht11_temp_value && gctl_t.interval_stop_run_flag  ==0){

            if(gctl_t.manual_turn_off_ptc_flag ==0 && gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
                gctl_t.ptc_flag = 1;
				sendDisplayCommand(0x02,0x1); // 关闭干燥功能
				osDelay(5);

                Ptc_On();
                Disp_Dry_Icon();

                gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 

              
                  
            }


        }
        else if(gctl_t.gSet_temperature_value <   gctl_t.dht11_temp_value || gctl_t.gSet_temperature_value ==   gctl_t.dht11_temp_value){

            gctl_t.ptc_flag = 0;
            Ptc_Off();
            Disp_Dry_Icon();
			sendDisplayCommand(0x02,0); // 关闭干燥功能
	        osDelay(5);
            
            gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 


        }
 
    }

  
}


