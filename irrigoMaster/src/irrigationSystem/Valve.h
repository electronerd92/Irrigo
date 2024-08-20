#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>

// #region ValveMode

enum ValveMode : byte
{
    OFF,
    CLASSIC,
    SMART
};

static inline const __FlashStringHelper *valveModeToString(ValveMode mode)
{
    switch (mode)
    {
    case OFF:
        return F("OFF");
    case CLASSIC:
        return F("CLASSIC");
    case SMART:
        return F("SMART");
    default:
        return F(""); // Handle unexpected values
    }
}

static inline uint8_t valveModeStringLength(ValveMode mode)
{
    switch (mode)
    {
    case OFF:
        return 3; // Length of "OFF"
    case CLASSIC:
        return 7; // Length of "CLASSIC"
    case SMART:
        return 5; // Length of "SMART"
    default:
        return 0; // Default length (could be adjusted or used for error handling)
    }
}

// #endregion

struct Time
{
    uint8_t hour;
    uint8_t minute;
};

class Valve
{
private:
    ValveMode mode;

    uint8_t frequency; // Frequency in hours
    uint8_t duration;  // Duration in minutes

public:
    Valve();
    // Assuming some methods for Valve class
    void open();
    void close();
    Valve &operator=(const Valve &other); // Copy assignment operator

    ValveMode getMode() const;
    void setMode(ValveMode md);

    Time getStartTime() const;
    void setStartTime(Time startTime);

    uint8_t getFrequency() const;
    void setFrequency(uint8_t frequency);

    uint8_t getDuration() const;
    void setDuration(uint8_t duration);
};

#endif // VALVE_H