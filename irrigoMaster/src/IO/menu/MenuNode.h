#ifndef MENU_NODE_H
#define MENU_NODE_H

#include <Arduino.h>
#include "MenuItem.h"

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
};

class MenuNodeWrapper : public MenuItem
{
private:
    MenuNode *source;
    bool canEdit;

    void applyEditState()
    {
        source->setCanEdit(canEdit);
    }

public:
    MenuNodeWrapper(MenuNode *src, bool canEdt) : MenuItem(src->getName()),
                                                  source(src), canEdit(canEdt) {};

    MenuItemType getType() override
    {
        applyEditState();
        return source->getType();
    };
    uint8_t getItemsCount() override
    {
        applyEditState();
        return source->getItemsCount();
    };
    bool customExeRightCmd() override
    {
        applyEditState();
        return source->customExeRightCmd();
    };
    bool customExeLeftCmd() override
    {
        applyEditState();
        return source->customExeLeftCmd();
    };
    bool customExeSelectCmd(MenuItem *&currentMenuItem) override
    {
        applyEditState();
        return source->customExeSelectCmd(currentMenuItem);
    };
    bool customPrintLine(LCD *lcd, uint8_t line, uint8_t index) override
    {
        applyEditState();
        return source->customPrintLine(lcd, line, index);
    };
};

#endif // MENU_NODE_H