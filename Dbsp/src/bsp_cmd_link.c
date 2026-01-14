#include "bsp.h"

#define MAX_BUFFER_SIZE  12

#define MAX_BUFFER_SIZE  12

#define USART1_IT_FLAG   0

#define FRAME_HEADER 0x5A
#define FRAME_END 0xFE



static uint8_t transferSize;
static uint8_t outputBuf[MAX_BUFFER_SIZE];

volatile uint8_t transOngoingFlag;
volatile uint8_t usart2_transOngoingFlag;

/********************************************************************************
	**
	*Function Name:void FillFrame(uint8_t *buf, uint8_t cmd, uint8_t *data, uint8_t dataLen) 
	*Function :
	*Input Ref: humidity value and temperature value
	*Return Ref:NO
	*
*******************************************************************************/
void FillFrame(uint8_t *buf, uint8_t cmd, uint8_t *data, uint8_t dataLen) 
{
    buf[0] = FRAME_HEADER;
    buf[1] = 0x10; // Mainboard device number
    buf[2] = cmd;
	if(dataLen ==0) buf[3]=0;
    else buf[3] = 0x0F ; // Data or command

	if(buf[3] ==0){
       buf[4] = data[0];
       buf[5] = FRAME_END;
	   buf[6] = bcc_check(buf, 6 );
	}
	else{
	      buf[4] = dataLen;
	
		   for (uint8_t i = 0; i < dataLen; i++) {
			   buf[5 + i] = data[i];
		   }
	
		   buf[5 + dataLen] = FRAME_END;
		   buf[6 + dataLen] = bcc_check(buf, 6 + dataLen);


	}
}

// �?

void FillFrame_Response(uint8_t *buf, uint8_t cmd, uint8_t *data, uint8_t dataLen) 
{
    buf[0] = FRAME_HEADER;          // 帧头
    buf[1] = 0x10;                  // 主板设备�?
    buf[2] = 0xFF;                  // 应答信号标志
    buf[3] = cmd;                   // 命令类型
    buf[4] = (dataLen > 0) ? 0x0F : 0x00; // 数据标志�?0x0F 表示有数据，0x00 表示无数�?

    if (buf[4] == 0x00) {           // 无数据的情况
        buf[5] = data[0];           // 具体指令
        buf[6] = FRAME_END;         // 帧尾
        buf[7] = bcc_check(buf, 7); // 校验�?
    } else {                        // 有数据的情况
        buf[5] = dataLen;           // 数据长度
        if (data != NULL) {         // �?查数据指针是否有�?
            for (uint8_t i = 0; i < dataLen; i++) {
                buf[6 + i] = data[i]; // 填充数据
            }
        }
        buf[6 + dataLen] = FRAME_END;         // 帧尾
        buf[7 + dataLen] = bcc_check(buf, 7 + dataLen); // 校验�?
    }
}
// 公共函数：发送数�?
void TransmitData(uint8_t *buf, uint8_t size) 
{
    transferSize = size;

    #if 0
    if (transferSize) {
        while (transOngoingFlag); // 等待传输完成
        transOngoingFlag = 1;
        HAL_UART_Transmit_IT(&huart1, buf, transferSize);
    }
    #else
    	HAL_UART_Transmit_DMA(&huart1, buf, transferSize);
    #endif
}
//送命令响�?
void SendWifiData_Answer_Cmd(uint8_t cmd, uint8_t cmdata) 
{
    uint8_t cmdData[1] = {cmdata};
    FillFrame_Response(outputBuf, cmd,cmdData ,0);
    TransmitData(outputBuf,8);
}


/******************************************************************************
	*
	*Function Name:void set_timer_timing_value_handler(void)
	*Funcion: // 发�?�显示命�?
	*Input Ref: NO
	*Return Ref:NO
	*
******************************************************************************/
// 发�?�命令数�?
void SendData_Set_Command(uint8_t cmd, uint8_t data) 
{
    uint8_t cmdData[1] = {data};
    FillFrame(outputBuf, cmd, cmdData, 0);
    TransmitData(outputBuf, 7);
}

void sendDisplayCommand(uint8_t command,uint8_t data) 
{
    
	SendData_Set_Command(command, data);
    
}

void SendData_Data(uint8_t cmd, uint8_t data) 
{
    uint8_t cmdData[1] = {data};
    FillFrame(outputBuf, cmd, cmdData, 1);
    TransmitData(outputBuf, 8);
}


/********************************************************************************
	**
	*Function Name:
	*Function :
	*Input Ref: humidity value and temperature value
	*Return Ref:NO
	*
*******************************************************************************/
void sendData_setTemp_value(uint8_t temp)
{

	//crc=0x55;
	outputBuf[0]=0x5A; //head : mainboard Board = 0x5A
	outputBuf[1]=0x10; //main board device No: 0x10
	outputBuf[2]=0x2A; //set temperature value 
	outputBuf[3]=0x0F; // 0x0F : is data ,don't command data.
	outputBuf[4]= 0x01; //data of length: 0x01 - 2 byte.
	outputBuf[5] =temp;
 

    outputBuf[6] = 0xFE; //frame of end flag .
    outputBuf[7] = bcc_check(outputBuf,7);
	
	//for(i=3;i<6;i++) crc ^= outputBuf[i];
	//outputBuf[i]=crc;
	transferSize=8;
	#if 0
	if(transferSize)
	{
		while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 



}
/********************************************************************************
	**
	*Function Name:sendData_Real_TimeHum(uint8_t hum,uint8_t temp)
	*Function :
	*Input Ref: humidity value and temperature value
	*Return Ref:NO
	*
*******************************************************************************/
void sendData_Real_TimeHum(uint8_t hum,uint8_t temp)
{

	//crc=0x55;
	outputBuf[0]=0x5A; //head : mainboard Board = 0x5A
	outputBuf[1]=0x10; //main board device No: 0x10
	outputBuf[2]=0x1A; //command : temperature of value 
	outputBuf[3]=0x0F; // 0x0F : is data ,don't command data.
	outputBuf[4]= 0x02; //data of length: 0x01 - 2 byte.
	outputBuf[5] =hum;
    outputBuf[6] =temp;

    outputBuf[7] = 0xFE;
    outputBuf[8] = bcc_check(outputBuf,8);
	
	//for(i=3;i<6;i++) crc ^= outputBuf[i];
	//outputBuf[i]=crc;
	transferSize=9;
	#if 0
	if(transferSize)
	{
		while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 



}
/********************************************************************************
    **
    *Function Name:void SendWifiData_To_PanelTime(uint8_t hours,uint8_t minutes,uint8_t seconds)
    *Function :
    *Input Ref: hours,minutes,seconds of beijing time 
    *Return Ref:NO
    *
*******************************************************************************/
void SendWifiData_To_PanelTime(uint8_t hours,uint8_t minutes,uint8_t seconds)
{
    outputBuf[0]=0x5A; //mainboard head : displayBoard = 0xA5
	outputBuf[1]=0x10; //mainboard device No: 01
	outputBuf[2]=0x1C; //command : is data of hours and minutes and seconds.
	outputBuf[3]=0x0F; // 0x0F : is data ,don't command data.
	outputBuf[4]= 0x03; //data of length: 0x01 - 3 byte.
	outputBuf[5]= hours; //	
	outputBuf[6]= minutes; //	
	outputBuf[7]= seconds; //	

    outputBuf[8] = 0xFE;
    outputBuf[9] = bcc_check(outputBuf,9);

	transferSize=10;
	#if 0
	if(transferSize)
	{
	while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
	transOngoingFlag=1;
	HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
}
/********************************************************************************
    **
    *Function Name:void SendWifiData_To_PanelTime(uint8_t hours,uint8_t minutes,uint8_t seconds)
    *Function :
    *Input Ref: hours,minutes,seconds of beijing time 
    *Return Ref:NO
    *
*******************************************************************************/
void SendWifiData_To_SynTimerTime(uint8_t hours,uint8_t minutes,uint8_t seconds)
{
    outputBuf[0]=0x5A; //mainboard head : displayBoard = 0xA5
	outputBuf[1]=0x10; //mainboard device No: 01
	outputBuf[2]=0x5C; //command : is data of hours and minutes and seconds.
	outputBuf[3]=0x0F; // 0x0F : is data ,don't command data.
	outputBuf[4]= 0x03; //data of length: 0x01 - 3 byte.
	outputBuf[5]= hours; //	
	outputBuf[6]= minutes; //	
	outputBuf[7]= seconds; //	

    outputBuf[8] = 0xFE;
    outputBuf[9] = bcc_check(outputBuf,9);

	transferSize=10;
	#if 0
	if(transferSize)
	{
	while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
	transOngoingFlag=1;
	HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
}

/*********************************************************
 * 
 * Function Name:void SendData_Temp_Data(uint8_t tdata)
 * Function:send temperature value 
 * 
*********************************************************/
#if 0
void SendData_Set_Command(uint8_t cmd,uint8_t data)  //  SendData_Set_Command(0x21, 0x01); //smart phone power on command .
{
    outputBuf[0]=0x5A; //main board head = 0x5A
	outputBuf[1]= 0x10; //display device Number:is 0x01
	outputBuf[2]=cmd; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]= data; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=0x00; // data is length: 00 ->don't data 
	outputBuf[5]=0xFE; // frame of end code -> 0xFE.
    outputBuf[6] = bcc_check(outputBuf,6);


		transferSize=7;
	#if 0
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
		#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
	
}
#endif 
/*********************************************************
 * 
 * Function Name:void SendData_Tx_Data(uint8_t dcmd,uint8_t ddata)
 * Function: 
 * Input Ref:cmd- command , dmddata-> command of mode .
 * Return Ref:NO
 * 
*********************************************************/
void SendData_Tx_Data(uint8_t dcmd,uint8_t ddata)

{
	outputBuf[0]=0x5A; //main board head = 0x5A
	outputBuf[1]= 0x10; //main board device number: 0x10 .
	outputBuf[2]= dcmd; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]= 0x0f; //  0x0f -> is data ,don't command.
	outputBuf[4]=0x01; // data is length: 00 ->don't data ,0x01 -> has one data.
    outputBuf[5]=ddata; // frame of end code -> 0xFE.
    outputBuf[6]=0xFE; // frame of end code -> 0xFE.
    outputBuf[7] = bcc_check(outputBuf,7);


		transferSize=8;
	#if 0
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
		#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
	
}
/********************************************************************************
    **
    *Function Name:void SendWifiData_Ref_three(uint8_t ptc,uint8_t plasma,uint8_t ultra)
    *Function :
    *Input Ref: hours,minutes,seconds of beijing time 
    *Return Ref:NO
    *
*******************************************************************************/
void SendWifiData_Ref_three(uint8_t ptc,uint8_t plasma,uint8_t ultra)
{
    outputBuf[0]=0x5A; //mainboard head : displayBoard = 0xA5
	outputBuf[1]=0x10; //mainboard device No: 01
	outputBuf[2]=0x20; //command : is data of hours and minutes and seconds.
	outputBuf[3]=0x0F; // is data tx
	outputBuf[4]= 0x03; // has three data.
	outputBuf[5]= ptc; //	
	outputBuf[6]= plasma; //	
	outputBuf[7]= ultra; //	

    outputBuf[8] = 0xFE;
    outputBuf[9] = bcc_check(outputBuf,9);

	transferSize=10;
	#if 0
	if(transferSize)
	{
    	while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
    	transOngoingFlag=1;
    	HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
}
/********************************************************************************
    **
    *Function Name:
    *Function : commad order , data -command type
    *Input Ref: commad order , data -command type
    *Return Ref:NO
    *
*******************************************************************************/
void SendWifiData_To_Data(uint8_t cmd,uint8_t data)
{
        outputBuf[0]=0x5A; //head : main board 0x5A
        outputBuf[1]=0x10; //main board device No: 0x10
        outputBuf[2]=cmd; //command type: fan speed of value 
        outputBuf[3]=0x0F; // 0x0F : is data ,don't command order.
        outputBuf[4]= 0x01; // don't data ,onlay is command order,recieve data is 1byte .
        outputBuf[5]= data; // don't data 
        
        outputBuf[6] = 0xFE;
        outputBuf[7] = bcc_check(outputBuf,7);
        
        transferSize=8;
		#if 0
        if(transferSize)
        {
            while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
            transOngoingFlag=1;
            HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
        }
		#else
     HAL_UART_Transmit_DMA(&huart1,outputBuf, transferSize);

	#endif 
	
}




/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}

	if(huart== &huart2){

       usart2_transOngoingFlag =0;

	}

}


