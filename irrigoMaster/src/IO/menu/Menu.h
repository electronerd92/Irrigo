#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "../lcd/LCD.h"
#include "../rotaryEncoder/RotaryEncoder.h"
#include "MenuItem.h"
#include "MenuList.h"

// Forward declaration instead of including IOSystem.h
class IOSystem;

class Menu
{
private:
    LCD *lcd;
    RotaryEncoder *rotaryEncoder;
    IOSystem *iosys;
    int8_t cursor;
    MenuItem *currentItem;

    static MenuList *create(IOSystem *iosys);
    void print();
    void printCursor();

public:
    Menu(LCD *lcd, RotaryEncoder *rotaryEncoder, IOSystem *iosys);
    void update();
};

#endif // MENU_H