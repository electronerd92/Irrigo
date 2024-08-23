#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "../ProjectConfig.h"
#include "Timer.hpp"
#include "CustomTypes.h"
#include "../SystemCache.h"
#include "Debug.hpp"

class Blinker
{
private:
    Timer blinkTimer;   // Timer to handle blinking
    uint8_t col;        // Column position of the blinking word
    uint8_t row;        // Row position of the blinking word
    uint8_t wordLength; // Length of the blinking word
    bool blinkState;    // Current state of blinking (visible or not)
    bool isBlinking;    // Flag to indicate if blinking is active
    bool rightToLeft;   // Variable to store blinking direction

    // #region bufferize

    inline void bufferize(const char *value, const char *format = nullptr)
    {
        strncpy(SystemCache::getBuffer(), value, SystemCache::getBufferSize());
        SystemCache::getBuffer()[SystemCache::getBufferSize() - 1] = '\0'; // Ensure null-termination
    }

    inline void bufferize(const __FlashStringHelper *value, const char *format = nullptr)
    {
        strncpy_P(SystemCache::getBuffer(), (PGM_P)value, SystemCache::getBufferSize());
        SystemCache::getBuffer()[SystemCache::getBufferSize() - 1] = '\0'; // Ensure null-termination
    }

    inline void bufferize(uint8_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%u", value);
    }

    inline void bufferize(int8_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%d", value);
    }

    inline void bufferize(uint16_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%u", value);
    }

    inline void bufferize(int16_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%d", value);
    }

    inline void bufferize(uint32_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%lu", value); // Use %lu for uint32_t
    }

    inline void bufferize(int32_t value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), "%ld", value); // Use %ld for int32_t
    }

    inline void bufferize(double value, const char *format = nullptr)
    {
        if (format)
            snprintf(SystemCache::getBuffer(), SystemCache::getBufferSize(), format, value);
        else
            dtostrf(value, 3, 1, SystemCache::getBuffer());
    }

    // #endregion

    // Private method to clear and print the word from the display
    void clearWord();
    void printWord();

public:
    Blinker();

    template <typename T>
    inline void startBlinking(const T &blinkWord, uint8_t col, uint8_t row, bool rightToLeft = false, const char *format = nullptr)
    {
        bufferize(blinkWord, format);
        this->col = col;
        this->row = row;
        this->wordLength = strlen(SystemCache::getBuffer());
        this->isBlinking = true;
        this->blinkState = true;
        this->rightToLeft = rightToLeft;
        this->blinkTimer.start();
    }

    // Stop blinking the word
    void stopBlinking(bool clear = true);

    // Update method to manage the blinking state
    void update();
};

#endif // BLINKER_H
