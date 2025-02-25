#include "Debug.hpp"
#include "MenuItem.h"

MenuItem::MenuItem(const __FlashStringHelper *name)
    : name(name)
{
    init();
}

void MenuItem::init()
{
    currentIndex = 0;
    refresh = RefreshType::CLEAR_ALL;
    scrollMode = true;
}

const __FlashStringHelper *MenuItem::getName() const
{
    return name;
}

MenuItem *MenuItem::getParent() const
{
    return parent;
}

void MenuItem::setParent(MenuItem *p)
{
    parent = p;
}

RefreshType MenuItem::getRefresh(bool reset)
{
    RefreshType tmp = refresh;
    if (reset)
    {
        refresh = RefreshType::NONE;
    }

    return tmp;
}

bool MenuItem::exeLeftCmd()
{
    if (scrollMode == false)
    {
        return customExeLeftCmd();
    }
    if (currentIndex > 0)
    {
        currentIndex--;
        return true;
    }
    return false;
}

bool MenuItem::exeRightCmd()
{
    if (scrollMode == false)
    {
        return customExeRightCmd();
    }

    if (currentIndex < getItemsCount() - 1)
    {
        currentIndex++;
        return true;
    }
    return false;
}

bool MenuItem::exeSelectCmd(MenuItem *&currentMenuItem)
{
    if (scrollMode && currentIndex == getItemsCount() - 1 && parent != nullptr)
    {
        currentMenuItem = parent;
        currentMenuItem->init();
        return true;
    }
    return customExeSelectCmd(currentMenuItem);
}

bool MenuItem::printLine(LCD *lcd, uint8_t line, uint8_t menuCursor)
{
    uint8_t index = currentIndex - menuCursor + line;

    if (index == getItemsCount() - 1 && parent != nullptr)
    {
        lcd->print(F("Back"), 1, line);
    }
    else if (index < getItemsCount())
    {
        return customPrintLine(lcd, line, index);
    }

    return false;
}