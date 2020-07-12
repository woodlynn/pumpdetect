
#include "capsensor.h"
unsigned char Capchargeflag,Interruptflag;
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
	GPIO_Init(  Cap_Port,Cap_Detect_Pin,     GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity (Cap_Detect_Pin,  EXTI_Trigger_Rising);
    enableInterrupts();//Ê¹ÄÜÖÐ¶Ï

}
void CapCharge(void){

	GPIO_ResetBits(Cap_Port,Cap_Charge_Pin);
	delayms(10000);
        GPIO_Init(Cap_Port,Cap_Charge_Pin,GPIO_Mode_In_FL_No_IT );
	
        
        
}


u16 GetCap(void){
        u16 TimCap_H,TimCap_L,TimCap,TimCapBefore,TimCapAfter;
	Capchargeflag=1;       
        TimCap_H = TIM3->CNTRH;
	TimCap_L = TIM3->CNTRL;
	
	TimCapBefore = ((TimCap_H&0xff)<<8)|((TimCap_L&0xff)<<0);

	CapCharge();	//Pull down capcharger Pin 
	//Wait the interrupt

        while (Interruptflag);
        	
	TimCap_H = TIM3->CNTRH;
	TimCap_L = TIM3->CNTRL;
	
	TimCapAfter = ((TimCap_H&0xff)<<8)|((TimCap_L&0xff)<<0);
	TimCap=TimCapAfter-TimCapBefore;
        return TimCap; 

}
