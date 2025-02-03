#ifndef MENU_LIST_H
#define MENU_LIST_H

#include <Arduino.h>
#include "MenuItem.h"
#include "MenuNode.h"
#include "../lcd/LCD.h"

class MenuList : public MenuItem
{
private:
    MenuItem **items;
    const uint8_t itemsCount;
    uint8_t currentItemsCount;

public:
    MenuList(const __FlashStringHelper *name, const uint8_t itemsCount);
    void addItem(MenuItem *item);
    void addItem(MenuNode *item, bool editable);

    MenuItemType getType() override;
    uint8_t getItemsCount() override;
    bool customExeRightCmd() override { return false; };
    bool customExeLeftCmd() override { return false; };
    bool customExeSelectCmd(MenuItem *&currentMenuItem) override;
    bool customPrintLine(LCD *lcd, uint8_t line, uint8_t index) override;
};

#endif // MENU_LIST_H