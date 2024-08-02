#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "MenuIterableObject.h"
#include "NavigableMenu.h"

class Menu
{
private:
    static Menu *instance;
    NavigableMenu *mainMenu;             // Constant pointer to the main menu item
    MenuIterableObject *currentMenuItem; // Pointer to the current menu item
    uint8_t cursor;
    bool callbackActivated;

    // Saved display state
    bool hasSavedDisplayState;
    uint8_t savedCursor;
    uint8_t savedSelectedIndex;

    // Private constructor to prevent external instantiation
    Menu();

public:
    // Deleted copy constructor and assignment operator to prevent copies
    Menu(const Menu &) = delete;
    Menu &operator=(const Menu &) = delete;

    static Menu &getInstance();

    // Static method to create the instance if it hasn't been created yet
    static void createInstance(NavigableMenu *mainMenuItem);

    void update();
    void setCurrentMenuItem(MenuIterableObject *newCurrentMenu);
    void navigateAndPrintMenu(Command cmd);
    void printMenu(bool clearAll);
    NavigableMenu *getMainMenu() const;

    // Methods for saving and restoring display state
    void saveDisplayState();
};

#endif // MENU_H