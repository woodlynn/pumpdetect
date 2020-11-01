#include "usart.h"


/*******************************************************************************
****入口参数：需要发送的字符串
****出口参数：无
****函数备注：USART发送函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//不为结束
        {
            USART_SendData8(USART1,*Str);         //发送数据 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
            Str++;//下一个数据
        }
}


void Usart_send_SensorData(u32 data){
  u8 databuf[9],i;
  for (i=8;i>0;i--){
      databuf[i-1]=data%10;
      databuf[i-1]+='0';
      data/=10;
  
  }
    databuf[8]=0;
  
  USART1_SendStr (databuf);
  }
  

