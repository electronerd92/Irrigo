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

MenuItemType MenuIterableItem::getType()
{
    return MenuItemType::ITERABLE;
}

const __FlashStringHelper *MenuIterableItem::getName()
{
    return name;
}

void MenuIterableItem::addItem(MenuItem *item)
{
    if (currentItemsCount < itemsCount)
    {
        item->setParent(this);
        items[currentItemsCount++] = item;
    }
}

bool MenuIterableItem::exeDownCmd()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        return true;
    }
    return false;
}

bool MenuIterableItem::exeUpCmd()
{
    uint8_t actualItemsCount = parent == nullptr
                                   ? itemsCount
                                   : itemsCount + 1;
    if (currentIndex < actualItemsCount - 1)
    {
        currentIndex++;
        return true;
    }
    return false;
}

bool MenuIterableItem::exeSelectCmd(MenuItem *currentMenuItem)
{
    currentMenuItem = items[currentIndex];
    return true;
}

bool MenuIterableItem::printLine(LCD *lcd, uint8_t line, uint8_t menuCursor)
{
    uint8_t index = currentIndex - menuCursor + line;
    if (index < itemsCount)
    {
        MenuItem *item = items[index];
        lcd->print(item->getName(), 1, line);

        if (item->getType() == MenuItemType::ITERABLE)
            lcd->print(F(">"), lcd->getColumnsNumber() - 2, line);

        return true;
    }
    else if (index == itemsCount && parent != nullptr)
    {
        lcd->print(F("Back"), 1, line);
    }
    return false;
}