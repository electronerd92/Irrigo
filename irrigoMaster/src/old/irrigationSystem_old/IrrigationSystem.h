#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include <Arduino.h>
#include "IrrigationValve.h"
#include "Pump.h"
#include "Tank.h"
#include "Timer.hpp"

enum class OperationState : uint8_t
{
    IDLE,
    STARTING_WATERING,
    STOPPING_WATERING,
    DISABLING_SYSTEM
};

class IrrigationSystem
{
private:
    static IrrigationSystem *instance; // Singleton instance
    static const uint8_t VALVES_NUMBER = 8;

    OperationState currentState;
    IrrigationValve valves[VALVES_NUMBER]; // Array of 8 Valve objects
    Pump pump;
    Tank tank;

    bool usePump;   // Boolean to indicate whether to use the pump
    bool isEnabled; // System status

    Timer openingClosingTimer;

    void startWatering(IrrigationValve *valve);
    void stopWatering(IrrigationValve *valve);
    void handleNonBlockingOperations();

    // Private constructor
    IrrigationSystem();

public:
    // Deleted copy constructor and assignment operator
    IrrigationSystem(const IrrigationSystem &) = delete;
    IrrigationSystem &operator=(const IrrigationSystem &) = delete;

    // Method to get the single instance of IrrigationSystem
    static IrrigationSystem &getInstance();

    uint8_t getValvesNumber() const;
    // Method to access the Valve objects
    IrrigationValve *getValve(uint8_t index);

    void turnMainValveOn();
    void turnMainValveOff();

    void setIsEnabled(bool value);
    bool getIsEnabled();
    void enableSystem();
    void disableSystem();

    bool getUsePump();
    void setUsePump(bool value); // Set whether to use the pump or main feed

    void update(); // Main loop method for handling the irrigation logic
};

#endif // IRRIGATIONSYSTEM_H