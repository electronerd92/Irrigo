#ifndef IRRIGATION_SYSTEM_H
#define IRRIGATION_SYSTEM_H

#include <Arduino.h>
#include "../MainSystem.h"
#include "Valve.h"

class IrrigationSystem
{
private:
    const MainSystem *mainSystem;
    static const uint8_t VALVES_NUMBER = 8;
    Valve valves[VALVES_NUMBER]; // Array of 8 Valve objects
    uint8_t valveIndex;

public:
    IrrigationSystem(MainSystem *mainSystem);

    uint8_t getValveIndex();
    void setValveIndex(uint8_t value);

    ValveMode getValveMode();
    void setValveMode(ValveMode value);

    Time_HHMM getValveStartTime();
    void setValveStartTimeHour(uint8_t value);
    void setValveStartTimeMinute(uint8_t value);

    uint8_t getValveFrequency();
    void setValveFrequency(uint8_t value);

    uint8_t getValveDuration();
    void setValveDuration(uint8_t value);
};

#endif // IRRIGATION_SYSTEM_H