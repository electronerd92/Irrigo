#ifndef IO_SYSTEM_H
#define IO_SYSTEM_H

#include <Arduino.h>
#include "MainSystem.h"
#include "IO/lcd/LCD.h"
#include "IO/rotaryEncoder/RotaryEncoder.h"
#include "IO/menu/Menu.h"

class IOSystem
{
private:
    const MainSystem *mainSystem;
    LCD lcd;
    RotaryEncoder rotaryEncoder;
    Menu menu;

public:
    IOSystem(MainSystem *mainSystem);
    void update();
};

#endif // IO_SYSTEM_H