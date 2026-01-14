#include "bsp_lcd.h"
#include "bsp.h"

lcd_ref glcd_t; 


#define WIFI_Symbol     		0x01 //addr 0xC5 -high word
#define WIFI_NO_Symbol          0

#define AI_Symbol    			0x01 //addr 0xC4 -high word
#define AI_NO_Symbol            0x0

#define DRY_Symbol              0x01  //addr 0xC9 ->T3 high word
#define DRY_NO_Symbol           0x0

#define PLASMA_Symbol             0x01  //addr 0xCA ->T4  high word
#define PLASMA_NO_Symbol          0x0

#define BUG_Symbol            	0x01   //addr 0xCC ->T5 high word
#define BUG_NO_Symbol         	0x0

#define TEMP_Symbol              0x01     //addr 0xC2 ->T7 high word
#define TIME_COLON              0x01
#define TIME_NO_COLON          0

#define HUMI_Symbol              0x01     //addr  0xC3 ->T6  high word





//Low 4bit 
#define seg_f   		0x02
#define seg_g   		0x04
#define seg_e	        0x08

//High 4bit
#define seg_a              0x10
#define seg_b              0x20
#define seg_c              0x40
#define seg_d              0x80

#define  COLON_SYMBOL                    0x01
#define  NO_COLON_SYMBOL                 0x00





#define MAX_LUM_VALUE  0x9F

const unsigned char segNumber_Low[]={
 
         seg_b+seg_c,        		      	// char "0"  	0x00
		 seg_b+seg_c,                      	// char "1"  	0x01
		 seg_b+seg_g,              		  	// char "2"  	0x02
		 seg_b+seg_g+seg_c,               	// char "3"  	0x03
		 seg_b+seg_g+seg_c,               	// char "4"  	0x04
		 seg_g+seg_c,              			// char "5"  	0x05
		 seg_g+seg_c,              			// char "6"  	0x06
		 seg_b+seg_c,                    	// char "7"  	0x07
		 seg_b+seg_g+seg_c,  		        // char "8"  	0x08
		 seg_b+seg_g+seg_c,        			// char "9"  	0x09
	     0                                  // char "null"  0x0A



};


const unsigned char segNumber_High[]={
         seg_a+seg_f+seg_e+seg_d,        // char "0"  		0x00
		 0,                				 // char "1"  		0x01
		 seg_a+seg_e+seg_d,              // char "2"  		0x02
		 seg_a+seg_d,                    // char "3"  		0x03
		 seg_f,                          // char "4"  		0x04
		 seg_a+seg_f+seg_d,              // char "5"  		0x05
		 seg_a+seg_f+seg_e+seg_d,        // char "6"  		0x06
		 seg_a,                    		 // char "7"  		0x07
		 seg_a+seg_f+seg_e+seg_d,  		 // char "8"  		0x08
		 seg_a+seg_f+seg_d,        		 // char "9"  		0x09
         0                               // char "NLL"  	0x16



};

static const uint8_t lcdNumber1_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber1_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

//digital "2"
static const uint8_t lcdNumber2_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber2_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};
//digital "3"
static const uint8_t lcdNumber3_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber3_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};
//digital "4"
static const uint8_t lcdNumber4_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber4_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};


//big Numbers 

static const uint8_t lcdNumber5_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber5_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber6_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber6_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber7_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber7_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber8_Low[]  ={0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber8_High[] ={0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

//"Er" ->digital positon '5''6'

static const uint8_t lcdNumber5_Low_E[]  ={0x0E};
static const uint8_t lcdNumber5_High_E[] ={0x90};

static const uint8_t lcdNumber6_Low_r[]={0x0C};
static const uint8_t lcdNumber6_High_r[] ={0x0};



lcd_ref glcd_t; 

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);








static uint8_t Detecting_Fault_Code(void);


static uint8_t	ptc_error_flag ,fan_error_flag;




/*****************************************************
 * 
 * Function Name:
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
static void TM1723_Start(void)
{
  TM1723_STB_SetLow();
	
}
static void TM1723_Stop(void)
{
   TM1723_STB_SetHigh();

}

static void TM1723_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1723_CLK_SetLow();
	 if(data & 0x01){
	     TM1723_DIO_SetHigh(); //TM1723 high of data to IC
		  
	 }
	 else{
	     TM1723_DIO_SetLow(); //TM1723 low level of data to IC
		  
	 }
   
    //delay_us(50);//delay_us(100)//big error add delay function
    TM1723_CLK_SetHigh(); //along up edge is write data 
   
	// delay_us(10);//big error add delay function
	 data =data>>1;//
	// delay_us(2);//big error add delay function
	}
    
}
void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
 
}

void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   #if 1
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();
   
   #else 
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_WriteData(addr,dat);
   TM1723_STB_SetHigh();
   #endif
}



/*****************************************************
 * 
 * Function Name: void Lcd_Display_Detials(void)
 * Function: display content
 * Input Ref: NO
 * Return Ref: NO
 * 
******************************************************/
void Lcd_Display_Detials(void)
{
     static uint8_t fault_code;
     fault_code =  Detecting_Fault_Code();
	 
	 TIM1723_Write_Cmd(0x00); // 0x00 -> display setup model
	 TIM1723_Write_Cmd(0x40); // 0x40 ->write data to display of register
	 TIM1723_Write_Cmd(0x44); // 0x44 -> write fix of address model

   /* display humidity number 1, 2 */

   LCD_Number_Ai_OneTwo_Humidity();



  if(fault_code ==0){
   /* display temperature  number 5, 6 */
   LCD_Number_FiveSix_Hours();


   /* display temperature  number 7, 8 */
   LCD_Number_SevenEight_Minutes();

 }
 else{
	LCD_Fault_Numbers_Code();

 }

   /* fan of degree numbers*/
 //  LCD_Wind_Icon();


   //open display
   TIM1723_Write_Cmd(MAX_LUM_VALUE);//(0x97);//(0x94);//(0x9B);


}

/*****************************************************
 * 
 * Function Name:  void LCD_Number_Ai_OneTwo_Humidity(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
void LCD_Number_Ai_OneTwo_Humidity(void)
{

  if(ai_mode_state()== 1){ //AI state 
  //number '1'
     TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4
  }
  else{
        //number '1'
     TM1723_Write_Display_Data(0xC4,(0x00+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4

  }

  if(gpro_t.tencent_link_success ==1){ //wifi icon 
  //number '2'
       TM1723_Write_Display_Data(0xC5,(0x01+lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5

    }
  
}


void Disip_Wifi_Icon_State(void)
{
   static uint8_t alternate_wifi_flag;

   if(gkey_t.wifi_led_fast_blink_flag==0){
   if(gpro_t.tencent_link_success ==0){

      if(gctl_t.gTimer_wifi_blink < 1  ){
          if(alternate_wifi_flag == 0){
             alternate_wifi_flag ++;
          TM1723_Write_Display_Data(0xC5,(0x01+lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5

            }
      }
      else if(gctl_t.gTimer_wifi_blink  > 0 && gctl_t.gTimer_wifi_blink  < 2){

          if(alternate_wifi_flag ==1){
             alternate_wifi_flag =0;
           TM1723_Write_Display_Data(0xC5,(lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5

            }
     }
      else if(gctl_t.gTimer_wifi_blink  > 1){

        gctl_t.gTimer_wifi_blink =0;
        alternate_wifi_flag =0;
         TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);

      }
      

     }
    
  }
  else{
    if(gpro_t.tencent_link_success ==0){
    
          if(gctl_t.gTimer_wifi_fast_blink < 19  ){ //9 * 10ms

             if(alternate_wifi_flag == 0){
                alternate_wifi_flag ++;
              
              TM1723_Write_Display_Data(0xC5,(0x01+lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5

              }
            }
          else if(gctl_t.gTimer_wifi_fast_blink  > 18 && gctl_t.gTimer_wifi_fast_blink < 28){

                  if(alternate_wifi_flag == 1){
                       alternate_wifi_flag =0;

                      TM1723_Write_Display_Data(0xC5,(lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5
                  }
          }
          else if(gctl_t.gTimer_wifi_fast_blink > 27){
    
           gctl_t.gTimer_wifi_fast_blink =0;
           alternate_wifi_flag =0;
            TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);
    
          }
          
    
       }
       else if(gpro_t.tencent_link_success ==1){
    
         TM1723_Write_Display_Data(0xC5,(0x01+lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5
        TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);
    
    
        }
      
    }

}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Number_ThreeFour_Temperature(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_ThreeFour_Temperature(void)
{
  //number '3' 
  TM1723_Write_Display_Data(0xC2,(0x01+lcdNumber3_High[glcd_t.number3_high] + lcdNumber3_Low[glcd_t.number3_low]  ) & 0xffff); //numbers : '3' addr: 0xC2

 //number '4' 
 TM1723_Write_Display_Data(0xC3,(0x01+lcdNumber4_High[glcd_t.number4_high] + lcdNumber4_Low[glcd_t.number4_low]) & 0xffff); //numbers : '4' addr: 0xC3


}

void lcd_donot_disp_number_34_temperature(void)
{
  //number '3' 
  TM1723_Write_Display_Data(0xC2,(0x01+lcdNumber3_High[0x0A] + lcdNumber3_Low[0X0A]  ) & 0xffff); //numbers : '3' addr: 0xC2

 //number '4' 
 TM1723_Write_Display_Data(0xC3,(0x01+lcdNumber4_High[0x0A] + lcdNumber4_Low[0x0A]) & 0xffff); //numb

}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Number_FiveSix_Hours(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_FiveSix_Hours(void)
{
   

   if(ptc_state()== 1){

        //number '5' and 'ptc' icon
        TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 
   }
   else{
       //number '5' and 'ptc' icon
        TM1723_Write_Display_Data(0xC9,(lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 

   }


   if(plasma_state() ==1){

   //number '6' 
    TM1723_Write_Display_Data(0xCA,(0x01+lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 

  }
  else{
      //number '6' 
    TM1723_Write_Display_Data(0xCA,(lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 

  }
}


void LCD_Numbers1234_Init(void)
{

     TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber5_High[0] + lcdNumber5_Low[0]  ) & 0xffff); 
     TM1723_Write_Display_Data(0xCA,(0x01+lcdNumber6_High[0] + lcdNumber6_Low[0] ) & 0xffff); 
     TM1723_Write_Display_Data(0xCB,(0x01+lcdNumber7_High[0] + lcdNumber7_Low[0]  ) & 0xffff);
     TM1723_Write_Display_Data(0xCC,(0x01+lcdNumber8_High[0] + lcdNumber8_Low[0] ) & 0xffff); //numbers :
     //AI icon display
     TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff);
     

}

/*****************************************************************************
 * 
 * Function Name:  static void LCD_Number_SevenEight_Minutes(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_SevenEight_Minutes(void)
{

  
     if(ultrasonic_state() == 1){


      if(gkey_t.key_mode == mode_set_timer || gkey_t.key_mode_switch_flag == 1){

         gkey_t.key_mode_switch_flag = 0;

        //timing ":" blank
           if(glcd_t.gtime_colon_symbol_flag ==0)
           	 TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low]) & 0xffff); //numbers : '1' addr: 0xC4
           else 
		   	   TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low]) & 0xffff); //number

	  }
	  //number '8'
	  TM1723_Write_Display_Data(0xCC,(0x01+lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers : '2' addr: 0xC

      }
      else{

         if(gkey_t.key_mode == mode_set_timer || gkey_t.key_mode_switch_flag == 1){

           gkey_t.key_mode_switch_flag = 0;

           //timing ":" blank
              if(glcd_t.gtime_colon_symbol_flag ==0)
              TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low]) & 0xffff); //numbers : '1' addr: 0xC4
              else
			  	 TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low]) & 0xffff); //numbers : '1' addr: 0xC4
		 }

         TM1723_Write_Display_Data(0xCC,(0x00+lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers

      }
}
/*****************************************************************************
 * 
 * Function Name: void display_works_times_four_numbers(uint8_t hours , uint8_t minutes,uint8_t sel)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void display_works_times_four_numbers(uint8_t hours , uint8_t minutes,uint8_t sel)
{

   if(sel ==0){
        glcd_t.number5_low = hours / 10;
		glcd_t.number5_high = hours / 10;


		glcd_t.number6_low = hours  % 10;
		glcd_t.number6_high = hours % 10;


        glcd_t.number7_low = minutes / 10;
		glcd_t.number7_high = minutes / 10;


		glcd_t.number8_low = minutes  % 10;
		glcd_t.number8_high = minutes % 10;
   	}
    else{
	  glcd_t.number5_low =  0x0A ;
      glcd_t.number5_high =  0x0A ;

      glcd_t.number6_low  =  0x0A; //
      glcd_t.number6_high =  0x0A; //
      
       //dispaly minutes 
      glcd_t.number7_low =   0x0A;
      glcd_t.number7_high =   0x0A;

      glcd_t.number8_low =   0x0A;
      glcd_t.number8_high =   0x0A;

    }



	if(ptc_state()== 1){
          TM1723_Write_Display_Data(0xC9,(DRY_Symbol+lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 
     }
     else{
          TM1723_Write_Display_Data(0xC9,(DRY_NO_Symbol+lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 

     }
	 
     if(plasma_state() ==1){

            TM1723_Write_Display_Data(0xCA,(PLASMA_Symbol+lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 

      }
      else{
          TM1723_Write_Display_Data(0xCA,(PLASMA_NO_Symbol+lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 

      }

	   //display time of colon symbol
      if(glcd_t.gtime_colon_symbol_flag == 0){
              TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low]) & 0xffff); //numbers : '1' addr: 

       }
       else{

         TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
       
       }
      

       if(ultrasonic_state() == 1){
        
             TM1723_Write_Display_Data(0xCC,(0x01+lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers

       }
       else{

          TM1723_Write_Display_Data(0xCC,(0x00+lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers
       }

      // TIM1723_Write_Cmd(LUM_VALUE);//(0x9B);
}

/*****************************************************************************
 * 
 * Function Name: static LCD_Fault_Numbers_Code(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static uint8_t Detecting_Fault_Code(void)
{
  

     if(ptc_error_state() == error){
		  ptc_error_flag = 1;
	 }
	 else{
		 ptc_error_flag =0;
	
	 }
	
	 if(fan_error_state()== error){
		fan_error_flag =1;

	 }
	 else{
	   fan_error_flag =0;
	
	 }

	 if(ptc_error_flag ==1 || fan_error_flag==1){

        return 1;
	 }
	 else
	    return 0;

	 

}
/*************************************************************************************
	*
	*Function Name: LCD_Fault_Numbers_Code(void)
	*Function : display error of code
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void LCD_Fault_Numbers_Code(void)
{

 
 // display "E",turn off dry icon 'ICON'of fucntion

 TM1723_Write_Display_Data(0xC9,(lcdNumber5_Low_E[0]  + lcdNumber5_High_E[0]) & 0xff); //numbers : '3' addr: 0xC2
   
 if(plasma_state()==1){
 //display 'r' 
 TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0] + PLASMA_Symbol) & 0xff); //numbers : 'r' 
  }
  else 
     TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0]) & 0xff); //numbers : 'r' 

 //display error code "01"--ptc_warning , "02"--fan_warning

 
 //"01" or "o2" blink
  if(glcd_t.gTimer_error_times < 2){ //500ms
  	if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==0){ //code is "02" ==1){ 

         //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
         if(ultrasonic_state()==1){
        
              TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xff);
			  if(glcd_t.gtime_colon_symbol_flag==0)
              	TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL + lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); //numbers : '1' addr: 0xC4
			  else
			  	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL + lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); 
		 }//numbers : '2' addr: 0xC
          else{
            
            TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1]) & 0xff);

          }

    }
	else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){ //code is "02"){
         	
  	     //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
        
        if(ultrasonic_state()==1){
            TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC
        }
        else{
             TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xff); 

        }

     }
     else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){ //code is "02" ==1){ 


          if(ultrasonic_state()==1){
        
              TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xff);
          }//numbers : '2' addr: 0xC
          else{
            
            TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1]) & 0xff);

          }

      }
   }
  else if(glcd_t.gTimer_error_times > 1 && glcd_t.gTimer_error_times < 4){


   if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==0 ){ //code is "02" ==1){ 
        //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] ) & 0xffff); //numbers : '2' addr: 0xC
        if(ultrasonic_state()==1){
        
              TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xff);
          }//numbers : '2' addr: 0xC
          else{
            
            TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1]) & 0xffff);

          }

     }
     else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0 ){ //code is "02"){
               
        //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xffff); //numbers : '2' addr: 0xC
        if(ultrasonic_state()==1){
                TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC
            }
            else{
                 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xff); 

            }

     }
     else if(gctl_t.ptc_warning==1 &&  gctl_t.fan_warning ==1 ){


   	 

        //error : 02
        if(ultrasonic_state()==1){
                TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
            }
            else{
                 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xffff); 

            }

            
       
         
   	   //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xffff); //numbers : '2' addr: 0xC

      }
   }
   else if(glcd_t.gTimer_error_times > 3){
      glcd_t.gTimer_error_times =0;
      if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==0){ //code is "02" ==1){ 
    	//TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
         if(ultrasonic_state()==1){
        
              TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xffff);
          }//numbers : '2' addr: 0xC
          else{
            
            TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1]) & 0xffff);

          }



      }
	 else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){ //code is "02"){
         	
  	    // TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
        if(ultrasonic_state()==1){
                TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
            }
            else{
                 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xffff); 

            }

     }
     else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){ //code is "02" ==1){ 

     }

  
   }

}

/*************************************************************************************
	*
	*Function Name: void fan_error_code_number(void)
	*Function : display error of code
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void fan_error_code_number(void)
{
 
 if(gctl_t.fan_warning ==1){

 
 // display "E",turn off dry icon 'ICON'of fucntion

 TM1723_Write_Display_Data(0xC9,(lcdNumber5_Low_E[0]  + lcdNumber5_High_E[0]) & 0xff); //numbers : '3' addr: 0xC2
   
 if(gctl_t.plasma_flag == 1){
    //display 'r' 
    TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0] + PLASMA_Symbol) & 0xff); //numbers : 'r' 
  }
  else 
     TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0]) & 0xff); //numbers : 'r' 

 //display error code "01"--ptc_warning , "02"--fan_warning


 // if(glcd_t.gTimer_error_times < 2){ //500ms
  	
    if(ultrasonic_state()==1){
		 if(glcd_t.gtime_colon_symbol_flag==0)
             TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); //numbers : '1' addr: 0xC4
         else
		 	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); 

		 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xff);
             
    }//display "02"
    else{
			if(glcd_t.gtime_colon_symbol_flag==0)
				TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); //numbers : '1' addr: 0xC4 
			else
				TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff);

			TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2]) & 0xff);

    }

    osDelay(300);

     if(ultrasonic_state()==1){
     if(glcd_t.gtime_colon_symbol_flag==0)
     	TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL +lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff); //numbers : '1' addr: 0xC4 
     else
	 	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL +lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff);
	 
	 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[0x0A] + lcdNumber8_Low[0x0A]+BUG_Symbol) & 0xff);
     }
     else{

		if(glcd_t.gtime_colon_symbol_flag==0)
             TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff); //numbers : '1' addr: 0xC4 
        else
			TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff); 

		TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[0x0A] + lcdNumber8_Low[0x0A]) & 0xff);


     }
    osDelay(300);

  }  

}
/*************************************************************************************
	*
	*Function Name: void ptc_error_code_number(void)
	*Function : display error of code
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void ptc_error_code_number(void)
{
 
 if(gctl_t.ptc_warning ==1){

 
 // display "E",turn off dry icon 'ICON'of fucntion

 TM1723_Write_Display_Data(0xC9,(lcdNumber5_Low_E[0]  + lcdNumber5_High_E[0]) & 0xff); //numbers : '3' addr: 0xC2
   
 if(plasma_state()==1){
    //display 'r' 
    TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0] + PLASMA_Symbol) & 0xff); //numbers : 'r' 
  }
  else 
     TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0]) & 0xff); //numbers : 'r' 

 //display error code "01"--ptc_warning , "02"--fan_warning


 // if(glcd_t.gTimer_error_times < 2){ //500ms
  	
    if(ultrasonic_state()==1){
		 if(glcd_t.gtime_colon_symbol_flag ==0)
         	TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); //numbers : '1' addr: 0xC4
		 else
		 	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff);
		 
		 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xff);
             
    }//display "02"
    else{

           if(glcd_t.gtime_colon_symbol_flag ==0)
			TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff); //numbers : '1' addr: 0xC4 
           else
		   	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0] + lcdNumber7_Low[0]) & 0xff);

		   TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1]) & 0xff);

    }

    osDelay(300);

     if(ultrasonic_state() == 1){
       if(glcd_t.gtime_colon_symbol_flag ==0)
       TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL+lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff); //numbers : '1' addr: 0xC4 
       else 
	   	 TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff);

	   TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[0x0A] + lcdNumber8_Low[0x0A]+ BUG_Symbol) & 0xff);
     }
     else{
         if(glcd_t.gtime_colon_symbol_flag ==0)
         TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL +lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff); //numbers : '1' addr: 0xC4 
         else
		 	TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[0x0A] + lcdNumber7_Low[0x0A]) & 0xff);
		 
		 TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[0x0A] + lcdNumber8_Low[0x0A]) & 0xff);


     }

    osDelay(300);

  }  

}

 
/*****************************************************************************
 * 
 * Function Name:  void LCD_Wind_Icon(uint8_t wind_sppeed)
 * Function: run wind speed value 
 * Input Ref:  wind_speed =0, is max ,wind_speed= 1, middle, wind_speed =2 is low
 * Return Ref:
 * 
*****************************************************************************/
#if 0
void LCD_Fan_Run_Icon(uint8_t wind_speed)
{


   static uint8_t alternate_flag;

   if(gctl_t.fan_warning == 0){
   switch(wind_speed){


   case 0x64:


   case 0: //max wind speed.
    
        if(glcd_t.gTimer_fan_blink > 10){ //open 

			glcd_t.gTimer_fan_blink=0;

            alternate_flag = alternate_flag ^ 0x01;

		    if(alternate_flag ==1){
            TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T17_WIND_SPEED_MID+T15+T9+T13) & 0xffff));//display  wind icon
            TM1723_Write_Display_Data(0xCF,((T18_WIND_SPEED_FULL+ T11)& 0xff));//display  wind icon	

            }
            else { //close

          
            TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T17_WIND_SPEED_MID+T15 +T10+T12+T14)& 0xffff));//display  wind icon
            TM1723_Write_Display_Data(0xCF,((T18_WIND_SPEED_FULL)& 0xff));//display  wind icon	

            }

        }
    break;

    

    case 1: //middle 

         if(glcd_t.gTimer_fan_blink  >11){ //open 
         glcd_t.gTimer_fan_blink=0;
              alternate_flag = alternate_flag ^ 0x01;
        		
               if(alternate_flag==1){ 
               TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T17_WIND_SPEED_MID+T15+T9+T13)&0xff));//display  wind icon
        	   TM1723_Write_Display_Data(0xCF,T11);//display  wind icon	
               }
               else{ //close

             
        	   TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T17_WIND_SPEED_MID+T15 +T10+T12+T14) & 0xffff));//display  wind icon
        	   TM1723_Write_Display_Data(0xCF,  0x00);//display  wind icon	
               }

        
        	}


    break;


    case 2: //lowd 


        if(glcd_t.gTimer_fan_blink > 15){ //open 
			   glcd_t.gTimer_fan_blink=0;

             alternate_flag = alternate_flag ^0x01;

			   if(alternate_flag==1){
        		
        	   TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T15+T9+T13)& 0xffff));//display  wind icon
        	   TM1723_Write_Display_Data(0xCF,T11);//display  wind icon	
                }
               else { //close

        		
        	   TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T15 +T10+T12+T14)& 0xffff));//display  wind icon
        	   TM1723_Write_Display_Data(0xCF,  0x0);//display  wind icon
                }

        	}
        	
       


    break;

   }

   }
}  


void Display_Wind_Icon_Inint(void)
{

   TIM1723_Write_Cmd(0x00); // 0x00 -> display setup model
   TIM1723_Write_Cmd(0x40); // 0x40 ->write data to display of register
	TIM1723_Write_Cmd(0x44); // 0x44 -> write fix of address model

   TM1723_Write_Display_Data(0xCE,((T16_WIND_SPEED_LOW+T17_WIND_SPEED_MID+T15+T9+T13) & 0xffff));//display  wind icon
    TM1723_Write_Display_Data(0xCF,((T18_WIND_SPEED_FULL+ T11)& 0xffff));//display  wind icon	

     TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);
}
#endif 
/*****************************************************************************
 * 
 * Function Name:  static LCD_Timer_Colon_Blink(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void dispLCD_timeColon_handler(void)
{

   if(glcd_t.gTimer_colon_blink > 0){ //if(glcd_t.gTimer_colon_blink > 4 && glcd_t.gTimer_colon_blink < 7){
		 glcd_t.gTimer_colon_blink=0;

	     glcd_t.gtime_colon_symbol_flag= glcd_t.gtime_colon_symbol_flag ^ 0x01;
   	}


   
 
   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

   

        switch(gkey_t.key_mode){

         
         case disp_works_timing :

	

	          glcd_t.number7_low = gpro_t.disp_works_minutes_value / 10;
			  glcd_t.number7_high = glcd_t.number7_low ;

		  
		 
		  if(glcd_t.gtime_colon_symbol_flag ==0)
             TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
          else 
		  	 TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL+lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
           
		  	
		 
         break;

         case disp_timer_timing:

			
             if(gkey_t.set_timer_timing_success ==1){
             
                    glcd_t.number7_low = gpro_t.set_timer_timing_minutes / 10;
		            glcd_t.number7_high =   glcd_t.number7_low;
			        if(glcd_t.gtime_colon_symbol_flag ==0)
                    	TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
                    else
						TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
             
              }
              else if(gkey_t.set_timer_timing_success == 0){ //&& gkey_t.gTimer_disp_switch_disp_mode > 3){
             
                     glcd_t.number7_low=0;
				     glcd_t.number7_high=0;

				
				
				if(glcd_t.gtime_colon_symbol_flag ==0)
				TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
				else
				TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
			 }
      
         break;

         case mode_set_timer:
		 	if(glcd_t.gtime_colon_symbol_flag ==0)
              TM1723_Write_Display_Data(0xCB,(COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
            else
			  TM1723_Write_Display_Data(0xCB,(NO_COLON_SYMBOL + lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] ) & 0xffff);
         break;

         }
     }
   // TIM1723_Write_Cmd(LUM_VALUE);//(0x9B);

 }
   
    
 

/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Off(void)
	*Function : don't display any one
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void Lcd_Display_Off(void)
{

	 TIM1723_Write_Cmd(CloseDispTM1723);//(0x80);

}



void Disp_HumidityTemp_Init(void)
{

    LCD_Number_ThreeFour_Temperature();
    LCD_Number_Ai_OneTwo_Humidity();

}


void Disp_SetTemp_Value(uint8_t temp_value)
{

    glcd_t.number3_low  = temp_value /10;
    glcd_t.number3_high = temp_value / 10;

    glcd_t.number4_low =  temp_value % 10;
    glcd_t.number4_high = temp_value % 10;

    
        

    LCD_Number_ThreeFour_Temperature();


}

/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Dry_Icon(void)
	*Function : display dry of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void disp_ai_iocn(void)
{

if(ai_mode_state()== 1){ //AI state 
 //number '1'
    TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4
 }
 else{
       //number '1'
    TM1723_Write_Display_Data(0xC4,(0x00+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4

 }

}

void disp_ai_symbol(void)
{
   TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4

}

void donot_disp_ai_symbol(void)
{

   TM1723_Write_Display_Data(0xC4,(0x00+lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xffff); //numbers : '1' addr: 0xC4

 }
/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Dry_Icon(void)
	*Function : display dry of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void Disp_Dry_Icon(void)
{
  
   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

        if(ptc_state()== 1){
        
                //number '5' and 'ptc' icon
                TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 
           }
           else{
               //number '5' and 'ptc' icon
                TM1723_Write_Display_Data(0xC9,(lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low]  ) & 0xffff); 
        
           }

    }
   
}

/*************************************************************************************
	*
	*Function Name: void Disp_Kill_Icon(void)
	*Function : display plasma of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void Disp_Kill_Icon(void)
{

   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning == 0){
    if(plasma_state() ==1){
    
     //number '6' 
      TM1723_Write_Display_Data(0xCA,(0x01+lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 
    
    }
    else{
        //number '6' 
      TM1723_Write_Display_Data(0xCA,(lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] ) & 0xffff); 
    
    }

    }



}

/*************************************************************************************
	*
	*Function Name: void Disp_Ultrsonic_Icon(void)
	*Function : display plasma of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void Disp_Ultrsonic_Icon(void)
{

    if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
        if(ultrasonic_state()==1){
        //number '8'
    	  TM1723_Write_Display_Data(0xCC,(0x01+lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers : '2' addr: 0xC
        }
        else{

             TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] ) & 0xffff); //numbers : '2' addr: 0xC

        }

    }
    
}





void Wifi_Icon_FastBlink(void)
{
    if(gkey_t.wifi_led_fast_blink_flag==1){
    if(gpro_t.tencent_link_success==0){
    
          if(gctl_t.gTimer_wifi_blink < 1  ){
              TM1723_Write_Display_Data(0xC5,(0x01+lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5
          }
          else if(gctl_t.gTimer_wifi_blink  > 0 && gctl_t.gTimer_wifi_blink  < 2){
               TM1723_Write_Display_Data(0xC5,(lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xffff); //numbers : '2' addr: 0xC5
    
          }
          else if(gctl_t.gTimer_wifi_blink  > 1){
    
            gctl_t.gTimer_wifi_blink =0;
    
          }
          
    
       }
    }

}


void OnlyDisp_Wind_Icon_Handler(void)
{
    TM1723_Write_Display_Data(0xC2,0x0);
    TM1723_Write_Display_Data(0xC3,0x0);
    TM1723_Write_Display_Data(0xC4,0x0);
    TM1723_Write_Display_Data(0xC5,0x0);

    TM1723_Write_Display_Data(0xC9,0x0);

    TM1723_Write_Display_Data(0xCA,0x0);
    TM1723_Write_Display_Data(0xCB,0x0);

    TM1723_Write_Display_Data(0xCC,0x0);

    wifi_t.set_wind_speed_value=0;
    
    LCD_Fan_Run_Icon(wifi_t.set_wind_speed_value);


}

void LcdDisp_Init(void)
{
    
        TM1723_Write_Display_Data(0xC2,0x0);
        TM1723_Write_Display_Data(0xC3,0x0);
        TM1723_Write_Display_Data(0xC4,0x0);
        TM1723_Write_Display_Data(0xC5,0x0);
    
        TM1723_Write_Display_Data(0xC9,0x0);
    
        TM1723_Write_Display_Data(0xCA,0x0);
        TM1723_Write_Display_Data(0xCB,0x0);
    
        TM1723_Write_Display_Data(0xCC,0x0);
    
       TM1723_Write_Display_Data(0xCE,0x0);
       TM1723_Write_Display_Data(0xCF,0x0); 
       
    



}


void disp_time_4bit_init(void)
{

	glcd_t.number5_low = 0;
	glcd_t.number5_high = 0;


	glcd_t.number6_low =0;
	glcd_t.number6_high =0;




	glcd_t.number7_low = 0;
	glcd_t.number7_high = 0;

	   
	glcd_t.number8_low = 0;
	glcd_t.number8_high = 0;
}
