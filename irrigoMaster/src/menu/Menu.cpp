#include "Menu.h"
#include "Debug.hpp"
#include "CommandManager.h"
#include "LCDManager.h"

// Initialize the static member
Menu *Menu::instance = nullptr;

// Private constructor
Menu::Menu()
    : mainMenu(nullptr), currentMenuItem(nullptr), cursor(0), callbackActivated(false) {}

// Static method to create the instance if it hasn't been created yet
Menu &Menu::create(MenuItem *mainMenuItem)
{
    if (instance == nullptr)
    {
        instance = new Menu();
        instance->mainMenu = mainMenuItem;
        instance->currentMenuItem = mainMenuItem;
    }
    return *instance;
}

// Static method to get the single instance
Menu &Menu::getInstance()
{
    if (instance == nullptr)
    {
        debugLog(F("Error: GetInstance called before Create"), LogLevel::ALERT);

        // Abort the program
        abort();
    }
    return *instance;
}

void Menu::setCurrentMenuItem(MenuItem *newCurrentMenu)
{
    currentMenuItem = newCurrentMenu;
}

void Menu::update()
{
    // the first command is for wakingUp the commandManager
    if (LCDManager::getInstance().getLCDTurnedON() == false)
        return;

    Command cmd = CommandManager::getInstance().readCommand();

    navigateAndPrintMenu(currentMenuItem, cmd);
}

void Menu::navigateAndPrintMenu(MenuIterableObject *menuItem, Command cmd)
{
    if (cmd == Command::NONE)
        return;

    // all the commands should go to the callback funtion if callbackActivated
    if (cmd == Command::SELECT || callbackActivated)
    {
        callbackActivated = menuItem->select(cmd);
        return;
    }

    LCDManager &lcdManager = LCDManager::getInstance();
    bool refreshAll = false;

    if (cmd == Command::UP && menuItem->decrementSelectedIndex())
    {
        refreshAll = lcdManager.scrollUp(&cursor);
    }

    else if (cmd == Command::DOWN && menuItem->incrementSelectedIndex())
    {
        refreshAll = lcdManager.scrollDown(&cursor);
    }

    if (refreshAll)
        lcdManager.clear();

    uint8_t selectedIndex = menuItem->getSelectedIndex();

    for (uint8_t line = 0; line < lcdManager.getLinesNumber(); line++)
    {
        uint8_t index = selectedIndex - cursor + line;
        if (menuItem->printContentAtIndex(index, lcdManager, line) == false)
            break;
    }
}