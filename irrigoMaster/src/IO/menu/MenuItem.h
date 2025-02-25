#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>
#include "../lcd/LCD.h"

enum class MenuItemType : byte
{
    LIST,
    VIEW_EDIT
};

class MenuItem
{
protected:
    const __FlashStringHelper *name;
    MenuItem *parent = nullptr;
    uint8_t currentIndex;
    RefreshType refresh;
    bool scrollMode;

public:
    // Constructor
    MenuItem(const __FlashStringHelper *name);
    void init();

    // Pure virtual methods that must be implemented by derived classes
    virtual MenuItemType getType() = 0;
    virtual uint8_t getItemsCount() = 0;
    virtual bool customExeRightCmd() = 0;
    virtual bool customExeLeftCmd() = 0;
    virtual bool customExeSelectCmd(MenuItem *&currentMenuItem) = 0;
    virtual bool customPrintLine(LCD *lcd, uint8_t line, uint8_t index) = 0;

    // Accessors
    const __FlashStringHelper *getName() const;
    MenuItem *getParent() const;
    bool exeRightCmd();
    bool exeLeftCmd();
    bool exeSelectCmd(MenuItem *&currentMenuItem);
    bool printLine(LCD *lcd, uint8_t line, uint8_t menuCursor);

    // Modifiers
    void setParent(MenuItem *p);

    // getters
    RefreshType getRefresh(bool reset = true);
};

#endif // MENU_ITEM_H