#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Arduino.h>
#include "RTClib.h"

// Forward declaration to avoid circular dependency
class IOSystem;

class MainSystem
{
private:
    RTC_DS3231 rtc;
    IOSystem *ioSystem;

public:
    MainSystem();
    void update();
};

#endif // MAIN_SYSTEM_H