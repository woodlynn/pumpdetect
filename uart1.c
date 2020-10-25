#include "uart1.h"
#include "stm8s.h"




#define   UART1_RX_MAX_LEN  64


u8 UART1_Rx_buff[UART1_RX_MAX_LEN];
u8 UART1_RX_NUM=0;
u8 UART1_Rx_Flag=0;
u8 UART1_Tx_Flag=0;


void Uart1_Init(void)
{
   /// ITC_SetSoftwarePriority(ITC_IRQ_TIM1_OVF, ITC_PRIORITYLEVEL_1);///设置最高优先级
    UART1_DeInit();
    UART1_Init((u32)57600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
    UART1_PARITY_NO ,UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);
 //   UART1_ITConfig(UART1_IT_RXNE_OR,  ENABLE);
    UART1_Cmd(ENABLE ); 
}



void UART1_SendByte(unsigned char data)
{
    UART1_SendData8(data);
    /* Loop until the end of transmission */
    while(UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}



void UART1_SendString(u8* Data)
{
    while(*Data)
        UART1_SendByte(*Data++);
  
}



u8 UART1_ReceiveByte(void)
{
     u8 recx; 
     while(UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
     recx = UART1_ReceiveData8();
     return  recx;
    
}



void UART1_ReciveIRQ(void)
{
    /*(USART1->DR);读取接收到的数据,当读完数据后自动取消RXNE的中断标志位*/
    const u8 Res = UART1_ReceiveData8();
    
    if(0==UART1_Rx_Flag) {
        UART1_Rx_buff[UART1_RX_NUM] = Res;
        if(0xa0 == (UART1_Rx_buff[0]&0xf0)) {
            UART1_RX_NUM ++;
            if(UART1_RX_MAX_LEN <= UART1_RX_NUM) {
                UART1_RX_NUM = 0;
            }
            if(0xff == Res) {
                UART1_Rx_Flag = 1;
                UART1_RX_NUM = 0;
            }
        }else {
            UART1_RX_NUM = 0;
        }
    }

}

