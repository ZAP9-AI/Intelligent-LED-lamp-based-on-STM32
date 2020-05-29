#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"


struct t_pid
{
	float SetLight;     //�趨�Ĺ���ǿ��
	float ActualLight;  //ʵ�ʵĹ���ǿ��
	float err;          //��ǰ���
	float err_last;     //��һ�����
	float Kp,Ki,Kd;     //��������,���ֳ���,΢�ֳ���
	float voltage;      //����ִ�����ı���
	float integral;     //�������ֵ
};

void pid_init(void);

float pid_realize(float light);


#endif

