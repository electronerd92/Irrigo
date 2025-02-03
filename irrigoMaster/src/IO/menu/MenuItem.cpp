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
    refresh = true;
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

bool MenuItem::getRefresh()
{
    bool tmp = refresh;
    refresh = false;
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