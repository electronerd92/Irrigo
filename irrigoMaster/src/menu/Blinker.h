#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "Timer.hpp"

class Blinker
{
private:
    Timer blinkTimer;                     // Timer to handle blinking
    const __FlashStringHelper *blinkWord; // The word to blink
    uint8_t col;                          // Column position of the blinking word
    uint8_t row;                          // Row position of the blinking word
    size_t wordLength;                    // Length of the blinking word
    bool blinkState;                      // Current state of blinking (visible or not)
    bool isBlinking;                      // Flag to indicate if blinking is active
    bool rightToLeft;                     // Variable to store blinking direction

public:
    Blinker(const uint32_t blinkInterval);

    // Start blinking a word at a specific position
    void startBlinking(const __FlashStringHelper *blinkWord, uint8_t col, uint8_t row, bool rightToLeft = false);

    // Stop blinking the word
    void stopBlinking();

    // Update method to manage the blinking state
    void update();
};

#endif // BLINKER_H
