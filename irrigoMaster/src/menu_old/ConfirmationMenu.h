#ifndef CONFIRMATIONMENU_H
#define CONFIRMATIONMENU_H

#include <Arduino.h>
#include "Command.h"

class ConfirmationMenu
{
private:
    static ConfirmationMenu *instance; // Singleton instance

    const __FlashStringHelper *labelYes; // Pointer to "YES" string
    const __FlashStringHelper *labelNo;  // Pointer to "NO" string
    bool selectionConfirmed;             // Tracks the current choice (OK or Cancel)

    // Private constructor to prevent direct instantiation
    ConfirmationMenu();

    // Helper function to update the display with current choices
    void updateDisplay();

public:
    // Deleted copy constructor and assignment operator to prevent copies
    ConfirmationMenu(const ConfirmationMenu &) = delete;
    ConfirmationMenu &operator=(const ConfirmationMenu &) = delete;

    // Method to get the singleton instance
    static ConfirmationMenu &getInstance();

    // Sets up and displays the confirmation menu
    void display();

    // Processes user commands and updates the selection
    bool handleCommand(Command cmd);

    // Returns whether the user selected YES
    bool isConfirmed();
};

#endif // CONFIRMATIONMENU_H