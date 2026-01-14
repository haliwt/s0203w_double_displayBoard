#include "bsp_ptc.h"
#include "bsp.h"


void Ptc_On(void)
{

   PTC_SetHigh();


}

void Ptc_Off(void)
{

   PTC_SetLow();

}




