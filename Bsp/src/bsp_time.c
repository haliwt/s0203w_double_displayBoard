#include "bsp.h"

#define UNIT_TEST   0


static void Works_Time_Out(void);


static void interval_continuce_works_fun(void);

static void interval_two_hours_stop_action(void);

 uint8_t fan_continue_flag;

void  works_two_hours_handler(void)
{

  


	#if  UNIT_TEST  
	if(gpro_t.gTimer_run_total > 9){//119 //120 minutes //be testing is 9

	#else
	if(gpro_t.gTimer_run_total >119){

	#endif 
		gpro_t.gTimer_run_total =0;
	
		gpro_t.gTimer_run_one_mintue =0;
		fan_continue_flag=0;
		gctl_t.step_process=7;
		gctl_t.interval_stop_run_flag  =1 ;
		gpro_t.wind_speed_init_flag = 1;
		gpro_t.fan_lower_speed++;
		gpro_t.fan_middle_speed ++ ;

	}
	
	if(gctl_t.interval_stop_run_flag  ==1){
		Works_Time_Out();

	}
}

/**********************************************************************************************************
*	Âá? Êï? Âê?: static uint8_t Works_Time_Out(void)
*	ÂäüËÉΩËØ¥Êòé: ‰∏ªÊùøÂ∑•‰Ωú2Â∞èÊó∂ÔºåÂÅúÊ≠¢Â∑•‰Ω?10ÂàÜÈíü
*			 
*	ÂΩ?    Âè?: Êó?
*	Ëø? Âõ? ÂÄ?: Êó?
**********************************************************************************************************/
static void  Works_Time_Out(void)
{

    #if UNIT_TEST


	if( gpro_t.gTimer_run_total< 4){  //test for 4 minutes.
		
		interval_two_hours_stop_action();//Mainboard_Fun_Stop();
		 
    }
	#else

	 if(gpro_t.gTimer_run_total < 11){  //test for 10 minutes.
		
		interval_two_hours_stop_action();//Mainboard_Fun_Stop();
		 
     }



	#endif 
    

	if(gpro_t.gTimer_run_one_mintue < 60 && ( fan_continue_flag ==0)){

		Fan_Run();

	}

	if(gpro_t.gTimer_run_one_mintue > 60){

	     fan_continue_flag=1;

         Fan_Stop();
	 }

	#if UNIT_TEST
	if(gpro_t.gTimer_run_total > 4 && gctl_t.interval_stop_run_flag==1){ //10 minutes,test for 4 minutes .

	#else
	  if(gpro_t.gTimer_run_total > 10 && gctl_t.interval_stop_run_flag==1){


	#endif 
	
		gpro_t.gTimer_run_total=0;

        gctl_t.interval_stop_run_flag= 0;
		
        interval_continuce_works_fun();
		
      }
}
/********************************************************************************************************
*
*	Âá? Êï? Âê?: static void interval_two_hours_stop_action(void)
*	ÂäüËÉΩËØ¥Êòé: ‰∏ªÊùøÂ∑•‰ΩúÔºöÂäüËÉΩÂä®‰ΩúËæìÂá?			 
*	ÂΩ?    Âè?: Êó?
*	Ëø? Âõ? ÂÄ?: Êó?
*
**********************************************************************************************************/
static void interval_two_hours_stop_action(void)
{
   Ptc_Off();

   Ultrasonic_Pwm_Stop();
  // Fan_Stop();
   Plasma_Off();

   if(ptc_state() ==1){


      
       Disp_Dry_Icon();


     }
    else{

           
 
     Disp_Dry_Icon();
    }
            

    if(plasma_state() ==1){
		
 
       Disp_Kill_Icon();

    }
	else{

	 
       Disp_Kill_Icon();

	}

    if(ultrasonic_state() ==1){


         Disp_Ultrsonic_Icon();

    }
    else{

 
    Disp_Ultrsonic_Icon();


    }

  
 
 }


	
static void interval_continuce_works_fun(void)
{
  
    if(ptc_state() ==1){
    
    
          Ptc_On();
          Disp_Dry_Icon();
    
    
        }
       else{
    
              
        Ptc_Off();
        Disp_Dry_Icon();
       }
               
    
       
    
       
    
       if(plasma_state() ==1){
           
          Plasma_On();
    
       }
       else{
    
          Plasma_Off();
    
       }
    
       if(ultrasonic_state() ==1){
    
            Ultrasonic_Pwm_Output();
    
    
       }
       else{
    
       Ultrasonic_Pwm_Stop();
    
    
       }
    
     
       switch(wifi_t.set_wind_speed_value){
       
            case 0: //full speed
       
       
              Fan_Run();
       
            break;
       
            case 1 : //middle speed
             Fan_Run_Middle();
       
            break;
       
            case 2: //lower speed
             if(gpro_t.wind_speed_init_flag ==1){
                   gpro_t.wind_speed_init_flag++;
                   gpro_t.fan_lower_speed++;
                     Fan_Run();
                     osDelay(1000);
             }
             else
                Fan_Run_Lower();
            break;
       
       
          }


}


void Display_modeKey_switchTime_Handler(void)
{

	// static uint8_t switch_counter;

	  if(gctl_t.ptc_warning == 0 && gctl_t.fan_warning ==0){
	 
		switch(gpro_t.receive_disp_mode){
	  
		case disp_works_timing :
		     if(gpro_t.gTimer_disp_short_time <4 ){
	
				dispLCD_worksTime_fun();
	
			}
			else if(gpro_t.gTimer_disp_short_time > 3 ){
				 
					gpro_t.gTimer_disp_short_time=0;
					gkey_t.key_mode = disp_works_timing;
					gctl_t.ai_flag =1;
			
					gpro_t.receive_disp_mode=0xff	;
			}
			
			
		break;
		
		case disp_timer_timing:
	   
		    if(gkey_t.set_timer_timing_success == 0 && gpro_t.gTimer_disp_short_time < 4){ //&& gkey_t.gTimer_disp_switch_disp_mode > 3){
	
				 gctl_t.ai_flag = 0; // don't  DISPLAY AI ICON
				 donot_disp_ai_symbol();
				 display_timer_times_handler();
			  
			}
			else if(gpro_t.gTimer_disp_short_time > 3 && gkey_t.set_timer_timing_success == 0){
				    
					gpro_t.gTimer_disp_short_time=0;
					gctl_t.ai_flag =1;
					disp_ai_symbol();
					display_works_times_handler();
					gkey_t.key_mode = disp_works_timing;
			        gpro_t.receive_disp_mode=0xff	;
	
	
			}
			else if(gpro_t.gTimer_disp_short_time > 3 && gkey_t.set_timer_timing_success == 1){

                 gctl_t.ai_flag = 0; // don't  DISPLAY AI ICON
				 donot_disp_ai_symbol();

                    glcd_t.number5_low = gpro_t.set_timer_timing_hours / 10;
					glcd_t.number5_high = 	glcd_t.number6_low / 10;


					glcd_t.number6_low = gpro_t.set_timer_timing_hours  % 10;
					glcd_t.number6_high = 	glcd_t.number6_low;


			        glcd_t.number7_low = 	gpro_t.set_timer_timing_minutes / 10;
					glcd_t.number7_high = glcd_t.number7_low;


					glcd_t.number8_low = gpro_t.set_timer_timing_minutes % 10;
					glcd_t.number8_high = glcd_t.number8_low;
				 	display_works_times_handler(); //Display_Works_Timing();

				 
				 gkey_t.key_mode = disp_timer_timing;
			      gpro_t.receive_disp_mode=0xff	;

			}
	
		break;

		default:

		break;
	
	
		
	
		 
		 
		}


	  }

}



void dispLCD_worksTime_fun(void)
{
       gctl_t.ai_flag = 1; //  DISPLAY AI ICON
	   disp_ai_symbol();

	  
	    glcd_t.number5_low = gpro_t.disp_works_hours_value / 10;
		glcd_t.number5_high = glcd_t.number5_low;


		glcd_t.number6_low = gpro_t.disp_works_hours_value  % 10;
		glcd_t.number6_high = glcd_t.number6_low;


        glcd_t.number7_low = gpro_t.disp_works_minutes_value / 10;
		glcd_t.number7_high = glcd_t.number7_low;


		glcd_t.number8_low = gpro_t.disp_works_minutes_value  % 10;
		glcd_t.number8_high = glcd_t.number8_low;
	 	display_works_times_handler(); //Display_Works_Timing();


}

void dispLCD_timerTime_fun(void)
{
	gctl_t.ai_flag = 0; // don't  DISPLAY AI ICON
	donot_disp_ai_symbol();

	glcd_t.number5_low = gpro_t.set_timer_timing_hours / 10;
	glcd_t.number5_high = glcd_t.number5_low;


	glcd_t.number6_low = gpro_t.set_timer_timing_hours  % 10;
	glcd_t.number6_high =   glcd_t.number6_low;


	glcd_t.number7_low =    gpro_t.set_timer_timing_minutes / 10;
	glcd_t.number7_high = glcd_t.number7_low;


	glcd_t.number8_low = gpro_t.set_timer_timing_minutes % 10;
	glcd_t.number8_high = glcd_t.number8_low;
	
	display_works_times_handler(); //Display_Works_Timing();
}

