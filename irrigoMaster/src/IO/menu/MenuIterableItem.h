#ifndef MENU_ITERABLE_ITEM_H
#define MENU_ITERABLE_ITEM_H

#include <Arduino.h>
#include "MenuItem.h"
#include "../lcd/LCD.h"

class MenuIterableItem : public MenuItem
{
private:
    const __FlashStringHelper *name;
    MenuItem **items;
    const uint8_t itemsCount;
    uint8_t currentItemsCount;
    uint8_t currentIndex;

public:
    MenuIterableItem(const __FlashStringHelper *name, const uint8_t itemsCount);

    const __FlashStringHelper *getName() override;
    MenuItemType getType() override;
    bool exeDownCmd() override;
    bool exeUpCmd() override;
    bool exeSelectCmd(MenuItem *currentMenuItem) override;
    bool printLine(LCD *lcd, uint8_t line, uint8_t menuCursor) override;

    


    bool printContentAtIndex(uint8_t index, LCD *lcd, uint8_t line);

    void addItem(MenuItem *item);


};

#endif // MENU_ITERABLE_ITEM_H