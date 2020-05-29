#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"

#define NULL  0
#define start 1
#define stop  0 
extern u8 value;


struct Menu{
	   u8 menu_num                   ;//菜单数目
	   u8 item                       ;//当前菜单项
	   u8 page_num                   ;//菜单页数
	   u8 page                       ;//菜单当前页数
	   u8 menu_level                 ;//菜单等级
	   u8 start_bit                  ;//功能确定，1为可以设定，0为不可以设定,在智能模式下：0：Reading 1:Writting 2:Moive 3: Game
	   struct Menu *parent           ;//上一级菜单
		 struct Menu *children         ;//下一级菜单
		 void(*Function)(void)         ;//当前菜单的功能函数
};

struct AlarmA{
	   u16 year;
	   u8 month;
	   u8 date;
	   int hours;
	   int minutes;
	   int seconds;
};

//struct Clear_bit{             //用于切换菜单或者光标标记，防止一直清屏
//	   u8 manual_bit;     
//	   u8 intelligent_bit;
//	   u8 cursor_bit;
//	   u8 setting_bit;
//	   u8 level3_bit;
//};

//void Main_display(void);

void Manual_display(void);
void Intelligent_display(void);
void Settings_display(void);
void Set_display(void);
void Observed_Value(void);
//void Manual_Setting_display(void);
//void Intelligent_Setting_display(void);



#endif
