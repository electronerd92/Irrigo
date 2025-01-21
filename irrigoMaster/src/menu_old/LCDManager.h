#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Debug.hpp"
#include "Timer.hpp" // Include the Timer class
#include "Blinker.h" // Include the Blinker class
#include "../SystemCache.h"

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
    void clearRightToLeft(uint8_t col, uint8_t row);
    void clear(int8_t col = -1, int8_t row = -1);

    inline void printRightToLeftFormatted(uint8_t col, uint8_t row, const char *format, ...)
    {
        char *buffer = SystemCache::getBuffer(); // Get the shared buffer from SystemCache
        va_list args;
        va_start(args, format);                                        // Start processing the variable arguments
        vsnprintf(buffer, SystemCache::getBufferSize(), format, args); // Format the string into the buffer
        va_end(args);                                                  // Clean up the variable argument list
        printRightToLeft(buffer, strlen(buffer), col, row);
    }

    template <typename T>
    inline void printRightToLeft(const T &message, uint8_t messageLength, uint8_t col = 0, uint8_t row = 0)
    {
        print(message, columnsNumber - col - messageLength, row);
    }

    inline void printFormatted(uint8_t col, uint8_t row, const char *format, ...)
    {
        char *buffer = SystemCache::getBuffer(); // Get the shared buffer from SystemCache
        va_list args;
        va_start(args, format);                                        // Start processing the variable arguments
        vsnprintf(buffer, SystemCache::getBufferSize(), format, args); // Format the string into the buffer
        va_end(args);                                                  // Clean up the variable argument list
        print(buffer, col, row);                                       // Print the formatted string to the LCD at the specified position
    }

    // Print a message at a specific position
    template <typename T>
    inline void print(const T &message, uint8_t col = 0, uint8_t row = 0)
    {
        if (LCDisON)
            inactivityTimer.start();

        lcd.setCursor(col, row);
        lcd.print(message);
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
    template <typename T>
    inline void startBlinking(const T &blinkWord, uint8_t col, uint8_t row, bool rightToLeft = false, const char *format = nullptr)
    {
        blinker.startBlinking(blinkWord, col, row, rightToLeft, format);
    }

    // Stop blinking the word
    void stopBlinking(bool clear = true);
};

#endif // LCDMANAGER_H