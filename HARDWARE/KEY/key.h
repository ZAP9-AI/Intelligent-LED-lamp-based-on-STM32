#ifndef __KEY_H
#define __KEY_H	 

#include "sys.h"  
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
 

//定义按键的功能
#define S1   PAin(3)
#define S2   PAin(4)
//#define S3   PDin(2)
#define S4   PBin(1)

//#define start 1          //启动
//#define stop  0          //停止

void KEY_Init(void)         ;//外部中断初始化
//void EXTIX_Init(void);

void KEY_Scan(void);
void KEY_ENTER(void)        ;//确定按键函数
void KEY_UP(void)           ;
void KEY_DOWN(void)         ;
void Num_Add(void)         ;
void Num_Subtract(void)     ;

 	 					    
#endif

























