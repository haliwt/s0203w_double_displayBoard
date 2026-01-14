#ifndef __BSP_DECODER_H
#define __BSP_DECODER_H
#include "main.h"



typedef struct _message_disp{

   uint8_t mesData[12];
   uint8_t mesLength;
   uint8_t bcc_check_code;
   
}message_disp;

extern message_disp mess_t;


void receive_message_displaybord_handler(void);


void receive_data_fromm_display(uint8_t *pdata);




uint8_t bcc_check(const unsigned char *data, int len) ;



#endif 

