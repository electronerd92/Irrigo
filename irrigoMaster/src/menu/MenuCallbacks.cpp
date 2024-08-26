#include "MenuCallbacks.h"
#include "Menu.h"
#include "ValveSettingsMenu.h"
#include "../irrigationSystem/IrrigationSystem.h"
#include "LCDManager.h"
#include "../System.h"

uint8_t MenuCallbacks::actionIndex = 0;

// #region Valve settings
void MenuCallbacks::showValveSettingsMenu()
{
    Menu::getInstance().saveDisplayState();
    Menu::getInstance().setCurrentMenuItem(&ValveSettingsMenu::getInstance());
}

bool MenuCallbacks::selectValve1(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(0));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve2(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(1));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve3(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(2));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve4(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(3));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve5(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(4));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve6(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(5));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve7(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(6));
    showValveSettingsMenu();
    return false;
}

bool MenuCallbacks::selectValve8(Command cmd)
{
    ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(7));
    showValveSettingsMenu();
    return false;
}

// #endregion Valve settings

bool MenuCallbacks::printInfo(Command cmd)
{
    static bool firstTime = true;

    if (firstTime)
    {
        firstTime = false;
        LCDManager::getInstance().clear();
        LCDManager::getInstance().print(F("Info..Press enter"));
        return true;
    }

    if (cmd == Command::SELECT && !firstTime)
    {
        firstTime = true;
        return false; // exit
    }
    return true;
}

bool MenuCallbacks::resetToFactorySettings(Command cmd)
{
    System::getInstance().resetToFactorySettings();
    return false;
}

bool MenuCallbacks::setDate(Command cmd)
{
    LCDManager::getInstance().stopBlinking(false);

    if (actionIndex == 1)
    {
        if (cmd == Command::SELECT)
        {
            actionIndex = 2;
        }
        else if (cmd == Command::UP)
        {
            System::getInstance().decreaseDay();
        }
        else if (cmd == Command::DOWN)
        {
            System::getInstance().increaseDay();
        }
    }

    else if (actionIndex == 2)
    {
        if (cmd == Command::SELECT)
        {
            actionIndex = 3;
        }
        if (cmd == Command::UP)
        {
            System::getInstance().decreaseMonth();
        }
        else if (cmd == Command::DOWN)
        {
            System::getInstance().increaseMonth();
        }
    }

    else if (actionIndex == 3)
    {
        if (cmd == Command::SELECT)
        {
            actionIndex = 0;
            return false;
        }
        if (cmd == Command::UP)
        {
            System::getInstance().decreaseYear();
        }
        else if (cmd == Command::DOWN)
        {
            System::getInstance().increaseYear();
        }
    }

    else
    {
        // Perform initial actions
        actionIndex = 1;
        DateTime dateTime = System::getInstance().getCurrentDateTime();
        LCDManager::getInstance().clear();
        LCDManager::getInstance().print(F("Set Date: "));
        LCDManager::getInstance().printFormatted(0, 1, "%02u/%02u/%04d", dateTime.day(), dateTime.month(), dateTime.year());
    }

    DateTime dateTime = System::getInstance().getCurrentDateTime(); // date updated after modifications

    if (actionIndex == 1)
        LCDManager::getInstance().startBlinking(dateTime.day(), 0, 1, false, "%02u");
    else if (actionIndex == 2)
        LCDManager::getInstance().startBlinking(dateTime.month(), 3, 1, false, "%02u");
    else
        LCDManager::getInstance().startBlinking(dateTime.year(), 6, 1, false, "%04d");

    return true;
}

bool MenuCallbacks::setTime(Command cmd)
{
    LCDManager::getInstance().stopBlinking(false);

    if (actionIndex == 1)
    {
        if (cmd == Command::SELECT)
        {
            actionIndex = 2;
        }
        else if (cmd == Command::UP)
        {
            System::getInstance().decreaseHour();
        }
        else if (cmd == Command::DOWN)
        {
            System::getInstance().increaseHour();
        }
    }

    else if (actionIndex == 2)
    {
        if (cmd == Command::SELECT)
        {
            actionIndex = 0;
            return false;
        }
        if (cmd == Command::UP)
        {
            System::getInstance().decreaseMinute();
        }
        else if (cmd == Command::DOWN)
        {
            System::getInstance().increaseMinute();
        }
    }

    else
    {
        // Perform initial actions
        actionIndex = 1;
        DateTime dateTime = System::getInstance().getCurrentDateTime();
        LCDManager::getInstance().clear();
        LCDManager::getInstance().print(F("Set Time: "));
        LCDManager::getInstance().printFormatted(0, 1, "%02u:%02u", dateTime.hour(), dateTime.minute());
    }

    DateTime dateTime = System::getInstance().getCurrentDateTime(); // date updated after modifications

    if (actionIndex == 1)
        LCDManager::getInstance().startBlinking(dateTime.hour(), 0, 1, false, "%02u");
    else
        LCDManager::getInstance().startBlinking(dateTime.minute(), 3, 1, false, "%02u");

    return true;
}