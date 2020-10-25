
#ifndef __UART1_H
#define __UART1_H
#include "stm8l15x.h"
#include "stm8l15x_usart.h"

/* Private macro -------------------------------------------------------------*/



extern u8 UART1_Rx_buff[];
extern u8 UART1_Rx_Flag;
extern u8 UART1_Tx_Flag;

void Uart1_Init(void);
void UART1_SendByte(unsigned char data);
void UART1_SendString(unsigned char* Data);
void UART1_ReciveIRQ(void);



#endif