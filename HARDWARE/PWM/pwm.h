#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define        pwm1        TIM3->CCR1       //占空比，最大为
#define        pwm2        TIM3->CCR2       //占空比，最大为
#define        EN1         PBout(10)
#define        EN2         PBout(5)
#define        Max_duty_cycle   1000         //总的占空比
void TIM3_PWM_Init(u16 arr,u16 psc )        ;//PWM波初始化
void XL6003_Init(void)                      ;//XL6003使能脚初始化

#endif
