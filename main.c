/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

本例程基于STC32G为主控芯片的实验箱进行编写测试。

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

单纯的IO口初始化，端口模式配置参考程序.

下载时, 选择时钟 12MHz (用户可自行修改频率).

//  功能描述   : LCD SPI演示例程
//               GND  电源地
//               VCC  3.3V电源
//               SCLK P1^0
//               MOSI P1^1
//               RES  P1^2
//               DC   P1^3
//               CS   P1^4

******************************************/

//#include "comm\STC32G.h"

#include "stdio.h"
#include "intrins.h"

#include "lcd.h"
#include "pic.h"

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;



/****************************** 用户定义宏 ***********************************/


/*****************************************************************************/

/*************  本地常量声明    **************/


/*************  本地变量声明    **************/


/*************  本地函数声明    **************/


/********************* 主函数 *************************/
void main(void)
{
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度


	P2M0 = 0x00; P2M1 = 0x00; 

	EA = 1;     //打开总中断
	LCD_Init();

   while(1)
    {
        LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
        LCD_ShowPicture(86, 0, 105, 56, gImage_1);
        LCD_ShowString(13, 60, "2.25 TFT RESOLUTION:284x76 DRIVER IC:ST7789", RED, WHITE, 12, 0);
        delay_ms(1000);
        LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
        LCD_Fill(0, 0, 37, LCD_H, RED);
        LCD_Fill(37, 0, 72, LCD_H, GREEN);
        LCD_Fill(72, 0, 107, LCD_H, BLUE);
        LCD_Fill(107, 0, 142, LCD_H, YELLOW);
        LCD_Fill(142, 0, 177, LCD_H, WHITE);
        LCD_Fill(177, 0, 209, LCD_H, GRAY);
        LCD_Fill(209, 0, 244, LCD_H, BLACK);
        LCD_Fill(244, 0, 284, LCD_H, MAGENTA);
        delay_ms(1000);
        LCD_Fill(0, 0, LCD_W / 2, LCD_H / 2, RED);
        LCD_Fill(LCD_W / 2, 0, LCD_W, LCD_H / 2, GREEN);
        LCD_Fill(0, LCD_H / 2, LCD_W / 2, LCD_H, BLUE);
        LCD_Fill(LCD_W / 2, LCD_H / 2, LCD_W, LCD_H, WHITE);
        delay_ms(1000);
		LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
		LCD_ShowPicture(5, 5, 76, 62, tuolaji);
		LCD_ShowChinese(100,35,"欢迎使用东方红农业装备",RED,WHITE,16,0);
		
		delay_ms(5000);
    }
}
