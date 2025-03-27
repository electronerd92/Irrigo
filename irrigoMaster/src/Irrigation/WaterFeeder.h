#ifndef WATER_FEEDER_H
#define WATER_FEEDER_H

#include <Arduino.h>
#include "../ProjectConfig.h"
#include "PumpSystem.h"

enum class WaterFeederType : uint8_t
{
    MAIN,
    PUMP,
    COUNT
};

class WaterFeeder
{
private:
    static const uint8_t mainValvePin = PIN_VALVE_MAIN;
    WaterFeederType type;
    bool available;
    PumpSystem pumpSystem;

public:
    WaterFeeder();
    void update();
    void start();
    bool stop(bool force = false);
    bool isAvailable();
    uint16_t getLiters() { return 0; };

    WaterFeederType getType();
    void setType(WaterFeederType value);
};

#endif // WATER_FEEDER_H