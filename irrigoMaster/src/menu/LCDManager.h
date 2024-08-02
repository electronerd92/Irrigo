#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Timer.hpp" // Include the Timer class
#include "Blinker.h" // Include the Blinker class

class LCDManager
{
private:
    static LCDManager *instance; // Singleton instance
    LiquidCrystal_I2C lcd;       // LCD instance
    const uint8_t linesNumber;   // Number of lines on the LCD
    const uint8_t columnsNumber; // Number of columns on the LCD
    Timer inactivityTimer;       // Timer to track inactivity
    bool LCDisON;
    Blinker blinker; // Blinker instance

    // Private constructor
    LCDManager();

public:
    // Deleted copy constructor and assignment operator
    LCDManager(const LCDManager &) = delete;
    LCDManager &operator=(const LCDManager &) = delete;

    // Method to get the singleton instance
    static LCDManager &getInstance();

    // Clear the LCD
    void clear(int8_t col = -1, int8_t row = -1);

    // Print a message at a specific position
    template <typename T>
    inline void print(const T &message, uint8_t col = 0, uint8_t row = 0, bool rightToLeft = false)
    {
        if (LCDisON)
            inactivityTimer.start();

        if (rightToLeft)
        {
            lcd.setCursor(columnsNumber - 1 - col, row);
            lcd.rightToLeft();
        }
        else
        {
            lcd.setCursor(col, row);
            lcd.leftToRight();
        }

        lcd.print(message);

        // Reset Printing direction to leftToRight for consistency
        lcd.leftToRight();
    }

    // Scroll up the display
    bool scrollUp(uint8_t *cursor);

    // Scroll down the display
    bool scrollDown(uint8_t *cursor);

    // Get the number of lines on the LCD
    uint8_t getLinesNumber() const;

    bool getLCDTurnedON() const;

    void update();

    // Start blinking a word at a specific position
    void startBlinking(const __FlashStringHelper *blinkWord, int8_t col, uint8_t row);

    // Stop blinking the word
    void stopBlinking();
};

#endif // LCDMANAGER_H