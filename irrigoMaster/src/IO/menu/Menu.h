#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "../lcd/LCD.h"
#include "../rotaryEncoder/RotaryEncoder.h"
#include "MenuItem.h"
#include "MenuIterableItem.h"

class Menu
{
private:
    LCD *lcd;
    RotaryEncoder *rotaryEncoder;
    int8_t cursor;
    MenuItem *currentItem;

    static MenuIterableItem *create();
    void print(bool forceRefresh = false);
    void printCursor();

public:
    Menu(LCD *lcd, RotaryEncoder *rotaryEncoder);
    void update();
};

#endif // MENU_H