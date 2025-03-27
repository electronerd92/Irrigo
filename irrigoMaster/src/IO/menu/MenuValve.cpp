#include "MenuValve.h"
#include "Debug.hpp"

/*
L'idea è di avere un sottoindice in modo da poter avere più campi per linea, editabili uno alla volta
Utile ad esempio nel settare un orario o lo start time etc
Potrei usare il concetto unicamente nel setter e lasciare il getter com'è in questo modo il blink funziona
customExeSelectCmd servità ad incrementare e resettare il subindex
Nel setter agisco in conseguenza al subIndex in corso
*/

MenuValve::MenuValve(const __FlashStringHelper *name, IOSystem *iosys)
    : MenuNode(name, iosys),
      currentSubIndex(0)
{
    valveSettings[0].name = F("Valve");
    valveSettings[0].subItems = 0;
    valveSettings[0].getter = &MenuValve::getValveIndex;
    valveSettings[0].setter = &MenuValve::setValveIndex;

    valveSettings[1].name = F("Mode");
    valveSettings[1].subItems = 0;
    valveSettings[1].getter = &MenuValve::getMode;
    valveSettings[1].setter = &MenuValve::setMode;

    valveSettings[2].name = F("Start");
    valveSettings[2].subItems = 1;
    valveSettings[2].getter = &MenuValve::getStartTime;
    valveSettings[2].setter = &MenuValve::setStartTime;

    valveSettings[3].name = F("Freq[h]");
    valveSettings[3].subItems = 0;
    valveSettings[3].getter = &MenuValve::getFrequency;
    valveSettings[3].setter = &MenuValve::setFrequency;

    valveSettings[4].name = F("Duration[min]");
    valveSettings[4].subItems = 0;
    valveSettings[4].getter = &MenuValve::getDuration;
    valveSettings[4].setter = &MenuValve::setDuration;
}

void MenuValve::customExtraInit()
{
    MenuNode::customExtraInit();
    ioSystem->initValveIndex();
}

uint8_t MenuValve::getItemsCount()
{
    return NODE_ITEMS_COUNT + 1;
}

bool MenuValve::customExeRightCmd()
{
    refresh = RefreshType::REFRESH;
    (this->*valveSettings[getCurrentIndex()].setter)(true);
    return false;
}

bool MenuValve::customExeLeftCmd()
{
    refresh = RefreshType::REFRESH;
    (this->*valveSettings[getCurrentIndex()].setter)(false);
    return false;
}

bool MenuValve::customExeSelectCmd(MenuItem *&currentMenuItem)
{
    refresh = RefreshType::REFRESH;

    // 0 because even in show mode need to switch valve to viex params
    if (scrollMode == true && (getCurrentIndex() == 0 || canEdit))
    {
        currentSubIndex = 0;
        scrollMode = false;
    }
    else if (currentSubIndex == valveSettings[getCurrentIndex()].subItems)
    {
        scrollMode = true;
        refresh = RefreshType::CLEAR_ALL;
    }
    else
    {
        currentSubIndex++;
    }
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

    else if (index == getCurrentIndex())
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

const char *MenuValve::getValveIndex()
{
    return ioSystem->getValveIndex();
}
void MenuValve::setValveIndex(bool goUp)
{
    ioSystem->setValveIndex(goUp);
}

const char *MenuValve::getStartTime()
{
    return ioSystem->getValveStartTime();
}
void MenuValve::setStartTime(bool goUp)
{
    if (currentSubIndex == 0)
    {
        ioSystem->setValveStartTimeHour(goUp);
    }
    else
    {
        ioSystem->setValveStartTimeMinute(goUp);
    }
}

const char *MenuValve::getMode()
{
    return ioSystem->getValveMode();
}

void MenuValve::setMode(bool goUp)
{
    ioSystem->setValveMode(goUp);
}

const char *MenuValve::getFrequency()
{
    return ioSystem->getValveFrequency();
}

void MenuValve::setFrequency(bool goUp)
{
    ioSystem->setValveFrequency(goUp);
}

const char *MenuValve::getDuration()
{
    return ioSystem->getValveDuration();
}

void MenuValve::setDuration(bool goUp)
{
    ioSystem->setValveDuration(goUp);
}