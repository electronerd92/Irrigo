#include "Blinker.h"
#include "LCDManager.h"

Blinker::Blinker(const uint32_t blinkInterval)
    : blinkTimer(blinkInterval),
      blinkWord(nullptr),
      col(0),
      row(0),
      wordLength(0),
      blinkState(true),
      isBlinking(false)
{
}

void Blinker::startBlinking(const __FlashStringHelper *blinkWord, int8_t col, uint8_t row)
{
    this->blinkWord = blinkWord;
    this->col = col;
    this->row = row;
    this->wordLength = strlen_P(reinterpret_cast<const char *>(blinkWord));
    this->isBlinking = true;
    this->blinkState = true;
    this->blinkTimer.start();
}

void Blinker::stopBlinking()
{
    if (!isBlinking)
        return;
    isBlinking = false;
    // Ensure the word is printed when stopping
    LCDManager::getInstance().print(blinkWord, col, row);
}

void Blinker::update()
{
    if (isBlinking && blinkTimer.timeout())
    {
        if (blinkState)
        {
            // Clear the word
            for (size_t i = 0; i < wordLength; ++i)
            {
                LCDManager::getInstance().print(F(" "), col + i, row);
            }
        }
        else
        {
            // Print the word
            LCDManager::getInstance().print(blinkWord, col, row);
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}
