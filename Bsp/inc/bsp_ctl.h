#ifndef __BSP_CTL_H
#define __BSP_CTL_H
#include "main.h"

typedef enum{

  turn_on,
  turn_off

}backlight_state;



typedef enum{

   close,
   open
  
}hard_state;


typedef enum{

   good,
   error

}hard_error_state;

typedef struct _bsp_ctl{

    uint8_t ptc_flag;
	uint8_t plasma_flag;
	uint8_t ultrasonic_flag;
    uint8_t ai_flag;
    uint8_t wifi_flag;
    uint8_t gSet_temperature_value;
    uint8_t step_process;
    uint8_t interval_stop_run_flag;

    uint8_t manual_turn_off_ptc_flag ;



    //wifi
    uint8_t disp_works_hours;
    uint8_t disp_works_minutes;
    uint8_t gTimer_ctl_disp_disp_works_timing_second;

    uint8_t  dht11_temp_value;
    uint8_t  dht11_humidity_value;
    
 

	uint8_t ptc_warning;
	uint8_t fan_warning;


	uint8_t gTimer_process_display;
    uint8_t gTimer_wifi_blink;

    uint8_t gTimer_wifi_fast_blink;
   // uint8_t gTimer_feed_dog_times;

    
   
	

}bsp_ctl;

extern bsp_ctl gctl_t;

extern uint8_t (*ptc_state)(void); //adjust of ptc is open or close
extern uint8_t (*plasma_state)(void); //adjust of plasma is open or close
extern uint8_t (*ultrasonic_state)(void); //adjust of ultrasoic is open or close

extern uint8_t (*ai_mode_state)(void);
extern uint8_t (*power_on_state)(void);




extern uint8_t (*ptc_error_state)(void);
extern uint8_t (*fan_error_state)(void);

extern void (*backlight_on_off_state)(void);
extern void (*wake_up_backlight_on)(void);


void bsp_ctl_init(void);


void Ptc_State_Handler( uint8_t (*ptc_handler)(void));
void  Plasma_State_Handler(uint8_t(*plasma_handler)(void));
void  Ultrasonic_state_Handler(uint8_t(*ultrasonic_handler)(void));
void  Fan_state_Handler(uint8_t(*fan_handler)(void));

void  Ai_Mode_Handler(uint8_t(*ai_handler)(void));
void  Power_On_Handler(uint8_t(*power_handler)(void));



void  Ptc_error_state_Handler(uint8_t(*error_handler)(void));
void  Fan_error_state_Handler(uint8_t(*fan_error_handler)(void));
void  backlight_on_off_handler(void (*backlight_state_handler)(void));

void  wake_up_backlight_on_handler(void (*backlight_on_handler)(void));


void main_fun_init(void);


uint8_t Ptc_Default_Handler(void);
uint8_t Plasma_Default_Handler(void);
uint8_t Ultrasonic_Default_Handler(void);
uint8_t Fan_Default_Handler(void);

uint8_t Ptc_Error_Default_Handler(void);

uint8_t Fan_Error_Default_Handler(void);




#endif 

