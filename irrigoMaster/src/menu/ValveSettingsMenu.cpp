#include "ValveSettingsMenu.h"
#include "Menu.h"

// Initialize the singleton instance pointer to nullptr
ValveSettingsMenu *ValveSettingsMenu::instance = nullptr;

// Private constructor
ValveSettingsMenu::ValveSettingsMenu() : parent(nullptr), source(nullptr), tmpSource(), selectedIndex(0), timeModeCount(3)
{
    timeModeSettings = new const __FlashStringHelper *[timeModeCount];
}

// Static method to get the singleton instance
ValveSettingsMenu &ValveSettingsMenu::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ValveSettingsMenu();
        instance->create();
    }
    return *instance;
}

void ValveSettingsMenu::create()
{
    timeModeSettings[0] = F("Start time");
    timeModeSettings[1] = F("Duration");
    timeModeSettings[2] = F("Frequenty");
}

// Set the source
void ValveSettingsMenu::setSource(Valve *source)
{
    if (source != nullptr)
    {
        // this->source = source;
        // this->tmpSource = *source; // Make a copy of the source object
    }
}

// Method to validate and apply changes
// void ValveSettingsMenu::validateSettings()
// {
//     if (source != nullptr)
//     {
//         *source = tmpSource; // Replace the original source with the modified copy
//     }
// }

bool ValveSettingsMenu::selectEffect(Command cmd) const
{
    return false;
}

const bool ValveSettingsMenu::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    // Print content at the specified index
    // Placeholder logic
    return false;
}

uint8_t ValveSettingsMenu::getSelectedIndex() const
{
    return selectedIndex;
}

void ValveSettingsMenu::resetSelectedIndex()
{
    selectedIndex = 0;
}

bool ValveSettingsMenu::incrementSelectedIndex()
{
    if (selectedIndex < timeModeCount - 1)
    {
        ++selectedIndex;
        return true;
    }
    return false;
}

bool ValveSettingsMenu::decrementSelectedIndex()
{
    if (selectedIndex > 0)
    {
        --selectedIndex;
        return true;
    }
    return false;
}

bool ValveSettingsMenu::select(Command cmd) const
{
    if (selectedIndex == 0)
    {
        Menu::getInstance().setCurrentMenuItem(parent);
        return false;
    }

    return true;
    // timeModeSettings[selectedIndex]->selectEffect(cmd);
}

MenuIterableObject *ValveSettingsMenu::getParent() const
{
    return nullptr;
}

void ValveSettingsMenu::setParent(MenuIterableObject *parent)
{
}