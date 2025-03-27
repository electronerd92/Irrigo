#include "WaterFeeder.h"

WaterFeeder::WaterFeeder()
    : type(WaterFeederType::MAIN),
      available(true),
      pumpSystem()
{
    pinMode(mainValvePin, OUTPUT);
    stop();
}

void WaterFeeder::update()
{
    pumpSystem.update();
}

void WaterFeeder::start()
{
    if (type == WaterFeederType::MAIN)
    {
        digitalWrite(mainValvePin, ON);
    }
    else // WaterFeederType::PUMP
    {
        return pumpSystem.start();
    }
}

bool WaterFeeder::stop(bool force)
{
    if (type == WaterFeederType::MAIN)
    {
        digitalWrite(mainValvePin, OFF);
        return true;
    }
    else // WaterFeederType::PUMP
    {
        return pumpSystem.stop(force);
    }
}

bool WaterFeeder::isAvailable()
{
    if (type == WaterFeederType::MAIN)
    {
        return digitalRead(mainValvePin) == OFF;
    }
    else // WaterFeederType::PUMP
    {
        return pumpSystem.isAvailable();
    }
}

WaterFeederType WaterFeeder::getType()
{
    return type;
}

void WaterFeeder::setType(WaterFeederType value)
{
    type = value;
}