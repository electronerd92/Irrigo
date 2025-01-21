#include "Debug.hpp"
#include "MenuIterableItem.h"

MenuIterableItem::MenuIterableItem(const __FlashStringHelper *name, uint8_t itemsCount)
    : name(name),
      itemsCount(itemsCount),
      currentItemCount(0),
      index(0)
{
    items = new MenuItem *[itemsCount];
}

void MenuIterableItem::addItem(MenuItem *item)
{
    if (currentItemCount < itemsCount)
    {
        item->setParent(this);
        items[currentItemCount++] = item;
    }
}