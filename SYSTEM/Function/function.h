#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f10x.h"

void Week_Display(u8 week);//星期显示函数
void Time_Date_display(void);//时间和日期显示函数
void Switch_mode(u8 mode);//模式切换mode:0 1 2 3
void Lights_pwm_display(u16 light1, u16 light2, u16 Pwm1, u16 Pwm2);//光强和PWM占空比显示
void Options_Choose(u8 option_num);//选项选择
void Set_Date(void);
void Set_Time(void);
void Set_AlarmA(void);
//void Display_Button(void);
//void Num_Change(u8 num);//改变数值


#endif

