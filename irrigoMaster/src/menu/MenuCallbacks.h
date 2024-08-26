#ifndef MENU_CALLBACKS_H
#define MENU_CALLBACKS_H

#include <Arduino.h>
#include "Command.h"

class MenuCallbacks
{
private:
    static void showValveSettingsMenu();
    static uint8_t actionIndex; // used to handle complex MenuCallbacks function

public:
    // Define static callback functions
    static bool selectValve1(Command cmd);
    static bool selectValve2(Command cmd);
    static bool selectValve3(Command cmd);
    static bool selectValve4(Command cmd);
    static bool selectValve5(Command cmd);
    static bool selectValve6(Command cmd);
    static bool selectValve7(Command cmd);
    static bool selectValve8(Command cmd);

    static bool printInfo(Command cmd);
    static bool resetToFactorySettings(Command cmd);

    static bool setDate(Command cmd);
    static bool setTime(Command cmd);
};

#endif // MENU_CALLBACKS_H