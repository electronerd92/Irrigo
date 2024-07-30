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
Menu &Menu::create(NavigableMenu *mainMenuItem)
{
    if (instance == nullptr)
    {
        instance = new Menu();
        mainMenuItem->removeParent();
        instance->mainMenu = mainMenuItem;
        instance->setCurrentMenuItem(mainMenuItem);
    }
    return *instance;
}

// Static method to get the single instance
Menu &Menu::getInstance()
{
    if (instance == nullptr)
    {
        debugLog(F("Error: GetInstance called before Create"), LogLevel::ALERT);
    }
    return *instance;
}

void Menu::setCurrentMenuItem(NavigableMenu *newCurrentMenu)
{
    currentMenuItem = newCurrentMenu;
    cursor = 0;
    currentMenuItem->resetSelectedIndex();
    printMenu(true);
}

void Menu::update()
{
    // the first command is for wakingUp the commandManager
    if (LCDManager::getInstance().getLCDTurnedON() == false)
    {
        if (currentMenuItem != mainMenu || cursor != 0)
            setCurrentMenuItem(mainMenu);

        return;
    }

    navigateAndPrintMenu(CommandManager::getInstance().readCommand());
}

void Menu::navigateAndPrintMenu(Command cmd)
{
    if (cmd == Command::NONE)
        return;

    // all the commands should go to the callback funtion if callbackActivated
    if (cmd == Command::SELECT || callbackActivated)
    {
        callbackActivated = currentMenuItem->select(cmd);
        return;
    }

    bool clearAll = false; // must be false beause of decrementSelectedIndex/incrementSelectedIndex

    if (cmd == Command::UP && currentMenuItem->decrementSelectedIndex())
    {
        clearAll = !LCDManager::getInstance().scrollUp(&cursor);
    }

    else if (cmd == Command::DOWN && currentMenuItem->incrementSelectedIndex())
    {
        clearAll = !LCDManager::getInstance().scrollDown(&cursor);
    }

    printMenu(clearAll);
}

void Menu::printMenu(bool clearAll)
{
    LCDManager &lcdManager = LCDManager::getInstance();

    clearAll ? lcdManager.clear() : lcdManager.clear(0);
    lcdManager.print(F(">"), 0, cursor);

    if (clearAll)
    {
        uint8_t selectedIndex = currentMenuItem->getSelectedIndex();

        for (uint8_t line = 0; line < lcdManager.getLinesNumber(); line++)
        {
            uint8_t index = selectedIndex - cursor + line;
            if (currentMenuItem->printContentAtIndex(index, lcdManager, line) == false)
                break;
        }
    }
}

NavigableMenu *Menu::getMainMenu() const
{
    return mainMenu;
}