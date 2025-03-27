#include "Valve.h"
#include "RTClib.h"
#include "Debug.hpp"

Valve::Valve(uint8_t p, bool isExt)
    : pin(p),
      isExterior(isExt),
      mode(ValveMode::OFF),
      startTime{0, 0},
      frequency(12), // 12 h
      duration(1),   // 1 min
      openingTime(0),
      isOpeningTimeUpdated(false),
      durationTimer((uint32_t)(duration)*MIN_TO_MS),
      isClosing(false),
      closingTimer(DELAY_OPENING_CLOSING_VALVE)
{
    pinMode(pin, OUTPUT);
    close(true);
}

void Valve::open()
{
    durationTimer.updateInterval((uint32_t)(duration)*MIN_TO_MS);
    turnOnOff(ON);
}

bool Valve::isOpen()
{
    return digitalRead(pin) == ON;
}

bool Valve::close(bool force)
{
    if (force)
    {
        delay(DELAY_OPENING_CLOSING_VALVE);
        turnOnOff(OFF);
        isClosing = false;
        return true;
    }

    if (isClosing == false)
    {
        isClosing = true;
        closingTimer.start();
        return false;
    }

    if (closingTimer.timeout())
    {
        isClosing = false;
        turnOnOff(OFF);
        return true;
    }

    return false;
}

bool Valve::canOpen(uint32_t currentTime)
{
    if (mode == ValveMode::TIMER)
    {
        if (!isOpeningTimeUpdated)
        {
            updateOpeningTime(currentTime);
        }
        if (currentTime >= openingTime)
        {
            openingTime += (uint32_t)(frequency) * 3600;
            return true;
        }
    }
    return false;
}

bool Valve::canClose(uint16_t feededLiters)
{
    return durationTimer.timeout();
}

// #region helper functions

void Valve::turnOnOff(uint8_t onOff)
{
    if (onOff == ON)
    {
        digitalWrite(pin, ON);
        if (isExterior)
        {
            digitalWrite(exteriorValvePin, ON);
        }
    }
    else
    {
        if (isExterior)
        {
            digitalWrite(exteriorValvePin, OFF);
        }
        digitalWrite(pin, OFF);
    }
}

void Valve::updateOpeningTime(uint32_t currentTime)
{
    DateTime now(currentTime);
    DateTime startDateTime(now.year(), now.month(), now.day(), startTime.hour, startTime.minute, 0);
    openingTime = startDateTime.unixtime();
    while (openingTime <= now.unixtime())
    {
        openingTime += (uint32_t)(frequency) * 3600;
    }
    isOpeningTimeUpdated = true;
}

// #endregion

// #region getter/setter parameters

ValveMode Valve::getMode()
{
    return mode;
}

void Valve::setMode(ValveMode value)
{
    mode = value;
    isOpeningTimeUpdated = false;
}

Time_HHMM Valve::getStartTime()
{
    return startTime;
}

void Valve::setStartTime(Time_HHMM value)
{
    startTime = value;
    isOpeningTimeUpdated = false;
}

uint8_t Valve::getFrequency()
{
    return frequency;
}

void Valve::setFrequency(uint8_t value)
{
    frequency = value;
    isOpeningTimeUpdated = false;
}

uint8_t Valve::getDuration()
{
    return duration;
}

void Valve::setDuration(uint8_t value)
{
    duration = value;
}

// #endregion
