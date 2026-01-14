#ifndef __BSP_CMD_LINK_H
#define __BSP_CMD_LINK_H
#include "main.h"

//extern uint8_t disp_inputBuf[4];

void sendData_setTemp_value(uint8_t temp);


void sendData_Real_TimeHum(uint8_t hum,uint8_t temp);

void SendData_Tx_Data(uint8_t dcmd,uint8_t ddata);

void SendWifiData_To_PanelWindSpeed(uint8_t dat1);


void SendWifiData_To_PanelTime(uint8_t hours,uint8_t minutes,uint8_t seconds);

void SendWifiData_To_Data(uint8_t cmd,uint8_t data);

void SendData_Set_Command(uint8_t cmd,uint8_t data) ;

void SendWifiData_Ref_three(uint8_t ptc,uint8_t plasma,uint8_t ultra);

void SendWifiData_To_SynTimerTime(uint8_t hours,uint8_t minutes,uint8_t seconds);


void SendWifiData_Answer_Cmd(uint8_t cmd, uint8_t cmdata) ;

void sendDisplayCommand(uint8_t command,uint8_t data) ;

void SendData_Data(uint8_t cmd, uint8_t data) ;



#endif 


