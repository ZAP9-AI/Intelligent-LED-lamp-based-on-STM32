#include "delay.h"
#include "sys.h"
#include "stm32f10x_adc.h"
#include "adc.h"

//=========================================================================================
/**********************************��ʼ��ADC**********************************************/
/**********************************ADCͨ����ʼ��**********************************************/
//=========================================================================================
		   
void Adc_Init(void)                                                              
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure                          ;//����GPIO�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE )    ;//ʹ��GPIOA,ADC1ͨ��ʱ��
  
	RCC_ADCCLKConfig(RCC_PCLK2_Div6)                                                ;//��Ƶ����6ʱ��Ϊ72M/6=12MHz
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2         ;//PA1 PA2 anolog����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN                 ;//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure)                        ;//��ʼ��GPIO	

 	ADC_DeInit(ADC1)                                                                ;//������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent                               ;//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE                                    ;//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE                              ;//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None              ;//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right                           ;//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1                                          ;//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure)                                              ;//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���	
 
	ADC_Cmd(ADC1, ENABLE)                                                           ;//ʹ��ָ����ADC1

	ADC_ResetCalibration(ADC1)                                                      ;//����ָ����ADC1�ĸ�λ�Ĵ���

    while(ADC_GetResetCalibrationStatus(ADC1))                                    ;//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�

	ADC_StartCalibration(ADC1)                                                      ;//����ָ����ADC1�ĸ�λ�Ĵ���

	while(ADC_GetCalibrationStatus(ADC1))                                           ;//��ȡָ��ADC1��У׼����,����״̬��ȴ�
	
}

//================================================================================================
/**********************************ADC1_CHx ͨ��ת��*********************************************/
//================================================================================================
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 )               ;//ADC1,��һ��ת��,����ʱ��Ϊ239.5����	  			    
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE)                                          ;//ʹ��ָ����ADC1�����ת����������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ))                                  ;//�ȴ�ת������
//	ADC_ClearFlag(ADC1, ADC_FLAG_EOC); 
	return ADC_GetConversionValue(ADC1)                                             ;//�������һ��ADC1�������ת�����
}


//=========================================================================================
/***************************��ȡLight Sens_1 ����������������ֵ***************************/
/***************************0~1000:0,�;1000,����***************************************/	
//=========================================================================================



u16 Get_Natural_Light(void)
{
	u16 lsens1_val               = 0                             ;//����������ջ������ֵ
	u8 t                                                           ;//����������մ���
	for(t=0;t<READ_TIMES;t++)
	{
		lsens1_val                += Get_Adc(ADC_Channel_1)        ;//��ȡADCֵ
		delay_ms(5)                                                ;//��ʱ5ms
	}
	lsens1_val                  /=READ_TIMES               ;//�õ�ƽ��ֵ 
	lsens1_val = (u16)(lsens1_val*(1000.0/4096.0));
	return (lsens1_val)                                 ;//���ػ�ȡ�Ĺ���ǿ��
}
//=========================================================================================
/***************************��ȡLight Sens_2 �ƹ������������ֵ***************************/
/***************************0~1000:0,�;1000,����***************************************/	
//=========================================================================================
																												
u16 Get_LED_Light(void)
{
	u16 lsens2_val               =0                              ;//�����������LED���ֵ
	u8 t                                                         ;//����������մ���
	for(t=0;t<READ_TIMES;t++)
	{
		lsens2_val                += Get_Adc(ADC_Channel_2)        ;//��ȡADCֵ
		delay_ms(5)                                                ;//��ʱ5ms
	}
	lsens2_val                  /=READ_TIMES               ;//�õ�ƽ��ֵ 
	lsens2_val = (u16)(lsens2_val*(1000.0/4096.0));
	return   (lsens2_val)                               ;//���ػ�ȡ�Ĺ���ǿ��Lux
}
