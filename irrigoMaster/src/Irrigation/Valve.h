#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>
#include "CustomTypes.h"
#include "Timer.hpp"
#include "../ProjectConfig.h"

enum class ValveMode : byte
{
    OFF,
    TIMER,
    COUNT // used to get the number of ValveMode by Menu
};

class Valve
{
private:
    static const uint8_t exteriorValvePin = PIN_VALVE_EXT;
    const uint8_t pin;
    bool isExterior;
    ValveMode mode;
    Time_HHMM startTime;
    uint8_t frequency; // Frequency in h
    uint8_t duration;  // Duration in min
    uint32_t openingTime;
    bool isOpeningTimeUpdated;
    Timer durationTimer;
    bool isClosing;
    Timer closingTimer;

    void turnOnOff(uint8_t onOff);
    void updateOpeningTime(uint32_t currentTime);

public:
    Valve(uint8_t p, bool isExt);
    bool close(bool force = false);
    void open();
    bool isOpen();

    bool canOpen(uint32_t currentTime);
    bool canClose(uint16_t feededLiters);

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