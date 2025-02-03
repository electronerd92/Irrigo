#include "Debug.hpp"
#include "MenuList.h"

MenuList::MenuList(const __FlashStringHelper *name, const uint8_t itemsCount)
    : MenuItem(name),
      itemsCount(itemsCount),
      currentItemsCount(0)
{
    items = new MenuItem *[itemsCount];
}

void MenuList::addItem(MenuItem *item)
{
    if (currentItemsCount < itemsCount)
    {
        item->setParent(this);
        items[currentItemsCount++] = item;
    }
}

MenuItemType MenuList::getType()
{
    return MenuItemType::LIST;
}

uint8_t MenuList::getItemsCount()
{
    return parent == nullptr
               ? itemsCount
               : itemsCount + 1;
}

bool MenuList::customExeSelectCmd(MenuItem *&currentMenuItem)
{
    currentMenuItem = items[currentIndex];
    currentMenuItem->init();
    return true;
}

bool MenuList::printLine(LCD *lcd, uint8_t line, uint8_t menuCursor)
{
    uint8_t index = currentIndex - menuCursor + line;
    if (index < itemsCount)
    {
        MenuItem *item = items[index];
        lcd->print(item->getName(), 1, line);

        if (item->getType() == MenuItemType::LIST)
            lcd->print(F(">"), lcd->getColumnsNumber() - 2, line);

        return true;
    }
    else if (index == itemsCount)
    {
        lcd->print(F("Back"), 1, line);
    }
    return false;
}