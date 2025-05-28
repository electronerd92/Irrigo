#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>
#include <Encoder.h>
#include "Command.h"
#include "Timer.hpp"

class RotaryEncoder
{
private:
    Encoder encoder;
    Command lastCommand;
    long lastPosition;

    bool buttonPressed;

    Timer debounceTimer;
    Timer accelerationTimer;

    int stepThreshold;

    // Constants
    static constexpr uint32_t debounceDelay = 50;
    static constexpr uint32_t accelerationTimeout = 400;
    static constexpr int defaultThreshold = 4;
    static constexpr int fastThreshold = 2;

    void handleRotation();
    void handleButton();

public:
    RotaryEncoder();
    Command readCommand();
    void update();
};

#endif // ROTARY_ENCODER_H