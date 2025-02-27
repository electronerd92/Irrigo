#include "IrrigationSystem.h"
#include "../ProjectConfig.h"
#include "CustomTypes.h"

IrrigationSystem::IrrigationSystem(MainSystem *mainSystem)
    : mainSystem(mainSystem),
      valves{
          Valve(PIN_VALVE_1),
          Valve(PIN_VALVE_2),
          Valve(PIN_VALVE_3),
          Valve(PIN_VALVE_4),
          Valve(PIN_VALVE_5),
          Valve(PIN_VALVE_6),
          Valve(PIN_VALVE_7),
          Valve(PIN_VALVE_8)},
      valveIndex(0)

{
}

uint8_t IrrigationSystem::getValveIndex()
{
    return valveIndex;
}

void IrrigationSystem::setValveIndex(uint8_t value)
{
    if (value < VALVES_NUMBER)
    {
        valveIndex = value;
    }
}

ValveMode IrrigationSystem::getValveMode()
{
    return valves[valveIndex].getMode();
}

void IrrigationSystem::setValveMode(ValveMode value)
{
    valves[valveIndex].setMode(value);
}

Time_HHMM IrrigationSystem::getValveStartTime()
{
    return valves[valveIndex].getStartTime();
}

void IrrigationSystem::setValveStartTimeHour(uint8_t value)
{
    if (value < 24)
    {
        Time_HHMM newStartTime = {value, valves[valveIndex].getStartTime().minute};
        valves[valveIndex].setStartTime(newStartTime);
    }
}

void IrrigationSystem::setValveStartTimeMinute(uint8_t value)
{
    if (value < 60)
    {
        Time_HHMM newStartTime = {valves[valveIndex].getStartTime().hour, value};
        valves[valveIndex].setStartTime(newStartTime);
    }
}

uint8_t IrrigationSystem::getValveFrequency()
{
    return valves[valveIndex].getFrequency();
}

void IrrigationSystem::setValveFrequency(uint8_t value)
{
    if (value > 0)
    {
        valves[valveIndex].setFrequency(value);
    }
}

uint8_t IrrigationSystem::getValveDuration()
{
    return valves[valveIndex].getDuration();
}

void IrrigationSystem::setValveDuration(uint8_t value)
{
    if (value > 0)
    {
        valves[valveIndex].setDuration(value);
    }
}