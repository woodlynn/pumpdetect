/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4������GPIO����
*******************************************************************************/
#include "stm8l15x.h"
//#include "lcd.h"
#include "fdc2214.h"
#include "usart.h"
#include "Display.h"

//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_4


/*jj******************************************************************************
****��������:
****��������:��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}


/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������Һ����ʾADCת����ĵ�ѹֵ
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void SendData(u32 data){
    u8 databuf[9],i;
    for (i=8;i>0;i--){
        databuf[i-1]=data%10;
        databuf[i-1]+='0';

        data/=10;
    
    }
    databuf[8]=0;
    USART1_SendStr(databuf); 
    USART_SendData8(USART1,'\n');

    
}
int main( void )
{
    u32 CapValue;
   GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
   
    CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSIΪϵͳʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//����Ƶ , 2
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//����IIC1ʱ��    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����ADC/USARTʱ��

    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����115200��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART
    
  //  InitLCD();                  //lcd disabled
    LcdPortInit();                  //use 5110lcd





    GPIO_Init(GPIOC, GPIO_Pin_0,   GPIO_Mode_In_FL_No_IT );
    GPIO_Init(GPIOC, GPIO_Pin_1,   GPIO_Mode_In_FL_No_IT );
    FDC2214_Init();    
//    data_convertor(2990);
//    Display();

//    data_convertor(CapValue);
//    Display();
    CapValue= FCD2214_ReadCH(0);
    
     
     
    while(1){
    Delay (50000);      
    CapValue=  FCD2214_ReadCH(0);
    
	Usart_send_SensorData(CapValue);//use usart to send data 20201101
	Display_SensorData(CapValue);
  //  CapValue/=10000;
 //   data_convertor(CapValue);
 //   Display();

 
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
