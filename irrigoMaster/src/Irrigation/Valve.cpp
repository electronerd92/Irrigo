#include "Valve.h"

Valve::Valve(uint8_t p)
    : pin(p),
      mode(ValveMode::OFF),
      startTime{0, 0},
      frequency(12),
      duration(1)
{
}

ValveMode Valve::getMode()
{
    return mode;
}

void Valve::setMode(ValveMode value)
{
    mode = value;
}

Time_HHMM Valve::getStartTime()
{
    return startTime;
}

void Valve::setStartTime(Time_HHMM value)
{
    startTime = value;
}

uint8_t Valve::getFrequency()
{
    return frequency;
}

void Valve::setFrequency(uint8_t value)
{
    frequency = value;
}

uint8_t Valve::getDuration()
{
    return duration;
}

void Valve::setDuration(uint8_t value)
{
    duration = value;
}