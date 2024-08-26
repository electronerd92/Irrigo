#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "RTClib.h"

class System
{
private:
    static System *instance; // Singleton instance
    RTC_DS3231 rtc;
    uint8_t lastCheckedDay;
    bool dstApplied;
    // Private constructor to prevent instantiation
    System();

    void updateDST();
    bool isDST(DateTime now);
    uint8_t getLastSunday(uint8_t month, uint16_t year);
    uint8_t daysInMonth(uint16_t year, uint8_t month);

public:
    // Deleted copy constructor and assignment operator
    System(const System &) = delete;
    System &operator=(const System &) = delete;

    // Method to get the singleton instance
    static System &getInstance();

    void update();

    uint32_t getUnixTime();
    void setUnixTime(uint32_t unixTime);
    DateTime getCurrentDateTime();

    void increaseDay();
    void decreaseDay();
    void increaseMonth();
    void decreaseMonth();
    void increaseYear();
    void decreaseYear();
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();

    void saveToEEPROM();
    void loadFromEEPROM();
    void resetToFactorySettings();
    uint8_t calculateChecksum(uint16_t startAddr, uint16_t endAddr);
};

#endif // SYSTEM_H