#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "RTClib.h"

class System
{
private:
    static System *instance; // Singleton instance

    // Private constructor to prevent instantiation
    System();

public:
    // Deleted copy constructor and assignment operator
    System(const System &) = delete;
    System &operator=(const System &) = delete;

    // Method to get the singleton instance
    static System &getInstance();

    RTC_DS3231 rtc;

    uint32_t getUnixTime();
};

#endif // SYSTEM_H