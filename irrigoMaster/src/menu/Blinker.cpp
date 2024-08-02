#include "Blinker.h"
#include "LCDManager.h"

Blinker::Blinker(const uint32_t blinkInterval)
    : blinkTimer(blinkInterval),
      blinkWord(nullptr),
      col(0),
      row(0),
      wordLength(0),
      blinkState(true),
      isBlinking(false),
      rightToLeft(false)
{
}

void Blinker::startBlinking(const __FlashStringHelper *blinkWord, uint8_t col, uint8_t row, bool rightToLeft)
{
    this->blinkWord = blinkWord;
    this->col = col;
    this->row = row;
    this->wordLength = strlen_P(reinterpret_cast<const char *>(blinkWord));
    this->isBlinking = true;
    this->blinkState = true;
    this->rightToLeft = rightToLeft;
    this->blinkTimer.start();
}

void Blinker::stopBlinking()
{
    if (!isBlinking)
        return;
    isBlinking = false;
    // Ensure the word is printed when stopping
    LCDManager::getInstance().print(blinkWord, col, row, rightToLeft);
}

void Blinker::update()
{
    if (isBlinking && blinkTimer.timeout())
    {
        if (blinkState)
        {
            // Clear the word
            for (uint8_t i = 0; i < wordLength; ++i)
            {
                if (rightToLeft)
                {
                    LCDManager::getInstance().clear(col - i, row);
                }
                else
                {
                    LCDManager::getInstance().clear(col + i, row);
                }
            }
        }
        else
        {
            // Print the word
            LCDManager::getInstance().print(blinkWord, col, row, rightToLeft);
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}
