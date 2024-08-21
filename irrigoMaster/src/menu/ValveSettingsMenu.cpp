#include "ValveSettingsMenu.h"
#include "Menu.h"
#include "Debug.hpp"
#include "LCDManager.h"

// Initialize the singleton instance pointer to nullptr
ValveSettingsMenu *ValveSettingsMenu::instance = nullptr;
// Initialize static state variables
uint8_t ValveSettingsMenu::initialActionPerformed = 0;

// Private constructor
ValveSettingsMenu::ValveSettingsMenu(MenuIterableObject *parent)
    : parent(parent), source(nullptr), tmpSource(0), selectedIndex(0)
{
    goBackMenu = new CallableMenu(F("Go Back"), goBack);
    validateSettingsMenu = new CallableMenu(F("Validate"), validateSettings);
    changeModeMenu = new CallableMenu(F("Mode"), changeMode);
    setStartTimeMenu = new CallableMenu(F("Start"), setStartTime);
    setPeriodMenu = new CallableMenu(F("Period[min]"), setPeriod);
    setFrequencyMenu = new CallableMenu(F("Freq[h]"), setFrequency);
    setSoilMoistureLevelMenu = new CallableMenu(F("Soil Moisture Level"), setSoilMoistureLevel);
}

// Static method to create the singleton instance
void ValveSettingsMenu::createInstance(MenuIterableObject *parent)
{
    if (instance == nullptr)
    {
        instance = new ValveSettingsMenu(parent);
    }
}

// Static method to get the singleton instance
ValveSettingsMenu &ValveSettingsMenu::getInstance()
{
    if (instance == nullptr)
    {
        debugLog(F("Error: GetInstance called before Create"), LogLevel::ALERT);
    }
    return *instance;
}

// Set the source
void ValveSettingsMenu::setSource(IrrigationValve *src)
{
    source = src;
    tmpSource = *src;  // Copy the source for modifications
    selectedIndex = 0; // Reset the selected index
}

// Getter for tmpSource
IrrigationValve &ValveSettingsMenu::getTmpSource()
{
    return instance->tmpSource;
}

// Method to validate and apply changes
void ValveSettingsMenu::validateTmpSource()
{
    *source = tmpSource; // Replace the original source with the modified copy
}

const CallableMenu *ValveSettingsMenu::getMenuAtIndex(uint8_t index) const
{
    ValveMode valveMode = tmpSource.getMode();
    switch (valveMode)
    {
    case ValveMode::OFF:
        switch (index)
        {
        case 0:
            return goBackMenu;
        case 1:
            return changeModeMenu;
        case 2:
            return validateSettingsMenu;
        }
        break;

    case ValveMode::CLASSIC:
        switch (index)
        {
        case 0:
            return goBackMenu;
        case 1:
            return changeModeMenu;
        case 2:
            return setStartTimeMenu;
        case 3:
            return setPeriodMenu;
        case 4:
            return setFrequencyMenu;
        case 5:
            return validateSettingsMenu;
        }
        break;

    case ValveMode::SMART:
        switch (index)
        {
        case 0:
            return goBackMenu;
        case 1:
            return changeModeMenu;
        case 2:
            return setStartTimeMenu;
        case 3:
            return setSoilMoistureLevelMenu;
        case 4:
            return setFrequencyMenu;
        case 5:
            return validateSettingsMenu;
        }
        break;
    default:
        break;
    }
    return nullptr;
}

const uint8_t ValveSettingsMenu::getMaxCount() const
{
    ValveMode valveMode = tmpSource.getMode();

    if (valveMode == ValveMode::OFF)
        return 3;
    if (valveMode == ValveMode::CLASSIC || valveMode == ValveMode::SMART)
        return 6;
    return 0;
}

const bool ValveSettingsMenu::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    if (index < getMaxCount())
    {
        lcdManager.print(getMenuAtIndex(index)->getName(), 1, row);

        if (getMenuAtIndex(index) == changeModeMenu)
            lcdManager.printRightToLeft(valveModeToString(tmpSource.getMode()), valveModeStringLength(tmpSource.getMode()), 0, row);

        else if (getMenuAtIndex(index) == setStartTimeMenu)
            lcdManager.printRightToLeftFormatted(0, row, "%02u:%02u", tmpSource.getStartTime().hour, tmpSource.getStartTime().minute);

        else if (getMenuAtIndex(index) == setPeriodMenu)
            lcdManager.printRightToLeftFormatted(0, row, "%u", tmpSource.getPeriod());

        else if (getMenuAtIndex(index) == setFrequencyMenu)
            lcdManager.printRightToLeftFormatted(0, row, "%u", tmpSource.getFrequency());

        return true;
    }

    return false;
}

uint8_t ValveSettingsMenu::getSelectedIndex() const
{
    return selectedIndex;
}

void ValveSettingsMenu::setSelectedIndex(uint8_t index)
{
    selectedIndex = index;
}

bool ValveSettingsMenu::incrementSelectedIndex()
{
    if (selectedIndex < getMaxCount() - 1)
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
    return getMenuAtIndex(selectedIndex)->selectEffect(cmd);
}

MenuIterableObject *ValveSettingsMenu::getParent() const
{
    return parent;
}

// Define the callback functions
bool ValveSettingsMenu::goBack(Command cmd)
{
    Menu::getInstance().setCurrentMenuItem(ValveSettingsMenu::getInstance().getParent(), true);
    return false;
}

bool ValveSettingsMenu::validateSettings(Command cmd)
{
    ValveSettingsMenu::getInstance().validateTmpSource();
    ValveSettingsMenu::goBack(cmd);
    return false;
}

bool ValveSettingsMenu::changeMode(Command cmd)
{
    IrrigationValve &tmpSource = ValveSettingsMenu::getInstance().getTmpSource();

    LCDManager::getInstance().stopBlinking();

    // Check if initial actions have been performed
    if (initialActionPerformed)
    {
        // If the command is SELECT, skip further processing
        if (cmd == Command::SELECT)
        {
            initialActionPerformed = 0;
            return false;
        }

        // Get the current mode
        ValveMode currentMode = tmpSource.getMode();

        // Calculate the next mode based on the command
        ValveMode nextMode;
        if (cmd == Command::UP)
        {
            nextMode = static_cast<ValveMode>((static_cast<uint8_t>(currentMode) + 2) % static_cast<uint8_t>(ValveMode::COUNT));
        }
        else if (cmd == Command::DOWN)
        {
            nextMode = static_cast<ValveMode>((static_cast<uint8_t>(currentMode) + 1) % static_cast<uint8_t>(ValveMode::COUNT)); // (currentMode - 1 + 3) % 3
        }

        // Set the next mode
        tmpSource.setMode(nextMode);
    }

    else
    {
        // Perform initial actions
        initialActionPerformed = 1;
    }

    Menu::getInstance().startBlinking(valveModeToString(tmpSource.getMode()), 0, true);
    return true;
}

bool ValveSettingsMenu::setStartTime(Command cmd)
{
    IrrigationValve &tmpSource = ValveSettingsMenu::getInstance().getTmpSource();

    LCDManager::getInstance().stopBlinking();

    if (initialActionPerformed == 1)
    {
        // If the command is SELECT, skip further processing
        if (cmd == Command::SELECT)
        {
            initialActionPerformed = 2;
        }
        else if (cmd == Command::UP)
        {
            tmpSource.decreaseStartTimeHour();
        }
        else if (cmd == Command::DOWN)
        {
            tmpSource.increaseStartTimeHour();
        }
    }

    else if (initialActionPerformed == 2)
    {
        if (cmd == Command::SELECT)
        {
            initialActionPerformed = 0;
            return false;
        }
        if (cmd == Command::UP)
        {
            tmpSource.decreaseStartTimeMinute();
        }
        else if (cmd == Command::DOWN)
        {
            tmpSource.increaseStartTimeMinute();
        }
    }
    else
    {
        // Perform initial actions
        initialActionPerformed = 1;
    }

    Menu::getInstance().startBlinking(tmpSource.getStartTime(), 0, true);

    return true;
}

bool ValveSettingsMenu::setPeriod(Command cmd)
{
    IrrigationValve &tmpSource = ValveSettingsMenu::getInstance().getTmpSource();

    LCDManager::getInstance().stopBlinking();

    // Check if initial actions have been performed
    if (initialActionPerformed)
    {
        // If the command is SELECT, skip further processing
        if (cmd == Command::SELECT)
        {
            initialActionPerformed = 0;
            return false;
        }
        if (cmd == Command::UP)
        {
            tmpSource.decreasePeriod();
        }
        else if (cmd == Command::DOWN)
        {
            tmpSource.increasePeriod();
        }
    }
    else
    {
        // Perform initial actions
        initialActionPerformed = 1;
    }

    Menu::getInstance().startBlinking(tmpSource.getPeriod(), 0, true);

    return true;
}

bool ValveSettingsMenu::setFrequency(Command cmd)
{
    IrrigationValve &tmpSource = ValveSettingsMenu::getInstance().getTmpSource();

    LCDManager::getInstance().stopBlinking();

    // Check if initial actions have been performed
    if (initialActionPerformed)
    {
        // If the command is SELECT, skip further processing
        if (cmd == Command::SELECT)
        {
            initialActionPerformed = 0;
            return false;
        }
        if (cmd == Command::UP)
        {
            tmpSource.decreaseFrequency();
        }
        else if (cmd == Command::DOWN)
        {
            tmpSource.increaseFrequency();
        }
    }
    else
    {
        // Perform initial actions
        initialActionPerformed = 1;
    }

    Menu::getInstance().startBlinking(tmpSource.getFrequency(), 0, true);

    return true;
}

bool ValveSettingsMenu::setSoilMoistureLevel(Command cmd)
{
    // Implement the logic to set the soil moisture level
    // Example: prompt user to enter soil moisture level
    return true;
}