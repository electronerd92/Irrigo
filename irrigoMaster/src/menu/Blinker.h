#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "Timer.hpp"

class Blinker
{
private:
    Timer blinkTimer;                // Timer to handle blinking
    const __FlashStringHelper *blinkWord; // The word to blink
    int8_t col;                      // Column position of the blinking word
    uint8_t row;                     // Row position of the blinking word
    size_t wordLength;               // Length of the blinking word
    bool blinkState;                 // Current state of blinking (visible or not)
    bool isBlinking;                 // Flag to indicate if blinking is active

public:
    Blinker(const uint32_t blinkInterval);

    // Start blinking a word at a specific position
    void startBlinking(const __FlashStringHelper *blinkWord, int8_t col, uint8_t row);

    // Stop blinking the word
    void stopBlinking();

    // Update method to manage the blinking state
    void update();
};

#endif // BLINKER_H
