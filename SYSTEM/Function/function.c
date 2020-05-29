#include "function.h"
#include "oled.h"
#include "menu.h"
#include "rtc.h"
#include "pwm.h"
#include "usmart.h"
#include "usmart_str.h"

extern struct Menu Intelligent_mode[5]            ;//智能模式
extern struct _calendar_obj calendar;//时钟结构体 
extern u8 Time_value[3] ;
extern u16 Date_value[3] ;
extern struct Menu Set_menu[5]                    ;
extern struct AlarmA alarma ;

extern struct Menu *menuP                         ;

void Week_Display(u8 week)
{
	switch(week)
	{
		case 1:
		{
			OLED_ShowString(65,49,"Monday",12);
		  break;
		}
		case 2:
		{
			OLED_ShowString(65,49,"Tuesday",12);
		  break;
		}
		case 3:
		{
			OLED_ShowString(65,49,"Wednesday",12);
		  break;
		}
		case 4:
		{
			OLED_ShowString(65,49,"Thursday",12);
		  break;
		}
		case 5:
		{
			OLED_ShowString(65,49,"Friday",12);
		  break;
		}
		case 6:
		{
			OLED_ShowString(65,49,"Saturday",12);
		  break;
		}
		case 7:
		{
			OLED_ShowString(65,49,"Sunday",12);
		  break;
		}
		default:
			break;
	}	
}


void Time_Date_display(void)
{
	u8 tbuf[40];
	sprintf((char*)tbuf,"%02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);
	OLED_ShowString(15,12,tbuf,24); //显示时间
	sprintf((char*)tbuf,"%04d-%02d-%02d",calendar.w_year,calendar.w_month,calendar.w_date);
	OLED_ShowString(2,39,tbuf,12); //日期
	Week_Display(calendar.week);//星期s
  free(tbuf);
}


void Switch_mode(u8 mode)
{
	switch(mode)
	{
		case 1:
		{
			OLED_ShowString(23,0,"Reading Mode",12);
			break;
		}
		case 2:
		{
			OLED_ShowString(23,0,"Writting Mode",12);
			break;
		}
		case 3:
		{
			OLED_ShowString(23,0,"Movie Mode",12);
			break;
		}
		case 4:
		{
			OLED_ShowString(23,0,"Game Mode",12);
			break;
		}
		default:
			break;
	}
}


void Lights_pwm_display(u16 light1, u16 light2, u16 Pwm1, u16 Pwm2)
{
	u8 tbuf[40];
	sprintf((char*)tbuf,"1.Ambient_L:%02d",200); 	
	OLED_ShowString(15,13,tbuf,12);
	
	sprintf((char*)tbuf,"2.LED_L:%02d",200); 	
	OLED_ShowString(15,26,tbuf,12);
	
	sprintf((char*)tbuf,"3.Y_Pwm:%2d%/%2d", 20,150); 	
	OLED_ShowString(15,38,tbuf,12);
	
	sprintf((char*)tbuf,"4.W_Pwm:%2d%/%2d", 30,150); 	
	OLED_ShowString(15,50,tbuf,12);
}

void Options_Choose(u8 option_num)
{
  switch(menuP->page)
	{
		case 1:
		{
			switch(option_num)
	    {
		    case 1:
		    {
			    OLED_ShowString(0,13,"->",12);
			    break;
		    }
		    case 2:
		    {
			    OLED_ShowString(0,26,"->",12);
			    break;
		    }
		    case 3:
		    {
			    OLED_ShowString(0,38,"->",12);
			    break;
		    }
		    case 4:
		    {
				  OLED_ShowString(0,50,"->",12);
		    }
		    default:
			  break;
	   }
	      break;
	  }
	  case 2:
	  {
			if(menuP == &Set_menu[3])
			{
				OLED_ShowString(0,13,"->",12);
			}
			else if(menuP == &Set_menu[4])
			{
				OLED_ShowString(0,26,"->",12);
			}
			else 
			{
				OLED_ShowString(0,13,"->",12);
			}
		  break;
	  }
	  default :
		  break;
	}
}


/*=========================================================*/
/*==================设置时间=========================*/
/*=========================================================*/
	
void Set_Time(void)
{
	switch(menuP->start_bit)
	{
		case 1:
		{
			RTC_Set(calendar.w_year, calendar.w_month, calendar.w_date, Time_value[0], calendar.min, calendar.sec);	
			break;
		}
		case 2:
		{
			RTC_Set(calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, Time_value[1], calendar.sec);
			break;
		}
		case 3:
		{
			RTC_Set(calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, calendar.min, Time_value[2]);
			break;
		}
		default:
			break;
	}

}

/*=========================================================*/
/*==================设置日期=========================*/
/*=========================================================*/
	
void Set_Date(void)
{
	switch(menuP->start_bit)
	{
		case 1:
		{
			RTC_Set(Date_value[0], calendar.w_month, calendar.w_date,  calendar.hour, calendar.min, calendar.sec);	
			break;
		}
		case 2:
		{
			RTC_Set(calendar.w_year, Date_value[1], calendar.w_date, calendar.hour, calendar.min, calendar.sec);
			break;
		}
		case 3:
		{
			RTC_Set(calendar.w_year, calendar.w_month, Date_value[2], calendar.hour, calendar.min,calendar.sec);
			break;
		}
		default:
			break;
	}
}

/*=========================================================*/
/*==================设置闹钟=========================*/
/*=========================================================*/
	
void Set_AlarmA(void)
{
	switch(menuP->start_bit)
	{
		case 5:
		{
			RTC_Alarm_Set(alarma.year, alarma.month, alarma.date, alarma.hours, alarma.minutes, alarma.seconds);	
			break;
		}
		default:
			break;
	}
}


