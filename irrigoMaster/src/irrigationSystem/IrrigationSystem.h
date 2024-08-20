#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include <Arduino.h>
#include "IrrigationValve.h"

#define VALVES_NUMBER 8

class IrrigationSystem
{
private:
    static IrrigationSystem *instance; // Singleton instance

    IrrigationValve valves[VALVES_NUMBER]; // Array of 8 Valve objects

    void startWatering(IrrigationValve *valve);

    // Private constructor
    IrrigationSystem();

public:
    // Deleted copy constructor and assignment operator
    IrrigationSystem(const IrrigationSystem &) = delete;
    IrrigationSystem &operator=(const IrrigationSystem &) = delete;

    // Method to get the single instance of IrrigationSystem
    static IrrigationSystem &getInstance();

    // Method to access the Valve objects
    IrrigationValve *getValve(uint8_t index);

    void update();
};

#endif // IRRIGATIONSYSTEM_H