#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Arduino.h>
#include "RTClib.h"

// Forward declaration to avoid circular dependency
class IOSystem;
class IrrigationSystem;

class MainSystem
{
private:
    RTC_DS3231 rtc;
    IOSystem *ioSystem;
    IrrigationSystem *irrigationSystem;

public:
    MainSystem();
    void update();

    // getters
    IrrigationSystem *getIrrigationSystem();

    uint32_t getUnixTime();
};

#endif // MAIN_SYSTEM_H