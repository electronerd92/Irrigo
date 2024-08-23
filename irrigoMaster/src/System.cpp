#include "System.h"
#include <EEPROM.h>
#include <avr/wdt.h>
#include "ProjectConfig.h"
#include "irrigationSystem/IrrigationSystem.h"

// Initialize the static member
System *System::instance = nullptr;

System::System()
{
    rtc.begin();
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
    for (uint8_t i = 0; i < irrigationSystem.getValveNumber(); i++)
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
    for (uint8_t i = 0; i < irrigationSystem.getValveNumber(); i++)
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