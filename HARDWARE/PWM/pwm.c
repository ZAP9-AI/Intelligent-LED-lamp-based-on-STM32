#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "pwm.h"
//=========================================================================================
/******************************定时器TIM3初始化函数***************************************/
/******************************TIM3 PWM部分初始化*****************************************/
/******************************arr：自动重装值********************************************/
/******************************psc：时钟预分频数******************************************/
/******************************TIM3_CH1->PA.6>>CCR1  TIM3_CH2->PA.7>>CCR2*****************/
//=========================================================================================	  

void TIM3_PWM_Init(u16 arr,u16 psc ) 
{  
	GPIO_InitTypeDef         GPIO_InitStructure                                      ;//定义GPIO结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure                                   ;//定义TIM的结构体
	TIM_OCInitTypeDef        TIM_OCInitStructure                                     ;//定义TIM_CHx结构体
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)                              ;//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE)                            ;//使能GPIO外设和AFIO复用功能模块时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE)                              ;//PB.4开始默认为SJRST无普通I/O输出功能,使PB.4->JTRST失能,恢复PB.4普通I/O的功能
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)                              ;//Timer3部分重映射  TIM3_CH2->PA6 TIM_CH1->PA7
                                                                                    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5  CH1的PWM脉冲波 GPIOB.4
	GPIO_InitStructure.GPIO_Pin              = GPIO_Pin_6|GPIO_Pin_7                 ;//TIM3_CH1  TIM3_CH2
	GPIO_InitStructure.GPIO_Mode             = GPIO_Mode_AF_PP                       ;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed            = GPIO_Speed_50MHz                      ;//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure)                                            ;//初始化GPIO
 
                                                                                    //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period         = arr                                   ;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler      = psc                                   ;//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision  = 0                                     ;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode    = TIM_CounterMode_Up                    ;//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure)                                   ;//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	                                                                                  //初始化TIM3 CH1 CH2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode           = TIM_OCMode_PWM1                       ;//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState      = TIM_OutputState_Enable                ;//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity       = TIM_OCPolarity_High                   ;//输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure)                                          ;//根据T指定的参数初始化外设TIM3 OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable)                                 ;//使能TIM3在CCR1上的预装载寄存器
 
	
	TIM_OCInitStructure.TIM_OCMode           = TIM_OCMode_PWM1                       ;//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState      = TIM_OutputState_Enable                ;//比较输出使能 
	TIM_OCInitStructure.TIM_OCPolarity       = TIM_OCPolarity_High                   ;//输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure)                                          ;//根据指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable)                                 ;//使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE)                                                            ;//使能TIM3
	
}

void XL6003_Init(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure                                      ;//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE)                            ;//使能GPIO外设和AFIO复用功能模块时钟
	                                                                                    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5  CH1的PWM脉冲波 GPIOB.4
	GPIO_InitStructure.GPIO_Pin              = GPIO_Pin_5|GPIO_Pin_10                 ;//TIM3_CH1  TIM3_CH2
	GPIO_InitStructure.GPIO_Mode             = GPIO_Mode_AF_PP                       ;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed            = GPIO_Speed_50MHz                      ;//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure)                                            ;//初始化GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高
	GPIO_SetBits(GPIOB,GPIO_Pin_10);						 //PB.10 输出高
	
}

