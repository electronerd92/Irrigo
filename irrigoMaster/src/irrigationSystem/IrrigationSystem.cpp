#include "IrrigationSystem.h"
#include "../ProjectConfig.h"

// Initialize the static member
IrrigationSystem *IrrigationSystem::instance = nullptr;

// Private constructor
IrrigationSystem::IrrigationSystem() : valves{
                                           IrrigationValve(PIN_VALVE_1),
                                           IrrigationValve(PIN_VALVE_2),
                                           IrrigationValve(PIN_VALVE_3),
                                           IrrigationValve(PIN_VALVE_4),
                                           IrrigationValveExt(PIN_VALVE_5, PIN_VALVE_EXT),
                                           IrrigationValveExt(PIN_VALVE_6, PIN_VALVE_EXT),
                                           IrrigationValveExt(PIN_VALVE_7, PIN_VALVE_EXT),
                                           IrrigationValveExt(PIN_VALVE_8, PIN_VALVE_EXT)}
{
    pinMode(PIN_VALVE_MAIN, OUTPUT);
}

// Method to get the single instance of IrrigationSystem
IrrigationSystem &IrrigationSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new IrrigationSystem();
    }
    return *instance;
}

// Method to access the Valve objects
IrrigationValve *IrrigationSystem::getValve(uint8_t index)
{
    return &valves[index];
}

void IrrigationSystem::update()
{
    // Check if the system is activated

    if (feedWater == pump && pump.hasWater == false)
        emergencyStop();

    bool aValveIsOpen = false;

    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        if (valves[i].isOpen())
        {
            aValveIsOpen = true;
            if (valves[i].canClose())
            {
                stopWatering(valves[i]);
            }
        }
    }

    if (aValveIsOpen)
        return;

    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        if (valves[i].canOpen())
        {
            startWatering(&valves[i]);
            break;
        }
    }
}

void IrrigationSystem::startWatering(IrrigationValve *valve)
{
    valve->open();
    delay(DELAY_OPENING_CLOSING_VALVE);

    if (feedWater == pump)
    {
        pump.start();
    }

    else
    {
        digitalWrite(PIN_VALVE_MAIN, HIGH);
    }
}

void IrrigationSystem::stopWatering(IrrigationValve *valve)
{

    if (feedWater == pump)
    {
        pump.stop();
    }

    else
    {
        digitalWrite(PIN_VALVE_MAIN, LOW);
    }

    delay(DELAY_OPENING_CLOSING_VALVE);

    valve->close();
}

void IrrigationSystem::emergencyStop
{
    pump.stop();
    digitalWrite(PIN_VALVE_MAIN, LOW);
    delay(DELAY_OPENING_CLOSING_VALVE);

    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        valves[i].close();
    }
}
