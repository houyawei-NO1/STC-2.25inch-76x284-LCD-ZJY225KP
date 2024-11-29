#include "spi.h"

void LCD_GPIOInit(void)
{
    /*
     ����MCU�ͺ���Ҫ��ʼ���˿�����
     ��LCD�йصĹܽ�ȫ������Ϊ�������
    */
}

/**
 * @brief       IOģ��SPI����һ���ֽ�����
 * @param       dat: ��Ҫ���͵��ֽ�����
 * @retval      ��
 */
void LCD_WR_Bus(uint8_t dat)
{
    uint8_t i;
    LCD_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        LCD_SCK_Clr();
        if (dat & 0x80)
        {
            LCD_MOSI_Set();
        }
        else
        {
            LCD_MOSI_Clr();
        }
        LCD_SCK_Set();
        dat <<= 1;
    }
    LCD_CS_Set();
}

/**
 * @brief       ��Һ��д�Ĵ�������
 * @param       reg: Ҫд������
 * @retval      ��
 */
void LCD_WR_REG(uint8_t reg)
{
    LCD_DC_Clr();
    LCD_WR_Bus(reg);
    LCD_DC_Set();
}

/**
 * @brief       ��Һ��дһ���ֽ�����
 * @param       dat: Ҫд������
 * @retval      ��
 */
void LCD_WR_DATA8(uint8_t dat)
{
    LCD_DC_Set();
    LCD_WR_Bus(dat);
    LCD_DC_Set();
}

/**
 * @brief       ��Һ��дһ����������
 * @param       dat: Ҫд������
 * @retval      ��
 */
void LCD_WR_DATA(uint16_t dat)
{
    LCD_DC_Set();
    LCD_WR_Bus(dat >> 8);
    LCD_WR_Bus(dat & 0xFF);
    LCD_DC_Set();
}
