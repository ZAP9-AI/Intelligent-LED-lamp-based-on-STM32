#include "menu.h"
#include "oled.h"
#include "rtc.h"
#include "usmart.h"
#include "usmart_str.h"
#include "function.h"
#include "adc.h"
#include "pwm.h"



extern u8 cursor_position ;
extern int Natural_Light;//环境光
extern int LED_Light;//LED灯光
extern u8 beep_bit;
extern struct _calendar_obj calendar;
extern u8  Time_value[3] ;
extern u16 Date_value[3] ;
//extern u8 tbuf[40];

struct Menu *menuP                         ;//指向当前菜单

struct Menu Manual_mode                    ;//手动模式
struct Menu Intelligent_mode[4]            ;//智能模式
struct Menu Settings_menu[3]               ;//设置菜单
struct Menu Set_menu[5]                    ;//
struct Menu Browse_Value[5] ;
struct AlarmA alarma ;

struct AlarmA alarma = {
	  1,
	  1,
	  1,
	  1,
	  1,
	  1,
	};

struct Menu Manual_mode ={
    1,1,1,1,1,0,Settings_menu,Intelligent_mode,Manual_display,
	};

struct Menu Intelligent_mode[4] ={
  {4,1,1,1,2,0,&Manual_mode, Settings_menu, Intelligent_display},
	{4,2,1,1,2,0,&Manual_mode, Settings_menu, Intelligent_display},
	{4,3,1,1,2,0,&Manual_mode, Settings_menu, Intelligent_display},
	{4,4,1,1,2,0,&Manual_mode, Settings_menu, Intelligent_display},
	};


struct Menu Settings_menu[3] = {
	 {3,1,1,1,3,0,Intelligent_mode, Browse_Value, Settings_display},
	 {3,2,1,1,3,0,Intelligent_mode, Set_menu, Settings_display},
	 {3,3,1,1,3,0,Intelligent_mode, &Manual_mode, Settings_display},
  };

struct Menu Set_menu[5] = {
	 {5,1,2,1,4,0,Settings_menu, NULL, Set_display},
	 {5,2,2,1,4,0,Settings_menu, NULL, Set_display},
	 {5,3,2,1,4,0,Settings_menu, NULL, Set_display},
	 {5,4,2,2,4,0,Settings_menu, NULL, Set_display},
	 {5,5,2,2,4,0,Settings_menu, NULL, Set_display},
  };

struct Menu Browse_Value[5]={
	 {5,1,2,1,5,0,Settings_menu,NULL,Observed_Value},
	 {5,2,2,1,5,0,Settings_menu,NULL,Observed_Value},
	 {5,3,2,1,5,0,Settings_menu,NULL,Observed_Value},
	 {5,4,2,1,5,0,Settings_menu,NULL,Observed_Value},
	 {5,5,2,2,5,0,Settings_menu,NULL,Observed_Value},
};	

struct Menu *menuP = &Manual_mode             ;//指向主菜单的第一项

///*=========================================================*/
///*==================主菜单显示函数=========================*/
///*=========================================================*/
//	
//void Main_display(void)
//{
//	
//}

/*=========================================================*/
/*==================手动模式显示函数==========================*/
/*=========================================================*/

void Manual_display(void)
{
//  Options_Choose(menuP->item);	
  OLED_ShowString(23,0,"Manual Mode",12);
  Time_Date_display();	
}	

/*=========================================================*/
/*==================智能模式显示函数==========================*/
/*=========================================================*/

void Intelligent_display(void)
{
   Switch_mode(menuP->item);
   Time_Date_display();	
}	

	
/*=========================================================*/
/*==================设置模式显示函数==========================*/
/*=========================================================*/

void Settings_display(void)
{
  OLED_ShowString(23,0,"Settings",12);
  Options_Choose(menuP->item);
  OLED_ShowString(15,13,"1.Browse Value",12);
  OLED_ShowString(15,26,"2.Set T_D_A",12);
  OLED_ShowString(15,38,"3.Back",12);
}	

/*=========================================================*/
/*==================设置模式显示函数==========================*/
/*=========================================================*/

void Set_display(void)
{
  u8 tbuf[40];
  OLED_ShowString(33,0,"Set",12);
  Options_Choose(menuP->item);
  switch(menuP->page)
	{
		case 1:
	  {
		  sprintf((char*)tbuf,"1.Time:%02d:%02d:%02d",Time_value[0],Time_value[1],Time_value[2]);
	    OLED_ShowString(15,13,tbuf,12); //时间
	    sprintf((char*)tbuf,"2.Date:%04d-%02d-%02d",Date_value[0],Date_value[1],Date_value[2]);
      OLED_ShowString(15,26,tbuf,12); //日期
	    sprintf((char*)tbuf,"3.alarm:%02d:%02d:%02d",alarma.hours,alarma.minutes,alarma.seconds);
	    OLED_ShowString(15,38,tbuf,12);//闹钟
			sprintf((char*)tbuf,"%04d-%02d-%02d",alarma.year, alarma.month, alarma.date);
	    OLED_ShowString(62,50,tbuf,12);
	    break;
		}
		case 2:
		{
			if(beep_bit==1)
		  {
		    OLED_ShowString(15,13,"4.alarm:     ON",12);
	    }
	    else if(beep_bit==0 )
	    {
		    OLED_ShowString(15,13,"4.alarm:     OFF",12);
	    }
		  OLED_ShowString(15,26,"5.Back",12);
		  break;
		}
		default:
		  break;
	}		
}	


/*=========================================================*/
/*==================查看pwm和光传感器的值函数=========================*/
/*=========================================================*/

void Observed_Value(void)
{
	OLED_ShowString(33,0,"Value Display",12);
	Options_Choose(menuP->item);
	switch(menuP->page)
	{
		case 1:
	  {
			Lights_pwm_display(Natural_Light,LED_Light,pwm1,pwm2);
			break;
		}
		case 2:
		{
			OLED_ShowString(15,13,"5.Back",12);
			break;
		}
		default:
			break;
	}
}
