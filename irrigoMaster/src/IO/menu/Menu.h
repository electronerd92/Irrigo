#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "../lcd/LCD.h"
#include "../rotaryEncoder/RotaryEncoder.h"
#include "MenuItem.h"

class Menu
{
private:
    LCD *lcd;
    RotaryEncoder *rotaryEncoder;
    MenuItem *currentItem;

    void create();
    void print();

public:
    Menu(LCD *lcd, RotaryEncoder *rotaryEncoder);
    void update();
};

#endif // MENU_H