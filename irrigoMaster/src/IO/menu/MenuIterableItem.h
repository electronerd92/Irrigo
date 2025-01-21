#ifndef MENU_ITERABLE_ITEM_H
#define MENU_ITERABLE_ITEM_H

#include <Arduino.h>
#include "MenuItem.h"

class MenuIterableItem : public MenuItem
{
private:
    const __FlashStringHelper *name;
    MenuItem **items;
    uint8_t itemsCount;
    uint8_t currentItemCount;
    uint8_t index;

public:
    MenuIterableItem(const __FlashStringHelper *name, uint8_t itemsCount);
    void decreaseIndex() { };
    void increaseIndex() { };
    MenuItem* selectItem() { return nullptr; };
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