#ifndef __USART_H
#define __USART_H


#include "stm8l15x.h"
void USART1_SendStr(unsigned char *Str) ;
void Usart_send_SensorData(u32 data);

#endif