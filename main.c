/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4������GPIO����
*******************************************************************************/
#include "stm8l15x.h"
#include "lcd.h"
//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_4


/*******************************************************************************
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
int main( void )
{
    u16 CapValue;
   GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
   
    CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//HSIΪϵͳʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ
 
//    u16 u16_adc1_value;   
    u16 VoltageValue;
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����ADC/USARTʱ��
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM3,ENABLE);//ENABLE TIM3CLK
    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����115200��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART
    TIM3_DeInit();
    TIM3_TimeBaseInit(TIM3_Prescaler_1,TIM3_CounterMode_Up,0X2323);//16M/8/128=15.625K��0xff=255,255*��1/15.625��=0.01632S����Լ61���ж���1S
//    GPIO_Init(IR_GPIO_PORT, IR_GPIO_PINS, GPIO_Mode_In_FL_IT);//��ʼ��������GPB6�����ж�����
    TIM3_ARRPreloadConfig(ENABLE);	/* Ԥװ��ʹ�� */
    TIM3_Cmd(ENABLE);   
    Capinit();                                  //cap enable 
    InitLCD();                                  //lcd enable
  
    data_convertor(2990);
    Display();
    CapValue=GetCap();
    data_convertor(CapValue);
     Display();
    
    while(1){
    
     CapValue=GetCap();
     data_convertor(CapValue);
     Display();
     Delay(10000000);
    
     
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
