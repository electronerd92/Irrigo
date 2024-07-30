#ifndef MENUITERABLEOBJECT_H
#define MENUITERABLEOBJECT_H

#include <Arduino.h>
#include "MenuObject.h"
#include "LCDManager.h"
#include "Command.h"

class MenuIterableObject : public MenuObject
{
public:
    MenuObjectType getType() const override
    {
        return MenuObjectType::ITERABLE;
    }
    virtual const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const = 0;
    virtual uint8_t getSelectedIndex() const = 0;
    virtual void resetSelectedIndex() = 0;
    virtual bool incrementSelectedIndex() = 0;
    virtual bool decrementSelectedIndex() = 0;
    virtual bool select(Command cmd) const = 0;

    virtual MenuIterableObject *getParent() const = 0;
    virtual void setParent(MenuIterableObject *parent) = 0;
};

#endif // MENUITERABLEOBJECT_H