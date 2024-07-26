#include "LCDManager.h"
#include "../ProjectConfig.h"

// Initialize the static member
LCDManager *LCDManager::instance = nullptr;

// Private constructor
LCDManager::LCDManager()
    : lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS), linesNumber(LCD_ROWS)
{
    lcd.init();
    lcd.backlight();
}

// Method to get the single instance of CommandManager
LCDManager &LCDManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new LCDManager();
    }
    return *instance;
}

// Clear the LCD
void LCDManager::clear()
{
    lcd.clear();
}

// Set the cursor position
void LCDManager::setCursor(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
}

// // Print a message at a specific position
// template <typename T>
// void LCDManager::print(const T &message, uint8_t col, uint8_t row)
// {
//     setCursor(col, row);
//     lcd.print(message);
// }

// Get the number of lines on the LCD
uint8_t LCDManager::getLinesNumber() const
{
    return linesNumber;
}

// Scroll up the display
bool LCDManager::scrollUp(uint8_t *cursor)
{
    if (*cursor > 0)
    {
        --(*cursor);
        return true;
    }
    return false;
}

// Scroll down the display
bool LCDManager::scrollDown(uint8_t *cursor)
{
    if (*cursor < (linesNumber - 1))
    {
        ++(*cursor);
        return true;
    }
    return false;
}

bool LCDManager::getLCDTurnedON() const
{
    return true;
}
