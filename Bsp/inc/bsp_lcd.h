#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "main.h"

//#define TM1723_POWER_ON()				HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_SET)
//#define TM1723_POWER_OFF()             HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_RESET)


#define LCD_BACK_LIGHT_ON()				HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_SET)
#define LCD_BACK_LIGHT_OFF()            HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_RESET)




#define TM1723_CLK_SetHigh()            do{TM1723_SCLK_GPIO_Port ->BSRR |=TM1723_SCLK_Pin; }while(0)//HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_SET)    // ï¿½ï¿½ï¿½ï¿½ßµï¿½Æ?
#define TM1723_CLK_SetLow()             do{TM1723_SCLK_GPIO_Port ->BSRR |=(uint32_t)TM1723_SCLK_Pin<<16; }while(0)//HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_RESET)  // ï¿½ï¿½ï¿½ï¿½Íµï¿½Æ?

#define TM1723_DIO_SetHigh()            do{TM1723_DIO_GPIO_Port->BSRR |=TM1723_DIO_Pin;}while(0)//HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_SET)    // ï¿½ï¿½ï¿½ï¿½ßµï¿½Æ?
#define TM1723_DIO_SetLow()             do{TM1723_DIO_GPIO_Port->BSRR |=(uint32_t)TM1723_DIO_Pin<<16;}while(0)//HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_RESET)    // output low level

#define TM1723_STB_SetHigh()            do{TM1723_STB_GPIO_Port->BSRR |=TM1723_STB_Pin;}while(0)//HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_SET)
#define TM1723_STB_SetLow()             do{TM1723_STB_GPIO_Port->BSRR |=(uint32_t)TM1723_STB_Pin<<16;}while(0)//HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_RESET)

//extern volatile uint8_t DispData[3];//??LED??
#define		BitSET(x,y)		x|=(1<<y)				//?1
#define		BitCLR(x,y)		x&=~(1<<y)				//?0


#define DisplayReg           0x40// to write display register 
  
#define AddrFixed 	         0x44// 
#define AddrAutoAdd         0x40 
 
   
  
#define OpenDispTM1723          0x97 // full screen is tunr on light
#define OpenDispTM1723_5        0X9f
#define TM1723Default          	0x87
#define CloseDispTM1723		    0x80//  

#define LUM_VALUE        0x94//0x92//0x93//0x95//0x94//0x97(max)


 //Display Address 
#define Addr00H  		0xC0//??00H  -> Write display address 0xC0 
#define Addr01H  		0xC1//??01H

#define Addr02H  		0xC2//??02H
#define Addr03H  		0xC3//??03H
//digital 3
#define Addr04H  		0xC4//??03H
#define Addr05H  		0xC5//??03H
//digital 4
#define Addr06H  		0xC6//??00H
#define Addr07H  		0xC7//??01H


//Humidity SMG address
#define Addr08H  		0xC8//??02H
#define Addr09H  		0xC9//??03H

#define Addr0AH  		0xCA//??03H
#define Addr0BH  		0xCB//??03H

//temperature SMG address
#define Addr0CH         0xCC//??0CH
#define Addr0DH         0xCD//??0DH

#define Addr0EH         0xCE//??0CH
#define Addr0FH         0xCF//??0DH


//wind symbol 0xCE
/****run wind 1******/
#define T8                       0X01
#define T9                       0x01      //addr 0xCE --> high word
#define T11                      0x01    //address:0xCF
#define T13                      0X04     //address: 0xCE
/**run wind 2*******/
#define T10                      0x10     // addr 0xCE -> high word
#define T12                      0x40     //addr 0xCE -->high word
#define T14                      0x02     //address: 0xCE
/****************/
#define T15                      0x20      //address: 0xCE


//display wid stronger icon
#define T16_WIND_SPEED_LOW       0x08     // high LOW
//high middle

#define T17_WIND_SPEED_MID       0x80//addr 0xCE
//wind symbol 0xCF
#define T18_WIND_SPEED_FULL      0x02   //addr 0xCF





typedef struct _LCD_Ref{

     uint8_t number1_low;
	 uint8_t number1_high;
	 
	 uint8_t number2_low;
	 uint8_t number2_high;
	 
	 uint8_t number3_low;
	 uint8_t number3_high;
	 
	 uint8_t number4_low;
	 uint8_t number4_high;
	 
	 uint8_t number5_low;
	 uint8_t number5_high;

	 uint8_t number6_low;
	 uint8_t number6_high;

	 uint8_t number7_low;
	 uint8_t number7_high;

	 uint8_t number8_low;
	 uint8_t number8_high;

	 uint8_t gtime_colon_symbol_flag ;

	 uint8_t gTimer_colon_blink;
	 uint8_t gTimer_fan_blink;
	 uint8_t gTimer_error_times;
	 uint8_t gTimer_lcd_blink;
     uint8_t gTimer_wifi_fast_blink ;
	
}lcd_ref;



extern lcd_ref glcd_t; 

void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);


void TIM1723_Write_Cmd(uint8_t cmd);


void LcdDisp_Init(void);


void Lcd_Display_Detials(void);

void LCD_Display_Wind_Icon_Handler(void);


void Disp_Dry_Icon(void);

void Disp_Kill_Icon(void);

void Disp_Ultrsonic_Icon(void);

void Wifi_Icon_FastBlink(void);


void Disp_HumidityTemp_Init(void);



void Lcd_Display_Off(void);


void Lcd_Display_Off(void);

void dispLCD_timeColon_handler(void);


void LCD_Number_ThreeFour_Temperature(void);




void LCD_Number_FiveSix_Hours(void);
void LCD_Number_SevenEight_Minutes(void);

//void LCD_Fan_Run_Icon(uint8_t speed_valu);

//void Display_Wind_Icon_Inint(void);

void Disip_Wifi_Icon_State(void  );

void LCD_Numbers1234_Init(void);

void LCD_Number_Ai_OneTwo_Humidity(void);

void Disp_SetTemp_Value(uint8_t temp_value);

void Lcd_Display_SensorTemp_Value(void);

void OnlyDisp_Wind_Icon_Handler(void);

void LCD_Fault_Numbers_Code(void);

void disp_ai_iocn(void);

void disp_ai_symbol(void);

void donot_disp_ai_symbol(void);

void lcd_donot_disp_number_34_temperature(void);

void fan_error_code_number(void);

void ptc_error_code_number(void);

void display_works_times_four_numbers(uint8_t hours , uint8_t minutes,uint8_t sel);





void disp_time_4bit_init(void);


#endif 


