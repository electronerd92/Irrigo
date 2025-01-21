#include "Blinker.h"
#include "LCDManager.h"

Blinker::Blinker()
    : blinkTimer(LCD_BLINK_INTERVAL),
      col(0),
      row(0),
      wordLength(0),
      blinkState(true),
      isBlinking(false),
      rightToLeft(false)
{
}

void Blinker::stopBlinking(bool clear)
{
    if (!isBlinking)
        return;
    isBlinking = false;
    // Clear the word if it's visible and clear is true
    if (blinkState && clear)
    {
        clearWord();
    }

    // Print the word if it's not visible and clear is false
    else if (!blinkState && !clear)
    {
        printWord();
    }
}

void Blinker::clearWord()
{
    for (uint8_t i = 0; i < wordLength; ++i)
    {
        rightToLeft ? LCDManager::getInstance().clearRightToLeft(col + i, row) : LCDManager::getInstance().clear(col + i, row);
    }
}

void Blinker::printWord()
{
    rightToLeft
        ? LCDManager::getInstance().printRightToLeft(SystemCache::getBuffer(), wordLength, col, row)
        : LCDManager::getInstance().print(SystemCache::getBuffer(), col, row);
}

void Blinker::update()
{
    if (isBlinking && blinkTimer.timeout())
    {
        if (blinkState)
        {
            // Clear the word
            clearWord();
        }
        else
        {
            // Print the word
            printWord();
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}
