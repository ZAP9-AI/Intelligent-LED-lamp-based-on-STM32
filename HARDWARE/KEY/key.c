#include "key.h"
#include "delay.h" 
#include "menu.h"
#include "rtc.h"
#include "function.h"
#include "pwm.h"
//#include "oled.h"


//////////////////////////////////////////////////////////////////////////////////	 
//CH445�����жϺ���
//������Ӧ�����Ĺ���								  
////////////////////////////////////////////////////////////////////////////////// 

u8 key_num =0;   //������ֵ
u8  Time_value[3]={0} ;
u16 Date_value[3]={0} ;
extern struct Menu *menuP ;
extern struct Menu Manual_mode[5]          ;//�ֶ�ģʽ���ò˵�
extern struct Menu Intelligent_mode[6]     ;//����ģʽ���ò˵�
extern struct Menu Set_menu[5];
extern struct Menu Browse_Value[5];
extern struct _calendar_obj calendar;//ʱ�ӽṹ�� 
extern struct AlarmA alarma ;

u8 beep_bit=1;//�ж�BEEP���ر�־λ,1:ON 0:OFF
struct Menu *L_menuP                         ;
u8 pid_bit ;//PID������־λ,pid_bit=0:�ر� ,pid_bit=1:����

//������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;//S4��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD1,2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//S4��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOD1,2,3,4
} 

void KEY_Scan(void)
{
	if((S1==1||S2==1||S4==1))
	{
		delay_ms(10);//ȥ���� 
		if(S1==1)
		{
			key_num=1;
		}
		else if(S2==1)
		{
			key_num=2;
		}
		else if(S4==1)
		{
			key_num=4;
		}
	}
	else if(S1==0&&S2==0&&S4==0)
	{	    	
 	  key_num=0;// �ް�������
	}
}




void Num_Add(void) 
{
	if(menuP == &Set_menu[0])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
//				Time_value[0]=0;
//				Time_value[0]=Time_value[0]+calendar.hour;
				Time_value[0]++;
				if(Time_value[0]>=24)
				{
					Time_value[0]=0;
				}
			  break;
		  }
		  case 2:
		  {
//				Time_value[1]=0;
//		  	Time_value[1]=Time_value[1]+calendar.min;
				Time_value[1]++;
				if(Time_value[1]>59)
				{
					Time_value[1]=0;
				}
			  break;
	  	}
		  case 3:
		  {
//				Time_value[2]=0;
//		  	Time_value[2]=Time_value[1]+calendar.sec;
				Time_value[2]++;
				if(Time_value[2]>59)
				{
					Time_value[2]=0;
				}
		  	break;
	  	 }
		  default:
		  	break;
   	}
		Set_Time();
	}
	else if(menuP == &Set_menu[1])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
				Date_value[0]=0;
				Date_value[0]=Date_value[0]+calendar.w_year;
				Date_value[0]++;
				if(Date_value[0]>2099)
				{
					Date_value[0]=1970;
				}
			  break;
		  }
		  case 2:
		  {
				Date_value[1]=0;
		  	Date_value[1]=Date_value[1]+calendar.w_month;
				Date_value[1]++;
				if(Date_value[1]>12)
				{
					Date_value[1]=1;
				}
			  break;
	  	}
		  case 3:
		  {
				Date_value[2]=0;
		  	Date_value[2]=Date_value[2]+calendar.w_date;
				Date_value[2]++;
				if(Date_value[2]>31)
				{
					Date_value[2]=1;
				}
			  break;
	  	}
		  default:
		  	break;
   	}
		Set_Date();
	}
	else if(menuP == &Set_menu[2])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
				alarma.hours+=1;
				if(alarma.hours>23)
				{
					alarma.hours=0;
				}
			  break;
		  }
		  case 2:
		  {
		  	alarma.minutes+=1;
				if(alarma.minutes>59)
				{
					alarma.minutes=0;
				}
			  break;
	  	}
		  case 3:
		  {
		  	alarma.seconds+=1;
				if(alarma.seconds>59)
				{
					alarma.seconds=0;
				}
			  break;
	  	}
			case 4:
		  {
		  	alarma.year+=1;
				if(alarma.year>2099)
				{
					alarma.year=1970;
				}
			  break;
	  	}
			case 5:
		  {
		  	alarma.month+=1;
				if(alarma.month>12)
				{
					alarma.month=1;
				}
			  break;
	  	}
			case 6:
		  {
		  	alarma.date+=1;
				if(alarma.date>31)
				{
					alarma.date=1;
				}
			  break;
	  	}
		  default:
		  	break;
   	}
		Set_AlarmA();
	}
}



void Num_Subtract(void)     
{
	if(menuP == &Set_menu[0])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
				if(Time_value[0]==0)
				{
					Time_value[0]=23;
				}
				else
					Time_value[0]--;
			  break;
		  }
		  case 2:
		  {
				
				if(Time_value[1]==0)
				{
					Time_value[1]=59;
				}
				else
					Time_value[1]--;
			  break;
	  	}
		  case 3:
		  {
				
				if(Time_value[2]==0)
				{
					Time_value[2]=59;
				}
				else 
					Time_value[2]--;
		  	break;
			}
		  default:
		  	break;
   	}
		Set_Time();
	}
	else if(menuP == &Set_menu[1])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
				Date_value[0]--;
				if(Date_value[0]<1970)
				{
					Date_value[0]=2099;
				}
			  break;
		  }
			case 2:
		  {
				Date_value[1]--;
				if(Date_value[1]<1)
				{
					Date_value[1]=12;
				}
			  break;
	  	}
			case 3:
		  {
				Date_value[2]--;
				if(Date_value[2]<1)
				{
					Date_value[2]=31;
				}
			  break;
	  	}
		  default:
		  	break;
   	}
		Set_Date();
	}
	else if(menuP == &Set_menu[2])
	{
		switch(menuP->start_bit)
	  {
		  case 1:
		  {
				if(alarma.hours==0)
				{
					alarma.hours=23;
				}
				else
					alarma.hours--;
			  break;
		  }
		  case 2:
		  {
				if(alarma.minutes==0)
				{
					alarma.minutes=59;
				}
				else
					alarma.minutes--;
			  break;
	  	}
		  case 3:
		  {
				if(alarma.seconds==0)
				{
					alarma.seconds=59;
				}
				else
				  alarma.seconds--;
			  break;
	  	}
			case 4:
		  {
		  	alarma.year-=1;
				if(alarma.year<1970)
				{
					alarma.year=2099;
				}
			  break;
	  	}
			case 5:
		  {
		  	alarma.month-=1;
				if(alarma.month<1)
				{
					alarma.month=12;
				}
			  break;
	  	}
			case 6:
		  {
		  	alarma.date-=1;
				if(alarma.date<1)
				{
					alarma.date=31;
				}
			  break;
	  	}
		  default:
		  	break;
   	}
		Set_AlarmA();
	}
}



void KEY_ENTER(void)      
{
	switch(menuP->menu_level)
	{
		case 1:
		{
			menuP->start_bit+=1;
			if(menuP->start_bit>2)
			{
				menuP->start_bit=0;
			}
		  break;
		}
		case 2:
		{
			if(menuP->item < menuP->menu_num)
			{
				menuP=menuP+1;
			}
			else if(menuP->item == menuP->menu_num)
			{
				menuP=menuP-menuP->menu_num+1;
			}
			break;
		}
		case 3:
		{
			if(menuP->item==1 || menuP->item==2)
			{
				menuP=menuP->children;
        if(menuP == &Set_menu[0])
				{
					Time_value[0]= calendar.hour;
					Time_value[1]= calendar.min;
					Time_value[2]= calendar.sec;
          Date_value[0]= calendar.w_year ;
					Date_value[1]= calendar.w_month ;
					Date_value[2]= calendar.w_date ;
				}			
			}
			else if(menuP->item == menuP->menu_num)
			{
				menuP=L_menuP;
			}
			break;
		}
		case 4:
		{
			if(menuP == &Set_menu[0] || menuP == &Set_menu[1])
			{
				menuP->start_bit++;
				if(menuP->start_bit>3)
				{
					menuP->start_bit=0;
				}
			}
			else if(menuP == &Set_menu[2])
			{
				menuP->start_bit++;
				if(menuP->start_bit>6)
				{
					menuP->start_bit=0;
				}
			}
			else if(menuP == &Set_menu[3])
			{
				beep_bit=beep_bit^1;
			}
			else if(menuP == &Set_menu[4])
			{
				menuP=menuP->parent;
			}
			else
			{
				menuP=menuP;
			}
			break;
		}
		case 5:
		{
			if(menuP->item == menuP->menu_num)
			{
				menuP=menuP->parent;
			}
			else
			{
				menuP =menuP;
			}
			break;
		}
		default:
			break;
	}
} 

void KEY_UP(void)  
{
	u8 i ;
	switch(menuP->menu_level)
	{
		case 1:
		{
			if(menuP->start_bit == 1)
			{
				for(i=1;i<=100;i++)
				{
					if(pwm1>=900)
					{
						pwm1 = 900 ;
						break;
					}
					pwm1+=1;
				}				
			}
			else if(menuP->start_bit == 2)
			{
				for(i=1;i<=100;i++)
				{
					if(pwm2>=900)
					{
						pwm2 = 900 ;
						break;
					}
					pwm2+=1;
				}		
			}
			else
			{
				menuP = menuP->children;
				pid_bit=1;//���ֶ�ģʽ��������ģʽ
			}
			break;
		}
		case 2:
		{
			pid_bit=1;//������ģʽ�������ã�ϵͳ�Թ���������ģʽ
			L_menuP = menuP;
			menuP = menuP->children;
			break;
		}
		case 3:
		{
			if(menuP->item > 1 && menuP->item<=menuP->menu_num)
			{
				menuP=menuP-1;
			}
			else if(menuP->item==1)
		  {
			  menuP=menuP+menuP->menu_num-1;
		  } 
			else
			{
				menuP=menuP;
			}
			break;
		}
		case 4 :
		{
			if(menuP->start_bit!=0)
			{
				Num_Add();
			}
			else if(menuP->start_bit==0)
			{
				if(menuP->item > 1 && menuP->item<=menuP->menu_num)
			  {
				  menuP=menuP-1;
			  }
			  else if(menuP->item==1)
		    {
			    menuP=menuP+menuP->menu_num-1;
		    }
        else
			  {
				  menuP=menuP;
			  }				
			}
			break;
		}
		case 5:
		{
			if(menuP->item > 1 && menuP->item<=menuP->menu_num)
			{
				menuP=menuP-1;
			}
			else if(menuP->item==1)
		  {
			  menuP=menuP+menuP->menu_num-1;
		  }
			else
			{
				menuP=menuP;
			}
      break;				
		}
		default:
			break;
	}
}	

void KEY_DOWN(void) 
{
	u8 i;
	switch(menuP->menu_level)
	{
		case 1:
		{
			if(menuP->start_bit == 1)
			{
				for(i=1;i<=100;i++)
				{
					if(pwm1<=100)
					{
						pwm1 = 100 ;
						break;
					}
					pwm1-=1;
				}				
			}
			else if(menuP->start_bit == 2)
			{
				for(i=1;i<=100;i++)
				{
					if(pwm2<=100)
					{
						pwm2 = 100 ;
						break;
					}
					pwm2-=1;
				}		
			}
			else
			{
				pid_bit=0;//��ʾ��ǰ���ֶ�ģʽ�������ã�ϵͳ��Ȼ�������ֶ�ģʽ
				L_menuP = menuP;
			  menuP = menuP->parent;
			}
			
			break;
		}
		case 2:
		{
			menuP = menuP->parent;
			pid_bit=0;//������ģʽ�����ֶ�ģʽ
			break;
		}
		case 3:
		{
			if(menuP->item >= 1 && menuP->item<menuP->menu_num)
			{
				menuP=menuP+1;
			}
			else if(menuP->item==menuP->menu_num)
		  {
			  menuP=menuP-(menuP->menu_num)+1;
		  }
      else
			{
				menuP=menuP;
			}			
			break;
		}
		case 4 :
		{
			if(menuP->start_bit!=0)
			{
				Num_Subtract();
			}
			else if(menuP->start_bit==0)
			{
				if(menuP->item >= 1 && menuP->item<menuP->menu_num)
			  {
				  menuP=menuP+1;
			  }
			  else if(menuP->item==menuP->menu_num)
		    {
			    menuP=menuP-(menuP->menu_num)+1;
		    }
        else
			  {
				  menuP=menuP;
			  }				
			}
			break;
		}
		case 5:
		{
			if(menuP->item >= 1 && menuP->item<menuP->menu_num)
			{
				menuP=menuP+1;
			}
			else if(menuP->item==menuP->menu_num)
		  {
			  menuP=menuP-(menuP->menu_num)+1;
		  }
			else
			{
				menuP=menuP;
			}
      break;				
		}
		default:
			break;
	}
}	


