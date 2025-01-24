#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>
#include "../lcd/LCD.h"

enum class MenuItemType : byte
{
    ITERABLE,
    CALLABLE
};

class MenuItem
{
protected:
    MenuItem *parent = nullptr;

public:
    // Pure virtual methods that must be implemented by derived classes
    virtual const __FlashStringHelper *getName() = 0;
    virtual MenuItemType getType() = 0;
    virtual bool exeDownCmd() = 0;
    virtual bool exeUpCmd() = 0;
    virtual bool exeSelectCmd(MenuItem *currentMenuItem) = 0;
    virtual bool printLine(LCD *lcd, uint8_t line, uint8_t menuCursor) = 0;

    // Parent handling
    virtual MenuItem *getParent() { return parent; };
    virtual void setParent(MenuItem *p) { this->parent = p; }
};

#endif // MENU_ITEM_H