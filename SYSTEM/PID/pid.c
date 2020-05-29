#include "pid.h"
#include <stdlib.h> 

/*=============================================================*/
//积分分离的PID控制算法
/*=============================================================*/
struct t_pid pid ;

void pid_init(void)
{
	pid.SetLight=0.0;
	pid.ActualLight=0.0;
	pid.err=0.0;
	pid.err_last=0.0;
	pid.voltage=0.0;
	pid.integral=0.0;
	pid.Kp=0.4;
	pid.Ki=0.2;
	pid.Kd=0.2;
}


float pid_realize(float light)
{
	float index;
	pid.SetLight=light;
	pid.err=pid.SetLight-pid.ActualLight;
	if(abs(pid.err)>200)
	{
		index=0.0;
	}
	else if(abs(pid.err)<180)
	{
		index=1.0;
		pid.integral+=pid.err;
	}
	else
	{
		index=(200-abs(pid.err))/20;
		pid.integral+=pid.err;
	}
	pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	pid.err_last=pid.err;
	pid.ActualLight=pid.voltage*1.0;
	return pid.ActualLight;
}
