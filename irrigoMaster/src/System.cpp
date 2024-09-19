#include "System.h"
#include <EEPROM.h>
#include "ProjectConfig.h"
#include "irrigationSystem/IrrigationSystem.h"
#include "Debug.hpp"

// Initialize the static member
System *System::instance = nullptr;

System::System()
{
    rtc.begin();
    DateTime now = rtc.now();
    lastCheckedDay = now.day(); // Initialize last checked day
    dstApplied = isDST(now);    // Check if DST should be applied now
}

System &System::getInstance()
{
    if (instance == nullptr)
    {
        instance = new System();
    }
    return *instance;
}

uint32_t System::getUnixTime()
{
    return rtc.now().unixtime();
}

void System::setUnixTime(uint32_t unixTime)
{
    rtc.adjust(DateTime(unixTime));
}

DateTime System::getCurrentDateTime()
{
    return rtc.now();
}

// Utility function to calculate the number of days in a given month
uint8_t System::daysInMonth(uint16_t year, uint8_t month)
{
    if (month == 2)
    {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

// #region RTC settings
void System::increaseDay()
{
    DateTime now = rtc.now();
    uint8_t day = now.day() + 1;
    uint8_t maxDay = daysInMonth(now.year(), now.month());

    if (day > maxDay)
    {
        day = 1;
    }

    DateTime newDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::decreaseDay()
{
    DateTime now = rtc.now();
    uint8_t day = now.day() - 1;
    uint8_t maxDay = daysInMonth(now.year(), now.month());

    if (day < 1)
    {
        day = maxDay;
    }

    DateTime newDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::increaseMonth()
{
    DateTime now = rtc.now();
    uint8_t month = (now.month() % 12) + 1;
    uint16_t year = now.year();

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day(), maxDay);

    DateTime newDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::decreaseMonth()
{
    DateTime now = rtc.now();
    uint8_t month = (now.month() + 10) % 12 + 1;
    uint16_t year = now.year();

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day(), maxDay);

    DateTime newDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::increaseYear()
{
    DateTime now = rtc.now();
    DateTime newDateTime = DateTime(now.year() + 1, now.month(), now.day(), now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::decreaseYear()
{
    DateTime now = rtc.now();
    DateTime newDateTime = DateTime(now.year() - 1, now.month(), now.day(), now.hour(), now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::increaseHour()
{
    DateTime now = rtc.now();
    uint8_t hour = (now.hour() + 1) % 24;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), hour, now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::decreaseHour()
{
    DateTime now = rtc.now();
    uint8_t hour = (now.hour() + 23) % 24;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), hour, now.minute(), now.second());
    rtc.adjust(newDateTime);
}

void System::increaseMinute()
{
    DateTime now = rtc.now();
    uint8_t minute = (now.minute() + 1) % 60;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), now.hour(), minute, 0);
    rtc.adjust(newDateTime);
}

void System::decreaseMinute()
{
    DateTime now = rtc.now();
    uint8_t minute = (now.minute() + 59) % 60;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), now.hour(), minute, 0);
    rtc.adjust(newDateTime);
}
// #endregion RTC settings

// #region Daylight Saving Time
void System::updateDST()
{
    DateTime now = rtc.now();
    bool currentlyDST = isDST(now);

    // Only adjust if there is a transition
    if (currentlyDST && !dstApplied)
    {
        rtc.adjust(DateTime(now.unixtime() + 3600)); // Add 3600 seconds (1 hour)
        dstApplied = true;                           // Mark DST as applied
    }
    else if (!currentlyDST && dstApplied)
    {
        rtc.adjust(DateTime(now.unixtime() - 3600)); // Subtract 3600 seconds (1 hour)
        dstApplied = false;                          // Mark DST as not applied
    }
}

bool System::isDST(DateTime now)
{
    uint8_t lastSundayMarch = getLastSunday(3, now.year());
    uint8_t lastSundayOctober = getLastSunday(10, now.year());

    DateTime dstStart(now.year(), 3, lastSundayMarch, 2, 0, 0);
    DateTime dstEnd(now.year(), 10, lastSundayOctober, 3, 0, 0);

    return now >= dstStart && now < dstEnd;
}

uint8_t System::getLastSunday(uint8_t month, uint16_t year)
{
    DateTime lastDayOfMonth(year, month, 31);
    uint8_t weekday = lastDayOfMonth.dayOfTheWeek();
    return 31 - weekday; // 31st minus the day of the week gives the last Sunday
}
// #endregion Daylight Saving Time

void System::saveToEEPROM()
{
    uint16_t addr = 0;

    // Save version identifier
    EEPROM.update(addr++, EEPROM_VERSION_HIGH);
    EEPROM.update(addr++, EEPROM_VERSION_LOW);

    // #region save irrigationSystem parameters
    IrrigationSystem &irrigationSystem = IrrigationSystem::getInstance();

    EEPROM.update(addr++, irrigationSystem.getUsePump());
    EEPROM.update(addr++, irrigationSystem.getIsEnabled());

    // Save each valve's parameters
    for (uint8_t i = 0; i < irrigationSystem.getValvesNumber(); i++)
    {
        IrrigationValve *valve = irrigationSystem.getValve(i);

        // Save mode
        EEPROM.update(addr++, (uint8_t)valve->getMode());

        // Save start time
        Time_HHMM startTime = valve->getStartTime();
        EEPROM.update(addr++, startTime.hour);
        EEPROM.update(addr++, startTime.minute);

        // Save frequency
        EEPROM.update(addr++, valve->getFrequency());

        // Save period
        EEPROM.update(addr++, valve->getPeriod());
    }

    // #endregion save irrigationSystem parameters

    // Calculate and save a checksum or CRC (example: simple checksum)
    uint8_t checksum = calculateChecksum(0, addr);
    EEPROM.update(addr++, checksum);
}

void System::loadFromEEPROM()
{
    uint16_t addr = 0;

    // Read and verify version identifier
    uint8_t versionHigh = EEPROM.read(addr++);
    uint8_t versionLow = EEPROM.read(addr++);

    if (versionHigh != EEPROM_VERSION_HIGH || versionLow != EEPROM_VERSION_LOW)
    {
        // Incompatible version or no data saved
        return;
    }

    // #region load irrigationSystem parameters
    IrrigationSystem &irrigationSystem = IrrigationSystem::getInstance();

    bool usePump = EEPROM.read(addr++);
    bool isEnabled = EEPROM.read(addr++);
    irrigationSystem.setUsePump(usePump);
    irrigationSystem.setIsEnabled(isEnabled);

    // Load valve parameters
    for (uint8_t i = 0; i < irrigationSystem.getValvesNumber(); i++)
    {
        IrrigationValve *valve = irrigationSystem.getValve(i);

        valve->setMode((ValveMode)EEPROM.read(addr++));
        Time_HHMM startTime;
        startTime.hour = EEPROM.read(addr++);
        startTime.minute = EEPROM.read(addr++);
        valve->setStartTime(startTime);
        valve->setFrequency(EEPROM.read(addr++));
        valve->setPeriod(EEPROM.read(addr++));
    }

    // #endregion load irrigationSystem parameters

    // Verify checksum
    uint8_t storedChecksum = EEPROM.read(addr++);
    uint8_t calculatedChecksum = calculateChecksum(0, addr - 1);

    if (storedChecksum != calculatedChecksum)
    {
        resetToFactorySettings();
        return;
    }
}

// Simple checksum calculation
uint8_t System::calculateChecksum(uint16_t startAddr, uint16_t endAddr)
{
    uint8_t sum = 0;
    for (uint16_t i = startAddr; i < endAddr; i++)
    {
        sum += EEPROM.read(i);
    }
    return sum;
}

void System::resetToFactorySettings()
{
    EEPROM.update(0, 0); // Set the version/flag byte to 0x00
    EEPROM.update(1, 0); // Set the version/flag byte to 0x00
    // software reset
    asm volatile("  jmp 0"); // Jump to the start of the program (address 0)
}

void System::update()
{
    DateTime now = rtc.now();

    if (now.day() != lastCheckedDay)
    {
        // Run this check only once per day
        lastCheckedDay = now.day(); // Update the last checked day
        updateDST();                // Check and apply or remove DST if necessary
    }
}
