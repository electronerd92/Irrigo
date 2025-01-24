#include "menu.h"
#include "Debug.hpp"

Menu::Menu(LCD *lcd, RotaryEncoder *rotaryEncoder)
    : lcd(lcd), rotaryEncoder(rotaryEncoder), cursor(0), currentItem(nullptr)
{
    currentItem = Menu::create();
    print(true);
}

void Menu::update()
{
    Command cmd = rotaryEncoder->readCommand();

    if (cmd == Command::NONE)
        return;

    else if (cmd == Command::DOWN && currentItem->exeUpCmd())
    {
        cursor++;
    }
    else if (cmd == Command::UP && currentItem->exeDownCmd())
    {
        cursor--;
    }
    else if (cmd == Command::SELECT)
    {
        currentItem->exeSelectCmd(currentItem);
    }

    print();
}

void Menu::print(bool forceRefresh)
{
    bool refreshAll = forceRefresh;

    if (cursor < 0)
    {
        cursor = 0;
        refreshAll = true;
    }
    else if (cursor >= lcd->getLinesNumber())
    {
        cursor = (int8_t)(lcd->getLinesNumber()) - 1;
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

MenuIterableItem *Menu::create()
{
    MenuIterableItem *mainMenu = new MenuIterableItem(F("Main"), 6);
    MenuIterableItem *settingsMenu = new MenuIterableItem(F("Settings"), 2);
    MenuIterableItem *infoMenu = new MenuIterableItem(F("Info"), 2);
    MenuIterableItem *infoMenu2 = new MenuIterableItem(F("Info2"), 2);
    MenuIterableItem *infoMenu3 = new MenuIterableItem(F("Info3"), 2);
    MenuIterableItem *infoMenu4 = new MenuIterableItem(F("Info4"), 2);
    MenuIterableItem *infoMenu5 = new MenuIterableItem(F("Info5"), 2);

    mainMenu->addItem(settingsMenu);
    mainMenu->addItem(infoMenu);
    mainMenu->addItem(infoMenu2);
    mainMenu->addItem(infoMenu3);
    mainMenu->addItem(infoMenu4);
    mainMenu->addItem(infoMenu5);

    return mainMenu; // Return the top-level menu
}