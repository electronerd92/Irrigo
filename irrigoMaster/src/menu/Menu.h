#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "MenuItem.h"

class Menu
{
private:
    static Menu *instance;
    const MenuItem *mainMenu;  // Constant pointer to the main menu item
    MenuItem *currentMenuItem; // Pointer to the current menu item
    uint8_t cursor;
    bool callbackActivated;

    // Private constructor to prevent external instantiation
    Menu();

public:
    // Deleted copy constructor and assignment operator to prevent copies
    Menu(const Menu &) = delete;
    Menu &operator=(const Menu &) = delete;

    static Menu &getInstance();

    // Static method to create the instance if it hasn't been created yet
    static Menu &create(MenuItem *mainMenuItem);

    void update();
    void setCurrentMenuItem(MenuItem *newCurrentMenu);
    void navigateAndPrintMenu(MenuIterableObject *menuItem, Command cmd);
};

#endif // MENU_H