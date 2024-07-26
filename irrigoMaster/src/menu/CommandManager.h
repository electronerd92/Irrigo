#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <Arduino.h>
#include <SimpleRotary.h>
#include "Command.h"

class CommandManager
{
private:
    static CommandManager *instance;
    SimpleRotary encoder;
    Command lastCommand;

    // Private constructor to prevent instantiation
    CommandManager();

public:
    // Deleted copy constructor and assignment operator
    CommandManager(const CommandManager &) = delete;
    CommandManager &operator=(const CommandManager &) = delete;

    // Method to get the single instance of CommandManager
    static CommandManager &getInstance();

    // Method to read the command from the rotary encoder and button
    Command readCommand();
    void update();
};

#endif // COMMAND_MANAGER_H