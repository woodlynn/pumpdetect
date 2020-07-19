#ifndef __CAPSENSOR_H
#define __CAPSENSOR_H

#include "stm8l15x.h"


#define Cap_Port 	GPIOD //tmp to add
#define Cap_Charge_Pin 	GPIO_Pin_5
#define Cap_Detect_Pin	GPIO_Pin_6


u16 GetCap(void);
void clearCapchargeflag(void);
extern unsigned char Capchargeflag,Interruptflag;
extern  u16 TimCap,TimCapBefore,TimCapAfter, TimCap_H,TimCap_L;


#endif