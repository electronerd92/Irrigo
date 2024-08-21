#include "Pump.h"
#include "../ProjectConfig.h"

Pump::Pump(uint8_t pumpPin, uint8_t pumpValvePin) : pumpPin(pumpPin), pumpValvePin(pumpValvePin)
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
    digitalWrite(pumpPin, LOW);
    delay(DELAY_OPENING_CLOSING_VALVE);
    digitalWrite(pumpValvePin, LOW);
}