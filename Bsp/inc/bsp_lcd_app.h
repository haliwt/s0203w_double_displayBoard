#ifndef __BSP_LCD_APP_H
#define __BSP_LCD_APP_H
#include "main.h"

void Set_Timer_Timing_Lcd_Blink(void );

void PowerOn_Init(void);


void LCD_Disp_Works_Timing_Init(void);

void LCD_Disp_Timer_Timing_Init(void);


void MainBoard_Run_Feature_Handler(void);



void PowerOff_freeFun(void);

void PowerOff_Off_Led(void);


void Display_MainBoard_Feature_Handler(void);

void Display_Works_Timing(void);


void Display_Timer_Timing(void);

void LCD_Disp_Timer_Timing(void);


void Display_WorksTimingr_Handler(uint8_t sel_item);


void Set_Timer_Timing_Lcd_Blink(void );


//void Record_WorksTime_DonotDisp_Handler(void);


void Mainboard_Action_Fun(void);

void Disp_HumidityTemp_Value(void);

void Display_Wind_Icon_Inint(void);

//void LCD_Wind_Run_Icon(uint8_t wind_speed);

void LCD_Fan_Run_Icon(uint8_t wind_speed);

void LCD_fanRun_switchTimer_handle(void);


#endif


