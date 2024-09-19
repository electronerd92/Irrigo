#include "Pump.h"
#include "../ProjectConfig.h"

Pump::Pump(uint8_t pumpPin, uint8_t pumpValvePin) : pumpPin(pumpPin),
                                                    pumpValvePin(pumpValvePin),
                                                    stopTimer(DELAY_OPENING_CLOSING_VALVE),
                                                    stopping(false)
{
    pinMode(pumpPin, OUTPUT);
    pinMode(pumpValvePin, OUTPUT);
}

void Pump::start()
{
    digitalWrite(pumpValvePin, HIGH);
    digitalWrite(pumpPin, HIGH);
}

void Pump::stop()
{
    // Initiate stopping process
    digitalWrite(pumpPin, LOW);
    stopTimer.start(); // Start non-blocking timer
    stopping = true;
}

void Pump::update()
{
    if (stopping && stopTimer.timeout())
    {
        digitalWrite(pumpValvePin, LOW); // Close valve after the delay
        stopping = false;                // Reset stopping flag
    }
}

bool Pump::isOff()
{
    return (digitalRead(pumpPin) == LOW && digitalRead(pumpValvePin) == LOW);
}