#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

enum class RefreshType : byte
{
    NONE,
    REFRESH,
    CLEAR_ALL
};

// Forward declaration to avoid circular dependency
class Blinker;

class LCD
{
private:
    LiquidCrystal_I2C lcd;
    Blinker *blinker;

public:
    LCD();
    void update();

    template <typename T>
    inline void print(const T &message, uint8_t col, uint8_t row)
    {
        lcd.setCursor(col, row);
        lcd.print(message);
    }

    template <typename T>
    inline void print(const T &message)
    {
        lcd.print(message);
    }

    uint8_t getLinesNumber();
    uint8_t getColumnsNumber();

    void clear();
    void clearChar(uint8_t col, uint8_t row);
    void clearColumn(uint8_t col);

    void startBlinker(const char *word, uint8_t c, uint8_t r);
    void stopBlinker();
};

#endif // LCD_H