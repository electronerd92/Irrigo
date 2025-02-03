#include "MenuValve.h"

MenuValve::MenuValve(const __FlashStringHelper *name, IOSystem *iosys) : MenuNode(name, iosys)
{
    valveSettings[0] = {F("Valve"), &MenuValve::getValveState, &MenuValve::setValveState};
    valveSettings[1] = {F("Mode"), &MenuValve::getValveState, &MenuValve::setValveState};
    valveSettings[2] = {F("Mode"), nullptr, &MenuValve::setValveState};
}

uint8_t MenuValve::getItemsCount()
{
    return nodeItemsCount + 1;
}

bool MenuValve::customExeRightCmd()
{
    refresh = RefreshType::REFRESH;
    (this->*valveSettings[currentIndex].setter)(IncreaseDecrease::INCREASE);
    return false;
}

bool MenuValve::customExeLeftCmd()
{
    refresh = RefreshType::REFRESH;
    (this->*valveSettings[currentIndex].setter)(IncreaseDecrease::DECREASE);
    return false;
}

bool MenuValve::customExeSelectCmd(MenuItem *&currentMenuItem)
{
    refresh = RefreshType::REFRESH;

    if (scrollMode == true)
    {
        if (currentIndex == 0 || canEdit)
        {
            scrollMode = false;
        }
        return false;
    }
    scrollMode = true;
    return false;
}

bool MenuValve::customPrintLine(LCD *lcd, uint8_t line, uint8_t index)
{
    lcd->stopBlinker(); // clear blink and buffer if not already stopped
    if (scrollMode == true)
    {
        lcd->print(valveSettings[index].name, 1, line);
        if (valveSettings[index].getter != nullptr)
        {
            const char *buffer = (this->*valveSettings[index].getter)();
            uint8_t column = lcd->getColumnsNumber() - strlen(buffer);
            lcd->print(buffer, column, line);
        }
        return true;
    }

    else if (index == currentIndex)
    {
        if (valveSettings[index].getter != nullptr)
        {
            const char *buffer = (this->*valveSettings[index].getter)();
            uint8_t column = lcd->getColumnsNumber() - strlen(buffer);
            lcd->startBlinker(buffer, column, line);
        }
        return false;
    }

    return true;
}

const char *MenuValve::getValveState()
{
    return "test";
}
void MenuValve::setValveState(IncreaseDecrease action)
{
}