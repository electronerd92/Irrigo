#include "Tank.h"

Tank::Tank(uint8_t emptyPin, uint8_t fullPin) : emptyWLSensorPin(emptyPin), fullWLSensorPin(fullPin)
{
    pinMode(emptyPin, INPUT_PULLUP);
    pinMode(fullPin, INPUT_PULLUP);
}

bool Tank::isEmpty()
{
    return !digitalRead(emptyWLSensorPin);
}

bool Tank::isFull()
{
    return !digitalRead(fullWLSensorPin);
}
