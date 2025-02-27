#ifndef MENU_NODE_H
#define MENU_NODE_H

#include <Arduino.h>
#include "MenuItem.h"
#include "Debug.hpp"

// Forward declaration to avoid circular dependency
class IOSystem;

class MenuNode : public MenuItem
{
protected:
    IOSystem *ioSystem;
    bool canEdit;

public:
    MenuNode(const __FlashStringHelper *name, IOSystem *iosys) : MenuItem(name), ioSystem(iosys), canEdit(false) {};
    void setCanEdit(bool value) { canEdit = value; };
    MenuItemType getType() override { return MenuItemType::VIEW_EDIT; };
    void customExtraInit() override
    {
        if (canEdit)
            debugLog("Set EditMode true");
    };
    void customFinish() override
    {
        if (canEdit)
            debugLog("Set EditMode false");
    };
};

#endif // MENU_NODE_H