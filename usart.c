#include "usart.h"


/*******************************************************************************
****��ڲ�������Ҫ���͵��ַ���
****���ڲ�������
****������ע��USART���ͺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//��Ϊ����
        {
            USART_SendData8(USART1,*Str);         //�������� 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
            Str++;//��һ������
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
  

