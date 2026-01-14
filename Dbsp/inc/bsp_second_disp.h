#ifndef __BSP_SECOND_DISP_H
#define __BSP_SECOND_DISP_H
#include "main.h"



typedef struct{

    
    uint8_t second_disp_power_on;

   // g_tDisp.second_disp_power_on_flag = 1;


    
    uint8_t disp_power_off;
    uint8_t disp_cmd_ptc ;
    uint8_t disp_cmd_plasma;
    uint8_t disp_cmd_ultrasonic;
    uint8_t disp_set_temp_value;
    uint8_t disp_set_timer_value;
    uint8_t disp_set_temp_value_flag;
   
    uint8_t disp_second_link_state_flag;

    uint8_t ai_mode_flag;


}second_disp_ref;


extern second_disp_ref  g_tDisp;

void second_disp_power_on_fun(void);
void second_disp_power_off_fun(void);

void second_disp_set_link_wifi_fun(void);





void second_disp_ai_time_fun(void);


void second_disp_not_ai_timer_fun(void);


void link_second_disp_board_handler(void);



#endif 

