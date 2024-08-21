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
                                           IrrigationValveExt(PIN_VALVE_8, PIN_VALVE_EXT)},
                                       pump(PIN_PUMP, PIN_VALVE_PUMP), // setup pump
                                       usePump(false),                 // Default to using main feed
                                       isEnabled(false)                // Default status
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

// Set whether to use the pump or main feed
void IrrigationSystem::setUsePump(bool value)
{
    usePump = value;
}

void IrrigationSystem::update()
{
    // Check if the system is enabled
    if (!isEnabled)
    {
        return;
    }

    if (usePump /*&& !tank.hasWater()*/)
    {
        disableSystem();
    }

    bool aValveIsOpen = false;

    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        if (valves[i].isOpen())
        {
            aValveIsOpen = true;
            if (valves[i].canClose())
            {
                stopWatering(&valves[i]);
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
    usePump ? pump.start() : turnMainValveOn();
}

void IrrigationSystem::stopWatering(IrrigationValve *valve)
{
    usePump ? pump.stop() : turnMainValveOff();
    delay(DELAY_OPENING_CLOSING_VALVE);
    valve->close();
}

void IrrigationSystem::disableSystem()
{
    pump.stop();
    turnMainValveOff();
    delay(DELAY_OPENING_CLOSING_VALVE);

    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        valves[i].close();
    }
}

void IrrigationSystem::turnMainValveOn()
{
    digitalWrite(PIN_VALVE_MAIN, HIGH);
}

void IrrigationSystem::turnMainValveOff()
{
    digitalWrite(PIN_VALVE_MAIN, LOW);
}
