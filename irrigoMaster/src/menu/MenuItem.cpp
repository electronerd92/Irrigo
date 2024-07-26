#include "MenuItem.h"
#include "Menu.h"
#include "Debug.hpp"

// Constructor for a MenuItem with sub-items
MenuItem::MenuItem(const __FlashStringHelper *name, uint8_t maxSubItems)
    : name(name), subItemCount(0), maxSubItems(maxSubItems + 1), selectedIndex(0), callback(nullptr)
{
    // maxSubItems is the parameter not the member
    subItems = new MenuItem *[maxSubItems + 1]; // Allocate space for sub-items and parent
    subItems[maxSubItems] = nullptr;            // Initialize the parent pointer to nullptr
}

// Constructor for a MenuItem with a callback but no sub-items
MenuItem::MenuItem(const __FlashStringHelper *name, bool (*callback)(Command))
    : name(name), subItems(nullptr), subItemCount(0), maxSubItems(0), selectedIndex(0), callback(callback) {}

// Method to check if the MenuItem has a callback
bool MenuItem::hasCallBack() const
{
    return callback != nullptr;
}

// Add a sub-item to the menu item
bool MenuItem::addSubItem(MenuItem *item)
{
    if (subItems && subItemCount < maxSubItems - 1)
    {
        subItems[subItemCount++] = item;
        if (item->subItems)
            item->subItems[item->maxSubItems - 1] = this; // Set the parent of the sub-item if it has subItems

        debugLog("subItemCount", subItemCount);
        return true;
    }
    return false;
}

// Method to call the callback function if it is provided
bool MenuItem::select(Command cmd) const
{
    if (subItems[selectedIndex]->hasCallBack())
    {
        return subItems[selectedIndex]->callback(cmd); // Call the callback function
    }

    Menu::getInstance().setCurrentMenuItem(subItems[selectedIndex]); // Set current menu to selected sub-item

    return false; // Return false if no callback is provided
}

// Method to increment the selected index
bool MenuItem::incrementSelectedIndex()
{
    if (selectedIndex < maxSubItems && subItems[selectedIndex + 1])
    {
        ++selectedIndex;
        return true;
    }
    return false;
}

// Method to decrement the selected index
bool MenuItem::decrementSelectedIndex()
{
    if (selectedIndex > 0)
    {
        --selectedIndex;
        return true;
    }
    return false;
}

// Get the selected index
uint8_t MenuItem::getSelectedIndex() const
{
    return selectedIndex;
}

// print content
const bool MenuItem::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    if (index < maxSubItems)
    {
        lcdManager.print(subItems[index]->getName(), 1, row);
        return true;
    }
    return false;
}

// Get aname
const __FlashStringHelper *MenuItem::getName() const
{
    return name;
}