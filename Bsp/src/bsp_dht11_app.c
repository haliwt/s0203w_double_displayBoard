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

    static uint8_t recoder_close_ptc_times,ptc_default_on= 0xff, ptc_default_off = 0xff;

    if(gpro_t.gTimer_set_temp_value > 4){
		gpro_t.gTimer_set_temp_value=0;
    if(gpro_t.set_temperature_value_success==1){

  

        if(gctl_t.gSet_temperature_value > gctl_t.dht11_temp_value && gctl_t.interval_stop_run_flag  ==0){

            if(gctl_t.manual_turn_off_ptc_flag ==0 && gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
                gctl_t.ptc_flag = 1;
			

                
                Disp_Dry_Icon();

                gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 
                if(ptc_default_on != gctl_t.ptc_flag ){
					ptc_default_on = gctl_t.ptc_flag;
					Ptc_On();
	              	sendDisplayCommand(0x22,0x01); // 关闭干燥功能
					osDelay(10);

                }
                  
            }


        }
        else if(gctl_t.gSet_temperature_value < gctl_t.dht11_temp_value || gctl_t.gSet_temperature_value ==   gctl_t.dht11_temp_value){

            gctl_t.ptc_flag = 0;
            Ptc_Off();
            Disp_Dry_Icon();
			if(ptc_default_off != gctl_t.ptc_flag ){
			     ptc_default_off = gctl_t.ptc_flag;
				  Ptc_Off();
				  sendDisplayCommand(0x22,0); // 关闭干燥功能
	       		 osDelay(10);
			}
            
            gpro_t.gTimer_run_dht11=2;  //at once display sensor of temperature value 


        }
 
    }
	else{

	    if(gctl_t.interval_stop_run_flag  ==0){

        if(gctl_t.dht11_temp_value > 39){
				recoder_close_ptc_times=1;

		        gctl_t.ptc_flag = 0;
				Ptc_Off();
				Disp_Dry_Icon();
				if(ptc_default_off != gctl_t.ptc_flag ){
			       ptc_default_off = gctl_t.ptc_flag;
				    Ptc_Off();
				   sendDisplayCommand(0x22,0); // 关闭干燥功能
	       		     osDelay(10);
			     }
				sendDisplayCommand(0x22,0); // 关闭干燥功能
	            osDelay(10);

        }
		else if(gctl_t.dht11_temp_value < 39 && recoder_close_ptc_times == 0 && gctl_t.manual_turn_off_ptc_flag ==0){

		    
	               gctl_t.ptc_flag = 1;
				  
				  
				   Disp_Dry_Icon();
				   if(ptc_default_on != gctl_t.ptc_flag ){
					ptc_default_on = gctl_t.ptc_flag;
					 Ptc_On();
	              	sendDisplayCommand(0x22,0x01); // 关闭干燥功能
					osDelay(10);

                   }

		}
		else if(gctl_t.dht11_temp_value < 38 && recoder_close_ptc_times > 0 && gctl_t.manual_turn_off_ptc_flag ==0){

		    
	               gctl_t.ptc_flag = 1;
				  
				  
				   Disp_Dry_Icon();
				 if(ptc_default_on != gctl_t.ptc_flag ){
					ptc_default_on = gctl_t.ptc_flag;
					Ptc_On();
	              	sendDisplayCommand(0x22,0x01); // 关闭干燥功能
					osDelay(10);

                 }

		}

	    }
	  

	}

	 

    }
}


