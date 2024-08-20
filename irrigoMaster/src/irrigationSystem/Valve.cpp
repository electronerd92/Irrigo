#include "Valve.h"

Valve::Valve() : mode(ValveMode::OFF), startTime{0, 0}, frequency(12), duration(1)
{
    // Default constructor with initial values
}

Valve &Valve::operator=(const Valve &other)
{
    if (this != &other)
    {
        // Free existing resources
        mode = other.mode;
        startTime = other.startTime;
        frequency = other.frequency;
        duration = other.duration;
    }
    return *this;
}

ValveMode Valve::getMode() const
{
    return mode;
}
void Valve::setMode(ValveMode md)
{
    mode = md;
}

StartTime Valve::getStartTime() const
{
    return startTime;
}

void Valve::setStartTime(StartTime startTime)
{
    this->startTime = startTime;
}

uint8_t Valve::getFrequency() const
{
    return frequency;
}

void Valve::setFrequency(uint8_t frequency)
{
    if (isValidFrequency(frequency))
    {
        this->frequency = frequency;
    }
}

uint8_t Valve::getDuration() const
{
    return duration;
}

void Valve::setDuration(uint8_t duration)
{
    if (isValidDuration(duration))
    {
        this->duration = duration;
    }
}

bool Valve::isValidFrequency(uint8_t frequency) const
{
    // Frequency must be positive and a multiple of 12
    return frequency > 0 && frequency % 12 == 0;
}

bool Valve::isValidDuration(uint8_t duration) const
{
    // Duration must be positive
    return duration > 0;
}