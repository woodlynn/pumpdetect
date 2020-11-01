/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
//#include "lcd.h"
#include "fdc2214.h"
#include "usart.h"
#include "Display.h"

//定义LED与按键接口
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_4


/*jj******************************************************************************
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
   
    CLK_HSICmd(ENABLE);//开始内部高频RC
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSI为系统时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//不分频 , 2
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//开启IIC1时钟    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启ADC/USART时钟

    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，115200，8N1
    USART_Cmd (USART1,ENABLE);//使能USART
    
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
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
