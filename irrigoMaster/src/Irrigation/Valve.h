#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>
#include "CustomTypes.h"

enum class ValveMode : byte
{
    OFF,
    TIMER,
    COUNT
};

class Valve
{
private:
    const uint8_t pin;
    ValveMode mode;
    Time_HHMM startTime;
    uint8_t frequency; // Frequency in hours
    uint8_t duration;    // Duration in minutes

public:
    Valve(uint8_t p);

    ValveMode getMode();
    void setMode(ValveMode value);

    Time_HHMM getStartTime();
    void setStartTime(Time_HHMM value);

    uint8_t getFrequency();
    void setFrequency(uint8_t value);

    uint8_t getDuration();
    void setDuration(uint8_t value);
};

#endif // VALVE_H