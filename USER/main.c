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



//��ʼ����
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);


//oled��ʾ����
//�������ȼ�
#define DISPLAY_TASK_PRIO		2
//�����ջ��С	
#define DISPLAY_STK_SIZE 		512
//������
TaskHandle_t DisplayTask_Handler;
//������
void display_task(void *pvParameters);



//�⴫����temp6000�ɼ���ǿ����
//�������ȼ�
#define TEMP6000_TASK_PRIO		3
//�����ջ��С	
#define TEMP6000_STK_SIZE 		128  
//������
TaskHandle_t Temp6000Task_Handler;
//������
void temp6000_task(void *pvParameters);


//LED��������оƬxl6003����LED����
//�������ȼ�
#define XL6003_TASK_PRIO		4
//�����ջ��С	
#define XL6003_STK_SIZE 		128  
//������
TaskHandle_t Xl6003Task_Handler;
//������
void xl6003_task(void *pvParameters);



//PID�㷨��������
//�������ȼ�
#define PID_TASK_PRIO		5
//�����ջ��С	
#define PID_STK_SIZE 		128  
//������
TaskHandle_t PidTask_Handler;
//������
void pid_task(void *pvParameters);

//BEEP����
//�������ȼ�
#define BEEP_TASK_PRIO		6
//�����ջ��С	
#define BEEP_STK_SIZE 		128  
//������
TaskHandle_t BeepTask_Handler;
//������
void beep_task(void *pvParameters);


//������������
//�������ȼ�
#define KEY_TASK_PRIO		7
//�����ջ��С	
#define KEY_STK_SIZE 		512 
//������
TaskHandle_t KeyTask_Handler;
//������
void key_task(void *pvParameters);



////�����ź������
//SemaphoreHandle_t MutexSemaphore;	//�����ź���

int Natural_Light=0;//������
int LED_Light=0;//LED�ƹ�
extern struct Menu *menuP;
extern struct Menu Intelligent_mode[4]            ;
extern u8 key_num;
extern u8 beep_bit;
extern u8 pid_bit ;
float set_light ;//����ģʽ�µ�LED����������
extern struct t_pid pid ;
u16 W_light=5 ;//��ɫLEDռ��
u16 Y_light=5 ;//��ɫLEDռ��
float pwm ;

int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	uart_init(115200);     				//��ʼ������
	WKUP_Init();
  KEY_Init()         ;
	BEEP_Init()        ;
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
  OLED_Init();
	pid_init();
	TIM3_PWM_Init(7199,10);//pwm = 100M / ((arr+1)*(psc+1))(Hz)  1000hz
	XL6003_Init();
  set_light = 300;
//������ʼ����
  xTaskCreate((TaskFunction_t )start_task,            //������
               (const char*    )"start_task",          //��������
               (uint16_t       )START_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                  //���ݸ��������Ĳ���
               (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&StartTask_Handler);   //������              
  vTaskStartScheduler();          //�����������
}


//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	
//   
   //����oled��ʾ����
   xTaskCreate((TaskFunction_t )display_task,            //������
               (const char*    )"display_task",          //��������
               (uint16_t       )DISPLAY_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                    //���ݸ��������Ĳ���
               (UBaseType_t    )DISPLAY_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&DisplayTask_Handler);   //������
               
   //����temp6000����ǿ�Ȳɼ�����
   xTaskCreate((TaskFunction_t )temp6000_task,            //������
               (const char*    )"temp6000_task",          //��������
               (uint16_t       )TEMP6000_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                     //���ݸ��������Ĳ���
               (UBaseType_t    )TEMP6000_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&Temp6000Task_Handler);   //������
               
   //����xl6003 LED������������
   xTaskCreate((TaskFunction_t )xl6003_task,            //������
               (const char*    )"xl6003_task",          //��������
               (uint16_t       )XL6003_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                   //���ݸ��������Ĳ���
               (UBaseType_t    )XL6003_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&Xl6003Task_Handler);   //������
    
   //����PID�㷨����
   xTaskCreate((TaskFunction_t )pid_task,            //������
               (const char*    )"pid_task",          //��������
               (uint16_t       )PID_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                //���ݸ��������Ĳ���
               (UBaseType_t    )PID_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&PidTask_Handler);       //������ 
							 
	//����BEEP����
   xTaskCreate((TaskFunction_t )beep_task,            //������
               (const char*    )"beep_task",          //��������
               (uint16_t       )BEEP_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                //���ݸ��������Ĳ���
               (UBaseType_t    )BEEP_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&BeepTask_Handler);       //������ 
							 
	 //����������������
   xTaskCreate((TaskFunction_t )key_task,            //������
               (const char*    )"key_task",          //��������
               (uint16_t       )KEY_STK_SIZE,        //�����ջ��С
               (void*          )NULL,                //���ݸ��������Ĳ���
               (UBaseType_t    )KEY_TASK_PRIO,       //�������ȼ�
               (TaskHandle_t*  )&KeyTask_Handler);   //������ 
                         
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}


void display_task(void *pvParameters)
{
	while(1)
	{	
		if(menuP->Function!=0)
	  {
		  menuP->Function();
		  vTaskDelay(1);			//��ʱ10ms 
	  }
	  else 
	  {
		  vTaskDelay(1);			//��ʱ10ms 
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
	  vTaskDelay(1);			//��ʱ10ms 
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
	  vTaskDelay(1);			//��ʱ1ms 
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
			vTaskDelay(1);			//��ʱ1ms 
		}
		else
	  {
			vTaskDelay(1);			//��ʱ1ms 
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
			NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//��ȡ����֪ͨ
		  if(NotifyValue==1)									//����֮ǰ������ֵ֪ͨΪ1��˵������֪ͨ��Ч
		  {
				BEEP_ON;
			  vTaskDelay(1);	
			}		
      else 
		  {
			  vTaskDelay(60000);      //��������һ���Ӻ�ر�
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
	  vTaskDelay(1);			//��ʱ10ms 
	}
}
