#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define        pwm1        TIM3->CCR1       //ռ�ձȣ����Ϊ
#define        pwm2        TIM3->CCR2       //ռ�ձȣ����Ϊ
#define        EN1         PBout(10)
#define        EN2         PBout(5)
#define        Max_duty_cycle   1000         //�ܵ�ռ�ձ�
void TIM3_PWM_Init(u16 arr,u16 psc )        ;//PWM����ʼ��
void XL6003_Init(void)                      ;//XL6003ʹ�ܽų�ʼ��

#endif
