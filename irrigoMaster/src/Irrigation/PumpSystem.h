#ifndef PUMP_SYSTEM_H
#define PUMP_SYSTEM_H

#include <Arduino.h>
#include "../ProjectConfig.h"
#include "Timer.hpp"

class PumpSystem
{
private:
    static const uint8_t pumpRelayPin = PIN_RELAY_PUMP;
    static const uint8_t pumpValvePin = PIN_VALVE_PUMP;
    static const uint8_t tankEmptyPin = PIN_TANK_EMPTY;
    static const uint8_t tankFullPin = PIN_TANK_FULL;
    bool isStopping;
    Timer stoppingTimer;

    bool isWatering();

public:
    PumpSystem();
    void update();
    void start();
    bool stop(bool force = false);
    bool isAvailable();

    bool tankIsEmpty();
    bool tankIsFull();
};

#endif // PUMP_SYSTEM_H