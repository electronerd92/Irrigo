#ifndef MENUITERABLEOBJECT_H
#define MENUITERABLEOBJECT_H

#include <Arduino.h>
#include "LCDManager.h"
#include "Command.h"

class MenuIterableObject
{
public:
    virtual ~MenuIterableObject() = default;

    virtual const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const = 0;
    virtual uint8_t getSelectedIndex() const = 0;
    virtual bool incrementSelectedIndex() = 0;
    virtual bool decrementSelectedIndex() = 0;
    virtual bool select(Command cmd) const = 0;
};

#endif // MENUITERABLEOBJECT_H