#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCD
{
private:
    LiquidCrystal_I2C lcd;

public:
    LCD();

    template <typename T>
    inline void print(const T &message, uint8_t col = 0, uint8_t row = 0)
    {
        lcd.setCursor(col, row);
        lcd.print(message);
    }

    uint8_t getLinesNumber();
    uint8_t getColumnsNumber();

    void clear();
    void clearChar(uint8_t col, uint8_t row);
    void clearColumn(uint8_t col);
};

#endif // LCD_H