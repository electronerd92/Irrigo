#include "Blinker.h"

Blinker::Blinker(LCD *lcd)
    : lcd(lcd),
      blinkTimer(LCD_BLINK_INTERVAL),
      col(0),
      row(0),
      blinkState(false),
      isBlinking(false),
      wordLength(0)
{
    buffer[0] = '\0'; // Initialize empty string
}
void Blinker::startBlinking(const char *word, uint8_t c, uint8_t r)
{
    wordLength = min(strlen(word), LCD_BLINK_BUFFER_SIZE - 1);
    strncpy(buffer, word, wordLength);
    buffer[wordLength] = '\0'; // Null-terminate
    col = c;
    row = r;
    blinkState = true;
    isBlinking = true;
    blinkTimer.start();
}

void Blinker::stopBlinking()
{
    if (!isBlinking)
        return;
    isBlinking = false;
    clearWord();
}

void Blinker::update()
{
    if (isBlinking && blinkTimer.timeout())
    {
        if (blinkState)
        {
            clearWord();
        }
        else
        {
            printWord();
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}

void Blinker::printWord()
{
    lcd->print(buffer, col, row);
}

void Blinker::clearWord()
{
    for (uint8_t c = 0; c < wordLength; c++)
    {
        lcd->clearChar(c + col, row);
    }
}
