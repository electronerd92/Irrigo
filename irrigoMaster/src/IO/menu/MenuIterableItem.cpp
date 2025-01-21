#include "Debug.hpp"
#include "MenuIterableItem.h"

MenuIterableItem::MenuIterableItem(const __FlashStringHelper *name, const uint8_t itemsCount)
    : name(name),
      itemsCount(itemsCount),
      currentItemsCount(0),
      currentIndex(0)
{
    items = new MenuItem *[itemsCount];
}

void MenuIterableItem::addItem(MenuItem *item)
{
    if (currentItemsCount < itemsCount)
    {
        item->setParent(this);
        items[currentItemsCount++] = item;
    }
}

uint8_t MenuIterableItem::getCurrentIndex()
{
    return currentIndex;
}

bool MenuIterableItem::decreaseCurrentIndex()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        return true;
    }
    return false;
}

bool MenuIterableItem::increaseCurrentIndex()
{
    uint8_t actualItemsCount = getParent() == nullptr
                                   ? itemsCount
                                   : itemsCount + 1;
    if (currentIndex < actualItemsCount - 1)
    {
        currentIndex++;
        return true;
    }
    return false;
}

bool MenuIterableItem::printContentAtIndex(uint8_t index, LCD *lcd, uint8_t line)
{
    if (index < itemsCount)
    {
        MenuItem *item = items[index];
        lcd->print(item->getName(), 1, line);

        if (item->getType() == MenuItemType::ITERABLE)
            lcd->print(F(">"), lcd->getColumnsNumber() - 2, line);

        return true;
    }
    else if (index == itemsCount && getParent() != nullptr)
    {
        lcd->print(F("Back"), 1, line);
    }
    return false;
}