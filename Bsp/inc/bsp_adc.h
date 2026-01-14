#ifndef __BSP_ADC_H_
#define __BSP_ADC_H_
#include "main.h"


void Judge_PTC_Temperature_Value(void);
void Get_PTC_Temperature_Voltage(uint32_t channel,uint8_t times);


void Get_Fan_Adc_Fun(uint32_t channel,uint8_t times);

void detected_ptc_fan_error_handler(void);


#endif
