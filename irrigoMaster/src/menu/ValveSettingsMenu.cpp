#include "ValveSettingsMenu.h"
#include "Menu.h"

// Initialize the singleton instance pointer to nullptr
ValveSettingsMenu *ValveSettingsMenu::instance = nullptr;
// Initialize static state variables
bool ValveSettingsMenu::initialActionPerformed = false;

// Private constructor
ValveSettingsMenu::ValveSettingsMenu() : parent(nullptr), source(nullptr), tmpSource(), selectedIndex(0)
{
    goBackMenu = new CallableMenu(F("Go Back"), goBack);
    validateSettingsMenu = new CallableMenu(F("Validate"), validateSettings);
    changeModeMenu = new CallableMenu(F("Mode"), changeMode);
    setStartTimeMenu = new CallableMenu(F("Start Time"), setStartTime);
    setDurationMenu = new CallableMenu(F("Duration"), setDuration);
    setFrequencyMenu = new CallableMenu(F("Frequency"), setFrequency);
    setSoilMoistureLevelMenu = new CallableMenu(F("Soil Moisture Level"), setSoilMoistureLevel);
}

// Static method to get the singleton instance
ValveSettingsMenu &ValveSettingsMenu::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ValveSettingsMenu();
    }
    return *instance;
}

// Set the source
void ValveSettingsMenu::setSource(Valve *src)
{
    source = src;
    tmpSource = *src;  // Copy the source for modifications
    selectedIndex = 0; // Reset the selected index
}

// Getter for tmpSource
Valve &ValveSettingsMenu::getTmpSource()
{
    return instance->tmpSource;
}

// Method to validate and apply changes
void ValveSettingsMenu::validateTmpSource()
{
    if (source != nullptr)
    {
        *source = tmpSource; // Replace the original source with the modified copy
    }
}

const CallableMenu *ValveSettingsMenu::getSelectedMenu() const
{
    ValveMode valveMode = tmpSource.getMode();
    switch (valveMode)
    {
    case ValveMode::OFF:
        switch (selectedIndex)
        {
        case 0:
            return goBackMenu;
        case 1:
            return changeModeMenu;
        }
        break;

    case ValveMode::CLASSIC:
        switch (selectedIndex)
        {
        case 0:
            return goBackMenu;
        case 1:
            return changeModeMenu;
        case 2:
            return setStartTimeMenu;
        case 3:
            return setDurationMenu;
        case 4:
            return setFrequencyMenu;
        case 5:
            return validateSettingsMenu;
        }
        break;

    case ValveMode::SMART:
        switch (selectedIndex)
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
    }
    return nullptr;
}

const uint8_t ValveSettingsMenu::getMaxCount() const
{
    ValveMode valveMode = tmpSource.getMode();

    if (valveMode == ValveMode::OFF)
        return 2;
    if (valveMode == ValveMode::CLASSIC || valveMode == ValveMode::SMART)
        return 6;
    return 0;
}

const bool ValveSettingsMenu::printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const
{
    if (index < getMaxCount())
    {
        lcdManager.print(getSelectedMenu()->getName(), 1, row);
        return true;
    }
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
    return getSelectedMenu()->selectEffect(cmd);
}

MenuIterableObject *ValveSettingsMenu::getParent() const
{
    return parent;
}

void ValveSettingsMenu::setParent(MenuIterableObject *p)
{
    parent = p;
}

// Define the callback functions
bool ValveSettingsMenu::goBack(Command cmd)
{
    Menu::getInstance().setCurrentMenuItem(ValveSettingsMenu::getInstance().getParent());
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
    // Check if initial actions have been performed
    if (!initialActionPerformed)
    {
        // Perform initial actions
        initialActionPerformed = true;
        return true;
    }

    // If the command is SELECT, skip further processing
    if (cmd == Command::SELECT)
    {
        initialActionPerformed = false;
        return false;
    }

    ValveSettingsMenu &menu = ValveSettingsMenu::getInstance();
    Valve &tmpSource = menu.getTmpSource();

    // Get the current mode
    ValveMode currentMode = tmpSource.getMode();

    // Calculate the next mode based on the command
    ValveMode nextMode;
    if (cmd == Command::UP)
    {
        nextMode = static_cast<ValveMode>((currentMode + 1) % 3);
    }
    else if (cmd == Command::DOWN)
    {
        nextMode = static_cast<ValveMode>((currentMode + 2) % 3); // (currentMode - 1 + 3) % 3
    }

    // Set the next mode
    tmpSource.setMode(nextMode);

    return true;
}

bool ValveSettingsMenu::setStartTime(Command cmd)
{
    // Implement the logic to set the start time
    // Example: prompt user to enter start time
    return true;
}

bool ValveSettingsMenu::setDuration(Command cmd)
{
    // Implement the logic to set the duration
    // Example: prompt user to enter duration
    return true;
}

bool ValveSettingsMenu::setFrequency(Command cmd)
{
    // Implement the logic to set the frequency
    // Example: prompt user to enter frequency
    return true;
}

bool ValveSettingsMenu::setSoilMoistureLevel(Command cmd)
{
    // Implement the logic to set the soil moisture level
    // Example: prompt user to enter soil moisture level
    return true;
}