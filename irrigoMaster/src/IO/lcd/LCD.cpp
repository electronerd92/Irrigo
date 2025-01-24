#include "LCD.h"
#include "../../ProjectConfig.h"

LCD::LCD() : lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)
{
    lcd.init();
    lcd.backlight();
}

uint8_t LCD::getLinesNumber()
{
    return LCD_ROWS;
}

uint8_t LCD::getColumnsNumber()
{
    return LCD_COLUMNS;
}

void LCD::clear()
{
    lcd.clear();
}

void LCD::clearChar(uint8_t col, uint8_t row)
{
    print(F(" "), col, row);
}

void LCD::clearColumn(uint8_t col)
{
    for (uint8_t r = 0; r < LCD_ROWS; ++r)
    {
        clearChar(col, r);
    }
}