#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>
#include "MenuIterableObject.h"
#include "Command.h"
#include "LCDManager.h"

class MenuItem : public MenuIterableObject
{
private:
    const __FlashStringHelper *name; // Store name in PROGMEM
    MenuItem **subItems;             // Array of pointers to sub-items
    uint8_t subItemCount;
    uint8_t maxSubItems;
    uint8_t selectedIndex;     // Current selected index for navigation
    bool (*callback)(Command); // Function pointer for the callback

public:
    // Constructor for a MenuItem with sub-items
    MenuItem(const __FlashStringHelper *name, uint8_t maxSubItems);

    // Constructor for a MenuItem with a callback but no sub-items
    MenuItem(const __FlashStringHelper *name, bool (*callback)(Command));

    // Method to call the callback function if it is provided
    bool select(Command cmd) const override;

    // Check if a callback is provided
    bool hasCallBack() const;

    // Add a sub-item to the menu item
    bool addSubItem(MenuItem *item);

    // Method to increment the selected index
    bool incrementSelectedIndex() override;

    // Method to decrement the selected index
    bool decrementSelectedIndex() override;

    // Get the selected index
    uint8_t getSelectedIndex() const override;

    // Get name
    const __FlashStringHelper *getName() const;

    // print content
    const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const override;
};

#endif // MENU_ITEM_H