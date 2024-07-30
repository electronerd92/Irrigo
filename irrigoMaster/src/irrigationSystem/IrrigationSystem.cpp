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