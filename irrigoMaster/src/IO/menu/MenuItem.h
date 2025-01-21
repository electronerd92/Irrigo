#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>

enum class MenuItemType : byte
{
    ITERABLE,
    CALLABLE
};

class MenuItem
{
private:
    MenuItem *parent;

public:
    virtual const __FlashStringHelper *getName() const = 0;
    virtual MenuItemType getType() const = 0;
    virtual MenuItem *getParent() { return parent; };
    virtual void setParent(MenuItem *) { this->parent = parent; };
};

#endif // MENU_ITEM_H