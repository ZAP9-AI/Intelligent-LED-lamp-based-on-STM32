#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"


struct t_pid
{
	float SetLight;     //设定的光照强度
	float ActualLight;  //实际的光照强度
	float err;          //当前误差
	float err_last;     //上一次误差
	float Kp,Ki,Kd;     //比例常数,积分常数,微分常数
	float voltage;      //控制执行器的变量
	float integral;     //定义积分值
};

void pid_init(void);

float pid_realize(float light);


#endif

