#include "IrrigationSystem.h"
#include "../ProjectConfig.h"

// Initialize the static member
IrrigationSystem *IrrigationSystem::instance = nullptr;

// Private constructor
IrrigationSystem::IrrigationSystem() : currentState(OperationState::IDLE),
                                       valves{
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
                                       isEnabled(false),                  // Default status
                                       openingClosingTimer(DELAY_OPENING_CLOSING_VALVE)
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

uint8_t IrrigationSystem::getValvesNumber() const
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

void IrrigationSystem::handleNonBlockingOperations()
{
    if (openingClosingTimer.timeout())
    {
        switch (currentState)
        {
        case OperationState::STARTING_WATERING:
            usePump ? pump.start() : turnMainValveOn();
            currentState = OperationState::IDLE; // Reset state after starting
            break;

        case OperationState::STOPPING_WATERING:
            usePump ? pump.stop() : turnMainValveOff();
            currentState = OperationState::IDLE; // Reset state after stopping
            break;

        case OperationState::DISABLING_SYSTEM:
            // Finish disabling by closing all valves
            for (uint8_t i = 0; i < VALVES_NUMBER; i++)
            {
                valves[i].close();
            }
            currentState = OperationState::IDLE; // Reset state after disabling
            break;

        case OperationState::IDLE:
            // No active operations
            break;
        }
    }
}

void IrrigationSystem::update()
{
    // Handle any ongoing non-blocking operations (e.g., stopping/starting)
    handleNonBlockingOperations();

    // Update the pump to handle non-blocking stop
    pump.update();

    // Check if the system is enabled
    if (!isEnabled)
    {
        return;
    }

    if (usePump && tank.isEmpty())
    {
        disableSystem();
        return;
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
    currentState = OperationState::STARTING_WATERING;
    openingClosingTimer.start();
}

void IrrigationSystem::stopWatering(IrrigationValve *valve)
{
    // If the pump and main valve are both off, close the valve and stop processing
    if (digitalRead(PIN_VALVE_MAIN) == LOW && (!usePump || pump.isOff()))
    {
        valve->close();
        currentState = OperationState::IDLE; // Reset the state when done
        return;
    }

    if (currentState != OperationState::STOPPING_WATERING)
    {
        currentState = OperationState::STOPPING_WATERING;
        openingClosingTimer.start();
    }
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
    if (currentState != OperationState::DISABLING_SYSTEM)
    {
        isEnabled = false;
        currentState = OperationState::DISABLING_SYSTEM;
        pump.stop();
        turnMainValveOff();
        openingClosingTimer.start(); // Start the timer for the non-blocking process
    }

    handleNonBlockingOperations();
}

void IrrigationSystem::turnMainValveOn()
{
    digitalWrite(PIN_VALVE_MAIN, HIGH);
}

void IrrigationSystem::turnMainValveOff()
{
    digitalWrite(PIN_VALVE_MAIN, LOW);
}
