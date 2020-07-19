
#include "capsensor.h"

unsigned char Capchargeflag,Interruptflag;
u16 TimCap,TimCapBefore,TimCapAfter,TimCap_H,TimCap_L;
void delayms(uint16_t nCount){
  while (nCount != 0)
  {   
    nCount--;
  }
}

void clearCapchargeflag(void){
    Interruptflag=0;
}

void Capinit (void){
	GPIO_Init(  Cap_Port,Cap_Charge_Pin,     GPIO_Mode_Out_PP_High_Fast);
	GPIO_Init(  Cap_Port,Cap_Detect_Pin,     GPIO_Mode_In_FL_IT);
    EXTI_SetPinSensitivity (Cap_Detect_Pin,  EXTI_Trigger_Rising);


}
void CapCharge(void){
        GPIO_Init(Cap_Port,Cap_Charge_Pin, GPIO_Mode_Out_PP_Low_Fast);  
	GPIO_ResetBits(Cap_Port,Cap_Charge_Pin);
        
	                            delayms(1000);

        enableInterrupts();//Ê¹ÄÜÖÐ¶Ï
        delayms(100);
        GPIO_Init(Cap_Port,Cap_Charge_Pin,GPIO_Mode_In_FL_No_IT );        
            delayms(1000);
}


u16 GetCap(void){

	Interruptflag=1;       
        TimCap_H = TIM3->CNTRH;
	TimCap_L = TIM3->CNTRL;
	
	TimCapBefore = ((TimCap_H&0xff)<<8)|((TimCap_L&0xff)<<0);

	CapCharge();	//Pull down capcharger Pin 
	//Wait the interrupt

 //       while (Interruptflag);
        	

	TimCap=TimCapAfter-TimCapBefore;
        disableInterrupts();
        
        return TimCap; 

}
