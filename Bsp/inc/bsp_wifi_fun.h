#ifndef __BSP_WIFI_FUN_
#define __BSP_WIFI_FUN_
#include "main.h"



#define SSID                    "UYIKIA"
#define PASSWD                  "20329263"


#define TOPIC                  "open"

#define TOPIC_VALUE            1
//#define SMARTCONFIG      			0


#define PRODUCT_ID              "EHQB1P53IH" //production ID 
//#define DEVUICE_NAME            "UYIJIA01-afcc8"      //device Name:
#define DEVICE_SECRET           "5xdQMgx7ZHznYyQK6wvdmolc"//"5xdQMgx7ZHznYyQK6wvdmolc"  //Secret key 
#define PRODUCT_REGION          "ap-guangzhou" //filed name 

#define WIFI_IC_ENABLE()         HAL_GPIO_WritePin(WIFI_EN_GPIO_Port,WIFI_EN_Pin,GPIO_PIN_SET)
#define WIFI_IC_DISABLE()        HAL_GPIO_WritePin(WIFI_EN_GPIO_Port,WIFI_EN_Pin,GPIO_PIN_RESET)



typedef struct _WIFI_FUN{
	

   
    uint8_t wifi_data[150]; 

    uint8_t wifi_data_rx[40];


    uint8_t soft_ap_config_success;
	//uint8_t tencent_link_success;

    uint8_t link_net_tencent_data_flag; //after send publish datat to tencent .
   
    uint8_t wifi_rx_counter;
    uint8_t rx_data_success ;
	
    uint8_t soft_ap_config_flag;
    
    uint8_t get_rx_beijing_time_enable;
  
    uint8_t wifi_uart_rx_counter;
     uint8_t once_rx_data_done;
	 uint8_t response_wifi_signal_label;
	 //smart phone 
    uint8_t smartphone_app_power_on_flag;
   
    //fan
	uint8_t set_wind_speed_value;
    uint8_t received_data_from_tencent_cloud ;


    //timer
    uint8_t gTimer_linking_tencent_duration;
	
  
	
	uint8_t gTimer_wifi_rx_error;


     uint8_t gTimer_auto_link_net_time;
     uint8_t gTimer_power_first_link_tencent;
	
    uint16_t gTimer_get_beijing_time;
	uint16_t gTimer_auto_detected_net_state_times;
    
	uint32_t randomName[1];
	
	
}WIFI_FUN;

extern WIFI_FUN   wifi_t;

//extern uint8_t (*wifi_link_net_state)(void); //函数指针


void Wifi_Init(void);

void PowerOn_Host(void (*poweronHandler)(void));
void PowerOff_Host(void (*poweroffHandler)(void));




void wifiDisplayTemperature_Humidity(void);

//void Wifi_Link_Net_Handler(uint8_t (*wifi_link_handler)(void));




void link_wifi_net_state_handler(void);


uint8_t at_send_data(uint8_t* pdata, uint16_t len);



#endif 


