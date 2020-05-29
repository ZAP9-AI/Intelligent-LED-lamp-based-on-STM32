#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "wkup.h"
#include "menu.h"
#include "adc.h"
#include "rtc.h"
#include "key.h"
#include "beep.h"
#include "usmart.h"
#include "oled.h"
#include "pid.h"
#include "pwm.h"



//开始任务
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);


//oled显示任务
//任务优先级
#define DISPLAY_TASK_PRIO		2
//任务堆栈大小	
#define DISPLAY_STK_SIZE 		512
//任务句柄
TaskHandle_t DisplayTask_Handler;
//任务函数
void display_task(void *pvParameters);



//光传感器temp6000采集光强任务
//任务优先级
#define TEMP6000_TASK_PRIO		3
//任务堆栈大小	
#define TEMP6000_STK_SIZE 		128  
//任务句柄
TaskHandle_t Temp6000Task_Handler;
//任务函数
void temp6000_task(void *pvParameters);


//LED恒流驱动芯片xl6003驱动LED任务
//任务优先级
#define XL6003_TASK_PRIO		4
//任务堆栈大小	
#define XL6003_STK_SIZE 		128  
//任务句柄
TaskHandle_t Xl6003Task_Handler;
//任务函数
void xl6003_task(void *pvParameters);



//PID算法控制任务
//任务优先级
#define PID_TASK_PRIO		5
//任务堆栈大小	
#define PID_STK_SIZE 		128  
//任务句柄
TaskHandle_t PidTask_Handler;
//任务函数
void pid_task(void *pvParameters);

//BEEP任务
//任务优先级
#define BEEP_TASK_PRIO		6
//任务堆栈大小	
#define BEEP_STK_SIZE 		128  
//任务句柄
TaskHandle_t BeepTask_Handler;
//任务函数
void beep_task(void *pvParameters);


//按键处理任务
//任务优先级
#define KEY_TASK_PRIO		7
//任务堆栈大小	
#define KEY_STK_SIZE 		512 
//任务句柄
TaskHandle_t KeyTask_Handler;
//任务函数
void key_task(void *pvParameters);



////互斥信号量句柄
//SemaphoreHandle_t MutexSemaphore;	//互斥信号量

int Natural_Light=0;//环境光
int LED_Light=0;//LED灯光
extern struct Menu *menuP;
extern struct Menu Intelligent_mode[4]            ;
extern u8 key_num;
extern u8 beep_bit;
extern u8 pid_bit ;
float set_light ;//智能模式下的LED的设置亮度
extern struct t_pid pid ;
u16 W_light=5 ;//白色LED占比
u16 Y_light=5 ;//黄色LED占比
float pwm ;

int main(void)
{
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	uart_init(115200);     				//初始化串口
	WKUP_Init();
  KEY_Init()         ;
	BEEP_Init()        ;
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	
	RTC_Init();	  			//RTC初始化
  OLED_Init();
	pid_init();
	TIM3_PWM_Init(7199,10);//pwm = 100M / ((arr+1)*(psc+1))(Hz)  1000hz
	XL6003_Init();
  set_light = 300;
//创建开始任务
  xTaskCreate((TaskFunction_t )start_task,            //任务函数
               (const char*    )"start_task",          //任务名称
               (uint16_t       )START_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                  //传递给任务函数的参数
               (UBaseType_t    )START_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
  vTaskStartScheduler();          //开启任务调度
}


//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	
//   
   //创建oled显示任务
   xTaskCreate((TaskFunction_t )display_task,            //任务函数
               (const char*    )"display_task",          //任务名称
               (uint16_t       )DISPLAY_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                    //传递给任务函数的参数
               (UBaseType_t    )DISPLAY_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&DisplayTask_Handler);   //任务句柄
               
   //创建temp6000光照强度采集任务
   xTaskCreate((TaskFunction_t )temp6000_task,            //任务函数
               (const char*    )"temp6000_task",          //任务名称
               (uint16_t       )TEMP6000_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                     //传递给任务函数的参数
               (UBaseType_t    )TEMP6000_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&Temp6000Task_Handler);   //任务句柄
               
   //创建xl6003 LED恒流驱动任务
   xTaskCreate((TaskFunction_t )xl6003_task,            //任务函数
               (const char*    )"xl6003_task",          //任务名称
               (uint16_t       )XL6003_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                   //传递给任务函数的参数
               (UBaseType_t    )XL6003_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&Xl6003Task_Handler);   //任务句柄
    
   //创建PID算法任务
   xTaskCreate((TaskFunction_t )pid_task,            //任务函数
               (const char*    )"pid_task",          //任务名称
               (uint16_t       )PID_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                //传递给任务函数的参数
               (UBaseType_t    )PID_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&PidTask_Handler);       //任务句柄 
							 
	//创建BEEP任务
   xTaskCreate((TaskFunction_t )beep_task,            //任务函数
               (const char*    )"beep_task",          //任务名称
               (uint16_t       )BEEP_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                //传递给任务函数的参数
               (UBaseType_t    )BEEP_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&BeepTask_Handler);       //任务句柄 
							 
	 //创建按键处理任务
   xTaskCreate((TaskFunction_t )key_task,            //任务函数
               (const char*    )"key_task",          //任务名称
               (uint16_t       )KEY_STK_SIZE,        //任务堆栈大小
               (void*          )NULL,                //传递给任务函数的参数
               (UBaseType_t    )KEY_TASK_PRIO,       //任务优先级
               (TaskHandle_t*  )&KeyTask_Handler);   //任务句柄 
                         
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}


void display_task(void *pvParameters)
{
	while(1)
	{	
		if(menuP->Function!=0)
	  {
		  menuP->Function();
		  vTaskDelay(1);			//延时10ms 
	  }
	  else 
	  {
		  vTaskDelay(1);			//延时10ms 
	  }
	}
}


void temp6000_task(void *pvParameters)
{
	while(1)
	{
	  Natural_Light=Get_Natural_Light();
	
	  LED_Light=Get_LED_Light();
		
		pid.ActualLight = Natural_Light + LED_Light ;
	  vTaskDelay(1);			//延时10ms 
	}
}


void xl6003_task(void *pvParameters)
{
	pwm1=50;
	pwm2=50;
	while(1)
	{
		if(menuP == &Intelligent_mode[0])//Reading mode
		{
			set_light = 300;
			Y_light = 7;
			W_light = 3;
		}
		else if(menuP == &Intelligent_mode[1])//Writting mode
		{
			set_light = 550;
			Y_light = 2;
			W_light = 8;
		}
		else if(menuP == &Intelligent_mode[2])//Movie mode
		{
			set_light = 90;
			Y_light = 7;
			W_light = 3;
		}
		else if(menuP == &Intelligent_mode[3])//Game mode
		{
			set_light = 200;
			Y_light = 5;
			W_light = 5;
		}
	  vTaskDelay(1);			//延时1ms 
	}
}


void pid_task(void *pvParameters)
{
	while(1)
	{
		if(pid_bit==1)
		{
			pwm = pid_realize(set_light);
			pwm1=pwm*(Y_light/10.0);
	    pwm2=pwm*(W_light/10.0);
			vTaskDelay(1);			//延时1ms 
		}
		else
	  {
			vTaskDelay(1);			//延时1ms 
		}
	}
}

void beep_task(void *pvParameters)
{
	u32 NotifyValue;
	while(1)
	{
		if(beep_bit==1 )
		{
			NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//获取任务通知
		  if(NotifyValue==1)									//清零之前的任务通知值为1，说明任务通知有效
		  {
				BEEP_ON;
			  vTaskDelay(1);	
			}		
      else 
		  {
			  vTaskDelay(60000);      //闹钟响铃一分钟后关闭
			  BEEP_OFF;
			  vTaskDelay(1);	
		  }			
	  }
		else 
		{
			vTaskDelay(1);	
		}
		vTaskDelay(1);
	}
}

void key_task(void *pvParameters)
{
	while(1)
	{
		KEY_Scan();
	  switch(key_num)
	  {
	  	case 1:
		  {
			  KEY_ENTER();
        OLED_Clear();				
			  break;
		  }
		  case 2:
		  {
		  	KEY_UP();
        OLED_Clear();				
		  	break;
		  }
		  case 4:
		  {
		  	KEY_DOWN();
				OLED_Clear();
		  	break;
		  }
		  default:
			  break;
	  }
		key_num=0;
	  vTaskDelay(1);			//延时10ms 
	}
}
