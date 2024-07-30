#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include <Arduino.h>

class IrrigationSystem
{
private:
    static IrrigationSystem *instance; // Singleton instance
    // Private constructor
    IrrigationSystem();

public:
    // Deleted copy constructor and assignment operator
    IrrigationSystem(const IrrigationSystem &) = delete;
    IrrigationSystem &operator=(const IrrigationSystem &) = delete;

    // Method to get the single instance of IrrigationSystem
    static IrrigationSystem &getInstance();
};

#endif // IRRIGATIONSYSTEM_H