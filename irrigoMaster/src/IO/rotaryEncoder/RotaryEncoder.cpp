#include "rotaryEncoder.h"
#include "../../ProjectConfig.h"
#include "Debug.hpp"

RotaryEncoder::RotaryEncoder()
    : encoder(ROTARY_PIN_A, ROTARY_PIN_B),
      lastCommand(Command::NONE),
      lastPosition(encoder.read()),
      buttonPressed(false),
      debounceTimer(debounceDelay),
      accelerationTimer(accelerationTimeout),
      stepThreshold(defaultThreshold)
{
    pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);
}

void RotaryEncoder::update()
{
    handleRotation();
    handleButton();
}

void RotaryEncoder::handleRotation()
{
    long currentPosition = encoder.read();
    long delta = currentPosition - lastPosition;

    if (abs(delta) >= stepThreshold)
    {
        // Adjust threshold based on rotation speed
        if (!accelerationTimer.timeout())
        {
            stepThreshold = fastThreshold;
        }
        else
        {
            stepThreshold = defaultThreshold;
        }

        accelerationTimer.start();
        lastCommand = (delta > 0) ? Command::LEFT : Command::RIGHT;
        lastPosition = currentPosition;
    }
}

void RotaryEncoder::handleButton()
{
    bool isPressed = digitalRead(ROTARY_BUTTON_PIN) == LOW;

    if (isPressed && !buttonPressed && debounceTimer.timeout())
    {
        buttonPressed = true;
        debounceTimer.start();
        lastCommand = Command::SELECT;
    }

    if (!isPressed && buttonPressed && debounceTimer.timeout())
    {
        buttonPressed = false;
        debounceTimer.start();
    }
}

Command RotaryEncoder::readCommand()
{
    Command cmd = lastCommand;
    lastCommand = Command::NONE;
    return cmd;
}