#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include <Arduino.h>
#include "Valve.h"

class IrrigationSystem
{
private:
    static IrrigationSystem *instance; // Singleton instance

    Valve valves[2]; // Array of 2 Valve objects

    // Private constructor
    IrrigationSystem();

public:
    // Deleted copy constructor and assignment operator
    IrrigationSystem(const IrrigationSystem &) = delete;
    IrrigationSystem &operator=(const IrrigationSystem &) = delete;

    // Method to get the single instance of IrrigationSystem
    static IrrigationSystem &getInstance();

    // Method to access the Valve objects
    Valve *getValve(int index);
};

#endif // IRRIGATIONSYSTEM_H