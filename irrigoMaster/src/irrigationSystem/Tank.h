#ifndef TANK_H
#define TANK_H

#include <Arduino.h>

class Tank
{
private:
    const uint8_t emptyWLSensorPin; // Water Level Sensor
    const uint8_t fullWLSensorPin;

public:
    Tank(uint8_t emptyPin, uint8_t fullPin);

    bool isEmpty();
    bool isFull();
};

#endif // TANK_H