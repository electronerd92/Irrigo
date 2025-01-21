#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>
#include <SimpleRotary.h>
#include "Command.h"

class RotaryEncoder
{
private:
    SimpleRotary encoder;
    Command lastCommand;

public:
    RotaryEncoder();

    // Method to read the command from the rotary encoder and button
    Command readCommand();
    void update();
};

#endif // ROTARY_ENCODER_H