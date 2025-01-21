#include "LCD.h"
#include "../../ProjectConfig.h"

LCD::LCD() : lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)
{
}

uint8_t LCD::getLinesNumber()
{
    return LCD_ROWS;
}