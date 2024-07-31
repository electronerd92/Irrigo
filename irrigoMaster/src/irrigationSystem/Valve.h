#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>

enum ValveMode : byte
{
    OFF,
    CLASSIC,
    SMART
};

class Valve
{
private:
    ValveMode mode;

public:
    Valve();
    // Assuming some methods for Valve class
    void open();
    void close();
    Valve &operator=(const Valve &other); // Copy assignment operator
    ValveMode getMode() const { return ValveMode::OFF; };
    void setMode(ValveMode md) { mode = md; };
};

#endif // VALVE_H