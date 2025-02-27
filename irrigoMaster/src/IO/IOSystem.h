#ifndef IO_SYSTEM_H
#define IO_SYSTEM_H

#include <Arduino.h>
#include "../MainSystem.h"
#include "lcd/LCD.h"
#include "rotaryEncoder/RotaryEncoder.h"
#include "menu/Menu.h"

class IOSystem
{
private:
    MainSystem *mainSystem;
    IrrigationSystem *irrigationSystem;
    LCD lcd;
    RotaryEncoder rotaryEncoder;
    Menu menu;

    static const uint8_t BUFFER_SIZE = 10; // Define a fixed buffer size
    char buffer[BUFFER_SIZE];

public:
    IOSystem(MainSystem *mainSystem);
    void update();

    void initValveIndex();
    const char *getValveIndex();
    void setValveIndex(bool goUp);

    const char *getValveMode();
    void setValveMode(bool goUp);

    const char *getValveStartTime();
    void setValveStartTimeHour(bool goUp);
    void setValveStartTimeMinute(bool goUp);

    const char *getValveFrequency();
    void setValveFrequency(bool goUp);

    const char *getValveDuration();
    void setValveDuration(bool goUp);
};

#endif // IO_SYSTEM_H