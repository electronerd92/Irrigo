#include "ConfirmationMenu.h"
#include "LCDManager.h"

// Initialize the static member
ConfirmationMenu *ConfirmationMenu::instance = nullptr;

// Default constructor to initialize YES and NO labels
ConfirmationMenu::ConfirmationMenu()
    : labelYes(F("[YES]")), labelNo(F("[NO]")), selectionConfirmed(false) // Default to NO
{
}

// Method to get the singleton instance
ConfirmationMenu &ConfirmationMenu::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ConfirmationMenu();
    }
    return *instance;
}

// Sets up and displays the confirmation menu
void ConfirmationMenu::display()
{
    LCDManager::getInstance().clear();
    LCDManager::getInstance().print(F("Confirm choice?"));
    LCDManager::getInstance().print(labelNo, 0, 1);
    LCDManager::getInstance().print(labelYes, 5, 1);
    selectionConfirmed = false;
    updateDisplay();
}

// Helper function to update the display with current choices
void ConfirmationMenu::updateDisplay()
{
    // Display the choices with blinking
    if (selectionConfirmed)
    {
        LCDManager::getInstance().startBlinking(labelYes, 5, 1);
    }
    else
    {
        LCDManager::getInstance().startBlinking(labelNo, 0, 1);
    }
}

// Processes user commands and updates the selection
bool ConfirmationMenu::handleCommand(Command cmd)
{
    LCDManager::getInstance().stopBlinking(false);

    if (cmd == Command::UP || cmd == Command::DOWN)
    {
        selectionConfirmed = !selectionConfirmed; // Toggle selection
        updateDisplay();                          // Update the display with current selection
    }
    else if (cmd == Command::SELECT)
    {
        return true; // Indicate that the selection has been made
    }

    return false; // Continue to show the confirmation menu
}

// Returns whether the user selected YES
bool ConfirmationMenu::isConfirmed()
{
    return selectionConfirmed;
}