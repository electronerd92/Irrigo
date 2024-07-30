#include "Menu.h"
#include "NavigableMenu.h"
#include "MenuObject.h"
#include "Debug.hpp"

// Constructor for a NavigableMenu with sub-items
NavigableMenu::NavigableMenu(const __FlashStringHelper *name, uint8_t maxSubItems)
    : name(name), subItemCount(0), maxSubItems(maxSubItems + 1), selectedIndex(0)
{
    subItems = new MenuObject *[maxSubItems + 1]; // Reserve space for sub-items and parent
    subItems[0] = nullptr;                        // Parent placeholder, will be set later
    subItemCount++;
}

//  Add a sub-item to the menu item
bool NavigableMenu::addSubItem(MenuObject *item)
{
    if (subItemCount < maxSubItems)
    {
        if (item->getType() == MenuObjectType::ITERABLE)
        {
            auto iterableItem = static_cast<MenuIterableObject *>(item);
            if (iterableItem->getParent() == nullptr)
            {
                iterableItem->setParent(this);
            }
        }

        subItems[subItemCount++] = item;
        return true;
    }
    return false;
}

// Override method to set the parent of the navigable menu
void NavigableMenu::setParent(MenuIterableObject *parent)
{
    subItems[0] = parent;
}

// Override method to get the parent of the navigable menu
MenuIterableObject *NavigableMenu::getParent() const
{
    return static_cast<MenuIterableObject *>(subItems[0]);
}

// Method to remove the parent and shift sub-items
void NavigableMenu::removeParent()
{
    // Shift all sub-items up by one position
    for (uint8_t i = 1; i < maxSubItems; ++i)
    {
        subItems[i - 1] = subItems[i];
    }
    subItems[maxSubItems] = nullptr; // Clear the last item
    subItemCount--;
}

// Method to call the callback function if it is provided
bool NavigableMenu::select(Command cmd) const
{
    if (selectedIndex < subItemCount)
    {
        return subItems[selectedIndex]->selectEffect(cmd);
    }
    return false;
}

// Method to perform the select effect
bool NavigableMenu::selectEffect(Command cmd) const
{
    Menu::getInstance().setCurrentMenuItem(const_cast<NavigableMenu *>(this)); // Set current menu to this menu
    return false;
}

// Method to increment the selected index
bool NavigableMenu::incrementSelectedIndex()
{
    if (selectedIndex < subItemCount - 1)
    {
        ++selectedIndex;
        return true;
    }
    return false;
}

// Method to decrement the selected index
bool NavigableMenu::decrementSelectedIndex()
{
    if (selectedIndex > 0)
    {
        --selectedIndex;
        return true;
    }
    return false;
}

// Get the selected index
uint8_t NavigableMenu::getSelectedIndex() const
{
    return selectedIndex;
}

// Reset the selected index
void NavigableMenu::resetSelectedIndex()
{
    selectedIndex = 0;
}

// Print content at index
const bool NavigableMenu::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    if (index < subItemCount)
    {
        MenuObject *item = subItems[index];
        lcdManager.print(item->getName(), 1, row);

        if (index == 0 && this != Menu::getInstance().getMainMenu())
            lcdManager.print(F("^"), -1, row);

        else if (item->getType() == MenuObjectType::ITERABLE)
            lcdManager.print(F(">"), -1, row);

        return true;
    }
    return false;
}

// Get the name of the menu
const __FlashStringHelper *NavigableMenu::getName() const
{
    return name;
}