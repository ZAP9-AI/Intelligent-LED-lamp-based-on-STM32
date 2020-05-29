#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

//////////////////////////////////////////////////////////////////////////////////	 
//蜂鸣器驱动代码	   
////////////////////////////////////////////////////////////////////////////////// 


//LED端口定义
#define BEEP_ON    GPIO_SetBits(GPIOB,GPIO_Pin_12) 	    // 蜂鸣器控制IO 
#define BEEP_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_12)	  // 蜂鸣器控制IO 


void BEEP_Init(void);//初始化		 				    
#endif

















