#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f10x.h"

void Week_Display(u8 week);//������ʾ����
void Time_Date_display(void);//ʱ���������ʾ����
void Switch_mode(u8 mode);//ģʽ�л�mode:0 1 2 3
void Lights_pwm_display(u16 light1, u16 light2, u16 Pwm1, u16 Pwm2);//��ǿ��PWMռ�ձ���ʾ
void Options_Choose(u8 option_num);//ѡ��ѡ��
void Set_Date(void);
void Set_Time(void);
void Set_AlarmA(void);
//void Display_Button(void);
//void Num_Change(u8 num);//�ı���ֵ


#endif

