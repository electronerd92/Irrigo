#include "Blinker.h"
#include "LCDManager.h"

Blinker::Blinker()
    : blinkTimer(LCD_BLINK_INTERVAL),
      blinkWord(new char[LCD_BLINK_BUFFER_SIZE]),
      col(0),
      row(0),
      wordLength(0),
      blinkState(true),
      isBlinking(false),
      rightToLeft(false)
{
}

void Blinker::stopBlinking()
{
    if (!isBlinking)
        return;
    isBlinking = false;
    // Clear the word if it was blinking
    if (blinkState)
    {
        clearWord();
    }
}

void Blinker::clearWord()
{
    for (uint8_t i = 0; i < wordLength; ++i)
    {
        rightToLeft ? LCDManager::getInstance().clearRightToLeft(col + i, row) : LCDManager::getInstance().clear(col + i, row);
    }
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
            rightToLeft ? LCDManager::getInstance().printRightToLeft(blinkWord, wordLength, col, row) : LCDManager::getInstance().print(blinkWord, col, row);
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}
