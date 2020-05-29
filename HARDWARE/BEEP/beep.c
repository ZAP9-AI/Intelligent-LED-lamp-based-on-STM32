#include "beep.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//蜂鸣器驱动代码	   
					  
////////////////////////////////////////////////////////////////////////////////// 	 




//初始化PF8为输出口		    
//BEEP IO初始化
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //BEEP-->PB.12 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.12
  GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出高

}






