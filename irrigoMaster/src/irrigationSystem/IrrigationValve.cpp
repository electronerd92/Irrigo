#include "IrrigationValve.h"

IrrigationValve::IrrigationValve(uint8_t pinNumber) : pin(pinNumber), mode(ValveMode::OFF), startTime{0, 0}, frequency(12), period(1)
{
    pinMode(pin, OUTPUT); // Initialize the pin as an OUTPUT
    close();              // Ensure the valve is closed initially
}

void IrrigationValve::open()
{
    digitalWrite(pin, HIGH); // Command to open the valve
}

void IrrigationValve::close()
{
    digitalWrite(pin, LOW); // Command to close the valve
}

IrrigationValve &IrrigationValve::operator=(const IrrigationValve &other)
{
    if (this != &other)
    {
        // Free existing resources
        mode = other.mode;
        startTime = other.startTime;
        frequency = other.frequency;
        period = other.period;
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

void IrrigationValve::setStartTime(Time_HHMM startTime)
{
    this->startTime = startTime;
}

void IrrigationValve::increaseStartTimeHour()
{
    startTime.hour = (startTime.hour + 1) % 24;
}

void IrrigationValve::decreaseStartTimeHour()
{
    startTime.hour = (startTime.hour == 0) ? 23 : startTime.hour - 1;
}

void IrrigationValve::increaseStartTimeMinute()
{
    startTime.minute = (startTime.minute + 1) % 60;
}

void IrrigationValve::decreaseStartTimeMinute()
{
    startTime.minute = (startTime.minute == 0) ? 59 : startTime.minute - 1;
}

uint8_t IrrigationValve::getFrequency() const
{
    return frequency;
}

void IrrigationValve::setFrequency(uint8_t frequency)
{
    this->frequency = frequency;
}

void IrrigationValve::increaseFrequency(void)
{
    frequency += 12;
}

void IrrigationValve::decreaseFrequency(void)
{
    if (frequency > 12)
        frequency -= 12;
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
