#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "pwm.h"
//=========================================================================================
/******************************��ʱ��TIM3��ʼ������***************************************/
/******************************TIM3 PWM���ֳ�ʼ��*****************************************/
/******************************arr���Զ���װֵ********************************************/
/******************************psc��ʱ��Ԥ��Ƶ��******************************************/
/******************************TIM3_CH1->PA.6>>CCR1  TIM3_CH2->PA.7>>CCR2*****************/
//=========================================================================================	  

void TIM3_PWM_Init(u16 arr,u16 psc ) 
{  
	GPIO_InitTypeDef         GPIO_InitStructure                                      ;//����GPIO�ṹ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure                                   ;//����TIM�Ľṹ��
	TIM_OCInitTypeDef        TIM_OCInitStructure                                     ;//����TIM_CHx�ṹ��
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)                              ;//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE)                            ;//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE)                              ;//PB.4��ʼĬ��ΪSJRST����ͨI/O�������,ʹPB.4->JTRSTʧ��,�ָ�PB.4��ͨI/O�Ĺ���
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)                              ;//Timer3������ӳ��  TIM3_CH2->PA6 TIM_CH1->PA7
                                                                                    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5  CH1��PWM���岨 GPIOB.4
	GPIO_InitStructure.GPIO_Pin              = GPIO_Pin_6|GPIO_Pin_7                 ;//TIM3_CH1  TIM3_CH2
	GPIO_InitStructure.GPIO_Mode             = GPIO_Mode_AF_PP                       ;//�����������
	GPIO_InitStructure.GPIO_Speed            = GPIO_Speed_50MHz                      ;//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure)                                            ;//��ʼ��GPIO
 
                                                                                    //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period         = arr                                   ;//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler      = psc                                   ;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision  = 0                                     ;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode    = TIM_CounterMode_Up                    ;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure)                                   ;//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	                                                                                  //��ʼ��TIM3 CH1 CH2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode           = TIM_OCMode_PWM1                       ;//ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState      = TIM_OutputState_Enable                ;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity       = TIM_OCPolarity_High                   ;//�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure)                                          ;//����Tָ���Ĳ�����ʼ������TIM3 OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable)                                 ;//ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
 
	
	TIM_OCInitStructure.TIM_OCMode           = TIM_OCMode_PWM1                       ;//ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState      = TIM_OutputState_Enable                ;//�Ƚ����ʹ�� 
	TIM_OCInitStructure.TIM_OCPolarity       = TIM_OCPolarity_High                   ;//�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure)                                          ;//����ָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable)                                 ;//ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE)                                                            ;//ʹ��TIM3
	
}

void XL6003_Init(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure                                      ;//����GPIO�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE)                            ;//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	                                                                                    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5  CH1��PWM���岨 GPIOB.4
	GPIO_InitStructure.GPIO_Pin              = GPIO_Pin_5|GPIO_Pin_10                 ;//TIM3_CH1  TIM3_CH2
	GPIO_InitStructure.GPIO_Mode             = GPIO_Mode_AF_PP                       ;//�����������
	GPIO_InitStructure.GPIO_Speed            = GPIO_Speed_50MHz                      ;//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure)                                            ;//��ʼ��GPIO
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);						 //PB.10 �����
	
}
