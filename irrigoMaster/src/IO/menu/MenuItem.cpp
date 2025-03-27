#include "Debug.hpp"
#include "MenuItem.h"

MenuItem::MenuItem(const __FlashStringHelper *name)
    : name(name)
{
    init();
}

uint8_t MenuItem::getCurrentIndex()
{
    return parent != nullptr ? currentIndex - 1 : currentIndex;
}

void MenuItem::init()
{
    currentIndex = 0;
    refresh = RefreshType::CLEAR_ALL;
    scrollMode = true;
    customExtraInit();
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
    if (scrollMode && currentIndex == 0 && parent != nullptr)
    {
        customFinish();
        currentMenuItem = parent;
        currentMenuItem->init();
        return true;
    }
    return customExeSelectCmd(currentMenuItem);
}

bool MenuItem::printLine(LCD *lcd, uint8_t line, uint8_t menuCursor)
{
    uint8_t index = currentIndex - menuCursor + line;
    int8_t parentOffset = parent != nullptr ? -1 : 0;

    if (index == 0 && parent != nullptr)
    {
        lcd->print(parent->name, 1, line);
        lcd->print(F("^"), lcd->getColumnsNumber() - 1, line);
        return true;
    }
    else if (index < getItemsCount())
    {
        return customPrintLine(lcd, line, index + parentOffset);
    }

    return false;
}