#include "lcd_init.h"
#include "stdio.h"

/**
 * @brief       ��׼ȷ������ʱ
 * @param       ms:Ҫ��ʱ��ʱ��
 * @retval      ��
 */
void delay_ms(uint16_t ms)
{
    uint16_t i;
    do{
          i = MAIN_Fosc / 6000;
          while(--i);
     }while(--ms);
}

/**
 * @brief       ���ù��λ��
 * @param       x:�����е�ַ
 * @param       y:�����е�ַ
 * @retval      ��
 */
void LCD_SetCursor(uint16_t x, uint16_t y)
{
    LCD_Address_Set(x, y, x, y);
}

/**
 * @brief       ������ʾ����
 * @param       xs:��������ʼ��ַ
 * @param       ys:��������ʼ��ַ
 * @param       xe:�����н�����ַ
 * @param       ye:�����н�����ַ
 * @retval      ��
 */
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(xs+0x52);
        LCD_WR_DATA(xe+0x52);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(ys+0x12);
        LCD_WR_DATA(ye+0x12);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(xs+0x52);
        LCD_WR_DATA(xe+0x52);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(ys+0x12);
        LCD_WR_DATA(ye+0x12);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(xs+0x12);
        LCD_WR_DATA(xe+0x12);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(ys+0x52);
        LCD_WR_DATA(ye+0x52);
        LCD_WR_REG(0x2c);//������д
    }
    else
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(xs+0x12);
        LCD_WR_DATA(xe+0x12);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(ys+0x52);
        LCD_WR_DATA(ye+0x52);
        LCD_WR_REG(0x2c);//������д
    }
}
/**
 * @brief       ָ����ɫ�������
 * @param       xs:�����������ʼ��ַ
 * @param       ys:�����������ʼ��ַ
 * @param       xe:��������н�����ַ
 * @param       ye:��������н�����ַ
 * @param       color:�����ɫֵ
 * @retval      ��
 */
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint16_t i, j;
    LCD_Address_Set(xs, ys, xe - 1, ye - 1);
    for (j = ys; j < ye; j++)
    {
        for (i = xs; i < xe; i++)
        {
            LCD_WR_DATA(color);
        }
    }
}

/**
 * @brief       ��ʼ��LCD
 * @param       ��
 * @retval      ��
 */
void LCD_Init(void)
{
    LCD_GPIOInit();
    LCD_RES_Set();
    delay_ms(20);
    LCD_RES_Clr();
    delay_ms(200);
    LCD_RES_Set();
    delay_ms(120);
    LCD_BLK_Set();

    LCD_WR_REG(0x11);
    delay_ms(120);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB0);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0xE0);

    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x45);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x1D);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x19);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x0F);

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xD6);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x21);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x15);
    LCD_WR_DATA8(0x2D);
    LCD_WR_DATA8(0x41);
    LCD_WR_DATA8(0x44);
    LCD_WR_DATA8(0x4F);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x1D);
    LCD_WR_DATA8(0x1F);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x1B);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x42);
    LCD_WR_DATA8(0x54);
    LCD_WR_DATA8(0x50);
    LCD_WR_DATA8(0x3E);
    LCD_WR_DATA8(0x1A);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x22);
    LCD_WR_DATA8(0x25);
    LCD_WR_REG(0x11);
    delay_ms(120);
    LCD_WR_REG(0x29);

}

