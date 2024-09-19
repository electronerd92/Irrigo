#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include "Timer.hpp"

class Pump
{
private:
    const uint8_t pumpPin;
    const uint8_t pumpValvePin;
    Timer stopTimer; // Timer for non-blocking delay
    bool stopping;   // Flag to track if the pump is stopping

public:
    Pump(uint8_t pumpPin, uint8_t pumpValvePin);

    void start();
    void stop();
    void update();
    bool isOff();
};

#endif // PUMP_H