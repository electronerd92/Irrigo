#include "LCDManager.h"
#include "../ProjectConfig.h"
#include "CommandManager.h"
#include "Command.h"

// Initialize the static member
LCDManager *LCDManager::instance = nullptr;

// Private constructor
LCDManager::LCDManager()
    : lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS),
      linesNumber(LCD_ROWS),
      columnsNumber(LCD_COLUMNS),
      inactivityTimer(LCD_TIME_ON), // Example: 1 minute inactivity period
      LCDisON(true)                 // Assume LCD is ON initially
{
    lcd.init();
    lcd.backlight();
    inactivityTimer.start();
}

// Method to get the single instance of LCDManager
LCDManager &LCDManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new LCDManager();
    }
    return *instance;
}

// Clear the LCD
void LCDManager::clear(int8_t col, int8_t row)
{
    if (col == -1 && row == -1)
    {
        // Clear the entire display
        lcd.clear();
    }
    else if (col != -1 && row == -1)
    {
        // Clear a specific column
        for (uint8_t r = 0; r < linesNumber; ++r)
        {
            lcd.setCursor(col, r);
            lcd.print(' ');
        }
    }
    else if (col == -1 && row != -1)
    {
        // Clear a specific row
        lcd.setCursor(0, row);
        for (uint8_t c = 0; c < columnsNumber; ++c)
        {
            lcd.print(' ');
        }
    }
    else if (col != -1 && row != -1)
    {
        // Clear a specific character
        lcd.setCursor(col, row);
        lcd.print(' ');
    }
}

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
    return LCDisON;
}

// Update method to manage LCD state based on inactivity
void LCDManager::update()
{
    if (LCDisON && inactivityTimer.timeout())
    {
        lcd.noBacklight();
        LCDisON = false;
    }
    else if (!LCDisON && CommandManager::getInstance().readCommand() != Command::NONE)
    {
        LCDisON = true;
        lcd.backlight();
        inactivityTimer.start();
    }
}