#include "rotaryEncoder.h"
#include "../../ProjectConfig.h"
#include "Debug.hpp"

RotaryEncoder::RotaryEncoder()
    : encoder(ROTARY_PIN_A, ROTARY_PIN_B, ROTARY_BUTTON_PIN), lastCommand(Command::NONE) {}

void RotaryEncoder::update()
{
    // Read the rotary encoder
    byte dir = encoder.rotate();

    if (dir != 0)
    {
        if (dir == 1) // CW
        {
            lastCommand = Command::RIGHT;
        }

        else if (dir == 2) // CCW
        {
            lastCommand = Command::LEFT;
        }
    }

    // Read the button state with debouncing

    if (encoder.push())
    {
        lastCommand = Command::SELECT;
    }
}

Command RotaryEncoder::readCommand()
{
    Command currentCmd = lastCommand;
    lastCommand = Command::NONE; // Clear the command after reading
    return currentCmd;
}