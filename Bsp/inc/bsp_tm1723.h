#ifndef __BSP_TM1723_H
#define __BSP_TM1723_H
#include "main.h"





// 函数声明

void TM1723_WriteData(uint8_t addr, uint8_t data);

void TM1723_All_Off(void);

//void TM1723_WriteMultipleData(uint8_t start_addr, uint8_t *data, uint8_t len);
//void TM1723_SetDisplay(uint8_t on_off, uint8_t pulse_width);
//void TM1723_ClearAll(void);
//void TM1723_WriteDigit(uint8_t digit, uint8_t value, uint8_t dot);
//void TM1723_DisplayNumber(uint16_t number, uint8_t start_digit, uint8_t length);


#endif 

