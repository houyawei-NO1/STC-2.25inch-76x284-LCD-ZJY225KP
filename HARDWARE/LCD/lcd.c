#include "lcd.h"
#include "lcdfont.h"
#include "string.h"

/**
 * @brief       ��LCD��Ļ�ϻ�һ����
 * @param       x:���ص�������
 * @param       y:���ص�������
 * @param       color:�����ɫֵ
 * @retval      ��
 */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetCursor(x, y);
    LCD_WR_DATA(color);
}

/**
 * @brief       ����֮�仭�ߺ���
 * @param       xs:���ε���ʼ������
 * @param       ys:���ε���ʼ������
 * @param       xe:���εĽ���������
 * @param       ye:���εĽ���������
 * @param       color:���ε���ɫֵ
 * @retval      ��
 */
void LCD_DrawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = xe - xs; // ������������
    delta_y = ye - ys;
    uRow = xs;
    uCol = ys;
    if (delta_x > 0)
    {
        incx = 1; // ���õ�������
    }
    else if (delta_x == 0)
    {
        incx = 0; // ������
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0; // ˮƽ��
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
    {
        distance = delta_x; // ѡȡ��������������
    }
    else
    {
        distance = delta_y;
    }
    for (t = 0; t <= distance + 1; t++) // �������
    {
        LCD_DrawPoint(uRow, uCol, color); // ����
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @brief       ���ƿ��ľ��κ���
 * @param       xs:���ε���ʼ������
 * @param       ys:���ε���ʼ������
 * @param       xe:���εĽ���������
 * @param       ye:���εĽ���������
 * @param       color:���ε���ɫֵ
 * @retval      ��
 */
void LCD_DrawRectangle(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    LCD_DrawLine(xs, ys, xe, ys, color);
    LCD_DrawLine(xs, ys, xs, ye, color);
    LCD_DrawLine(xs, ye, xe, ye, color);
    LCD_DrawLine(xe, ys, xe, ye, color);
}

/**
 * @brief       ����ʵ�ľ��κ���
 * @param       xs:���ε���ʼ������
 * @param       ys:���ε���ʼ������
 * @param       xe:���εĽ���������
 * @param       ye:���εĽ���������
 * @param       color:���ε���ɫֵ
 * @retval      ��
 */
void LCD_DrawFillRectangle(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    LCD_Fill(xs, ys, xe, ye, color);
}

/**
 * @brief       8�ַ�����Բ��(�ڲ�����)
 * @param       xc:Բ��������
 * @param       yc:Բ��������
 * @param       x:�����Բ�ĵ�������
 * @param       y:�����Բ�ĵ�������
 * @param       color:Բ�ε���ɫֵ
 * @retval      ��
 */
void Draw_Circle(int xc, int yc, int x, int y, uint16_t color)
{
    LCD_DrawPoint(xc + x, yc + y, color);
    LCD_DrawPoint(xc - x, yc + y, color);
    LCD_DrawPoint(xc + x, yc - y, color);
    LCD_DrawPoint(xc - x, yc - y, color);
    LCD_DrawPoint(xc + y, yc + x, color);
    LCD_DrawPoint(xc - y, yc + x, color);
    LCD_DrawPoint(xc + y, yc - x, color);
    LCD_DrawPoint(xc - y, yc - x, color);
}

/**
 * @brief       ����Բ��
 * @param       xc:Բ��������
 * @param       yc:Բ��������
 * @param       r:Բ�ΰ뾶
 * @param       color:Բ�ε���ɫֵ
 * @param       mode:�Ƿ����Բ��
 * @retval      ��
 */
void LCD_DrawCircle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color, uint16_t mode)
{
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r;
    /*����ʵ��Բ*/
    if (mode)
    {
        while (x <= y)
        {
            for (yi = x; yi <= y; yi++)
            {
                Draw_Circle(xc, yc, x, yi, color);
            }
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    /*���ƿ���Բ*/
    else
    {
        while (x <= y)
        {
            Draw_Circle(xc, yc, x, y, color);
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/**
 * @brief       ���ƿ���������
 * @param       x:��������������ʼ����
 * @param       y:��������������ʼ����
 * @param       xs:�����ζ���������
 * @param       ys:�����ζ���������
 * @param       xe:������ĩ��������
 * @param       ye:������ĩ��������
 * @param       color:�����ε���ɫֵ
 * @retval      ��
 */
void LCD_DrawTriangel(uint16_t x, uint16_t y, uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    LCD_DrawLine(x, y, xs, ys, color);
    LCD_DrawLine(xs, ys, xe, ye, color);
    LCD_DrawLine(xe, ye, x, y, color);
}

/**
 * @brief       ��ʾ�����ַ�
 * @param       x:�ַ���ʾλ������ʼ����
 * @param       y:�ַ���ʾλ������ʼ����
 * @param       num:��ʾ�ַ���ASCII��
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t temp, sizex, t, m = 0;
    uint16_t i, TypefaceNum; // һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' ';                                     // �õ�ƫ�ƺ��ֵ
    LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1); // ������ʾ����
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 12)
            temp = ascii_1206[num][i]; // ����6x12����
        else if (sizey == 16)
            temp = ascii_1608[num][i]; // ����8x16����
        else if (sizey == 24)
            temp = ascii_2412[num][i]; // ����12x24����
        else if (sizey == 32)
            temp = ascii_3216[num][i]; // ����16x32����
        else
            return;
        for (t = 0; t < 8; t++)
        {
            if (!mode) // �ǵ���ģʽ
            {
                if (temp & (0x01 << t))
                    LCD_WR_DATA(fc);
                else
                    LCD_WR_DATA(bc);
                m++;
                if (m % sizex == 0)
                {
                    m = 0;
                    break;
                }
            }
            else // ����ģʽ
            {
                if (temp & (0x01 << t))
                    LCD_DrawPoint(x, y, fc); // ��һ����
                x++;
                if ((x - x0) == sizex)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}

/**
 * @brief       ��ʾ�ַ���
 * @param       x:�ַ�����ʾλ������ʼ����
 * @param       y:�ַ�����ʾλ������ʼ����
 * @param       *s:��ʾ���ַ�������
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowString(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint16_t sizey, uint8_t mode)
{
    while ((*s <= '~') && (*s >= ' ')) // �ж��ǲ��ǷǷ��ַ�
    {
        if (x > (LCD_W - 1) || y > (LCD_H - 1))
            return;
        LCD_ShowChar(x, y, *s, fc, bc, sizey, mode);
        x += sizey / 2;
        s++;
    }
}

/**
 * @brief       ������(�ڲ�����)
 * @param       m:����
 * @param       n:ָ��
 * @retval      result:m��n����
 */
uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

/**
 * @brief       ��ʾ����
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       num:��ʾ������(0~4294967295)
 * @param       len:��ʾ���ֵ�λ��
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t t, temp, enshow = 0;
    uint8_t sizex = sizey / 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, mode);
                continue;
            }
            else
            {
                enshow = 1;
            }
        }
        LCD_ShowChar(x + t * sizex, y, temp + '0', fc, bc, sizey, mode);
    }
}

/**
 * @brief       ��ʾ������
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       num:��ʾ�ĸ�����
 * @param       pre:��ʾ����������
 * @param       len:��ʾ��������λ��(������С����)
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowFloatNum(uint16_t x, uint16_t y, float num, uint8_t pre, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint32_t i, temp, num1;
    uint8_t sizex = sizey / 2;
    num1 = num * mypow(10, pre);
    for (i = 0; i < len; i++)
    {
        temp = (num1 / mypow(10, len - i - 1)) % 10;
        if (i == (len - pre))
        {
            LCD_ShowChar(x + (len - pre) * sizex, y, '.', fc, bc, sizey, mode);
            i++;
            len += 1;
        }
        LCD_ShowChar(x + i * sizex, y, temp + '0', fc, bc, sizey, mode);
    }
}

/**
 * @brief       ��ʾ12x12����
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       *s:��ʾ�����ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChinese12x12(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k, HZnum;    // ������Ŀ
    uint16_t TypefaceNum; // һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont12) / sizeof(typFONT_GB12); // ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont12[k].Index[0] == *(s)) && (tfont12[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) // �ǵ��ӷ�ʽ
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j))
                        {
                            LCD_WR_DATA(fc);
                        }
                        else
                        {
                            LCD_WR_DATA(bc);
                        }
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else // ���ӷ�ʽ
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j))
                        {
                            LCD_DrawPoint(x, y, fc); // ��һ����
                        }
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; // ���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/**
 * @brief       ��ʾ16x16����
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       *s:��ʾ�����ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChinese16x16(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k, HZnum;    // ������Ŀ
    uint16_t TypefaceNum; // һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont16) / sizeof(typFONT_GB16); // ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) // �ǵ��ӷ�ʽ
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j))
                        {
                            LCD_WR_DATA(fc);
                        }
                        else
                        {
                            LCD_WR_DATA(bc);
                        }
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else // ���ӷ�ʽ
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j))
                        {
                            LCD_DrawPoint(x, y, fc); // ��һ����
                        }
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; // ���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/**
 * @brief       ��ʾ24x24����
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       *s:��ʾ�����ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChinese24x24(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k, HZnum;    // ������Ŀ
    uint16_t TypefaceNum; // һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont24) / sizeof(typFONT_GB24); // ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) // �ǵ��ӷ�ʽ
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j))
                        {
                            LCD_WR_DATA(fc);
                        }
                        else
                        {
                            LCD_WR_DATA(bc);
                        }
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else // ���ӷ�ʽ
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j))
                        {
                            LCD_DrawPoint(x, y, fc); // ��һ����
                        }
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; // ���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/**
 * @brief       ��ʾ32x32����
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       *s:��ʾ�����ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChinese32x32(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k, HZnum;    // ������Ŀ
    uint16_t TypefaceNum; // һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont32) / sizeof(typFONT_GB32); // ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) // �ǵ��ӷ�ʽ
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j))
                        {
                            LCD_WR_DATA(fc);
                        }
                        else
                        {
                            LCD_WR_DATA(bc);
                        }
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else // ���ӷ�ʽ
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j))
                        {
                            LCD_DrawPoint(x, y, fc); // ��һ����
                        }
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; // ���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/**
 * @brief       ��ʾ���ִ�
 * @param       x:������ʾλ������ʼ����
 * @param       y:������ʾλ������ʼ����
 * @param       *s:��ʾ�����ַ�
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowChinese(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    while (*s != 0)
    {
        if (sizey == 12)
            LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 16)
            LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 24)
            LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 32)
            LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
        else
            return;
        s += 2;
        x += sizey;
    }
}

/**
 * @brief       ��Ӣ�ַ�����
 * @param       x:��ʾλ������ʼ����
 * @param       y:��ʾλ������ʼ����
 * @param       *s:��ʾ�ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_ShowStr(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint16_t x0 = x;
    uint8_t bHz = 0; // �ַ���������
    while (*s != 0)  // ����δ����
    {
        if (!bHz) // Ӣ��
        {
            if (x > (LCD_W - sizey / 2) || y > (LCD_H - sizey))
            {
                return;
            }
            if (*s > 0x80)
            {
                bHz = 1; // ����
            }
            else // �ַ�
            {
                if (*s == 0x0D) // ���з���
                {
                    y += sizey;
                    x = x0;
                    s++;
                }
                else
                {
                    LCD_ShowChar(x, y, *s, fc, bc, sizey, mode);
                    x += sizey / 2; // �ַ�,Ϊȫ�ֵ�һ��
                }
                s++;
            }
        }
        else // ����
        {
            if (x > (LCD_W - sizey) || y > (LCD_H - sizey))
            {
                return;
            }
            bHz = 0;
            if (sizey == 12)
                LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
            else if (sizey == 16)
                LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
            else if (sizey == 24)
                LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
            else
                LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
            s += 2;
            x += sizey;
        }
    }
}

/**
 * @brief       �ַ�������ʾ
 * @param       x:�����������Ч
 * @param       y:��ʾλ������ʼ����
 * @param       *s:��ʾ�ַ���ʼ��ַ
 * @param       fc:�ַ���ɫ
 * @param       bc:�ַ�������ɫ
 * @param       sizey:�ַ���С
 * @param       mode:�Ƿ������ʾ
 * @retval      ��
 */
void LCD_StrCenter(uint16_t x, uint16_t y,const char *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint16_t len = strlen((const char *)s);
    uint16_t x1 = (LCD_W - len * 8) / 2;
    LCD_ShowStr(x1, y, s, fc, bc, sizey, mode);
}

/**
 * @brief       ͼƬ��ʾ����
 * @param       x:ͼƬ��ʾλ������ʼ����
 * @param       y:ͼƬ��ʾλ������ʼ����
 * @param       width:ͼƬ���
 * @param       height:ͼƬ�߶�
 * @param       pic:ͼƬȡģ����
 * @retval      ��
 */
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t pic[])
{
    uint8_t picH, picL;
    uint16_t i, j;
    uint32_t k = 0;
    LCD_Address_Set(x, y, x + width - 1, y + height - 1);
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            picH = pic[k * 2];
            picL = pic[k * 2 + 1];
            LCD_WR_DATA(picH << 8 | picL);
            k++;
        }
    }
}
