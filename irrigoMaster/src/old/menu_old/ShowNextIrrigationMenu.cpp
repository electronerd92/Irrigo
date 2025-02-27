#include "ShowNextIrrigationMenu.h"
#include "Menu.h"
#include "../System.h"
#include "../irrigationSystem/IrrigationSystem.h"
#include "Debug.hpp"

// Initialize the singleton instance pointer to nullptr
ShowNextIrrigationMenu *ShowNextIrrigationMenu::instance = nullptr;

ShowNextIrrigationMenu::ShowNextIrrigationMenu(MenuIterableObject *parent)
    : parent(parent)
{
}

// Static method to create the singleton instance
void ShowNextIrrigationMenu::createInstance(MenuIterableObject *parent)
{
    if (instance == nullptr)
    {
        instance = new ShowNextIrrigationMenu(parent);
    }
}

// Static method to get the singleton instance
ShowNextIrrigationMenu &ShowNextIrrigationMenu::getInstance()
{
    if (instance == nullptr)
    {
        debugLog(F("Error: GetInstance called before Create"), LogLevel::ALERT);
    }
    return *instance;
}

const bool ShowNextIrrigationMenu::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    if (index < IrrigationSystem::getInstance().getValvesNumber())
    {
        IrrigationValve *valve = IrrigationSystem::getInstance().getValve(index);
        DateTime nextIrrigationTime = valve->getNextIrrigationTime();
        LCDManager::getInstance().printFormatted(1, row, "[V%u]", valve->getID());
        ValveMode mode = valve->getMode();
        mode == ValveMode::OFF
            ? LCDManager::getInstance().printRightToLeft(valveModeToString(mode), valveModeStringLength(mode), 0, row)
            : LCDManager::getInstance().printRightToLeftFormatted(0, row, "%02u-%02u %02u:%02u", nextIrrigationTime.day(), nextIrrigationTime.month(), nextIrrigationTime.hour(), nextIrrigationTime.minute());
        return true;
    }
    return false;
}

uint8_t ShowNextIrrigationMenu::getSelectedIndex() const
{
    return selectedIndex;
}

void ShowNextIrrigationMenu::setSelectedIndex(uint8_t index)
{
    selectedIndex = index;
}

bool ShowNextIrrigationMenu::incrementSelectedIndex()
{
    if (selectedIndex < IrrigationSystem::getInstance().getValvesNumber() - 1)
    {
        ++selectedIndex;
        return true;
    }
    return false;
}

bool ShowNextIrrigationMenu::decrementSelectedIndex()
{
    if (selectedIndex > 0)
    {
        --selectedIndex;
        return true;
    }
    return false;
}

bool ShowNextIrrigationMenu::select(Command cmd) const
{
    Menu::getInstance().setCurrentMenuItem(parent, true);
    return false;
}