#include "IrrigationSystem.h"

// Initialize the static member
IrrigationSystem *IrrigationSystem::instance = nullptr;

// Private constructor
IrrigationSystem::IrrigationSystem()
{
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
Valve *IrrigationSystem::getValve(int index)
{
    if (index < 0 || index >= 2)
    {
        // Handle invalid index, for example, return the first valve
        return nullptr;
    }
    return &valves[index];
}