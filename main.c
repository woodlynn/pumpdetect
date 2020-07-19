/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
#include "lcd.h"
//定义LED与按键接口
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_4


/*******************************************************************************
****函数名称:
****函数功能:延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}


/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：断码液晶显示ADC转换后的电压值
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    u16 CapValue;
   GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
   
    CLK_HSICmd(ENABLE);//开始内部高频RC
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//HSI为系统时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频
 
//    u16 u16_adc1_value;   
    u16 VoltageValue;
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启ADC/USART时钟
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM3,ENABLE);//ENABLE TIM3CLK
    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，115200，8N1
    USART_Cmd (USART1,ENABLE);//使能USART
    TIM3_DeInit();
    TIM3_TimeBaseInit(TIM3_Prescaler_1,TIM3_CounterMode_Up,0X2323);//16M/8/128=15.625K，0xff=255,255*（1/15.625）=0.01632S，大约61次中断是1S
//    GPIO_Init(IR_GPIO_PORT, IR_GPIO_PINS, GPIO_Mode_In_FL_IT);//初始化按键，GPB6上拉中断输入
    TIM3_ARRPreloadConfig(ENABLE);	/* 预装载使能 */
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
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
