#include "IrrigationValve.h"
#include "Debug.hpp"

IrrigationValve::IrrigationValve(uint8_t id, uint8_t pinNumber)
    : id(id),
      pin(pinNumber),
      mode(ValveMode::OFF),
      startTime{0, 0},
      frequency(12),
      period(1),
      timer((uint32_t)(period) * 60000)
{
    pinMode(pin, OUTPUT); // Initialize the pin as an OUTPUT
    close();              // Ensure the valve is closed initially
    calculateNextIrrigationTime();
}

uint8_t IrrigationValve::getID() const
{
    return id;
}

DateTime IrrigationValve::getNextIrrigationTime()
{
    return DateTime(nextIrrigationTime);
}

void IrrigationValve::open()
{
    timer.updateInterval((uint32_t)(period) * 60000);
    digitalWrite(pin, HIGH); // Command to open the valve
}

bool IrrigationValve::isOpen()
{
    return digitalRead(pin);
}

void IrrigationValve::close()
{
    digitalWrite(pin, LOW); // Command to close the valve
}

void IrrigationValve::calculateNextIrrigationTime()
{
    DateTime now = System::getInstance().getCurrentDateTime();
    DateTime startDateTime(now.year(), now.month(), now.day(), startTime.hour, startTime.minute, 0);
    nextIrrigationTime = startDateTime.unixtime();

    while (nextIrrigationTime <= now.unixtime())
    {
        nextIrrigationTime += (uint32_t)(frequency) * 3600;
    }
}

bool IrrigationValve::canOpen()
{
    if (mode == ValveMode::OFF)
        return false;

    uint32_t currentTime = System::getInstance().getUnixTime();
    if (currentTime >= nextIrrigationTime)
    {
        nextIrrigationTime += (uint32_t)(frequency) * 3600;
        return true;
    }

    return false;
}

bool IrrigationValve::canClose()
{
    return timer.timeout();
}

IrrigationValve &IrrigationValve::operator=(const IrrigationValve &other)
{
    if (this != &other)
    {
        id = other.id;
        mode = other.mode;
        startTime = other.startTime;
        frequency = other.frequency;
        period = other.period;
        nextIrrigationTime = other.nextIrrigationTime;
    }
    return *this;
}

ValveMode IrrigationValve::getMode() const
{
    return mode;
}
void IrrigationValve::setMode(ValveMode md)
{
    mode = md;
}

Time_HHMM IrrigationValve::getStartTime() const
{
    return startTime;
}

void IrrigationValve::updateStartTime()
{
    calculateNextIrrigationTime();
}

void IrrigationValve::setStartTime(Time_HHMM startTime)
{
    this->startTime = startTime;
    updateStartTime();
}

void IrrigationValve::increaseStartTimeHour()
{
    Time_HHMM newTime = startTime;
    newTime.hour = (startTime.hour + 1) % 24;
    setStartTime(newTime);
}

void IrrigationValve::decreaseStartTimeHour()
{
    Time_HHMM newTime = startTime;
    newTime.hour = (startTime.hour == 0) ? 23 : startTime.hour - 1;
    setStartTime(newTime);
}

void IrrigationValve::increaseStartTimeMinute()
{
    Time_HHMM newTime = startTime;
    newTime.minute = (startTime.minute + 1) % 60;
    setStartTime(newTime);
}

void IrrigationValve::decreaseStartTimeMinute()
{
    Time_HHMM newTime = startTime;
    newTime.minute = (startTime.minute == 0) ? 59 : startTime.minute - 1;
    setStartTime(newTime);
}

uint8_t IrrigationValve::getFrequency() const
{
    return frequency;
}

void IrrigationValve::setFrequency(uint8_t frequency)
{
    this->frequency = frequency;
    updateStartTime();
}

void IrrigationValve::increaseFrequency(void)
{
    setFrequency(frequency + 12);
}

void IrrigationValve::decreaseFrequency(void)
{
    if (frequency > 12)
        setFrequency(frequency - 12);
}

uint8_t IrrigationValve::getPeriod() const
{
    return period;
}

void IrrigationValve::setPeriod(uint8_t period)
{
    this->period = period;
}

void IrrigationValve::increasePeriod()
{
    period++;
}
void IrrigationValve::decreasePeriod()
{
    if (period > 1)
        period--;
}
