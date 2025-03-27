#include "IrrigationSystem.h"
#include "../ProjectConfig.h"
#include "CustomTypes.h"

IrrigationSystem::IrrigationSystem(MainSystem *mainSystem)
    : mainSystem(mainSystem),
      valves{
          Valve(PIN_VALVE_1, false),
          Valve(PIN_VALVE_2, false),
          Valve(PIN_VALVE_3, false),
          Valve(PIN_VALVE_4, false),
          Valve(PIN_VALVE_5, true),
          Valve(PIN_VALVE_6, true),
          Valve(PIN_VALVE_7, true),
          Valve(PIN_VALVE_8, true)},
      valveIndex(0),
      mode(OFF),
      waterFeeder()

{
}

void IrrigationSystem::update()
{
    /* - vedo se sono in mode on/off
     *  - se in mode off allora passo
     *  - se in mode on :
     *   *  itero sulle valvole
     *   *  se un  valvola è open vedo se deve essere chiusa, in caso negativo allora return
     *   *  se nessuna valvola è open allora chido alla valvola se è pronta per irrigare
     *   *  se pronta lancio l'irrigazione con waterFeeder
     */

    waterFeeder.update();

    if (mode == OFF)
        return;

    bool aValveIsOpen = false;
    for (size_t i = 0; i < valveNumber; i++)
    {
        if (valves[i].isOpen())
        {
            aValveIsOpen = true;

            if (valves[i].canClose(waterFeeder.getLiters()) && waterFeeder.stop()) // waterFeeder not blocking close
            {
                valves[i].close(); // not blcoking close take some time, must be called all the time until isOpen==false
            }
        }
    }

    if (aValveIsOpen)
        return;

    for (size_t i = 0; i < valveNumber; i++)
    {
        if (valves[i].canOpen(mainSystem->getUnixTime()) && waterFeeder.isAvailable())
        {
            valves[i].open();
            waterFeeder.start();
            break;
        }
    }
}

void IrrigationSystem::EmergencyCloseAll()
{
    if (!waterFeeder.isAvailable())
    {
        waterFeeder.stop(true); // force blocking stop
    }
    for (size_t i = 0; i < valveNumber; i++)
    {
        if (valves[i].isOpen())
        {
            valves[i].close(true); // force blocking close
        }
    }
}

// #region getter/setter
uint8_t IrrigationSystem::getMode()
{
    return mode;
}

void IrrigationSystem::setMode(uint8_t value)
{
    mode = value;
}

WaterFeederType IrrigationSystem::getWaterFeederType()
{
    return waterFeeder.getType();
}

void IrrigationSystem::setWaterFeederType(WaterFeederType value)
{
    waterFeeder.setType(value);
}

uint8_t IrrigationSystem::getValveIndex()
{
    return valveIndex;
}

void IrrigationSystem::setValveIndex(uint8_t value)
{
    if (value < valveNumber)
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

// #endregion
