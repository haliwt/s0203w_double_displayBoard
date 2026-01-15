#include "bsp.h"

// 寮曡剼瀹氫箟 - 鏍规嵁瀹為檯杩炴帴淇敼
#define TM1723_SCK_PORT     GPIOB
#define TM1723_SCK_PIN      GPIO_PIN_6

#define TM1723_MOSI_PORT    GPIOB
#define TM1723_MOSI_PIN     GPIO_PIN_5

#define TM1723_CS_PORT      GPIOB
#define TM1723_CS_PIN       GPIO_PIN_7

#define TM1723_STB_PORT    GPIOB
#define TM1723_STB_PIN    GPIO_PIN_7

// TM1723鍛戒护瀹氫箟
#define TM1723_CMD_DATA     0x40
#define TM1723_CMD_DISPLAY  0x80
#define TM1723_CMD_ADDRESS  0xC0

// 鏄剧ず鎺у埗閫夐」
#define TM1723_DISPLAY_ON   0x08
#define TM1723_DISPLAY_OFF  0x00
#define TM1723_PULSE_1_16   0x00
#define TM1723_PULSE_2_16   0x01
#define TM1723_PULSE_4_16   0x02
#define TM1723_PULSE_10_16  0x03

// TM1723 鍛戒护瀹氫箟
#define TM1723_CMD_DATA_SET       0x40  // 鏁版嵁璁剧疆鍛戒护
#define TM1723_CMD_ADDR_FIXED     0x42  // 鍥哄畾鍦板潃妯″紡
#define TM1723_CMD_ADDR_AUTO_INC  0x40  // 鑷姩閫掑鍦板潃妯″紡
#define TM1723_CMD_DISPLAY_START  0xC0  // 鏄剧ず璧峰鍦板潃


// 寤舵椂瀹忓畾涔夛紙鏍规嵁涓婚璋冩暣锛?
#define SOFT_SPI_DELAY()    do { \
    asm volatile ("nop"); asm volatile ("nop"); \
    asm volatile ("nop"); asm volatile ("nop"); \
} while(0)



// 寤舵椂鍑芥暟
void Delay_us(uint16_t us) {
    //HAL_Delay(us / 1000 + 1);  // 绠?鍗曞疄鐜帮紝鑷冲皯淇濊瘉 1ms 鐨勫欢鏃?
}

  /**
 * @brief  TM1723鍐欏叆涓?涓瓧鑺?
 * @param  byte: 瑕佸啓鍏ョ殑瀛楄妭
 * @retval None
 */
static void SoftSPI_WriteByte(uint8_t data)
{

    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        TM1723_CLK_SetLow();
        delay_us(2);
        
        if(data & 0x01)
            TM1723_DIO_SetHigh(); //鍐欏叆鏁版嵁 鈥?1鈥?
        else
            TM1723_DIO_SetLow(); //鍐欏叆鏁版嵁 鈥?0鈥?
            
        delay_us(2);
        TM1723_CLK_SetHigh();
        delay_us(2);
        data >>= 1;
    }
}


// 鍚戞寚瀹氬湴鍧?鍐欏叆鏁版嵁
void TM1723_WriteData(uint8_t addr, uint8_t data)
{

   #if 0
// 鎷変綆CS
    HAL_GPIO_WritePin(TM1723_CS_PORT, TM1723_CS_PIN, GPIO_PIN_RESET);
    
    // 鍙戦?佸湴鍧?鍛戒护 (鍥哄畾鍦板潃妯″紡)
    SoftSPI_WriteByte(TM1723_CMD_ADDRESS | (addr & 0x0F));
    
    // 鍙戦?佹暟鎹懡浠? + 鍐欐暟鎹?
    SoftSPI_WriteByte(TM1723_CMD_DATA | 0x00);
    SoftSPI_WriteByte(data);
    
    // 鎷夐珮CS
    HAL_GPIO_WritePin(TM1723_CS_PORT, TM1723_CS_PIN, GPIO_PIN_SET);
	#else
	// 鍙戦?佸湴鍧?鍜屾暟鎹?
    SoftSPI_WriteByte(TM1723_CMD_DISPLAY_START | (addr & 0x0F));
   SoftSPI_WriteByte(data);




	#endif 
	
}





// 璁剧疆鏄剧ず鍙傛暟
void TM1723_SetDisplay(uint8_t on_off, uint8_t pulse_width)
{
    uint8_t cmd = TM1723_CMD_DISPLAY | on_off | (pulse_width & 0x03);
    
    // 鎷変綆CS
    HAL_GPIO_WritePin(TM1723_CS_PORT, TM1723_CS_PIN, GPIO_PIN_RESET);
    
    // 鍙戦?佸懡浠?
    SoftSPI_WriteByte(cmd);
    
    // 鎷夐珮CS
    HAL_GPIO_WritePin(TM1723_CS_PORT, TM1723_CS_PIN, GPIO_PIN_SET);
}

// 娓呴櫎鎵?鏈夋樉绀?
//void TM1723_ClearAll(void)
//{
//    uint8_t clear_data[16] = {0};
//    TM1723_WriteMultipleData(0, clear_data, 16);
//}


/**
 * @brief  关闭�?有显示（包括数码管和LED�?
 * @param  None
 * @retval None
 */
void TM1723_All_Off(void)
{
    
     TM1723_Write_Display_Data(0xC2,0x0); 
     TM1723_Write_Display_Data(0xC3,0X0); 
     TM1723_Write_Display_Data(0xC4,0X0);
     TM1723_Write_Display_Data(0xC5,0X0); //numbers :

	 TM1723_Write_Display_Data(0xC9,0x0); 
     TM1723_Write_Display_Data(0xCA,0X0); 
     TM1723_Write_Display_Data(0xCB,0X0);
     TM1723_Write_Display_Data(0xCC,0X0); //numbers :

     TM1723_Write_Display_Data(0xCE,0X0);
	 TM1723_Write_Display_Data(0xCF,0X0);
     
}

