#ifndef IRRIGATIONVALVE_H
#define IRRIGATIONVALVE_H

#include <Arduino.h>
#include "CustomTypes.h"
#include "Timer.hpp"
#include "../System.h"

// #region ValveMode

enum class ValveMode : uint8_t
{
    OFF,
    CLASSIC,
    SMART,
    COUNT
};

static inline const __FlashStringHelper *valveModeToString(ValveMode mode)
{
    switch (mode)
    {
    case ValveMode::OFF:
        return F("OFF");
    case ValveMode::CLASSIC:
        return F("CLASSIC");
    case ValveMode::SMART:
        return F("SMART");
    default:
        return F(""); // Handle unexpected values
    }
}

static inline uint8_t valveModeStringLength(ValveMode mode)
{
    switch (mode)
    {
    case ValveMode::OFF:
        return 3; // Length of "OFF"
    case ValveMode::CLASSIC:
        return 7; // Length of "CLASSIC"
    case ValveMode::SMART:
        return 5; // Length of "SMART"
    default:
        return 0; // Default length (could be adjusted or used for error handling)
    }
}

// #endregion

class IrrigationValve
{
protected:
    uint8_t id;
    const uint8_t pin; // Pin number for controlling the relay

private:
    ValveMode mode;
    Time_HHMM startTime;
    uint8_t frequency; // Frequency in hours
    uint8_t period;    // Duration in minutes
    uint32_t nextIrrigationTime;
    Timer timer;

    void calculateNextIrrigationTime();

public:
    IrrigationValve(uint8_t id, uint8_t pinNumber);
    IrrigationValve &operator=(const IrrigationValve &other); // Copy assignment operator
    uint8_t getID() const;
    DateTime getNextIrrigationTime();
    virtual void open();
    virtual void close();

    bool isOpen();
    bool canOpen();
    bool canClose();

    ValveMode getMode() const;
    void setMode(ValveMode md);

    Time_HHMM getStartTime() const;
    void updateStartTime();
    void setStartTime(Time_HHMM startTime);
    void increaseStartTimeHour();
    void decreaseStartTimeHour();
    void increaseStartTimeMinute();
    void decreaseStartTimeMinute();

    // Frequency min 12h, and step of 12h
    uint8_t getFrequency() const;
    void setFrequency(uint8_t frequency);
    void increaseFrequency();
    void decreaseFrequency();

    uint8_t getPeriod() const;
    void setPeriod(uint8_t period);
    void increasePeriod();
    void decreasePeriod();
};

// Extended class with two pins
class IrrigationValveExt : public IrrigationValve
{
private:
    const uint8_t commonPin; // Second pin for extended valve

public:
    IrrigationValveExt(uint8_t id, uint8_t pinNumber, uint8_t commonPinNumber)
        : IrrigationValve(id, pinNumber), commonPin(commonPinNumber)
    {
        pinMode(commonPin, OUTPUT);
        close();
    }

    // Override the open and close methods
    void open() override
    {
        IrrigationValve::open();       // Close valve
        digitalWrite(commonPin, HIGH); // Open first common valve
    }

    void close() override
    {
        digitalWrite(commonPin, LOW); // Close first common valve
        IrrigationValve::close();     // Close valve
    }
};

#endif // IRRIGATIONVALVE_H