#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

//////////////////////////////////////////////////////////////////////////////////	 
//��������������	   
////////////////////////////////////////////////////////////////////////////////// 


//LED�˿ڶ���
#define BEEP_ON    GPIO_SetBits(GPIOB,GPIO_Pin_12) 	    // ����������IO 
#define BEEP_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_12)	  // ����������IO 


void BEEP_Init(void);//��ʼ��		 				    
#endif

















