#include "CommandManager.h"
#include "../ProjectConfig.h"
#include "Debug.hpp"

// Initialize the static member
CommandManager *CommandManager::instance = nullptr;

// Private constructor
CommandManager::CommandManager()
    : encoder(ROTARY_PIN_A, ROTARY_PIN_B, ROTARY_BUTTON_PIN), lastCommand(Command::NONE) {}

// Method to get the single instance of CommandManager
CommandManager &CommandManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CommandManager();
    }
    return *instance;
}

void CommandManager::update()
{
    // Read the rotary encoder
    byte dir = encoder.rotate();

    if (dir != 0)
    {
        if (dir == 1) // CW
        {
            lastCommand = Command::DOWN;
        }

        else if (dir == 2) // CCW
        {
            lastCommand = Command::UP;
        }
    }

    // Read the button state with debouncing

    if (encoder.push())
    {
        lastCommand = Command::SELECT;
    }
}

Command CommandManager::readCommand()
{
    Command currentCmd = lastCommand;
    lastCommand = Command::NONE; // Clear the command after reading
    return currentCmd;
}