#ifndef __OLED_H
#define __OLED_H

#include "sys.h"
#include "stdlib.h"	


#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_7)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_7)

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_8)//RES
//#define OLED_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define IIC_READ_SDA    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_Area_Clear(u8 x0,u8 y0,u8 x1,u8 y1) ;
//void OLED_Cursor_Clear(u8 postion_num) ;
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
//void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
//void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);
void The_Arrow(u8 x0,u8 y0,u8 x1,u8 y1);//箭头
void Arrow(u8 num) ;//箭头的位置
void Main_Arrow(u8 num);
#endif




