#include "CallableMenu.h"
#include "Menu.h"

CallableMenu::CallableMenu(const __FlashStringHelper *name, bool (*callback)(Command))
    : name(name), callback(callback) {}

const __FlashStringHelper *CallableMenu::getName() const
{
    return name;
}

bool CallableMenu::selectEffect(Command cmd) const
{
    if (callback)
    {
        if (callback(cmd))
            return true;

        Menu::getInstance().printMenu(true);
        return false;
    }
    return false;
}