#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include <Arduino.h>
#include "Command.h"

enum MenuObjectType : byte
{
    ITERABLE,
    CALLABLE
};

class MenuObject
{
public:
    virtual const __FlashStringHelper *getName() const = 0;
    virtual bool selectEffect(Command cmd) const = 0;
    virtual MenuObjectType getType() const = 0;
};

#endif // MENUOBJECT_H