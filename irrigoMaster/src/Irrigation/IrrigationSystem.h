#ifndef IRRIGATION_SYSTEM_H
#define IRRIGATION_SYSTEM_H

#include <Arduino.h>
#include "../MainSystem.h"
#include "Valve.h"
#include "WaterFeeder.h"

class IrrigationSystem
{
private:
    MainSystem *mainSystem;
    static const uint8_t valveNumber = 8;
    Valve valves[valveNumber]; // Array of 8 Valve objects
    uint8_t valveIndex;
    uint8_t mode;
    WaterFeeder waterFeeder;

public:
    IrrigationSystem(MainSystem *mainSystem);

    void update();
    void EmergencyCloseAll();

    uint8_t getMode();
    void setMode(uint8_t value);

    WaterFeederType getWaterFeederType();
    void setWaterFeederType(WaterFeederType value);

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