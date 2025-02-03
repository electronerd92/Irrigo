#include "menu.h"
#include "Debug.hpp"

Menu::Menu(LCD *lcd, RotaryEncoder *rotaryEncoder)
    : lcd(lcd), rotaryEncoder(rotaryEncoder), cursor(0), currentItem(nullptr)
{
    currentItem = Menu::create();
    print();
}

void Menu::update()
{
    Command cmd = rotaryEncoder->readCommand();

    if (cmd == Command::NONE)
        return;

    else if (cmd == Command::RIGHT && currentItem->exeRightCmd())
    {
        cursor++;
    }
    else if (cmd == Command::LEFT && currentItem->exeLeftCmd())
    {
        cursor--;
    }
    else if (cmd == Command::SELECT && currentItem->exeSelectCmd(currentItem))
    {
        cursor = 0;
    }

    print();
}

void Menu::print()
{
    bool refreshAll = currentItem->getRefresh();

    if (cursor < 0)
    {
        cursor = 0;
        refreshAll = true;
    }
    else if (cursor >= lcd->getLinesNumber())
    {
        cursor = lcd->getLinesNumber() - 1;
        refreshAll = true;
    }

    if (refreshAll)
    {
        lcd->clear();

        for (uint8_t line = 0; line < lcd->getLinesNumber(); line++)
        {
            if (currentItem->printLine(lcd, line, (uint8_t)cursor) == false)
                break;
        }
    }
    else
    {
        lcd->clearColumn(0);
    }

    printCursor();
}

void Menu::printCursor()
{
    lcd->print(">", 0, cursor);
}

MenuList *Menu::create()
{
    MenuList *mainMenu = new MenuList(F("Main"), 6);
    MenuList *settingsMenu = new MenuList(F("Settings"), 4);
    MenuList *infoMenu = new MenuList(F("Info"), 2);
    MenuList *infoMenu2 = new MenuList(F("Info2"), 2);
    MenuList *infoMenu3 = new MenuList(F("Info3"), 2);
    MenuList *infoMenu4 = new MenuList(F("Info4"), 2);
    MenuList *infoMenu5 = new MenuList(F("Info5"), 2);

    mainMenu->addItem(settingsMenu);
    mainMenu->addItem(infoMenu);
    mainMenu->addItem(infoMenu2);
    mainMenu->addItem(infoMenu3);
    mainMenu->addItem(infoMenu4);
    mainMenu->addItem(infoMenu5);

    MenuList *settingsMenu2 = new MenuList(F("Settings2"), 2);
    MenuList *settingsMenu3 = new MenuList(F("Settings3"), 2);
    MenuList *settingsMenu4 = new MenuList(F("Settings4"), 2);
    MenuList *settingsMenu5 = new MenuList(F("Settings5"), 2);
    MenuList *settingsMenu6 = new MenuList(F("Settings6"), 2);

    settingsMenu->addItem(settingsMenu2);
    settingsMenu->addItem(settingsMenu3);
    settingsMenu->addItem(settingsMenu4);
    settingsMenu->addItem(settingsMenu5);
    settingsMenu->addItem(settingsMenu6);

    return mainMenu; // Return the top-level menu
}