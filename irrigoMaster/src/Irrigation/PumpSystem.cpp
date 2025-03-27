#include "PumpSystem.h"

PumpSystem::PumpSystem()
    : isStopping(false),
      stoppingTimer(DELAY_OPENING_CLOSING_VALVE)
{
    pinMode(pumpValvePin, OUTPUT);
    pinMode(pumpRelayPin, OUTPUT);
    pinMode(tankEmptyPin, INPUT_PULLUP);
    pinMode(tankFullPin, INPUT_PULLUP);
    stop(true);
}

void PumpSystem::update()
{
    if (isWatering() && tankIsEmpty())
    {
        stop(true);
        // TODO add message to MessageSystem and an Error
    }
}

void PumpSystem::start()
{
    digitalWrite(pumpValvePin, ON);
    digitalWrite(pumpRelayPin, ON);
}

//? first stop valve than pump with a delay
bool PumpSystem::stop(bool force)
{
    if (force)
    {
        digitalWrite(pumpRelayPin, OFF);
        delay(DELAY_OPENING_CLOSING_VALVE);
        digitalWrite(pumpValvePin, OFF);
        isStopping = false;
        return true;
    }

    if (isStopping == false)
    {
        digitalWrite(pumpRelayPin, OFF);
        isStopping = true;
        stoppingTimer.start();
        return false;
    }

    if (stoppingTimer.timeout())
    {
        isStopping = false;
        digitalWrite(pumpValvePin, OFF);
        return true;
    }

    return false;
}

bool PumpSystem::isAvailable()
{
    return !isWatering() && !tankIsEmpty();
}

bool PumpSystem::tankIsEmpty()
{
    return digitalRead(tankEmptyPin) == OFF;
}

bool PumpSystem::tankIsFull()
{
    return digitalRead(tankFullPin) == OFF;
}

//? valve is alwaays the last one to be shut off
bool PumpSystem::isWatering()
{
    return digitalRead(pumpValvePin) == ON;
}