#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDManager
{
private:
    static LCDManager *instance; // Singleton instance
    LiquidCrystal_I2C lcd;       // LCD instance
    uint8_t linesNumber;         // Number of lines on the LCD
    bool LCDisON;

    // Private constructor
    LCDManager();

public:
    // Deleted copy constructor and assignment operator
    LCDManager(const LCDManager &) = delete;
    LCDManager &operator=(const LCDManager &) = delete;

    // Method to get the singleton instance
    static LCDManager &getInstance();

    // Clear the LCD
    void clear();

    // Set the cursor position
    void setCursor(uint8_t col, uint8_t row);

    // Print a message at a specific position
    template <typename T>
    inline void print(const T &message, uint8_t col = 0, uint8_t row = 0)
    {
        setCursor(col, row);
        lcd.print(message);
    }

    // Scroll up the display
    bool scrollUp(uint8_t *cursor);

    // Scroll down the display
    bool scrollDown(uint8_t *cursor);

    // Get the number of lines on the LCD
    uint8_t getLinesNumber() const;

    bool getLCDTurnedON() const;
};

#endif // LCDMANAGER_H