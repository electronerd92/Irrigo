#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "../ProjectConfig.h"
#include "Timer.hpp"
#include "Debug.hpp"

class Blinker
{
private:
    Timer blinkTimer;   // Timer to handle blinking
    char *blinkWord;    // The word to blink
    uint8_t col;        // Column position of the blinking word
    uint8_t row;        // Row position of the blinking word
    uint8_t wordLength; // Length of the blinking word
    bool blinkState;    // Current state of blinking (visible or not)
    bool isBlinking;    // Flag to indicate if blinking is active
    bool rightToLeft;   // Variable to store blinking direction

    // #region bufferize

    inline void bufferize(const char *value)
    {
        strncpy(blinkWord, value, LCD_BLINK_BUFFER_SIZE);
        blinkWord[LCD_BLINK_BUFFER_SIZE - 1] = '\0'; // Ensure null-termination
    }

    inline void bufferize(const __FlashStringHelper *value)
    {
        strncpy_P(blinkWord, (PGM_P)value, LCD_BLINK_BUFFER_SIZE);
        blinkWord[LCD_BLINK_BUFFER_SIZE - 1] = '\0'; // Ensure null-termination
    }

    inline void bufferize(uint8_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%u", value);
    }

    inline void bufferize(int8_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%d", value);
    }

    inline void bufferize(uint16_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%u", value);
    }

    inline void bufferize(int16_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%d", value);
    }

    inline void bufferize(uint32_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%lu", value); // Use %lu for uint32_t
    }

    inline void bufferize(int32_t value)
    {
        snprintf(blinkWord, LCD_BLINK_BUFFER_SIZE, "%ld", value); // Use %ld for int32_t
    }

    inline void bufferize(double value)
    {
        dtostrf(value, 3, 1, blinkWord);
    }

    // #endregion

    // Private method to clear the word from the display
    void clearWord();

public:
    Blinker();

    template <typename T>
    inline void startBlinking(const T &blinkWord, uint8_t col, uint8_t row, bool rightToLeft = false)
    {
        bufferize(blinkWord); // Use the bufferize function to convert the word
        this->col = col;
        this->row = row;
        this->wordLength = strlen(this->blinkWord);
        this->isBlinking = true;
        this->blinkState = true;
        this->rightToLeft = rightToLeft;
        this->blinkTimer.start();
    }

    // Stop blinking the word
    void stopBlinking();

    // Update method to manage the blinking state
    void update();
};

#endif // BLINKER_H
