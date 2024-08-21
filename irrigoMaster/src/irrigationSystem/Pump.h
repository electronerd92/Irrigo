#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>

class Pump
{
private:
    const uint8_t pumpPin;
    const uint8_t pumpValvePin;

public:
    Pump(uint8_t pumpPin, uint8_t pumpValvePin);

    void start();
    void stop();
};

#endif // PUMP_H