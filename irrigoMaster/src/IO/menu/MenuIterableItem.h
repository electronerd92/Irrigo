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
    bool decreaseCurrentIndex();
    bool increaseCurrentIndex();
    uint8_t getCurrentIndex();
    bool printContentAtIndex(uint8_t index, LCD *lcd, uint8_t line);
    MenuItem *selectItem() { return nullptr; };
    void addItem(MenuItem *item);

    MenuItemType getType() const override
    {
        return MenuItemType::ITERABLE;
    }

    const __FlashStringHelper *getName() const override
    {
        return name;
    }
};

#endif // MENU_ITERABLE_ITEM_H