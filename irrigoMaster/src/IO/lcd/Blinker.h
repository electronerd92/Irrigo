#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "../../ProjectConfig.h"
#include "Timer.hpp"
#include "Debug.hpp"
#include "LCD.h"

class Blinker
{
private:
    LCD *lcd;
    Timer blinkTimer;
    uint8_t col;
    uint8_t row;
    bool blinkState;
    bool isBlinking;
    char buffer[LCD_BLINK_BUFFER_SIZE];
    uint8_t wordLength;

    void printWord();
    void clearWord();

public:
    Blinker(LCD *lcd);
    void startBlinking(const char *word, uint8_t c, uint8_t r);
    void stopBlinking();
    void update();
};

#endif // BLINKER_H