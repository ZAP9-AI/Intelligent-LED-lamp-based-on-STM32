#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"


#define READ_TIMES	10		                            //定义光敏传感器读取次数,读这么多次,然后取平均值
#define SENSOR_1   	ADC_Channel_1	     							  //定义环境光敏传感器所在的ADC_CH1通道编号
#define SENSOR_2   	ADC_Channel_2									    //定义灯光光敏传感器所在的ADC_CH2通道编号

void Adc_Init(void); //ADC通道初始化
u16  Get_Adc(u8 ch); //获得某个通道值  

u16 Get_Natural_Light(void);																	//读取环境光敏传感器的值
u16 Get_LED_Light(void);																		  //读取灯光光敏传感器的值

#endif 
