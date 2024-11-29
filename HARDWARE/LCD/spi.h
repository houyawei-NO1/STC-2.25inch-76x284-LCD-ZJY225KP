#ifndef _SPI_H_
#define _SPI_H_

//#include "reg51.h"
#include "..\..\comm\STC32G.h"
#define MAIN_Fosc        12000000UL
/*����    ����*/
#define uint8_t unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long
/* ����ܽŶ˿� */
sbit LCD_SCK = P2 ^ 0;  // ʱ�ӹܽ�
sbit LCD_MOSI = P2 ^ 1; // ���ݹܽ�
sbit LCD_RES = P2 ^ 2;  // ��λ�ܽ�
sbit LCD_DC = P2 ^ 3;   // ����/����ܽ�
sbit LCD_CS = P2 ^ 4;   // Ƭѡ�ź���
sbit LCD_BLK = P2 ^ 5;  // ������ƹܽ�

/* ����˿ڵ�ƽ״̬ */
#define LCD_SCK_Set() LCD_SCK = 1
#define LCD_SCK_Clr() LCD_SCK = 0

#define LCD_MOSI_Set() LCD_MOSI = 1
#define LCD_MOSI_Clr() LCD_MOSI = 0

#define LCD_RES_Set() LCD_RES = 1
#define LCD_RES_Clr() LCD_RES = 0

#define LCD_DC_Set() LCD_DC = 1
#define LCD_DC_Clr() LCD_DC = 0

#define LCD_CS_Set() LCD_CS = 1
#define LCD_CS_Clr() LCD_CS = 0

#define LCD_BLK_Set() LCD_BLK = 1
#define LCD_BLK_Clr() LCD_BLK = 0

/* �������� */
void LCD_GPIOInit(void);
void LCD_WR_Bus(uint8_t dat);
void LCD_WR_REG(uint8_t reg);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);

#endif





