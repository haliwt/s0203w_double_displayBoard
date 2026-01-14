#include "bsp_led.h"
#include "bsp.h"




static uint8_t Delay(int32_t count);

 uint32_t led_k;


void LED_POWER_ON(void)
{
    LED_POWER_KEY_SetHigh() ;


}
void LED_POWER_OFF(void)
{
	LED_POWER_KEY_SetLow() ;
}

void LED_Mode_On(void)
{
  LED_MODE_SetHigh();	

}
void LED_Mode_Off(void)
{

	LED_MODE_SetLow()	;


}

#if 0
static uint8_t  Delay(int32_t count)
{
   
    if(count ==0 || count <0){
       return 1;
    
    }
    else{
       while(count){

        count--;
       }

       return 0;
   }
  

}
#endif 

/***************************************************************
*
*Function Name: void LED_TempHum(void)
*Function : display temperature and humidity and times led 
*
*
*
**************************************************************/
void Breath_Led(void)
{
   
    static uint8_t breathing_time = 0;
    static uint8_t led_state = 0;
    
    breathing_time++;
    if(breathing_time >= 100)  // 呼吸周期1秒
    {
        breathing_time = 0;
        led_state = !led_state;
        
        if(led_state)
        {
            LED_POWER_ON();
        }
        else
        {
            LED_POWER_OFF();
        }
    }

}
	




void Backlight_On(void)
{
	BACKLIGHT_SetHigh();

}
void Backlight_Off(void)
{

	BACKLIGHT_SetLow();


}

