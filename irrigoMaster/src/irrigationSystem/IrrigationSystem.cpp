#include "IrrigationSystem.h"
#include "../ProjectConfig.h"

// Initialize the static member
IrrigationSystem *IrrigationSystem::instance = nullptr;

// Private constructor
IrrigationSystem::IrrigationSystem() : valves{
                                           IrrigationValve(ID_VALVE_1, PIN_VALVE_1),
                                           IrrigationValve(ID_VALVE_2, PIN_VALVE_2),
                                           IrrigationValve(ID_VALVE_3, PIN_VALVE_3),
                                           IrrigationValve(ID_VALVE_4, PIN_VALVE_4),
                                           IrrigationValveExt(ID_VALVE_5, PIN_VALVE_5, PIN_VALVE_EXT),
                                           IrrigationValveExt(ID_VALVE_6, PIN_VALVE_6, PIN_VALVE_EXT),
                                           IrrigationValveExt(ID_VALVE_7, PIN_VALVE_7, PIN_VALVE_EXT),
                                           IrrigationValveExt(ID_VALVE_8, PIN_VALVE_8, PIN_VALVE_EXT)},
                                       pump(PIN_PUMP, PIN_VALVE_PUMP),    // setup pump
                                       tank(PIN_WLS_EMPTY, PIN_WLS_FULL), // setup tank
                                       usePump(false),                    // Default to using main feed
                                       isEnabled(false)                   // Default status
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

uint8_t IrrigationSystem::getValveNumber() const
{
    return VALVES_NUMBER;
}

// Method to access the Valve objects
IrrigationValve *IrrigationSystem::getValve(uint8_t index)
{
    return &valves[index];
}

bool IrrigationSystem::getUsePump()
{
    return usePump;
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

    if (usePump && tank.isEmpty())
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

bool IrrigationSystem::getIsEnabled()
{
    return isEnabled;
}

void IrrigationSystem::setIsEnabled(bool value)
{
    value ? enableSystem() : disableSystem();
}

void IrrigationSystem::enableSystem()
{
    isEnabled = true;
    for (uint8_t i = 0; i < VALVES_NUMBER; i++)
    {
        valves[i].updateStartTime();
    }
}

void IrrigationSystem::disableSystem()
{
    isEnabled = false;
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
