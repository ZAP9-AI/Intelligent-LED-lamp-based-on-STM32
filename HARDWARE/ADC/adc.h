#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"


#define READ_TIMES	10		                            //���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
#define SENSOR_1   	ADC_Channel_1	     							  //���廷���������������ڵ�ADC_CH1ͨ�����
#define SENSOR_2   	ADC_Channel_2									    //����ƹ�������������ڵ�ADC_CH2ͨ�����

void Adc_Init(void); //ADCͨ����ʼ��
u16  Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  

u16 Get_Natural_Light(void);																	//��ȡ����������������ֵ
u16 Get_LED_Light(void);																		  //��ȡ�ƹ������������ֵ

#endif 
